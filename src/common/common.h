#ifndef __COMMON_NEW_H__
#define __COMMON_NEW_H__

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
    int flag_motor;
    int flag_finger;
    int flag_power;
    int flag_encoder;
    /* fingers ID */
    int finger_count;
    int finger_id_buffer[10];
    /* power */
    int last_charge_value;
    int last_nocharge_value;
    int change_stay_count;
    int voltage_bias;
    /* led */
    int led_mode;

} GlobalDataStru;

extern GlobalDataStru globalData;
extern void common_init(void);

#endif