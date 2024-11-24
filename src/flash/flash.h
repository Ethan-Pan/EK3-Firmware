// flash.h 文件
#ifndef __FLASH_H__
#define __FLASH_H__

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Preferences.h>
#include "common/common.h"
#include "finger/finger.h"
#include "ui.h"
#include "ui_helpers.h"
#include "ui_events.h"
#include "bluetooth/bluetooth.h"
#include "keyboard/keyboard.h"



extern int16_t gSecAngle;
extern int16_t gMinAngle;
extern int16_t gHourAngle;

typedef struct {
    /* weather */
    int temp_cur;
    int temp_max;
    int temp_min;
    int weather_hum;
    int weather_type;
    /* time */
    int time_hour;
    int time_min;
    int time_sec;
    /* date */
    int date_week;
    int date_month;
    int date_day;
    /* LED */
    int led_state;
    /* config info */
    char user_name[20];
    char location[20];
    int power_show;
    int encoder;
    char color[10];
    char power_save_start[10];
    char power_save_end[10];
    int power_start_hour;
    int power_start_min;
    int power_end_hour;
    int power_end_min;
    int power_deep_save;
    char finger_pin[30];
    int x_mode;
    char x_input[20];
    int update_flag;
    int connect_flag;
    char wifi_ssid[20];
    char wifi_password[20];
} JsonDataStru;

extern JsonDataStru gJsonData;
extern void config_init(void);
extern void serialEvent(void);
extern int config_check(void);
extern void clear_config(void);
extern void config_update(void);
extern void update_time(void);
extern void update_date(void);
extern void update_weather(void);

#endif
