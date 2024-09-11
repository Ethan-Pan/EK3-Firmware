/***************************************************
 * @ Function: Finger.cpp
 * @ Author: Ethan
 * @ Date: 2024-1-15
 * @ Description: finger enroll, finger identify
 * @ Version: V1.0
 * *************************************************/

#include "Finger.h"
#include "esp_task_wdt.h"

#define FINGER_TOUCH_PIN 14

static byte autoEnrollCommand[17] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x08, 0x31, 0x00, 0x01, 0x06, 0x00, 0x2E, 0x00, 0x6F}; // 自动注册命令, 手指按住不放就可以完成注册
static byte autoIdentifyCommand[17] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x08, 0x32, 0x02, 0x00, 0x01, 0x00, 0x06, 0x00, 0x44}; // 自动验证命令
static byte ledSuccessCommand[16] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x3C, 0x02, 0x02, 0x02, 0x01, 0x00, 0x4B}; // 验证成功等效：闪烁1次绿灯
static byte ledFailedCommand[16] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x3C, 0x02, 0x04, 0x04, 0x01, 0x00, 0x4F}; // 验证失败灯效：闪烁1次红灯
static byte ledIdentifyCommand[16] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x3C, 0x02, 0x01, 0x01, 0x01, 0x00, 0x49}; // 每验证一次灯效：闪烁1次蓝灯
static byte sleepCommand[12] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x33, 0x00, 0x37};   // 休眠模式，开启休眠之后才能使用touchID
static uint8_t gReceiveBuffer[128];   //串口接收数据的临时缓冲数组

static void ledSuccess(void);
static void ledFailed(void);
static void ledIdentify(void);
static void receiveData(uint16_t timeOut);
static void sendCommd(byte* buffer, int len);
static void cleanUartBuffer(void);
static void delay_ms(long int ms);
void IRAM_ATTR pin_ISR(void);

int gFingerISRFlag = 0;
int gCount = 0;

// 子任务：等待手指按下，自动识别然后休眠
void xTaskFinger(void *pt){
  while (1)
  {
    if(gFingerISRFlag == 1){
        vTaskDelay(100);
        if(digitalRead(FINGER_TOUCH_PIN) == HIGH){
            gCount += 1;
            if(gCount==2){
                gCount = 0;
                Serial.println("xTaskFinger");
                ledSuccess();
                openSleep(); 
            }
            gFingerISRFlag = 0;
            pinMode(FINGER_TOUCH_PIN, OUTPUT);
            digitalWrite(FINGER_TOUCH_PIN, LOW);
            attachInterrupt(digitalPinToInterrupt(FINGER_TOUCH_PIN), pin_ISR, RISING);
            pinMode(FINGER_TOUCH_PIN, INPUT);
        }
    }
    vTaskDelay(10);
  }
}

// 初始化
void fingerInit(int touchPin){
    Serial.begin(115200);
    Serial2.begin(57600, SERIAL_8N1, 16, 17);
    pinMode(touchPin, INPUT_PULLDOWN);
    delay_ms(200);  // finger模块启动延时
    openSleep();  // 开机自启休眠模式
    delay_ms(200); 
    attachInterrupt(digitalPinToInterrupt(touchPin), pin_ISR, RISING);
}

// 自动注册函数
void autoEnroll(){
    sendCommd(autoEnrollCommand, sizeof(autoEnrollCommand));
    receiveData(10000);
    if(gReceiveBuffer[6] == 0x07 && gReceiveBuffer[9] == 0x00){
        ledSuccess();
    }
}

// 自动验证
void autoIdentify(){
    sendCommd(autoIdentifyCommand, sizeof(autoIdentifyCommand));
    receiveData(5000);
    if(gReceiveBuffer[6] == 0x07 && gReceiveBuffer[9] == 0x00){ // 匹配到指纹
        ledSuccess();
    }
    else if(gReceiveBuffer[6] == 0x07 && gReceiveBuffer[9] == 0x09){ // 未匹配到指纹
        ledFailed();
    }
}

static void sendCommd(byte* buffer, int len){
    memset(gReceiveBuffer, 0, sizeof(gReceiveBuffer));
    Serial2.write(buffer, len);
    Serial2.flush();
}

static void receiveData(uint16_t timeOut){
    uint8_t i = 0;
    while(Serial2.available()==0 && (--timeOut)){
        delay(1);
    }
    while(Serial2.available() > 0){
        delay(2);
        gReceiveBuffer[i++] = Serial2.read();
        Serial.print(gReceiveBuffer[i-1], HEX);
        Serial.print(" ");
    }
}

// 开启休眠模式
void openSleep(){
    sendCommd(sleepCommand, sizeof(sleepCommand));
    receiveData(2000);
}

// 闪烁两次绿灯
static void ledSuccess(){
    sendCommd(ledSuccessCommand, sizeof(ledSuccessCommand));
    receiveData(2000);
}

// 闪烁两次红灯
static void ledFailed(){
    sendCommd(ledFailedCommand, sizeof(ledFailedCommand));
    receiveData(2000);
}

// 闪烁一次蓝灯
static void ledIdentify(){
    sendCommd(ledIdentifyCommand, sizeof(ledIdentifyCommand));
    receiveData(2000);
}

static void delay_ms(long int ms){
  for(int i=0;i<ms;i++)
  {
    delayMicroseconds(1000);
  }
}

void IRAM_ATTR pin_ISR(){
    detachInterrupt(digitalPinToInterrupt(FINGER_TOUCH_PIN));
    Serial.println("INTERRUPT");
    // delay_ms(10);
    gFingerISRFlag += 1;
}

// void setup(){
//     fingerInit(FINGER_TOUCH_PIN);
//     esp_task_wdt_init(10, true); // 参数：超时时间（秒），是否触发panic处理
//     // 将当前任务（通常是loop任务）添加到看门狗监控列表
//     esp_task_wdt_add(NULL); // 参数：NULL表示当前任务
//     xTaskCreate(xTaskFinger, "your name", 1024*4, NULL, 1, NULL);
// }

// void loop(){
//     esp_task_wdt_reset();
//     vTaskDelay(10);
// }

/* arduino 库版本 */

#include <Adafruit_Fingerprint.h>


int getFingerprintIDez();
void registerFingerprint();
int findEmptyID();
// 创建一个串口对象
// SoftwareSerial mySerial(2, 3); // RX, TX
#define mySerial Serial2
// 使用串口对象初始化指纹传感器
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// void setup() {
//   Serial.begin(115200);
//   while (!Serial);  // 对于一些需要串口连接的Arduino板，等待串口连接
//   Serial.println("指纹传感器测试");

//   finger.begin(57600);  // 指纹传感器的默认波特率为57600
//   if (finger.verifyPassword()) {
//     Serial.println("指纹传感器已找到");
//   } else {
//     Serial.println("指纹传感器未找到，请检查连接");
//     while (1) { delay(1); }
//   }
//   if (finger.emptyDatabase() == FINGERPRINT_OK) {
//     Serial.println("成功清除所有指纹！");
//   } else {
//     Serial.println("清除指纹失败！");
//   }
// }

// void loop() {
//   int result = getFingerprintIDez();
//   delay(50);  // 稍作延迟，避免过快重复读取
// }

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("图像采集成功");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("等待手指...");
      return -1;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("通信错误");
      return -1;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("图像采集失败");
      return -1;
    default:
      Serial.println("未知错误");
      return -1;
  }
  
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) {
    Serial.println("图像转换失败");
    return -1;
  }
  
  p = finger.fingerSearch(1);
  if (p == FINGERPRINT_OK) {
    Serial.println("找到匹配的指纹");
    Serial.print("ID #"); Serial.println(finger.fingerID);
    Serial.print("置信度: "); Serial.println(finger.confidence);
    return finger.fingerID;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("未找到匹配的指纹，准备注册为新指纹...");
    registerFingerprint();
    return -1;
  } else {
    Serial.println("搜索指纹失败");
    registerFingerprint();
    return -1;
  }
}

void registerFingerprint() {
  // 注意：注册新指纹的过程比较复杂，需要采集两次指纹并生成模板，然后存储模板
  // 这里仅提供一个简化的概念性实现步骤，具体实现可能需要根据指纹模块的说明书来完成
  
  Serial.println("请放上手指...");
  while (finger.getImage() != FINGERPRINT_OK);  // 等待手指放上
  
  if (finger.image2Tz(1) != FINGERPRINT_OK) {  // 生成特征图1
    return;
  }
  
  Serial.println("请再次放上手指...");
  while (finger.getImage() != FINGERPRINT_OK);  // 等待手指再次放上
  
  if (finger.image2Tz(2) != FINGERPRINT_OK) {  // 生成特征图2
    return;
  }
  
  if (finger.createModel() != FINGERPRINT_OK) {  // 合并特征图生成模板
    Serial.println("创建模板失败");
    return;
  }
  
//   int id = findEmptyID();  // 查找空闲的ID位置
    int id = 1;
  if (id < 0) {
    Serial.println("没有找到空闲的ID位置");
    return;
  }
  
  if (finger.storeModel(id) != FINGERPRINT_OK) {  // 存储模板
    Serial.println("模板存储失败"); return; }

    Serial.print("模板成功存储在ID #"); 
    Serial.println(id); }

int findEmptyID() { // 查找空闲的ID位置，这里简化处理，实际应用中可能需要根据你的指纹模块存储容量调整 
for (int page_id = 0; page_id < 127; page_id++) { // 假设最大ID为127
    uint8_t p = finger.loadModel(page_id); // 尝试加载指定ID的模型
    if (p == FINGERPRINT_NOFINGER) { // 检查是否未找到指纹
      return page_id; // 返回空闲的ID
    }
  }
  return -1; // 如果所有ID都被占用，返回-1
}
