// display.h 文件
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <CST816S.h>
#include <Ticker.h>
#include <driver/ledc.h>
#include "flash/flash.h"

extern void dis_init(void);
extern void turnOffScreen();
extern void turnOnScreen();

#endif