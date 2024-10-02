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
    float temp_cur;
    float temp_max;
    float temp_min;
    float weather_hum;
    int weather_type;
    /* time */
    int time_hour;
    int time_min;
    int time_sec;
    /* date */
    int date_week;
    int date_month;
    int date_day;
} JsonDataStru;

extern JsonDataStru gJsonData;
extern void connect_init(void);

#endif
