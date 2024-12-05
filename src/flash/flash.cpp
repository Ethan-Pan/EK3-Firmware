#include "flash.h"

int16_t gSecAngle = 0;
int16_t gMinAngle = 0;
int16_t gHourAngle = 0;

void update_time(void);
void update_date(void);
void update_weather(void);
void update_location(void);
void update_basic_information(void);
void serialEvent(void);
void update_config(char* receiveData, int length);
void clear_config(void);
int config_check(void);
void config_init(void);
static void load_config(void);
void config_query(void);

/* Preferences about flash */
Preferences preferences;

/*
* weather_type:
* 0: 晴天
* 1: 多云
* 2: 雨
* 3: 雪
*/
const char *g_connect_json = "{"
    "\"user_name\": \"EK3\","
    "\"weather_temp_cur\": 23,"
    "\"weather_temp_max\": 25,"
    "\"weather_temp_min\": 15,"
    "\"weather_hum\": 68,"
    "\"weather_type\": 0,"
    "\"time_hour\": 12,"
    "\"time_min\": 45,"
    "\"time_sec\": 45,"
    "\"date_week\": 3,"
    "\"date_month\": 10,"
    "\"date_day\": 5,"
    "\"location\": \"SHEN ZHEN\","
    "\"led_state\": 2"
"}";

JsonDataStru gJsonData = {0};

static void read_json(void);
static void upDate_json(void);
static void update_weather_data(char* receiveData);
void config_update(void);


void config_init(){
  preferences.begin("ek3", false);  // create a flash area named ek3
  globalData.flag_config = config_check();
  if(globalData.flag_config == 1){  
      read_json();
      Serial.printf("flag_config: %d\n", globalData.flag_config);
      load_config();
  }
}

void config_update(){
  upDate_json();
}

static void read_json(){
  // 分配JsonDocument的空间
  JsonDocument doc;
  // 反序列化JSON数据
  DeserializationError error = deserializeJson(doc, g_connect_json);
  if (error) {
    Serial.print(F("deserializeJson() 失败: "));
    Serial.println(error.c_str());
    return;
  }

  // 从json中提取值
  gJsonData.temp_cur = doc["weather_temp_cur"]; 
  gJsonData.weather_hum = doc["weather_hum"];
  gJsonData.weather_type = doc["weather_type"];
  gJsonData.temp_max = doc["weather_temp_max"];
  gJsonData.temp_min = doc["weather_temp_min"];
  gJsonData.time_hour = doc["time_hour"];
  gJsonData.time_min = doc["time_min"];
  gJsonData.time_sec = doc["time_sec"];
  gJsonData.date_week = doc["date_week"];
  gJsonData.date_month = doc["date_month"];
  gJsonData.date_day = doc["date_day"];
  gJsonData.led_state = doc["led_state"];
  globalData.led_mode = gJsonData.led_state;
  globalData.cur_time_hour = gJsonData.time_hour;
  globalData.cur_time_min = gJsonData.time_min;
  globalData.cur_time_sec = gJsonData.time_sec;
  // 从JSON中获取location字符串并赋值给gJsonData.location
  const char* locationStr = doc["location"];
  strncpy(gJsonData.location, locationStr, sizeof(gJsonData.location)-1);
  gJsonData.location[sizeof(gJsonData.location)-1] = '\0';  // 确保字符串以null结尾
  const char* user_name = doc["user_name"];
  strncpy(gJsonData.user_name, user_name, sizeof(gJsonData.user_name)-1);
  gJsonData.user_name[sizeof(gJsonData.user_name)-1] = '\0';  // 确保字符串以null结尾
}

/* load config from flash */
static void load_config(){
    /* load user name */
    String userName = preferences.getString("user_name", "");
    strncpy(gJsonData.user_name, userName.c_str(), sizeof(gJsonData.user_name)-1);
    gJsonData.user_name[sizeof(gJsonData.user_name)-1] = '\0';  
    /* load location */
    String location = preferences.getString("location", "");
    strncpy(gJsonData.location, location.c_str(), sizeof(gJsonData.location)-1);
    gJsonData.location[sizeof(gJsonData.location)-1] = '\0';  
    /* load power_show  */ 
    gJsonData.power_show = preferences.getInt("power_show", 0);
    /* load encoder */
    gJsonData.encoder = preferences.getInt("encoder", 0);
    /* load color */
    String color = preferences.getString("color", "");
    strncpy(gJsonData.color, color.c_str(), sizeof(gJsonData.color)-1);
    gJsonData.color[sizeof(gJsonData.color)-1] = '\0';  
    /* load power_save_start */
    String power_save_start = preferences.getString("power_save_st", "");
    strncpy(gJsonData.power_save_start, power_save_start.c_str(), sizeof(gJsonData.power_save_start)-1);
    gJsonData.power_save_start[sizeof(gJsonData.power_save_start)-1] = '\0';  
    char hour_str[3] = {0};
    char min_str[3] = {0};
    strncpy(hour_str, gJsonData.power_save_start, 2);
    strncpy(min_str, gJsonData.power_save_start + 3, 2);
    gJsonData.power_start_hour = atoi(hour_str);
    gJsonData.power_start_min = atoi(min_str);
    /* load power_save_end */
    String power_save_end = preferences.getString("power_save_end", "");
    strncpy(gJsonData.power_save_end, power_save_end.c_str(), sizeof(gJsonData.power_save_end)-1);
    gJsonData.power_save_end[sizeof(gJsonData.power_save_end)-1] = '\0';  
    strncpy(hour_str, gJsonData.power_save_end, 2);
    strncpy(min_str, gJsonData.power_save_end + 3, 2);
    gJsonData.power_end_hour = atoi(hour_str);
    gJsonData.power_end_min = atoi(min_str);
    /* load power_deep_save  */
    gJsonData.power_deep_save = preferences.getInt("power_deep_save", 0);
    /* load finger_pin */
    String finger_pin = preferences.getString("finger_pin", "");
    strncpy(gJsonData.finger_pin, finger_pin.c_str(), sizeof(gJsonData.finger_pin)-1);
    gJsonData.finger_pin[sizeof(gJsonData.finger_pin)-1] = '\0';  
    /* load x_mode */  
    gJsonData.x_mode = preferences.getInt("x_mode", 0);
    /* load x_input */
    String x_input = preferences.getString("x_input", "");
    strncpy(gJsonData.x_input, x_input.c_str(), sizeof(gJsonData.x_input)-1);
    gJsonData.x_input[sizeof(gJsonData.x_input)-1] = '\0';  
    /* load update_flag */
    gJsonData.update_flag = preferences.getInt("update_flag", 0);
    /* load connect_flag */
    gJsonData.connect_flag = preferences.getInt("connect_flag", 0);
    // /* load wifi_ssid */ 
    // String wifi_ssid = preferences.getString("wifi_ssid", "");
    // strncpy(gJsonData.wifi_ssid, wifi_ssid.c_str(), sizeof(gJsonData.wifi_ssid)-1);
    // gJsonData.wifi_ssid[sizeof(gJsonData.wifi_ssid)-1] = '\0';  
    // /* load wifi_password */
    // String wifi_password = preferences.getString("wifi_password", "");
    // strncpy(gJsonData.wifi_password, wifi_password.c_str(), sizeof(gJsonData.wifi_password)-1);
    // gJsonData.wifi_password[sizeof(gJsonData.wifi_password)-1] = '\0';  
}

static void upDate_json(){
  /* time update */
  update_time();
  /* date update */
  update_date();
  /* weather update */
  update_weather();
  /* location update */
  update_location();
  /* basic information update */
  update_basic_information();
}

void update_time(){
  globalData.cur_time_hour = gJsonData.time_hour;
  globalData.cur_time_min = gJsonData.time_min;
  globalData.cur_time_sec = gJsonData.time_sec;
  gSecAngle = globalData.cur_time_sec * 60;
  gMinAngle = globalData.cur_time_min * 60 + globalData.cur_time_sec;
  gHourAngle = (globalData.cur_time_hour - 12) * 300 + globalData.cur_time_min * 5;
  lv_img_set_angle(ui_min, gMinAngle);
  lv_img_set_angle(ui_hour, gHourAngle);
  lv_img_set_angle(ui_sec, gSecAngle);
  char time_str[3];
  sprintf(time_str, "%02d", globalData.cur_time_min);
  lv_label_set_text(ui_labTimeMin, time_str);
  lv_label_set_text(ui_labMusicMin, time_str);
  sprintf(time_str, "%01d", globalData.cur_time_hour%10);
  lv_label_set_text(ui_labTimeHour1, time_str);
  sprintf(time_str, "%01d", globalData.cur_time_hour/10);
  lv_label_set_text(ui_labTimeHour2, time_str);
  sprintf(time_str, "%02d", globalData.cur_time_hour);
  lv_label_set_text(ui_labMusicHour, time_str);
}

void update_date(){
  const char* week[8] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT","SUN"};
  const char* month[13] = {"", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
  /* week */
  char date_str[5];
  sprintf(date_str, "%s", week[gJsonData.date_week]);
  lv_label_set_text(ui_labWeek, date_str);
  lv_label_set_text(ui_labWeek2, date_str);
  /* day and month */
  char date_str2[5];
  sprintf(date_str2, "%d %s", gJsonData.date_day, month[gJsonData.date_month]);
  lv_label_set_text(ui_labDate, date_str2);
  lv_label_set_text(ui_labDate2, date_str2);
  char date_str3[20];
  const char* week_str[8] = {"SUN", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
  sprintf(date_str3, "%02d %02d %s", gJsonData.date_month, gJsonData.date_day, week_str[gJsonData.date_week]);
  lv_label_set_text(ui_labWeatherDate, date_str3);

}

void update_weather(){
/* current temperature */
  char weather_str[10];
  sprintf(weather_str, "%02d°", gJsonData.temp_cur);
  lv_label_set_text(ui_labTemp, weather_str);
  lv_label_set_text(ui_labTemp2, weather_str);
  lv_label_set_text(ui_labWeatherTemp, weather_str);
  /* max and min temperature */
  char temp_str[20];
  sprintf(temp_str, "Max:%02d°Min:%02d°", gJsonData.temp_max, gJsonData.temp_min);
  lv_label_set_text(ui_labWeatherMaxmin, temp_str);
  // /* humidity */
  sprintf(weather_str, "%02d", gJsonData.weather_hum);
  weather_str[2] = '%';
  weather_str[3] = '\0';
  lv_label_set_text(ui_labWeatherHum, weather_str);
  int code = gJsonData.weather_type;
  if(code >= 0 && code <= 3){
    gJsonData.weather_type = 0;
  }else if(code >= 4 && code <= 9){
    gJsonData.weather_type = 1;
  }else if(code >= 10 && code <= 20){
    gJsonData.weather_type = 2;
  }else if(code >= 21 && code <= 25){
    gJsonData.weather_type = 3;
  }else if(code >= 30 && code <= 32){
    gJsonData.weather_type = 1;
  }else{
    gJsonData.weather_type = 4;
  }
  /* weather type */
  switch (gJsonData.weather_type)
  {
  case 0:
    lv_label_set_text(ui_labWeatherTianqi, "Sunny");
    lv_obj_add_flag(ui_imgWatch1Cloudy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch1Rainy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch1Snow, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch2Cloudy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch2Rainy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch2Snow, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWeatherCloudy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWeatherRainy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWeatherSnow, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_imgWatch1Sunny, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_imgWatch2Sunny, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_imgWeatherSunny, LV_OBJ_FLAG_HIDDEN);
    break;
  case 1:
    lv_label_set_text(ui_labWeatherTianqi, "Cloudy");
    lv_obj_add_flag(ui_imgWatch1Sunny, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch1Rainy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch1Snow, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch2Sunny, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch2Rainy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch2Snow, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWeatherSunny, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWeatherRainy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWeatherSnow, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_imgWatch1Cloudy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_imgWatch2Cloudy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_imgWeatherCloudy, LV_OBJ_FLAG_HIDDEN);
    break;
  case 2:
    lv_label_set_text(ui_labWeatherTianqi, "Rainy");
    lv_obj_add_flag(ui_imgWatch1Sunny, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch1Cloudy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch1Snow, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch2Sunny, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch2Cloudy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch2Snow, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWeatherSunny, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWeatherCloudy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWeatherSnow, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_imgWatch1Rainy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_imgWatch2Rainy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_imgWeatherRainy, LV_OBJ_FLAG_HIDDEN);
    break;
  case 3:
    lv_label_set_text(ui_labWeatherTianqi, "Snowy");
    lv_obj_add_flag(ui_imgWatch1Sunny, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch1Cloudy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch1Rainy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch2Sunny, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch2Cloudy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWatch2Rainy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWeatherSunny, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWeatherCloudy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgWeatherRainy, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_imgWatch1Snow, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_imgWatch2Snow, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_imgWeatherSnow, LV_OBJ_FLAG_HIDDEN);
    break;
  default:
    lv_label_set_text(ui_labWeatherTianqi, "Unknown");
    break;
  }
}

void update_location(){
  lv_label_set_text(ui_labWeatherArea, gJsonData.location);
}

void update_basic_information(){
  lv_label_set_text(ui_Label15, gJsonData.user_name);
}

/* Already config check */
int config_check(){
  if(preferences.getInt("init_flag", 0) == 0){
      return 0;
  }
  else{
    return 1;
  }
}

/* Clear config */
void clear_config(){
  preferences.putInt("init_flag", 0);
  preferences.clear();
}

/*
 * uart command list:
 * pc connect: r-#001$   s-$001#
 * finger add: r-#011$   s-$001#   s-$000#   r-01 for finger eroll r-1 for id; s-001 for sunccess and s-000 for error
 * finger del: r-#021$   s-$001#   s-$000#   r-02 for finger delete r-1 for id; s-001 for sunccess and s-000 for error
 * finger emp: r-#030$   s-$001#   s-$000#  s-001 for sunccess and s-000 for error
 * config cmd: r-#04xy$  s-$001#    s-001 for sunccess 
 *             x-0 for user name, 
 *             x-1 for location, 
 *             x-2 for power_show, 
 *             x-3 for encoder, 
 *             x-4 for color, 
 *             x-5 for power_save_start, 
 *             x-6 for power_save_end, 
 *             x-7 for power_deep_save, 
 *             x-8 for finger_pin, 
 *             x-9 for x_mode, 
 *             x-a for x_input
 *             x-b for update_flag
 *             x-c for connect_flag
 *             x-d for wifi_ssid
 *             x-e for wifi_password
 * flash quiry: r-#050$   s-$001#   s-001 for sunccess 
 * esp restart: r-#060$   s-$001#   s-001 for sunccess 
 * ble address: r-#070$   s-$001#   s-001 for sunccess 
 * config clr: r-#090$   s-$001#   s-001 for sunccess 
 *  
 */
void serialEvent() {
    char receivedString[512] = "";
    int count = 0;
    int id, flag;
    while (Serial.available()) {
            char c = Serial.read();
            receivedString[count] = c;
            count++;
    }

    if(receivedString[count-1] == '$' && receivedString[0] == '#'){
      switch (receivedString[2]){
        case '0':
          /* pc connect */
          Serial.print("$001#");  
          memset(receivedString, 0, sizeof(char)*512);
          if(globalData.flag_first_connect == 0){
            globalData.flag_first_connect = 1;
            lv_obj_add_flag(ui_labOpen, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_pannelOpen, LV_OBJ_FLAG_HIDDEN);
          }
          break;

        case '1':
          /* add finger */
          id = receivedString[3] - '0';
          detachInterrupt(digitalPinToInterrupt(PIN_FINGER_TOUCH));  // 关闭指纹中断以免影响指纹注册
          finger_power_on();
          flag = finger_enroll(id);
          if(flag == 1){
              Serial.print("$001#");  
          }
          else if(flag == 0){
              Serial.print("$000#");  
          }
          memset(receivedString, 0, sizeof(char)*512);
          finger_sleep();
          attachInterrupt(digitalPinToInterrupt(PIN_FINGER_TOUCH), interrupt_finger_handler, RISING); 
          break;
        
        case '2':
          /* delete finger */
          id = receivedString[3] - '0';
          finger_power_on();
          flag = finger_delete(id);
          if(flag == 1){
              Serial.printf("$001#");  
          }
          else{
              Serial.printf("$000#");  
          }
          memset(receivedString, 0, sizeof(char)*512);
          finger_sleep();
          break;
        case '3':
          /* empty finger */
          finger_power_on();
          flag = finger_empty();
          if(flag == 1){
              Serial.printf("$001#");  
          }
          else{
              Serial.printf("$000#");  
          }
          memset(receivedString, 0, sizeof(char)*512);
          finger_sleep();
          break;
        
        case '4':
          /* update config */
          update_config(receivedString, count);
          memset(receivedString, 0, sizeof(char)*512);
          Serial.printf("$001#");
          break;
        case '5':
          /* flash quiry */
          config_query();
          memset(receivedString, 0, sizeof(char)*512);
          Serial.printf("$001#");
          break;
        case '6':
          /* reset */
          ESP.restart();
          memset(receivedString, 0, sizeof(char)*512);
          Serial.printf("$001#");
          break;
        case '7':
          /* get ble address */
          memset(receivedString, 0, sizeof(char)*512);
          char bleAddress[18];
          get_ble_address(bleAddress);
          Serial.printf("BLE Address:%s", bleAddress);
          break;
        case '8':
          /* get weather data */
          update_weather_data(receivedString);
          memset(receivedString, 0, sizeof(char)*512);
          globalData.weather_update_state = 1;
          Serial.printf("$001#");
          break;
        case '9':
          /* clear config */
          clear_config();
          memset(receivedString, 0, sizeof(char)*512);
          Serial.printf("$001#");
          ESP.restart();
          break;
        case 'a':
          /* firmware update */
          if(receivedString[3] == '1'){
            globalData.flag_firmware_update = 1;
            strncpy(globalData.firmware_new_version, &receivedString[4], count-5);
            globalData.firmware_new_version[count-5] = '\0'; 
          }
          else if(receivedString[3] == '0'){
            globalData.flag_firmware_update = 0;
          }
          else if(receivedString[3] == '2'){
            globalData.ota_download_state = 2;    // download success
          }
          else if(receivedString[3] == '3'){
            globalData.ota_download_state = 3;    // download error
          }
          memset(receivedString, 0, sizeof(char)*512);
          Serial.printf("$001#");
          break;
        default:
          break;
      }
    }
}
void config_query(){
    /* print user name */
    Serial.println("用户名: " + String(gJsonData.user_name));
    /* print location */
    Serial.println("位置: " + String(gJsonData.location));
    /* print power show */
    Serial.println("电量显示: " + String(gJsonData.power_show));
    /* print encoder */
    Serial.println("编码器: " + String(gJsonData.encoder));
    /* print color */
    Serial.println("颜色: " + String(gJsonData.color));
    /* print power save start */
    Serial.println("省电开始时间: " + String(gJsonData.power_save_start));
    /* print power save end */
    Serial.println("省电结束时间: " + String(gJsonData.power_save_end));
    /* print power deep save */
    Serial.println("深度省电: " + String(gJsonData.power_deep_save));
    /* print finger pin */
    Serial.println("指纹PIN: " + String(gJsonData.finger_pin));
    /* print x mode */
    Serial.println("X模式: " + String(gJsonData.x_mode));
    /* print x input */
    Serial.println("X输入: " + String(gJsonData.x_input));
    /* print update flag */
    Serial.println("更新标志: " + String(gJsonData.update_flag));
    /* print connect flag */
    Serial.println("连接标志: " + String(gJsonData.connect_flag));
    /* print wifi ssid */
    Serial.println("WiFi SSID: " + String(gJsonData.wifi_ssid));
    /* print wifi password */
    Serial.println("WiFi密码: " + String(gJsonData.wifi_password));
}


static void update_weather_data(char* receiveData){
    char* str_copy = strndup(receiveData + 2, strlen(receiveData + 2) - 1);  // 创建字符串副本，从第三个字符开始，不包含最后一个字符$
    char* token;
    int numbers[20] = {0};  // 存储提取的数字
    int count = 0;

    // 跳过第一个#
    token = strchr(str_copy, '#');
    if(token != NULL) {
        token++; // 移到#后面的字符
        
        while(*token != '\0' && count < 20) {
            if(isdigit(*token)) {
                char numStr[10] = {0};
                int i = 0;
                // 收集连续的数字
                while(isdigit(*token)) {
                    numStr[i++] = *token++;
                }
                numbers[count++] = atoi(numStr);
            } else {
                token++; // 跳过非数字字符(如#)
            }
        }
    }

    free(str_copy);  // 释放内存
    gJsonData.temp_cur = numbers[0];
    gJsonData.weather_hum = numbers[1];
    gJsonData.weather_type = numbers[2];
    gJsonData.temp_max = numbers[3];
    gJsonData.temp_min = numbers[4];
    gJsonData.date_month = numbers[5];
    gJsonData.date_day = numbers[6];
    gJsonData.date_week = numbers[7];
    gJsonData.time_hour = numbers[8];
    gJsonData.time_min = numbers[9];
    gJsonData.time_sec = numbers[10];

    update_weather();
    update_time();
    update_date();
}


void update_config(char* receiveData, int length){
  switch (receiveData[3]){
    case '0': {  
      /* user name */
      int nameLen = length - 5; 
      strncpy(gJsonData.user_name, &receiveData[4], nameLen);
      gJsonData.user_name[nameLen] = '\0'; 
      preferences.putString("user_name", gJsonData.user_name);
      preferences.putInt("init_flag", 1);
      break;
    }
    case '1': {
      /* area_city */
      int cityLen = length - 5; 
      strncpy(gJsonData.location, &receiveData[4], cityLen);
      gJsonData.location[cityLen] = '\0'; 
      preferences.putString("location", gJsonData.location);
      break;
    }
    case '2': {
      /* power_show */
      gJsonData.power_show = receiveData[4] - '0';
      preferences.putInt("power_show", gJsonData.power_show);
      break;
    }
    case '3': {
      /* encoder */
      gJsonData.encoder = receiveData[4] - '0';
      preferences.putInt("encoder", gJsonData.encoder);
      break;
    }
    case '4': {
      /* color */
      int colorLen = length - 5;
      strncpy(gJsonData.color, &receiveData[4], colorLen);
      gJsonData.color[colorLen] = '\0';
      preferences.putString("color", gJsonData.color);
      break;
    }
    case '5': {
      /* power_save_start */
      int startLen = length - 5;
      strncpy(gJsonData.power_save_start, &receiveData[4], startLen);
      gJsonData.power_save_start[startLen] = '\0';
      preferences.putString("power_save_st", gJsonData.power_save_start);
      break;
    }
    case '6': {
      /* power_save_end */
      int endLen = length - 5;
      strncpy(gJsonData.power_save_end, &receiveData[4], endLen);
      gJsonData.power_save_end[endLen] = '\0';
      preferences.putString("power_save_end", gJsonData.power_save_end);
      break;
    }
    case '7': {
      /* power_deep_save */
      gJsonData.power_deep_save = receiveData[4] - '0';
      preferences.putInt("power_deep_save", gJsonData.power_deep_save);
      break;
    }
    case '8': {
      /* finger_pin */
      int pinLen = length - 5;
      strncpy(gJsonData.finger_pin, &receiveData[4], pinLen);
      gJsonData.finger_pin[pinLen] = '\0';
      preferences.putString("finger_pin", gJsonData.finger_pin);
      break;
    }
    case '9': {
      /* x_mode */
      gJsonData.x_mode = receiveData[4] - '0';
      preferences.putInt("x_mode", gJsonData.x_mode);
      break;
    }
    case 'a': {
      /* x_input */
      int inputLen = length - 5;
      strncpy(gJsonData.x_input, &receiveData[4], inputLen);
      gJsonData.x_input[inputLen] = '\0';
      preferences.putString("x_input", gJsonData.x_input);
      break;
    }
    case 'b': {
      /* update_flag */
      gJsonData.update_flag = receiveData[4] - '0';
      preferences.putInt("update_flag", gJsonData.update_flag);
      break;
    }
    case 'c': {
      /* connect_flag */
      gJsonData.connect_flag = receiveData[4] - '0';
      preferences.putInt("connect_flag", gJsonData.connect_flag);
      break;
    }
    case 'd': {
      /* wifi_ssid */
      int ssidLen = length - 5;
      strncpy(gJsonData.wifi_ssid, &receiveData[4], ssidLen);
      gJsonData.wifi_ssid[ssidLen] = '\0';
      preferences.putString("wifi_ssid", gJsonData.wifi_ssid);
      break;
    }
    case 'e': {
      /* wifi_password */
      int passwordLen = length - 5;
      strncpy(gJsonData.wifi_password, &receiveData[4], passwordLen);
      gJsonData.wifi_password[passwordLen] = '\0';
      preferences.putString("wifi_password", gJsonData.wifi_password);
      break;
    }
    default:
      break;
  }
}
