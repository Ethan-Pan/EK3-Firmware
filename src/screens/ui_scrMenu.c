// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_scrMenu_screen_init(void)
{
    ui_scrMenu = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_scrMenu, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_scrMenu, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scrMenu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_scrMenu, &ui_img_background_240_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel1 = lv_obj_create(ui_scrMenu);
    lv_obj_set_width(ui_Panel1, lv_pct(96));
    lv_obj_set_height(ui_Panel1, lv_pct(94));
    lv_obj_set_x(ui_Panel1, 20);
    lv_obj_set_y(ui_Panel1, 10);
    lv_obj_set_flex_flow(ui_Panel1, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Panel1, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);      /// Flags
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel1, lv_color_hex(0x060000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_Panel1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_border_color(ui_Panel1, lv_color_hex(0x000000), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel1, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_Panel1, lv_color_hex(0x000000), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_Panel1, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_Panel1, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    ui_Panel2 = lv_obj_create(ui_Panel1);
    lv_obj_set_width(ui_Panel2, lv_pct(88));
    lv_obj_set_height(ui_Panel2, lv_pct(39));
    lv_obj_set_x(ui_Panel2, 1);
    lv_obj_set_y(ui_Panel2, -100);
    lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Panel2, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Panel2, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0xEE2525), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PalWatch2 = lv_obj_create(ui_Panel2);
    lv_obj_set_width(ui_PalWatch2, lv_pct(118));
    lv_obj_set_height(ui_PalWatch2, lv_pct(114));
    lv_obj_set_x(ui_PalWatch2, -1);
    lv_obj_set_y(ui_PalWatch2, -30);
    lv_obj_set_align(ui_PalWatch2, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_PalWatch2, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_PalWatch2, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PalWatch2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_PalWatch2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PalWatch2, lv_color_hex(0x111717), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PalWatch2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_PalWatch2, lv_color_hex(0x2BD1EE), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_opa(ui_PalWatch2, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui_PalWatch2, 25, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_spread(ui_PalWatch2, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_Image11 = lv_img_create(ui_PalWatch2);
    lv_img_set_src(ui_Image11, &ui_img_yonghu_png);
    lv_obj_set_width(ui_Image11, LV_SIZE_CONTENT);   /// 24
    lv_obj_set_height(ui_Image11, LV_SIZE_CONTENT);    /// 24
    lv_obj_set_x(ui_Image11, 3);
    lv_obj_set_y(ui_Image11, 20);
    lv_obj_set_align(ui_Image11, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Image11, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_Image11, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_add_flag(ui_Image11, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image11, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label15 = lv_label_create(ui_PalWatch2);
    lv_obj_set_width(ui_Label15, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label15, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label15, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label15, "Ethan");
    lv_obj_set_style_text_font(ui_Label15, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PalMusic = lv_obj_create(ui_Panel1);
    lv_obj_set_width(ui_PalMusic, lv_pct(88));
    lv_obj_set_height(ui_PalMusic, lv_pct(25));
    lv_obj_set_x(ui_PalMusic, -1);
    lv_obj_set_y(ui_PalMusic, -30);
    lv_obj_set_align(ui_PalMusic, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_PalMusic, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_PalMusic, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PalMusic, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_PalMusic, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PalMusic, lv_color_hex(0x101410), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PalMusic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_PalMusic, lv_color_hex(0x2BD1EE), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_opa(ui_PalMusic, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui_PalMusic, 25, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_spread(ui_PalMusic, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_Image19 = lv_img_create(ui_PalMusic);
    lv_img_set_src(ui_Image19, &ui_img_yinyue_png);
    lv_obj_set_width(ui_Image19, LV_SIZE_CONTENT);   /// 24
    lv_obj_set_height(ui_Image19, LV_SIZE_CONTENT);    /// 24
    lv_obj_set_x(ui_Image19, 3);
    lv_obj_set_y(ui_Image19, 20);
    lv_obj_set_align(ui_Image19, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Image19, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_Image19, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_add_flag(ui_Image19, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image19, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label2 = lv_label_create(ui_PalMusic);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "音乐");
    lv_obj_set_style_text_font(ui_Label2, &ui_font_chinese, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PalWeather = lv_obj_create(ui_Panel1);
    lv_obj_set_width(ui_PalWeather, lv_pct(88));
    lv_obj_set_height(ui_PalWeather, lv_pct(25));
    lv_obj_set_x(ui_PalWeather, -1);
    lv_obj_set_y(ui_PalWeather, -30);
    lv_obj_set_align(ui_PalWeather, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_PalWeather, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_PalWeather, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PalWeather, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_PalWeather, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PalWeather, lv_color_hex(0x101410), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PalWeather, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_PalWeather, lv_color_hex(0x2BD1EE), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_opa(ui_PalWeather, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui_PalWeather, 25, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_spread(ui_PalWeather, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_Image12 = lv_img_create(ui_PalWeather);
    lv_img_set_src(ui_Image12, &ui_img_tianqi_new_png);
    lv_obj_set_width(ui_Image12, LV_SIZE_CONTENT);   /// 24
    lv_obj_set_height(ui_Image12, LV_SIZE_CONTENT);    /// 24
    lv_obj_set_x(ui_Image12, 3);
    lv_obj_set_y(ui_Image12, 20);
    lv_obj_set_align(ui_Image12, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Image12, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_Image12, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_add_flag(ui_Image12, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image12, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label9 = lv_label_create(ui_PalWeather);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label9, "天气");
    lv_obj_set_style_text_font(ui_Label9, &ui_font_chinese, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PalTimer = lv_obj_create(ui_Panel1);
    lv_obj_set_width(ui_PalTimer, lv_pct(88));
    lv_obj_set_height(ui_PalTimer, lv_pct(25));
    lv_obj_set_x(ui_PalTimer, -1);
    lv_obj_set_y(ui_PalTimer, -30);
    lv_obj_set_align(ui_PalTimer, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_PalTimer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_PalTimer, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PalTimer, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_PalTimer, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PalTimer, lv_color_hex(0x101410), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PalTimer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_PalTimer, lv_color_hex(0x2BD1EE), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_opa(ui_PalTimer, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui_PalTimer, 25, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_spread(ui_PalTimer, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_Image6 = lv_img_create(ui_PalTimer);
    lv_img_set_src(ui_Image6, &ui_img_jishiqi_png);
    lv_obj_set_width(ui_Image6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Image6, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image6, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label10 = lv_label_create(ui_PalTimer);
    lv_obj_set_width(ui_Label10, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label10, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label10, "计时器");
    lv_obj_set_style_text_font(ui_Label10, &ui_font_chinese, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PalTomato = lv_obj_create(ui_Panel1);
    lv_obj_set_width(ui_PalTomato, lv_pct(88));
    lv_obj_set_height(ui_PalTomato, lv_pct(25));
    lv_obj_set_x(ui_PalTomato, -1);
    lv_obj_set_y(ui_PalTomato, -30);
    lv_obj_set_align(ui_PalTomato, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_PalTomato, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_PalTomato, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PalTomato, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_PalTomato, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PalTomato, lv_color_hex(0x101410), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PalTomato, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_PalTomato, lv_color_hex(0x2BD1EE), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_opa(ui_PalTomato, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui_PalTomato, 25, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_spread(ui_PalTomato, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_Image7 = lv_img_create(ui_PalTomato);
    lv_img_set_src(ui_Image7, &ui_img_fanqie_new_png);
    lv_obj_set_width(ui_Image7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Image7, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image7, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label11 = lv_label_create(ui_PalTomato);
    lv_obj_set_width(ui_Label11, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label11, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label11, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label11, "番茄时钟");
    lv_obj_set_style_text_font(ui_Label11, &ui_font_chinese, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PalLight = lv_obj_create(ui_Panel1);
    lv_obj_set_width(ui_PalLight, lv_pct(88));
    lv_obj_set_height(ui_PalLight, lv_pct(25));
    lv_obj_set_x(ui_PalLight, -1);
    lv_obj_set_y(ui_PalLight, -30);
    lv_obj_set_align(ui_PalLight, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_PalLight, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_PalLight, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PalLight, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_PalLight, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PalLight, lv_color_hex(0x101410), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PalLight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_PalLight, lv_color_hex(0x2BD1EE), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_opa(ui_PalLight, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui_PalLight, 25, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_spread(ui_PalLight, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_Image9 = lv_img_create(ui_PalLight);
    lv_img_set_src(ui_Image9, &ui_img_caihong_png);
    lv_obj_set_width(ui_Image9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Image9, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image9, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image9, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label12 = lv_label_create(ui_PalLight);
    lv_obj_set_width(ui_Label12, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label12, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label12, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label12, "灯效设置");
    lv_obj_set_style_text_font(ui_Label12, &ui_font_chinese, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PalUpdate = lv_obj_create(ui_Panel1);
    lv_obj_set_width(ui_PalUpdate, lv_pct(88));
    lv_obj_set_height(ui_PalUpdate, lv_pct(25));
    lv_obj_set_x(ui_PalUpdate, -1);
    lv_obj_set_y(ui_PalUpdate, -30);
    lv_obj_set_align(ui_PalUpdate, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_PalUpdate, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_PalUpdate, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PalUpdate, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_PalUpdate, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PalUpdate, lv_color_hex(0x111717), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PalUpdate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_PalUpdate, lv_color_hex(0x2BD1EE), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_opa(ui_PalUpdate, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui_PalUpdate, 25, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_spread(ui_PalUpdate, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_Image4 = lv_img_create(ui_PalUpdate);
    lv_img_set_src(ui_Image4, &ui_img_1051555317);
    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);   /// 24
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT);    /// 24
    lv_obj_set_x(ui_Image4, 3);
    lv_obj_set_y(ui_Image4, 20);
    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Image4, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_Image4, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image4, 300);

    ui_Label3 = lv_label_create(ui_PalUpdate);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "系统更新");
    lv_obj_set_style_text_font(ui_Label3, &ui_font_chinese, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel3 = lv_obj_create(ui_Panel1);
    lv_obj_set_width(ui_Panel3, lv_pct(88));
    lv_obj_set_height(ui_Panel3, lv_pct(25));
    lv_obj_set_x(ui_Panel3, 93);
    lv_obj_set_y(ui_Panel3, 26);
    lv_obj_set_align(ui_Panel3, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Panel3, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_Panel3, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_Panel3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Panel3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_PalWatch2, ui_event_PalWatch2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PalMusic, ui_event_PalMusic, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PalWeather, ui_event_PalWeather, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PalTimer, ui_event_PalTimer, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PalTomato, ui_event_PalTomato, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PalLight, ui_event_PalLight, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PalUpdate, ui_event_PalUpdate, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_scrMenu, ui_event_scrMenu, LV_EVENT_ALL, NULL);

}
