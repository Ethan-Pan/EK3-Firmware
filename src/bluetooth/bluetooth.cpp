#include "bluetooth.h"
#include "esp_bt_device.h"


void ble_init(void);
int ble_send_string(const char* str);
void get_ble_address(char* bleAddress);
void ble_deinit(void);
static void ble_receive_str_handle(const char* str);


// BLE服务和特征的UUID
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define HID_REPORT_ID_KEYBOARD 0x01
static unsigned long disconnectTime = 0;

static BLEServer *pServer = nullptr;
static BLECharacteristic *pCharacteristic = nullptr;
static bool deviceConnected = false;

// BLE服务器回调
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      disconnectTime = 0;  // 重置断开时间
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      delay(500);  // 短暂延迟以确保所有断开连接操作完成
      BLEDevice::startAdvertising();  // 立即开始重新广播
      Serial.println("设备断开连接，重新开始广播...");
    }
};

// BLE特征回调
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      if (rxValue.length() > 0) {
        ble_receive_str_handle(rxValue.c_str());
        // pCharacteristic->setValue(rxValue);
        // pCharacteristic->notify();
      }
    }
};


void ble_init() {
  String deviceName = String(gJsonData.user_name) + "'s EK3";
  BLEDevice::init(deviceName.c_str());  // 使用 c_str() 转换为 C 风格字符串
  pServer = BLEDevice::createServer();  // 创建BLE服务器
  pServer->setCallbacks(new MyServerCallbacks());  // 设置服务器回调函数

  BLEService *pService = pServer->createService(SERVICE_UUID);  // 创建BLE服务
  pCharacteristic = pService->createCharacteristic(  // 创建BLE特征
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |  // 设置特征属性:可读
                      BLECharacteristic::PROPERTY_WRITE |  // 可写
                      BLECharacteristic::PROPERTY_NOTIFY |  // 可通知
                      BLECharacteristic::PROPERTY_INDICATE  // 可指示
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());  // 设置特征回调函数
  pCharacteristic->addDescriptor(new BLE2902());  // 添加CCCD描述符

  pService->start();  // 启动BLE服务
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();  // 获取广播对象
  pAdvertising->addServiceUUID(pService->getUUID());  // 添加服务UUID到广播数据


  pAdvertising->setScanResponse(true);  // 设置扫描响应
  BLEDevice::startAdvertising();  // 开始广播
  Serial.println("Waiting a client connection to notify...");  // 打印等待连接的消息

}

/*
 * ble command list:
 * finger password: s-$111#
 * rotate right: s-$221#
 * rotate left: s-$222#
 * mute: s-$223#
 * no mute: s-$224# 
 * next: s-$225#
 * prev: s-$226#
 * play: s-$227#
 * pause: s-$228#
 * key up: s-$229#
 * key down: s-$230#
*/
int ble_send_string(const char* str) {
    if (!deviceConnected || !pCharacteristic) {
        return 0;
    }
    try {
        pCharacteristic->setValue(str);
        pCharacteristic->notify();
        return 1;
    } catch (...) {
        return 0;
    }
}

void get_ble_address(char* bleAddress){
  if(!deviceConnected){
     ble_init();
  }
    esp_bd_addr_t addr;
    memcpy(addr, esp_bt_dev_get_address(), ESP_BD_ADDR_LEN);
    sprintf(bleAddress, "%02X:%02X:%02X:%02X:%02X:%02X",
          addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
}

void ble_deinit(){
    if(deviceConnected){
        pServer->disconnect(pServer->getConnectedCount());
    }
    BLEDevice::deinit(true);
}


static void ble_receive_str_handle(const char* str){
    char* str_copy = strdup(str);  // 创建字符串副本
    char* token;
    int numbers[20] = {0};  // 存储提取的数字
    int count = 0;

    // 跳过第一个#
    token = strchr(str_copy, '#');
    if(token != NULL) {
        token++; // 移到#后面的字符
        
        while(*token != '\0' && count < 20) {
            if(isdigit(*token)) {
                char numStr[10] = {0};
                int i = 0;
                // 收集连续的数字
                while(isdigit(*token)) {
                    numStr[i++] = *token++;
                }
                numbers[count++] = atoi(numStr);
            } else {
                token++; // 跳过非数字字符(如#)
            }
        }
    }

    free(str_copy);  // 释放内存

    gJsonData.temp_cur = numbers[0];
    gJsonData.weather_hum = numbers[1];
    gJsonData.weather_type = numbers[2];
    gJsonData.temp_max = numbers[3];
    gJsonData.temp_min = numbers[4];
    gJsonData.date_month = numbers[5];
    gJsonData.date_day = numbers[6];
    gJsonData.date_week = numbers[7];
    gJsonData.time_hour = numbers[8];
    gJsonData.time_min = numbers[9];
    gJsonData.time_sec = numbers[10];

    update_weather();
    update_time();
    update_date();
}
