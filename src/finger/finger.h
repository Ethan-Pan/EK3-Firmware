// finger.h 文件
#ifndef __FINGER_H__
#define __FINGER_H__

#include "Arduino.h"
// #include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include "yfrobot_fpm383.h"
#include "common/common.h"


#define FINGERPRINT_TEMPLATE_MAX 10
#define PIN_FINGER_TOUCH 14

extern void finger_init(void);
extern int8_t finger_enroll(int id);
extern int8_t finger_delete(uint16_t id);
extern int8_t finger_empty(void);
extern int8_t finger_identify(void);
uint8_t finger_inquiry(void);
extern void finger_sleep(void);
extern void test_finger(void);
extern void IRAM_ATTR interrupt_finger_handler(void);
extern void finger_power_on(void);
extern void finger_power_off(void);
extern void test_finger();

#endif