#include "led.h"

CRGB leds[NUM_LEDS];

void led_init(){
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}

void led_rainbow(){
  // FastLED的内置彩虹效果
  fill_rainbow(leds, NUM_LEDS, millis() / 128, 7);
  // 为了看到彩虹效果的变化，这里有一个小延时
  FastLED.delay(5);
}

void led_close(){
    // 将所有LED熄灭
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
}
