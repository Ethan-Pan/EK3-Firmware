#include <Arduino.h>
#include "flash/flash.h"
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
#include "wifi/wifi.h"
#include "common/common.h"
#include  "keyboard/keyboard.h"
#include  "bluetooth/bluetooth.h"
 
void setup() {
    /* COMMON */
    common_init();
    /* READ CONFIG */
    config_init();
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
    /* KEYBOARD */
    if(globalData.flag_config == 1 && gJsonData.connect_flag == 1){
        ble_keyboard_init();
    }
    /* BLE */
    if(globalData.flag_config == 1 && gJsonData.connect_flag == 2){
        ble_init();
    }
    /* DISPLAY */
    dis_init();
    /* LVGL UI */
    ui_init(); 
    /* LVGL EVENT */
    ui_event_init();
    /* CONFIG UPDATE */
    config_update();
    /* CREATE TASK */
    task_init();  
}

void loop() {
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}

