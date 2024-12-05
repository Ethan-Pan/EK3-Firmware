#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "Arduino.h"
#include "BluetoothSerial.h"
#include <ArduinoJson.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <BleKeyboard.h>
#include "flash/flash.h"  

#define BLE_FINGER "$111#"
#define BLE_ROTATE_RIGHT "$221#"
#define BLE_ROTATE_LEFT "$222#"
#define BLE_MUTE "$223#"
#define BLE_NO_MUTE "$224#"
#define BLE_NEXT "$225#"
#define BLE_PREV "$226#"
#define BLE_PLAY "$227#"
#define BLE_PAUSE "$228#"
#define BLE_KEY_UP "$229#"
#define BLE_KEY_DOWN "$230#"

extern void ble_init(void);
extern int ble_send_string(const char* str);
extern void get_ble_address(char* bleAddress);
extern void ble_deinit(void);

#endif