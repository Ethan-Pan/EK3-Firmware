#include "motor.h"

volatile unsigned long pressTime = 0;

// 按键中断服务程序
void IRAM_ATTR handleButtonPress() {
  detachInterrupt(digitalPinToInterrupt(SWITCH_PIN));
  globalData.flag_motor = 1;
  pressTime = millis();
}

void motor_short(){
    digitalWrite(MOTOR_PIN, LOW);
    vTaskDelay(100);
    digitalWrite(MOTOR_PIN, HIGH);
}

void motor_init(){
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), handleButtonPress, FALLING);
}

