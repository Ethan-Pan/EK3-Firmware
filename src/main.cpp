#include <Arduino.h>
#include "interface/interface.h"
#include "ui.h"
#include "esp_sleep.h"
#include "LED/led.h"
#include "display/display.h"
#include "motor/motor.h"
#include "task/task.h"
#include "ui_events.h"
#include "power/power.h"
#include "finger/finger.h"
#include "encoder/encoder.h"


void setup() {
    Serial.begin(115200);
    /* COMMON */
    common_init();
    /* DISPLAY */
    dis_init();
    /* LED  */
    led_init();
    /* SWITCH & MOTOR */
    motor_init();
    /* FINGER */
    finger_init();
    /* ENCODER */
    encoder_init();
    /* POWER */
    power_init();
    /* LVGL UI */
    ui_init(); 
    /* LVGL EVENT */
    ui_event_init();
    /* READ JSON */
    connect_init();
    /* CREATE TASK */
    task_init();   
}

void loop() {
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}
