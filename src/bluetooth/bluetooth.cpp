#include "bluetooth.h"


void ble_init(void);
void ble_loop(void);

// BLE服务和特征的UUID
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
static unsigned long disconnectTime = 0;

BLEServer *pServer = nullptr;
BLECharacteristic *pCharacteristic = nullptr;
bool deviceConnected = false;

// BLE服务器回调
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

// BLE特征回调
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      if (rxValue.length() > 0) {
        Serial.println("Received Value: " + String(rxValue.c_str()));
        // 将接收到的JSON数据原样发送回去
        pCharacteristic->setValue(rxValue);
        pCharacteristic->notify();
      }
    }
};

void ble_init() {
  BLEDevice::init("ESP32_BLE_Test");  // 初始化BLE设备,设置设备名称为"ESP32_BLE"
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
//   pAdvertising->setMinPreferred(0x06);  // 设置最小连接间隔,单位为1.25ms
//   pAdvertising->setMinPreferred(0x12);  // 设置最大连接间隔,单位为1.25ms
  BLEDevice::startAdvertising();  // 开始广播
  Serial.println("Waiting a client connection to notify...");  // 打印等待连接的消息


//   BLEDevice::init("ESP32_BLE_Test");
//   BLEServer *pServer = BLEDevice::createServer();
//   BLEService *pService = pServer->createService(SERVICE_UUID);
//   pService->start();
//   BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
//   pAdvertising->addServiceUUID(pService->getUUID());
//   pAdvertising->setScanResponse(true);
// //   pAdvertising->start();
//   BLEDevice::startAdvertising();
//   Serial.println("BLE Advertise Started");
}

void ble_loop() {
  // 如果设备已连接，则在这里可以执行其他任务
  if (deviceConnected) {
    delay(10); // 做一些处理
  }
  // 如果设备断开连接
  if (!deviceConnected) {
    // 记录断开连接的时间
    if (disconnectTime == 0) {
      disconnectTime = millis();
    }
    
    // 如果断开连接超过3秒
    if (millis() - disconnectTime > 3000) {
      disconnectTime = 0;
      // 重新开始广播
      BLEDevice::startAdvertising();
      Serial.println("重新开始广播，等待新的连接...");
    }
  }
  
}
