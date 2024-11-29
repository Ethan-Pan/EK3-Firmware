#include "common.h"

GlobalDataStru globalData = {0};

void common_init(){
    Serial.begin(115200);
    strcpy(globalData.firmware_cur_version, "1.0");
    globalData.change_stay_count = 30;
    globalData.led_mode = 2;  // led breath
    globalData.encoder_last_count = 9999;  // the init value of encoder last count
    globalData.time_switch_on = millis();
    globalData.weather_update_time = 2;
}
