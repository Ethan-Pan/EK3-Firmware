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
}

/* switch task */
static void task_switch(void *pt){
    while (1){
        if(globalData.flag_motor == 1){
            unsigned long duration;
            vTaskDelay(100);
            while(digitalRead(SWITCH_PIN) == LOW){
              // 等待按键释放
                duration = millis() - pressTime;
                if(duration >= 2000){
                    digitalWrite(BL_PIN, LOW);
                    led_close();
                    switch_to_black_screen();
                    vTaskDelay(5000);
                    sleep_flag = 1;
                    globalData.flag_motor = 0;
                    esp_deep_sleep_start(); // 进入深度睡眠
                    break;
                }
            }
            if(sleep_flag == 0){
                duration = millis() - pressTime;
                if(duration <= 1000){
                    int curState = digitalRead(BL_PIN);
                    digitalWrite(BL_PIN, !curState);
                    if(globalData.flag_led == 0){
                        globalData.flag_led = 1;
                        led_close();
                    }
                    else{
                        globalData.flag_led = 0;
                        led_rainbow();
                        FastLED.show();
                    }
                }
                globalData.flag_motor = 0;
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
        lv_img_set_angle(ui_sec, gSecAngle);
        lv_img_set_angle(ui_sec_dot, gSecAngle);
        vTaskDelay(50);
    }
    
}

/* LVGL LED task */
static void task_LED(void *pt){
    while(1){
        switch (globalData.led_mode)
        {
        case 0:
            led_close();
            break;
        case 1:
            led_breath();
            break;
        case 2:
            led_stay();
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
        char time_str[5];
        int power = 0;
        uint32_t voltage = read_power();
        int voltage_state = get_charge_state() > 1500? 1:0;

        /* no charge state */
        if(voltage_state == 0){ 
            /* init the last power value */
            if(globalData.last_nocharge_value == 0){
                globalData.last_nocharge_value = voltage;
            }
            /* charge state change */
            if(globalData.flag_power == 2){
                lv_obj_add_flag(ui_imgCharge, LV_OBJ_FLAG_HIDDEN);
                vTaskDelay(100);  
                globalData.flag_power = 1;
                globalData.voltage_bias = voltage - globalData.last_charge_value;
                voltage -= globalData.voltage_bias;
            }else{
                voltage -= globalData.voltage_bias;
                globalData.voltage_bias -= globalData.voltage_bias/globalData.change_stay_count;
                if(voltage >= globalData.last_nocharge_value){
                    voltage = globalData.last_nocharge_value;
                }
            }
            globalData.last_nocharge_value = voltage;
            globalData.flag_power = 1;
        }
        /* charge state */
        else{
            /* init the last power value */
            if(globalData.last_charge_value == 0){
                globalData.last_charge_value = voltage;
            }
            /* charge state change */
            if(globalData.flag_power == 1){
                lv_obj_clear_flag(ui_imgCharge, LV_OBJ_FLAG_HIDDEN);
                vTaskDelay(100);  
                globalData.flag_power = 2;
                globalData.voltage_bias = voltage - globalData.last_nocharge_value;
                voltage -= globalData.voltage_bias;
            }else{
                voltage -= globalData.voltage_bias;
                globalData.voltage_bias -= globalData.voltage_bias/globalData.change_stay_count;
                if(voltage <= globalData.last_charge_value){
                    voltage = globalData.last_charge_value;
                }
            }
            globalData.last_charge_value = voltage;
            globalData.flag_power = 2;
        }

        if(voltage >= POWER_MAX){
                power = 100;
                lv_label_set_text(ui_labPower, "100%");
            }
            else if(voltage <= POWER_MIN){
                power = 0;
                lv_label_set_text(ui_labPower, "0%");
            }
            else{
                power = (voltage-POWER_MIN) * 100 / (POWER_MAX-POWER_MIN);
                
                sprintf(time_str, "%02d", power);
                time_str[2] = '%';
                time_str[3] = '\0';
                lv_label_set_text(ui_labPower, time_str);
        }
        if(power < 20){
            lv_obj_set_style_text_color(ui_labPower, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        else{
            lv_obj_set_style_text_color(ui_labPower, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        // sprintf(time_str, "%04d", voltage);
        // lv_label_set_text(ui_labDate, time_str);
        vTaskDelay(1000);  
    }
}

/* finger task */
static void task_finger(void *pt) {
    while (1) {
        if (globalData.flag_finger == 1) {
            // 认证指纹
            vTaskDelay(100);
            if(digitalRead(PIN_FINGER_TOUCH) == HIGH){
                Serial.println("finger task!");
                int8_t result = finger_identify();
                if (result == 1) {
                    Serial.println("指纹认证成功");
                } else {
                    Serial.println("指纹认证失败");
                }
                // 放置手指长时间放置多次触发
                vTaskDelay(1500);
                // 开启指纹休眠
                finger_sleep();
            }

            // 重置标志位
            globalData.flag_finger = 0;
            attachInterrupt(digitalPinToInterrupt(PIN_FINGER_TOUCH), interrupt_finger_handler, RISING);
        }
        
        vTaskDelay(10);  // 延时100毫秒
    }
}

/* encoder task */
static void task_encoder(void *pt){
    while(1){
        if(globalData.flag_encoder == 1){
            globalData.flag_encoder = 0;
            int64_t count = read_encoder_count();
            Serial.printf("ENCORDER COUNT: %d\n", count);
        }
        vTaskDelay(10);
    }
}

