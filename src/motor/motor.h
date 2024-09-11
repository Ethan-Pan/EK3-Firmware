// motor.h 文件
#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "Arduino.h"
#include "common/common.h"

#define SWITCH_PIN 13
#define MOTOR_PIN 4
#define BL_PIN 19

extern volatile unsigned long pressTime;

extern void motor_init(void);
extern void IRAM_ATTR handleButtonPress(void);

#endif