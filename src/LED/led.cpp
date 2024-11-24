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
void led_open(void);


void led_init(){
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}

void led_close(){
  FastLED.setBrightness(0);  // 将所有LED亮度设置为0
  FastLED.show();   // 更新LED显示
}

void led_rainbow() {
  FastLED.setBrightness(BRIGHTNESS);
  fill_rainbow(leds, NUM_LEDS, gHue, 7);
  FastLED.delay(10);
}

void led_open(){
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
}

void led_sky(){
  // Eight colored dots, weaving in and out of sync with each other
  FastLED.setBrightness(BRIGHTNESS);
  fadeToBlackBy(leds, NUM_LEDS, 20);
  byte dothue = 0;
  for (int i = 0; i < 8; i++) {
    leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(dothue, 200, 255);
    dothue += 32;
    FastLED.delay(10);
  }
}

void led_wave(){
  FastLED.setBrightness(BRIGHTNESS);
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(gHue+(i*2), 255, qadd8(inoise8(i*10, millis()/5), 16));
    FastLED.delay(10);
  }
}

void led_breath(){
  FastLED.setBrightness(BRIGHTNESS);
  // 使用正弦函数来创建平滑的亮度变化
  float breath = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;
  
  // 将呼吸效果的值映射到0-255范围
  uint8_t brightness = map(breath, 0, 255, 0, 255);
  
// 将16进制字符串转换为RGB值
  char color[7];
  strncpy(color, gJsonData.color + 1, 6); // 跳过#号
  color[6] = '\0';
  long rgb = strtol(color, NULL, 16);
  uint8_t r = (rgb >> 16) & 0xFF;
  uint8_t g = (rgb >> 8) & 0xFF; 
  uint8_t b = rgb & 0xFF;

  // 设置所有LED的颜色和亮度
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(r, g, b);
    leds[i].fadeToBlackBy(255 - brightness);
  }
  
  FastLED.show();  // 更新LED显示
  FastLED.delay(10);
}

void led_stay(){
  // 解析颜色字符串,格式为 #RRGGBB
  char color[7];
  strncpy(color, gJsonData.color + 1, 6); // 跳过#号
  color[6] = '\0';
  
  // 将16进制字符串转换为RGB值
  long rgb = strtol(color, NULL, 16);
  uint8_t r = (rgb >> 16) & 0xFF;
  uint8_t g = (rgb >> 8) & 0xFF; 
  uint8_t b = rgb & 0xFF;
  fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
  FastLED.setBrightness(BRIGHTNESS); 
  FastLED.show();
}
