#include "led.h"

CRGB leds[NUM_LEDS];
uint8_t gHue = 0; // 定义全局变量 gHu
uint8_t brightness = 0;
uint8_t fadeAmount = 5;

void led_sky(void);
void led_breath(void);
void led_wave(void);
void led_stay(void);
void led_rainbow(void);


void led_init(){
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}

void led_close(){
  FastLED.clear();  // 将所有LED设置为黑色（关闭）
  FastLED.show();   // 更新LED显示
}

void led_rainbow() {
  fill_rainbow(leds, NUM_LEDS, gHue, 7);
  FastLED.delay(10);
}


void led_sky(){
  // Eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy(leds, NUM_LEDS, 20);
  byte dothue = 0;
  for (int i = 0; i < 8; i++) {
    leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(dothue, 200, 255);
    dothue += 32;
    FastLED.delay(10);
  }
}

void led_wave(){
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(gHue+(i*2), 255, qadd8(inoise8(i*10, millis()/5), 16));
    FastLED.delay(10);
  }
}

void led_breath(){
  // 使用正弦函数来创建平滑的亮度变化
  float breath = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;
  
  // 将呼吸效果的值映射到0-255范围
  uint8_t brightness = map(breath, 0, 255, 0, 255);
  
  // 设置所有LED的颜色和亮度
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;
    leds[i].fadeToBlackBy(255 - brightness);
  }
  
  FastLED.show();  // 更新LED显示
  FastLED.delay(10);
}

void led_stay(){
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.setBrightness(200); 
  FastLED.show();
}
