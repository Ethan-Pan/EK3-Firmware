#include "interface.h"

int16_t gSecAngle = 0;
int16_t gMinAngle = 0;
int16_t gHourAngle = 0;

void update_time(void);
void update_date(void);
void update_weather(void);
void update_location(void);
void update_basic_information(void);

/*
* weather_type:
* 0: 晴天
* 1: 多云
* 2: 雨
* 3: 雪
*/
const char *g_connect_json = "{"
    "\"user_name\": \"Ethan\","
    "\"weather_temp_cur\": 23,"
    "\"weather_temp_max\": 25,"
    "\"weather_temp_min\": 15,"
    "\"weather_hum\": 68,"
    "\"weather_type\": 0,"
    "\"time_hour\": 19,"
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


void connect_init(){
  read_json();
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
  gSecAngle = globalData.cur_time_sec * 60;
  gMinAngle = globalData.cur_time_min * 60 + globalData.cur_time_sec;
  gHourAngle = (globalData.cur_time_hour - 12) * 300 + globalData.cur_time_min * 5;
  lv_img_set_angle(ui_min, gMinAngle);
  lv_img_set_angle(ui_hour, gHourAngle);
  lv_img_set_angle(ui_sec, gSecAngle);
  char time_str[3];
  sprintf(time_str, "%02d", globalData.cur_time_min);
  lv_label_set_text(ui_labTimeMin, time_str);
  sprintf(time_str, "%01d", globalData.cur_time_hour%10);
  lv_label_set_text(ui_labTimeHour1, time_str);
  sprintf(time_str, "%01d", globalData.cur_time_hour/10);
  lv_label_set_text(ui_labTimeHour2, time_str);
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

