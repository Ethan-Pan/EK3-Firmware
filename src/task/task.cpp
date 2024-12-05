#include "task.h"

#define ARC_TOMATO_INIT 25


// GlobalDataStru globalData = {0};

// 定义时间变量
static int hours = 0;
static int minutes = 0;
static int seconds = 0;

static int minutes_tomato = ARC_TOMATO_INIT;
static int seconds_tomato = 0;
static int count_tomato = 0;
static int sleep_flag = 0;

static int lastPower = 0;

static void task_switch(void *pt);
static void task_LED(void *pt);
static void task_timer(void *pt);
static void task_tomato(void *pt);
static void task_watch(void *pt);
static void task_real_time(void *pt);
static void task_power(void *pt);
static void task_finger(void *pt);
static void task_encoder(void *pt);
static void task_uart(void *pt);
static void task_weather_update(void *pt);
static void task_version_update(void *pt);
static void task_version_auto_update(void *pt);
static void task_music(void *pt);
static void ui_config_init(void);


/* task init */
void task_init(){
    xTaskCreate(task_switch, "task_switch", 1024*4, NULL, 1, NULL);
    xTaskCreate(task_LED, "task_LED", 1024*4, NULL, 1, NULL);
    xTaskCreate(task_timer, "task_timer", 1024*4, NULL, 1, NULL);
    xTaskCreate(task_tomato, "task_tomato", 1024*4, NULL, 1, NULL);
    xTaskCreate(task_watch, "task_watch", 1024*4, NULL, 1, NULL);
    xTaskCreate(task_power, "task_power", 1024*4, NULL, 1, NULL);
    xTaskCreate(task_finger, "task_finger", 1024*4, NULL, 1, NULL);
    xTaskCreate(task_encoder, "task_encoder", 1024*4, NULL, 1, NULL);
    xTaskCreate(task_uart, "task_uart", 1024*4, NULL, 1, NULL);
    xTaskCreate(task_music, "task_music", 1024*4, NULL, 1, NULL);
    xTaskCreate(task_weather_update, "task_weather_update", 1024*4, NULL, 1, NULL);
    xTaskCreate(task_version_update, "task_version_update", 1024*4, NULL, 1, NULL);
    xTaskCreate(task_version_auto_update, "task_version_auto_update", 1024*4, NULL, 1, NULL);
    ui_config_init();
}

/* ui config init */
/*
    for .c file (ui.h) connot include .cpp header (such as flash.h),
    so the ui config init is in the task.cpp file
*/
static void ui_config_init(){
    if(gJsonData.power_show == 0){
        lv_obj_add_flag(ui_labPower, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_labPower2, LV_OBJ_FLAG_HIDDEN);
    }
}

/* switch task */
static void task_switch(void *pt){
    while (1){
        if(globalData.flag_switch == 1){
            unsigned long duration;
            vTaskDelay(100);
            while(digitalRead(SWITCH_PIN) == LOW){
              // 等待按键释放
                duration = millis() - pressTime;
                if(duration >= 2000){
                    globalData.flag_led = 1;
                    led_close(); 
                    turnOffScreen();
                    motor_long();
                    vTaskDelay(2000);
                    sleep_flag = 1;
                    globalData.flag_switch = 0;
                    globalData.flag_screen = 1;
                    esp_deep_sleep_start(); // 进入深度睡眠
                    break;
                }
            }
            if(sleep_flag == 0){
                duration = millis() - pressTime;
                if(duration <= 1000){
                    if(globalData.flag_screen == 0){
                        turnOffScreen();
                        globalData.flag_screen = 1;
                    }
                    else{
                        turnOnScreen();
                        globalData.flag_screen = 0;
                    }
                    if(globalData.flag_led == 0){
                        globalData.flag_led = 1;
                        led_close();
                    }
                    else{
                        globalData.flag_led = 0;
                    }
                }
                globalData.flag_switch = 0;
                sleep_flag = 0;
                attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), handleButtonPress, FALLING);
            }
        }
        vTaskDelay(5);
  }
}

/* LVGL Watch 1 task */
static void task_watch(void *pt){
    char time_str[3];
    while (1)
    {
        gSecAngle += 3;
        if(gSecAngle >= 3600){
            gSecAngle = 0;
            gMinAngle += 60;
            gHourAngle += 5;
            lv_img_set_angle(ui_min, gMinAngle);
            lv_img_set_angle(ui_hour, gHourAngle);
            globalData.cur_time_min += 1;
            sprintf(time_str, "%02d", globalData.cur_time_min);
            lv_label_set_text(ui_labTimeMin, time_str);
        }
        if(gMinAngle >= 3600){
            gMinAngle = 0;
            lv_img_set_angle(ui_min, gMinAngle);
            globalData.cur_time_min = 0;
            sprintf(time_str, "%02d", globalData.cur_time_min);
            lv_label_set_text(ui_labTimeMin, time_str);
            globalData.cur_time_hour += 1;
            sprintf(time_str, "%01d", globalData.cur_time_hour%10);
            lv_label_set_text(ui_labTimeHour1, time_str);
            sprintf(time_str, "%01d", globalData.cur_time_hour/10);
            lv_label_set_text(ui_labTimeHour2, time_str);
        }
        if(gHourAngle >= 3600){
            gHourAngle = 0;
            lv_img_set_angle(ui_hour, gHourAngle);
            sprintf(time_str, "%02d", globalData.cur_time_hour);
            lv_label_set_text(ui_labTimeMin, time_str);
            globalData.cur_time_hour = 0;
            sprintf(time_str, "%01d", globalData.cur_time_hour%10);
            lv_label_set_text(ui_labTimeHour1, time_str);
            sprintf(time_str, "%01d", globalData.cur_time_hour/10);
            lv_label_set_text(ui_labTimeHour2, time_str);
        }        
        // 检查是否需要进入深度休眠
        // 检查当前时间是否在省电时间段内
        bool isInPowerSaveTime = false;
        
        if((globalData.cur_time_hour == gJsonData.power_end_hour && globalData.cur_time_min > gJsonData.power_end_min)||globalData.cur_time_hour > gJsonData.power_end_hour){
            isInPowerSaveTime = true;
        }
        else{
            isInPowerSaveTime = false;
        }
        // 开机之后10分钟进入深度休眠
        if(isInPowerSaveTime && (millis() - globalData.time_switch_on) >= 1000 * 60 * 10) {
            // 计算当前时间到power_end的时间差(以分钟为单位)
            int wakeupMinutes = 0;
            wakeupMinutes = (24 - globalData.cur_time_hour + gJsonData.power_end_hour) * 60 + 
                               (gJsonData.power_end_min - globalData.cur_time_min);
            // 设置定时器唤醒时间(转换为微秒)
            esp_sleep_enable_timer_wakeup(wakeupMinutes * 60 * 1000000ULL);
            Serial.printf("Deep Sleep MODE\n");
            led_close();
            turnOffScreen();
            esp_deep_sleep_start(); 
        }
        lv_img_set_angle(ui_sec, gSecAngle);
        lv_img_set_angle(ui_sec_dot, gSecAngle);
        vTaskDelay(50);
    }
    
}

/* LVGL LED task */
static void task_LED(void *pt){
    while(1){
        if(globalData.flag_led == 0){
            switch (globalData.led_mode)
            {
                case 0:
                    led_close();
                    break;
                case 2:
                    led_stay();
                    break;
                case 1:
                    led_breath();
                    break;
                case 3:
                    led_rainbow();
                    break;
                case 4:
                    led_sky();
                    break;
                case 5:
                    led_wave();
                    break;
                default:
                    led_close();
                    break;
            }
            gHue++;
            if(gHue >= 255){
                gHue = 0;
            }
        }
        vTaskDelay(10);
    }
    
}

/* LVGL timer task */
static void task_timer(void *pt){
    while(1){
        if(globalData.flag_timer == 1){
            vTaskDelay(980);
            seconds++;
            if (seconds >= 60)
            {
                seconds = 0;
                minutes++;
                if (minutes >= 60)
                {
                    minutes = 0;
                    hours++;
                    if (hours >= 24)
                    {
                        hours = 0;
                    }
                }
            }

            char time_str[3];
            sprintf(time_str, "%02d", hours);
            lv_label_set_text(ui_labelTimerHour1, time_str);

            sprintf(time_str, "%02d", minutes);
            lv_label_set_text(ui_labelTimerMin1, time_str);

            sprintf(time_str, "%02d", seconds);
            lv_label_set_text(ui_labelTimerSecond1, time_str);
        }
        if(globalData.flag_timer_rst == 1){
            globalData.flag_timer_rst = 0;
            seconds = 0;
            minutes = 0;
            hours = 0;
            char time_str[3];
            sprintf(time_str, "%02d", hours);
            lv_label_set_text(ui_labelTimerHour1, time_str);

            sprintf(time_str, "%02d", minutes);
            lv_label_set_text(ui_labelTimerMin1, time_str);

            sprintf(time_str, "%02d", seconds);
            lv_label_set_text(ui_labelTimerSecond1, time_str);
        }
        vTaskDelay(20);
    }
}

/* LVGL tomato task */
static void task_tomato(void *pt){
    char time_str[3];
    char count_str[3];
    float time_count;
    while(1){
        if(globalData.flag_tomato == 1){
            vTaskDelay(980);
            seconds_tomato--;
            if (seconds_tomato < 0)
            {
                minutes_tomato--;
                seconds_tomato = 59;
                if (minutes_tomato < 0)
                {   
                    minutes_tomato = ARC_TOMATO_INIT;
                    seconds_tomato = 0;
                    lv_obj_add_flag(ui_imgTomatoPause, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(ui_imgTomatoStart, LV_OBJ_FLAG_HIDDEN);
                    count_tomato += 1;
                    if(count_tomato < 10){
                        sprintf(count_str, "%01d", count_tomato);
                    }
                    else{
                        sprintf(count_str, "%02d", count_tomato);
                    }
                    lv_label_set_text(ui_labelTomatoCount, count_str);
                    globalData.flag_tomato = 0;
                }
            }

            sprintf(time_str, "%02d", minutes_tomato);
            lv_label_set_text(ui_labelTomatoMin, time_str);

            sprintf(time_str, "%02d", seconds_tomato);
            lv_label_set_text(ui_labelTomatoecond, time_str);
            if(globalData.flag_tomato == 0){
                time_count = 0;
            }else{
                time_count = 100.0f/(float)(ARC_TOMATO_INIT*60)*(ARC_TOMATO_INIT*60-minutes_tomato*60-seconds_tomato);
            }
            lv_arc_set_value(ui_arcTomato, (int16_t)time_count);
        }
        vTaskDelay(20);
    }
}

/* power task */
static void task_power(void *pt){
    while (1){
        vTaskDelay(1000);  
        char time_str[5];
        int power = 0;
        int realtimePercent = 0;
        uint32_t voltage_power = read_power();
        uint32_t voltage_state = get_charge_state() > 500? 1:0;
        if(voltage_state == 0){ 
            lv_obj_add_flag(ui_imgCharge, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_imgCharge2, LV_OBJ_FLAG_HIDDEN);
            /* init the last power value */
            if(globalData.last_nocharge_value == 0){
                globalData.last_nocharge_value = voltage_power;
            }
            /* charge state change */
            if(globalData.flag_power == 2){
                globalData.flag_power = 1;
                globalData.voltage_bias = voltage_power - globalData.last_charge_value;
                voltage_power -= globalData.voltage_bias;
            }else{
                voltage_power -= globalData.voltage_bias;
                globalData.voltage_bias -= globalData.voltage_bias/globalData.change_stay_count;
                if(voltage_power >= globalData.last_nocharge_value){
                    voltage_power = globalData.last_nocharge_value;
                }
            }
            globalData.last_nocharge_value = voltage_power;
            globalData.flag_power = 1;
        }
        /* charge state */
        else{
            lv_obj_clear_flag(ui_imgCharge, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_imgCharge2, LV_OBJ_FLAG_HIDDEN);
            /* init the last power value */
            if(globalData.last_charge_value == 0){
                globalData.last_charge_value = voltage_power;
            }
            /* charge state change */
            if(globalData.flag_power == 1){
                globalData.flag_power = 2;
                globalData.voltage_bias = voltage_power - globalData.last_nocharge_value;
                voltage_power -= globalData.voltage_bias;
            }else{
                voltage_power -= globalData.voltage_bias;
                globalData.voltage_bias -= globalData.voltage_bias/globalData.change_stay_count;
                if(voltage_power <= globalData.last_charge_value){
                    voltage_power = globalData.last_charge_value;
                }
            }
            globalData.last_charge_value = voltage_power;
            globalData.flag_power = 2;
        }

        if(voltage_power >= POWER_MAX){
                power = 100;
                lv_label_set_text(ui_labPower, "100%");
                lv_label_set_text(ui_labPower2, "100%");
                lv_arc_set_value(ui_ArcPower1, 100);
                lv_arc_set_value(ui_ArcPower2, 100);
            }
            else if(voltage_power <= POWER_MIN){
                power = 0;
                lv_label_set_text(ui_labPower, "0%");
                lv_label_set_text(ui_labPower2, "0%");
                lv_arc_set_value(ui_ArcPower1, 0);
                lv_arc_set_value(ui_ArcPower2, 0);
            }
            else{
                power = (voltage_power-POWER_MIN) * 100 / (POWER_MAX-POWER_MIN);
                
                sprintf(time_str, "%02d", power);
                time_str[2] = '%';
                time_str[3] = '\0';
                lv_label_set_text(ui_labPower, time_str);
                lv_label_set_text(ui_labPower2, time_str);
                lv_arc_set_value(ui_ArcPower1, power);
                lv_arc_set_value(ui_ArcPower2, power);
        }
        if(power < 20){
            lv_obj_set_style_text_color(ui_labPower, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(ui_labPower2, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(ui_ArcPower1, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(ui_ArcPower2, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        else if (power > 90)
        {
            lv_obj_set_style_arc_color(ui_ArcPower1, lv_color_hex(0X00aa1a), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(ui_ArcPower2, lv_color_hex(0x00aa1a), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        
        else{
            lv_obj_set_style_arc_color(ui_ArcPower1, lv_color_hex(0xB0E14A), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(ui_ArcPower2, lv_color_hex(0xB0E14A), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(ui_labPower, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(ui_labPower2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

/* finger task */
static void task_finger(void *pt){
    while (1) {
        if (globalData.flag_finger == 1) {
            vTaskDelay(100);
            if(digitalRead(PIN_FINGER_TOUCH) == HIGH){  
                globalData.time_finger_touch = millis();              
                if(globalData.flag_finger_power == 0){
                    finger_power_on();
                    globalData.flag_finger_power = 1;
                }
                int8_t result = finger_identify();
                if (result == 1) {
                    motor_short();
                    if(gJsonData.connect_flag == 1){
                        if(gJsonData.x_mode == 1){
                            keyboard_X_input();
                        }
                        else{
                            keyboard_finger();
                        }
                    }
                    if(gJsonData.connect_flag == 2){
                        ble_send_string(BLE_FINGER);
                    }
                } else {
                    motor_short_twice();
                    if(gJsonData.connect_flag == 1 && gJsonData.x_mode == 1){
                        keyboard_X_input();
                    }
                }
                // 防止手指长时间放置多次触发
                vTaskDelay(1000);
                finger_sleep();
            }
            globalData.flag_finger = 0;
            attachInterrupt(digitalPinToInterrupt(PIN_FINGER_TOUCH), interrupt_finger_handler, RISING);        
        }

        if(globalData.flag_finger_power == 1){
            if(millis()-globalData.time_finger_touch >= 10000){
                finger_power_off();
                globalData.flag_finger_power = 0;
            }
        }
        vTaskDelay(10);  
    }
}

/* encoder task */
static void task_encoder(void *pt){
    while(1){
        if(globalData.flag_encoder == 1){
            globalData.flag_encoder = 0;
            int64_t count = read_encoder_count();
            if(globalData.encoder_last_count == 9999){
                globalData.encoder_last_count = count;
            }else{
                if(count > globalData.encoder_last_count){
                    if(gJsonData.connect_flag == 1){
                        if(gJsonData.encoder == 0){
                            keyboard_volume_up();
                        }
                        else if(gJsonData.encoder == 1){
                            keyboard_down();
                        }
                    }
                    if(gJsonData.connect_flag == 2){
                        if(gJsonData.encoder == 0){
                            ble_send_string(BLE_ROTATE_RIGHT);
                        }
                        else if(gJsonData.encoder == 1){
                            ble_send_string(BLE_KEY_DOWN);
                        }
                        
                    }
                }
                else if(count < globalData.encoder_last_count){
                    if(gJsonData.connect_flag == 1){
                        if(gJsonData.encoder == 0){
                            keyboard_volume_down();
                        }
                        else if(gJsonData.encoder == 1){
                            keyboard_up();
                        }
                    }
                    if(gJsonData.connect_flag == 2){
                        if(gJsonData.encoder == 0){
                            ble_send_string(BLE_ROTATE_LEFT);
                        }
                        else if (gJsonData.encoder == 1)
                        {
                            ble_send_string(BLE_KEY_DOWN);
                        }
                    }
                }
            }
            globalData.encoder_last_count = count;  
        }
        vTaskDelay(10);
    }
}

/* uart task */
static void task_uart(void *pt) {
    while(1) {
        if(Serial.available()) {
            serialEvent();
        }
        vTaskDelay(5);  
    }
}

/* music task */
static void task_music(void *pt){
    while(1){
        switch (globalData.music_state)
        {
        case 1:
            if(gJsonData.connect_flag == 1){
                keyboard_play_pause();
            }
            if(gJsonData.connect_flag == 2){
                ble_send_string(BLE_PAUSE);
            }
            globalData.music_state = 0;
            break;
        case 2:
            if(gJsonData.connect_flag == 1){
                keyboard_play_pause();
            }
            if(gJsonData.connect_flag == 2){
                ble_send_string(BLE_PLAY);
            }
            globalData.music_state = 0;
            break;
        case 3:
            if(gJsonData.connect_flag == 1){
                keyboard_next();
            }
            if(gJsonData.connect_flag == 2){
                ble_send_string(BLE_NEXT);
            }
            globalData.music_state = 0;
            break;
        case 4:
            if(gJsonData.connect_flag == 1){
                keyboard_prev();
            }
            if(gJsonData.connect_flag == 2){
                ble_send_string(BLE_PREV);
            }
            globalData.music_state = 0;
            break;
        case 5:
            if(gJsonData.connect_flag == 1){
                keyboard_mute();
            }
            if(gJsonData.connect_flag == 2){
                ble_send_string(BLE_MUTE);
            }
            globalData.music_state = 0;
            break;
        case 6:
            if(gJsonData.connect_flag == 1){
                keyboard_unmute();
            }
            if(gJsonData.connect_flag == 2){
                ble_send_string(BLE_NO_MUTE);
            }
            globalData.music_state = 0;
            break;
        default:
            break;
        }
        vTaskDelay(10);
    }
}

static void task_weather_update(void *pt){
    while(1){
        if(gJsonData.connect_flag == 1){
            if(globalData.weather_update_state == 0){
                globalData.weather_update_time = 2;
                send_weather_update();
            }else{
                globalData.weather_update_time = 60 * 60;
                send_weather_update();
            }
        }
        vTaskDelay(1000 * globalData.weather_update_time);
    }
}

static void task_version_update(void *pt){
    while(1){
        if(gJsonData.connect_flag == 1){
            /* check update screen loaded */
            if(globalData.flag_update_scr_loaded == 1){
                send_version();
                globalData.flag_update_scr_loaded = 0;
                delay(2000);
                if(globalData.flag_firmware_update == 1){
                    globalData.flag_firmware_update = 0;
                    lv_obj_add_flag(ui_panelCheckUpdate, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_add_flag(ui_panelAlready, LV_OBJ_FLAG_HIDDEN);
                    char version_text[20];
                    sprintf(version_text, "EK3_release_%s", globalData.firmware_new_version);
                    lv_label_set_text(ui_labUpdate5, version_text);
                    lv_obj_clear_flag(ui_panelNewVersion, LV_OBJ_FLAG_HIDDEN);
                }
                else{
                    lv_obj_add_flag(ui_panelCheckUpdate, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_add_flag(ui_panelNewVersion, LV_OBJ_FLAG_HIDDEN);
                    char version_text[20];
                    sprintf(version_text, "EK3_release_%s", globalData.firmware_cur_version);
                    lv_label_set_text(ui_labUpdate3, version_text);
                    lv_obj_clear_flag(ui_panelAlready, LV_OBJ_FLAG_HIDDEN);
                }
            }
            /* check update confirm */
            if(globalData.flag_update_confirm == 1){
                globalData.flag_update_confirm = 0;
                send_update_download();
                lv_obj_add_flag(ui_panelNewVersion, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_panelNoConnect, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_panelAlready, LV_OBJ_FLAG_HIDDEN);
                lv_label_set_text(ui_labUpdate1, "更新下载中");
                lv_obj_clear_flag(ui_panelCheckUpdate, LV_OBJ_FLAG_HIDDEN);
            }
            if(globalData.ota_download_state == 2){
                globalData.ota_download_state = 0;
                lv_obj_add_flag(ui_panelCheckUpdate, LV_OBJ_FLAG_HIDDEN);
                lv_obj_clear_flag(ui_panelNoConnect, LV_OBJ_FLAG_HIDDEN);
                delay(3000);
                send_update_start();
            }
            if(globalData.ota_download_state == 3){
                globalData.flag_firmware_update = 0;
                globalData.ota_download_state = 0;
                lv_label_set_text(ui_labUpdate1, "更新下载失败");
                delay(3000);
                _ui_screen_change(&ui_scrMenu, LV_SCR_LOAD_ANIM_FADE_ON, 50, 0, &ui_scrMenu_screen_init);
            }
        }
        vTaskDelay(10);
    }
}


static void task_version_auto_update(void *pt){
    while(1){
        vTaskDelay(1000 * 60 * 60);
        if(gJsonData.update_flag  == 1){
            send_version();
            delay(2000);
            if(globalData.flag_firmware_update == 1){
                globalData.flag_firmware_update = 0;
                _ui_screen_change(&ui_scrUpdate, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 50, 0, &ui_scrUpdate_screen_init);
            }
        }
    }
}

