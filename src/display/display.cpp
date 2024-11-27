#include "display.h"

CST816S touch(21, 22, 5, 32); // SDA SCL RST INT        
TFT_eSPI tft = TFT_eSPI();
static lv_disp_draw_buf_t draw_buf;    //定义显示器变量
static lv_disp_drv_t disp_drv;
static lv_color_t* buf = nullptr;
static lv_color_t* buf2 = nullptr;
static lv_color_t *bufPtr = buf2;
bool bufFlag = 0;

Ticker screenOffTimer;

// 定义PWM通道、频率、分辨率、定时器和输出引脚
#define LEDC_CHANNEL   0
#define LEDC_TIMER     LEDC_TIMER_0
#define LEDC_MODE      LEDC_HIGH_SPEED_MODE
#define LEDC_OUTPUT_IO 19 // 使用IO19
#define LEDC_FREQUENCY 1000 // 频率1kHz
#define LEDC_RESOLUTION LEDC_TIMER_8_BIT // 8位分辨率
#define BACKLIGHT_PIN 19

void turnOffScreen(void);
void turnOnScreen(void);

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite(); 

    /* 通知LVGL绘图操作已完成 */
    lv_disp_flush_ready(disp);
}
 
 /*Read the touchpad该函数是修改过的，适配CST816D驱动*/
void my_touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data )
{
  if (touch.available())
  {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = touch.data.x;
    data->point.y = touch.data.y;

    // 点亮屏幕
    if(gJsonData.power_deep_save == 1){ // 如果开启深度休眠
        turnOnScreen();
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

void dis_init(){
    buf = (lv_color_t*) ps_malloc(TFT_WIDTH * TFT_WIDTH * 2);
    buf2 = (lv_color_t*) ps_malloc(TFT_WIDTH * TFT_WIDTH * 2);
    tft.init();         //初始化
    tft.setRotation(0); //屏幕旋转方向（横向）
    tft.fillScreen(TFT_BLACK);   // 清屏,以避免重启时载入TFT缓存
    delay(100);
    touch.begin();
    
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf, buf2, TFT_WIDTH * TFT_WIDTH); 
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);
    // 设定定时器 10s后关闭屏幕
    if(gJsonData.power_deep_save == 1){ // 如果开启深度休眠
        screenOffTimer.attach(10, turnOffScreen);
    }

    // 配置LED PWM功能
    ledcSetup(LEDC_CHANNEL, LEDC_FREQUENCY, LEDC_RESOLUTION);
    // 将PWM通道附加到GPIO引脚
    ledcAttachPin(LEDC_OUTPUT_IO, LEDC_CHANNEL);
    // 设置占空比为50%
    ledcWrite(LEDC_CHANNEL, 128); // 8位分辨率，最大值为255，50%占空比为128, 高亮是0，全灭是255
    digitalWrite(BACKLIGHT_PIN, LOW); // 打开背光
}

void turnOffScreen(){
  ledcWrite(LEDC_CHANNEL, 255);
  // tft.writecommand(0x10);
  // tft.endWrite();
  // screenOffTimer.detach();
}

void turnOnScreen(){
  ledcWrite(LEDC_CHANNEL, 128);
  // tft.writecommand(0x29); // 打开显示
  // tft.begin(); // 重新初始化TFT屏幕
  // screenOffTimer.attach(10, turnOffScreen); // 重新设置定时器
}