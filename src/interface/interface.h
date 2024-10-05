// interface.h 文件
#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <Arduino.h>
#include <ArduinoJson.h>
#include "common/common.h"
#include "ui.h"



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
    /* location */
    char location[20];
    /* LED */
    int led_state;
    /* information */
    char user_name[20];
} JsonDataStru;

extern JsonDataStru gJsonData;
extern void connect_init(void);

#endif
