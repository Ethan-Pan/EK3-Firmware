#include "interface.h"

int16_t gSecAngle = 0;
int16_t gMinAngle = 0;
int16_t gHourAngle = 0;

const char *g_connect_json = "{\"temp_cur\": 23.4, \"weather_hum\": 68, \"time_hour\": 19, \"time_min\": 45, \"time_sec\": 45, \"date_week\": 1, \"date_month\": 9, \"date_day\": 7}";

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
  gJsonData.temp_cur = doc["temp_cur"]; // 23.4
  gJsonData.weather_hum = doc["weather_hum"];
  gJsonData.time_hour = doc["time_hour"];
  gJsonData.time_min = doc["time_min"];
  gJsonData.time_sec = doc["time_sec"];

}

static void upDate_json(){
  /* time update */
  gSecAngle = gJsonData.time_sec * 60;
  gMinAngle = gJsonData.time_min * 60 + gJsonData.time_sec;
  gHourAngle = (gJsonData.time_hour - 12) * 300 + gJsonData.time_min * 5;
//   lv_img_set_angle(ui_hour, gHourAngle);
//   lv_img_set_angle(ui_min, gMinAngle);
//   lv_img_set_angle(ui_sec, gSecAngle);
}

