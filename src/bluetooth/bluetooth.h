#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "Arduino.h"
#include "BluetoothSerial.h"
#include <ArduinoJson.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <ArduinoJson.h>


extern void ble_init(void);
extern void ble_loop(void);


#endif
