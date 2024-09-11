// finger.h 文件
#ifndef __FINGER_H__
#define __FINGER_H__

#include "Arduino.h"
#include <cstring>

extern int gFingerISRFlag;

extern void fingerInit(int touchPin);
extern void autoEnroll(void);
extern void autoIdentify(void);
extern void openSleep(void);
extern void xTaskFinger(void *pt);
#endif