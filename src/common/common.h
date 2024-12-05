#ifndef __COMMON_NEW_H__
#define __COMMON_NEW_H__

#include <Arduino.h>

typedef struct {
    /* current time */
    int cur_time_hour;
    int cur_time_min;
    int cur_time_sec;
    /* current date */
    int cur_date_week;
    int cur_date_month;
    int cur_date_day;
    /*current power */
    int cur_power_valuse;
    /* flags */
    int flag_timer;
    int flag_tomato;
    int flag_timer_rst;
    int flag_led;
    int flag_switch;
    int flag_finger;
    int flag_power;
    int flag_encoder;
    int flag_screen;
    int flag_finger_power;
    int flag_config;
    int flag_wifi_connect;
    int flag_ble_busy;
    int flag_firmware_update;    
    int flag_update_scr_loaded;
    int flag_update_confirm;
    int flag_first_connect;
    /* fingers ID */
    int finger_count;
    /* power */
    int last_charge_value;
    int last_nocharge_value;
    int change_stay_count;
    int voltage_bias;
    int power_charge_state;
    int power_charge_base;
    /* led */
    int led_mode;
    /* time */
    unsigned long time_finger_touch;
    unsigned long time_switch_on;
    /* encoder */
    int encoder_last_count;
    /* music */
    int music_state;
    /* version */
    char firmware_cur_version[5];   
    char firmware_new_version[5];
    /* weater */
    int weather_update_state;
    int weather_update_time;
    /* ota */
    int ota_download_state;
    
} GlobalDataStru;

extern GlobalDataStru globalData;
extern void common_init(void);

#endif