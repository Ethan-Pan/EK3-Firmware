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
void finger_power_on();
void finger_power_off();
void test_finger();

/* soft uart port */ 
#define FPM_RX 25
#define FPM_TX 26
#define FPM_EN 13

YFROBOTFPM383 fpm(FPM_RX, FPM_TX);
int flag_enroll = 0;

void finger_init(){
  pinMode(FPM_EN, OUTPUT);
  finger_power_on();
  while (fpm.getChipSN() == "") {
    Serial.println("waiting for finger init......");
    delay(200);  //等待指纹识别模块初始化完成
  }
  Serial.println(fpm.getChipSN());
  finger_sleep();
  delay(200);
  finger_power_off();
  /* interrupt to touch out */ 
  pinMode(PIN_FINGER_TOUCH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_FINGER_TOUCH), interrupt_finger_handler, RISING);
}

void IRAM_ATTR interrupt_finger_handler(){
  /* close interrupt */ 
  detachInterrupt(digitalPinToInterrupt(PIN_FINGER_TOUCH));
  globalData.flag_finger = 1;
}


/* finger enroll */ 
int8_t finger_enroll(int id){
    flag_enroll = fpm.enroll(id, 4);
    if (flag_enroll == 0x00) {
      return 1;
    }
    else{
      return 0;
    }
}

/* finger delete function */ 
int8_t finger_delete(uint16_t id){
  /* delete the first finger */ 
  uint8_t flag_delete = fpm.deleteID(id);
  /* failed to delete finger */
  if(flag_delete != 0x00){
    return 0;
  }
  /* succcess to delete finger */
  else{
    return 1;
  }
}

/* finger empty function */ 
int8_t finger_empty(){
  uint8_t flag_empty = fpm.empty();
  if(flag_empty == 0x00){
    Serial.println("Success to empty finger buffer!");
    globalData.finger_count = 0;
    return 1;
  }else{
    Serial.println("Fail to empty finger buffer!");
    return 0;  
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
  // Serial.println("finger sleep!");
}


/* open finger power */
void finger_power_on(){
  digitalWrite(FPM_EN, HIGH);
  delay(180);
}

/*close finger power */
void finger_power_off(){
  digitalWrite(FPM_EN, LOW);
  delay(180);
}


void test_finger(){
  while (Serial.available() > 0) { // 检查是否有数据可读
    int input = Serial.parseInt(); // 读取整数数据
      switch (input) {
        case 1:
          finger_enroll(1);
          break;
        case 2:
          finger_delete(1);
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
