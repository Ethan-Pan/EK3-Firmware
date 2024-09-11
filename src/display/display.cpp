#include "display.h"

CST816S touch(21, 22, 5, 32); // SDA SCL RST INT        
TFT_eSPI tft = TFT_eSPI();
static lv_disp_draw_buf_t draw_buf;    //定义显示器变量
static lv_disp_drv_t disp_drv;
static lv_color_t* buf = nullptr;
static lv_color_t* buf2 = nullptr;
static lv_color_t *bufPtr = buf2;
bool bufFlag = 0;

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
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

void dis_init(){
    buf = (lv_color_t*) ps_malloc(TFT_WIDTH * TFT_WIDTH * 2);
    buf2 = (lv_color_t*) ps_malloc(TFT_WIDTH * TFT_WIDTH * 2);

    if (buf != NULL) {
        Serial.printf("Hello, buf PSRAM!"); // 确保buffer非NULL后再使用
    } else {
        Serial.printf("buf PSRAM failed!");
    }
    if (buf2 != NULL) {
        Serial.printf("Hello, buf2 PSRAM!"); // 确保buffer非NULL后再使用
    } else {
        Serial.printf("buf2 PSRAM failed!");
    }
    tft.init();         //初始化
    //tft.initDMA();
    tft.setRotation(0); //屏幕旋转方向（横向）
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

}