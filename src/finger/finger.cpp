/***************************************************
 * @ Function: Finger.cpp
 * @ Author: Ethan
 * @ Date: 2024-1-15
 * @ Description: finger enroll, finger identify
 * @ Version: V1.0
 * *************************************************/

#include "Finger.h"

void finger_init();
int8_t finger_enroll();
int8_t finger_delete(uint16_t id);
int8_t finger_empty();
int8_t finger_identify();
uint8_t finger_inquiry();
void finger_sleep();

void test_finger();

/* soft uart port */ 
#define FPM_RX 25
#define FPM_TX 26

YFROBOTFPM383 fpm(FPM_RX, FPM_TX);
int flag_enroll = 0;

void finger_init(){
  while (fpm.getChipSN() == "") {
    Serial.println("waiting for finger init......");
    delay(200);  //等待指纹识别模块初始化完成
  }
  Serial.println(fpm.getChipSN());
  finger_sleep();
  delay(200);
  /* interrupt to touch out */ 
  pinMode(PIN_FINGER_TOUCH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_FINGER_TOUCH), interrupt_finger_handler, RISING);
}

void IRAM_ATTR interrupt_finger_handler(){
  /* close interrupt */ 
  detachInterrupt(digitalPinToInterrupt(PIN_FINGER_TOUCH));
  globalData.flag_finger = 1;
  Serial.println("finger interrupt!");
}

/* finger enroll */ 
int8_t finger_enroll(){
  if(globalData.finger_count >= FINGERPRINT_TEMPLATE_MAX){
    Serial.println("the finger buffer is full, please remove!");
    return -1;
  }
  
  uint16_t cur_id = 0;
  for(int i = 0; i < FINGERPRINT_TEMPLATE_MAX; i++){
    if(globalData.finger_id_buffer[i] == 0){
      cur_id = i;
      /* start to enroll */ 
      Serial.println("Please pull your finger to the sensor 4 times in 30 seconds.");
      Serial.printf("The cur count is:%d\n", globalData.finger_count);
      Serial.printf("The next enroll id is:%d\n", cur_id);
      flag_enroll = fpm.enroll(cur_id, 4);
      if (flag_enroll == 0x00) {
        Serial.println("finger enroll success!");
        globalData.finger_count += 1;
        globalData.finger_id_buffer[i] = 1;
        return 1;
      }else{
        Serial.println("finger already exist!");
        return -1;
      }
    }
  }
  return -2;
}

/* finger delete function */ 
int8_t finger_delete(uint16_t id){
  /* delete the first finger */ 
  if(id == 0xff){  
    for(int i = 0; i < FINGERPRINT_TEMPLATE_MAX; i++){
      if(globalData.finger_id_buffer[i] == 1){
        return finger_delete(i);
      }
    }
  }

  uint8_t flag_delete = fpm.deleteID(id);
  if(flag_delete != 0x00){
    Serial.printf("Fail to delete finger %d!", id);
    return -1;
  }else{
    Serial.printf("Success to delete finger %d!", id);
    globalData.finger_count -= 1;
    globalData.finger_id_buffer[id] = 0;
    return 1;
  }
}

/* finger empty function */ 
int8_t finger_empty(){
  uint8_t flag_empty = fpm.empty();
  if(flag_empty == 0x00){
    Serial.println("Success to empty finger buffer!");
    globalData.finger_count = 0;
    memset(globalData.finger_id_buffer, 0, FINGERPRINT_TEMPLATE_MAX * sizeof(int));
    return 1;
  }else{
    Serial.println("Fail to empty finger buffer!");
    return -1;  
  }
}

/* finger identify function */ 
int8_t finger_identify(){
  /*验证指纹工作流程：
        1、无手指时，闪烁红绿色（黄色）灯一次
        2、搜索到未认证手指指纹，闪烁红色灯两次
        3、搜索未认证手指指纹，解析并校验数据，正常则返回指纹ID，并闪烁绿灯两次
  */
  uint8_t id = fpm.identify(false);  //验证指纹并获取指纹ID，参数true 在无手指状态是否有LED灯提示，您可以false关掉指示灯
  if(id < FINGERPRINT_TEMPLATE_MAX){
    Serial.printf("finger pass!");
    return 1;
  }
  if(id == 0xFF){
    Serial.printf("finger no pass!");
    return -1;
  }  
  return -1;
}

/* finger inquiry function */
uint8_t finger_inquiry(){
  uint8_t finger_enroll_num = fpm.inquiry();
  if(finger_enroll_num != globalData.finger_count){
    Serial.printf("[err]finger enroll nums not match!");
  }else{
    Serial.printf("finger enroll nums is:%d", finger_enroll_num);
  }
  return finger_enroll_num;
}

/* finger sleep function */
void finger_sleep(){
  fpm.sleep();
  Serial.println("finger sleep!");
}

void test_finger(){
  while (Serial.available() > 0) { // 检查是否有数据可读
    int input = Serial.parseInt(); // 读取整数数据
      switch (input) {
        case 1:
          finger_enroll();
          break;
        case 2:
          finger_delete(0xff);
          break;
        case 3:
          finger_empty();
          break;
        case 4:
          finger_identify();
          break;
        case 5:
          finger_inquiry();
          break;
        default:
          Serial.println("Uart Input Err!");
    }
  }
}
