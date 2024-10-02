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

void setup() {
    Serial.begin(115200);
    // /* DISPLAY */
    // dis_init();
    // /* LED  */
    // led_init();
    // /* SWITCH & MOTOR */
    // motor_init();4
    /* FINGER */
    finger_init();
    // /* POWER */
    // power_init();
    // /* LVGL UI */
    // ui_init(); 
    // ui_event_init();
    // /* READ JSON */
    // connect_init();
    // /* CREATE TASK */
    // task_init();
    // /* SLEEP MODE */
    // esp_sleep_enable_ext0_wakeup(GPIO_NUM_13, 0); 
}

void loop() {
  // lv_timer_handler(); /* let the GUI do its work */
  // delay(5);
  // enrollFingerprint();
  // delay(2000);
  test_finger();
  delay(5);
}
