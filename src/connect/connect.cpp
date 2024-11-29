#include "connect.h"

void connect_init(void){
    if(globalData.flag_config == 1 && gJsonData.connect_flag == 1){
        ble_keyboard_init();
    }
    /* BLE */
    if(globalData.flag_config == 1 && gJsonData.connect_flag == 2){
        ble_init();
    }
}


/* 串口发送指令获取天气数据 */
void send_weather_update(void){
    Serial.printf("AT+WEATHER=1");
}


/* 串口发送指令当前版本号 */
void send_version(void){
    Serial.printf("AT+VERSION=%s", globalData.firmware_cur_version);
}


/* 串口发送指令开启更新 */
void send_update_start(void){
    Serial.printf("AT+UPDATE=1");
}

/* 串口发送指令开启下载 */
void send_update_download(void){
    Serial.printf("AT+DOWNLOAD=1");
}

/* 串口发送指令检查连接状态 */
void send_check_connect(void){
    Serial.printf("AT+CONNECT=1");
}
