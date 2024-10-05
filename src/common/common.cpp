#include "common.h"

GlobalDataStru globalData = {0};

void common_init(){
    globalData.change_stay_count = 30;
    globalData.led_mode = 1;  // led breath
}
