#include "common.h"

GlobalDataStru globalData = {0};

void common_init(){
    Serial.begin(115200);
    globalData.change_stay_count = 30;
    globalData.led_mode = 2;  // led breath
}
