// finger.h 文件
#ifndef __FINGER_H__
#define __FINGER_H__

#include "Arduino.h"
// #include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include "yfrobot_fpm383.h"
#include "common/common.h"

extern void finger_init(void);
extern int8_t finger_enroll(void);
extern int8_t finger_delete(uint16_t id);
extern int8_t finger_empty(void);
extern int8_t finger_identify(void);
uint8_t finger_inquiry(void);

extern void test_finger(void);

#endif