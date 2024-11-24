#include "wifi.h"

// // WiFi credentials
// const char* ssid = "";
// const char* password = "";

// // NTP server to request epoch time
// const char* ntpServer = "pool.ntp.org";
// const long utcOffsetInSeconds = 28800; // UTC+8 for Shenzhen

// // Unix timestamp
// unsigned long epochTime;

// // NTP Client
// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, ntpServer, utcOffsetInSeconds);

// // Weather API
// const char* weatherApiKey = "SIRIAINjNneIGVRpR";
// char weatherLocation[10] = "shenzhen";
// const char location[5][11] = {"Shen Zhen", "Dong Guan", "Guang Zhou", "Hui Zhou", "Zhong Shan"};
// const char locationCode[5][11] = {"shenzhen", "dongguan", "guangzhou", "huizhou", "zhongshan"};

// int check_wifi_connect(void);

// void wifi_init(void){
//     /* GET WIFI INFO */
//     ssid = gJsonData.wifi_ssid;
//     password = gJsonData.wifi_password;
//     /* connect to wifi  */
//     // WiFi初始化
//     WiFi.begin(ssid, password);
    
//     // 等待连接，但设置超时
//     uint8_t timeout = 0;
//     while (WiFi.status() != WL_CONNECTED && timeout < 10) {
//         vTaskDelay(300);
//         Serial.print(".");
//         timeout++;
//     }
    
//     if (WiFi.status() != WL_CONNECTED) {
//         Serial.println("WiFi connect failed");
//         globalData.flag_wifi_connect = 0;
//     }else{
//         Serial.println("WiFi connect success");
//         globalData.flag_wifi_connect = 1;
//         timeClient.begin();
//         timeClient.setUpdateInterval(60000); // Update every minute
//     }
// }

// int check_wifi_connect(void){
//     // 如果已经连接，直接返回1
//     if (WiFi.status() == WL_CONNECTED) {
//         return 1;
//     }

//     /* GET WIFI INFO */
//     ssid = gJsonData.wifi_ssid;
//     password = gJsonData.wifi_password;
//     // 如果未连接，尝试重新连接
//     WiFi.begin(ssid, password);
    
//     // 等待3秒尝试连接
//     uint8_t timeout = 0;
//     while (WiFi.status() != WL_CONNECTED && timeout < 10) {
//         delay(300);
//         Serial.print(".");
//         timeout++;
//     }
    
//     // 检查连接结果
//     if (WiFi.status() != WL_CONNECTED) {
//         Serial.println("WiFi connect failed");
//         globalData.flag_wifi_connect = 0;
//         return 0;
//     } else {
//         Serial.println("WiFi connect success"); 
//         globalData.flag_wifi_connect = 1;
//         return 1;
//     }
// }


// void update_clock(void){
//     static uint8_t retryCount = 0;
//     const uint8_t MAX_RETRIES = 3;

//     do{
//         timeClient.update();
//         epochTime = timeClient.getEpochTime();
//         retryCount++;
//     }while(epochTime < 1672531200 && retryCount < MAX_RETRIES);

//     // 转换时间
//     struct tm *ptm = gmtime((time_t *)&epochTime);
//     if (ptm == nullptr) {
//         Serial.println("时间转换失败");
//         return;
//     }

//     // 更新时间数据
//     gJsonData.date_day = ptm->tm_mday;
//     gJsonData.date_month = ptm->tm_mon + 1;
//     globalData.cur_time_hour = ptm->tm_hour;
//     globalData.cur_time_sec = ptm->tm_sec;
//     globalData.cur_time_min = ptm->tm_min;
//     gJsonData.date_week = ptm->tm_wday;

// }   

// void update_weather_data(void){
//     if (WiFi.status() == WL_CONNECTED) {
//         for(int i = 0; i < sizeof(location)/sizeof(location[0]); i++) {
//             if(strcmp(gJsonData.location, location[i]) == 0) {
//                 strcpy(weatherLocation, locationCode[i]);
//                 break;
//             }
//         }
//         HTTPClient http;
//         String url = String("https://api.seniverse.com/v3/weather/now.json?key=") + String(weatherApiKey) + String("&location=") + String(weatherLocation) + String("&language=zh-Hans&unit=c");
//         http.begin(url);
//         int httpCode = http.GET();

//         if (httpCode > 0) {
//             String payload = http.getString();
            
//             StaticJsonDocument<1024> doc;
//             DeserializationError error = deserializeJson(doc, payload);
//             if (error) {
//                 Serial.print(F("deserializeJson() failed: "));
//                 Serial.println(error.c_str());
//                 return;
//             }   
            
//             // 正确访问嵌套的JSON结构
//             JsonObject now = doc["results"][0]["now"];
//             int temp = now["temperature"].as<int>();
//             int humidity = now["humidity"].as<int>();
//             int code = now["code"].as<int>();
//             gJsonData.temp_cur = temp;
//             gJsonData.weather_hum = humidity;
//             Serial.printf("温度: %d°C\n", temp);
//             Serial.printf("湿度: %d%%\n", humidity); 
//             Serial.printf("天气: %d\n", code);
//             if(code >= 0 && code <= 3){
//                 gJsonData.weather_type = 0;
//             }else if(code >= 4 && code <= 9){
//                 gJsonData.weather_type = 1;
//             }else if(code >= 10 && code <= 20){
//                 gJsonData.weather_type = 2;
//             }else if(code >= 21 && code <= 25){
//                 gJsonData.weather_type = 3;
//             }else{
//                 gJsonData.weather_type = 4;
//             }
            
//         } else {
//             Serial.printf("GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
//         }
//         http.end();
//         String url2 = String("https://api.seniverse.com/v3/weather/daily.json?key=") + String(weatherApiKey) + String("&location=") + String(weatherLocation) + String("&language=zh-Hans&unit=c&start=0&days=5");
//         http.begin(url2);
//         httpCode = http.GET();

//         if (httpCode > 0) {
//             String payload = http.getString();
//             StaticJsonDocument<2048> doc;
//             DeserializationError error = deserializeJson(doc, payload);
//             if (error) {
//                 Serial.print(F("deserializeJson() failed: "));
//                 Serial.println(error.c_str());
//                 return;
//             }   
//             // 正确访问嵌套的JSON结构
//               // 提取daily数组中第一天的high和low值
//             int high = doc["results"][0]["daily"][0]["high"].as<int>();
//             int low = doc["results"][0]["daily"][0]["low"].as<int>();
//             gJsonData.temp_max = high;
//             gJsonData.temp_min = low;
//             Serial.printf("最高温度: %d°C\n", high);
//             Serial.printf("最低温度: %d°C\n", low);

//             update_weather();

//         } else {
//             Serial.printf("GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
//         }
//         http.end();
//     }
// }

