// led.h 文件
#ifndef __LED_H__
#define __LED_H__

#include <Arduino.h>
#include <FastLED.h>
#include "flash/flash.h"


#define LED_PIN     12     // 定义连接到WS2812B的数据引脚
#define NUM_LEDS    2   // 定义LED的数量
#define BRIGHTNESS  100    // 定义亮度
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

extern CRGB leds[];
extern void led_rainbow(void);
extern void led_init(void);
extern void led_close(void);
extern void led_sky(void);
extern void led_breath(void);
extern void led_wave(void);
extern void led_stay(void);
extern void led_open(void);
extern uint8_t gHue;

#endif