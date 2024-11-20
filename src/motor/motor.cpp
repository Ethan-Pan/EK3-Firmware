#include "motor.h"

volatile unsigned long pressTime = 0;

// 按键中断服务程序
void IRAM_ATTR handleButtonPress() {
  detachInterrupt(digitalPinToInterrupt(SWITCH_PIN));
  globalData.flag_switch = 1;
  pressTime = millis();
}

void motor_short(){
    digitalWrite(MOTOR_PIN, HIGH);
    vTaskDelay(150);
    digitalWrite(MOTOR_PIN, LOW);
}

void motor_long(){
    digitalWrite(MOTOR_PIN, HIGH);
    vTaskDelay(1000);
    digitalWrite(MOTOR_PIN, LOW);
}

void motor_short_twice(){
    digitalWrite(MOTOR_PIN, HIGH);
    vTaskDelay(150);
    digitalWrite(MOTOR_PIN, LOW);
    vTaskDelay(50);
    digitalWrite(MOTOR_PIN, HIGH);
    vTaskDelay(150);
    digitalWrite(MOTOR_PIN, LOW);
}

void motor_init(){
    pinMode(MOTOR_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), handleButtonPress, FALLING);
    motor_short();
}

