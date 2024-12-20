// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_scrWatch2_screen_init(void)
{
    ui_scrWatch2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_scrWatch2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_scrWatch2, &ui_img_background2_240_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_imgCharge2 = lv_img_create(ui_scrWatch2);
    lv_img_set_src(ui_imgCharge2, &ui_img_flash_png);
    lv_obj_set_width(ui_imgCharge2, LV_SIZE_CONTENT);   /// 13
    lv_obj_set_height(ui_imgCharge2, LV_SIZE_CONTENT);    /// 18
    lv_obj_set_x(ui_imgCharge2, -1);
    lv_obj_set_y(ui_imgCharge2, -102);
    lv_obj_set_align(ui_imgCharge2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_imgCharge2, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_imgCharge2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_imgCharge2, 180);

    ui_labPower2 = lv_label_create(ui_scrWatch2);
    lv_obj_set_width(ui_labPower2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_labPower2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_labPower2, -1);
    lv_obj_set_y(ui_labPower2, 98);
    lv_obj_set_align(ui_labPower2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_labPower2, "86%");
    lv_obj_set_style_text_font(ui_labPower2, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_red_bar3 = lv_img_create(ui_scrWatch2);
    lv_img_set_src(ui_red_bar3, &ui_img_btn_bg_1_png);
    lv_obj_set_width(ui_red_bar3, LV_SIZE_CONTENT);   /// 30
    lv_obj_set_height(ui_red_bar3, LV_SIZE_CONTENT);    /// 40
    lv_obj_set_x(ui_red_bar3, 94);
    lv_obj_set_y(ui_red_bar3, -67);
    lv_obj_set_align(ui_red_bar3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_red_bar3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_red_bar3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_red_bar3, 157);

    ui_red_bar4 = lv_img_create(ui_scrWatch2);
    lv_img_set_src(ui_red_bar4, &ui_img_btn_bg_3_png);
    lv_obj_set_width(ui_red_bar4, LV_SIZE_CONTENT);   /// 30
    lv_obj_set_height(ui_red_bar4, LV_SIZE_CONTENT);    /// 41
    lv_obj_set_x(ui_red_bar4, 95);
    lv_obj_set_y(ui_red_bar4, 65);
    lv_obj_set_align(ui_red_bar4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_red_bar4, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_red_bar4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_red_bar4, 157);

    ui_imgWatch2Cloudy = lv_img_create(ui_scrWatch2);
    lv_img_set_src(ui_imgWatch2Cloudy, &ui_img_weather_cloud_png);
    lv_obj_set_width(ui_imgWatch2Cloudy, LV_SIZE_CONTENT);   /// 37
    lv_obj_set_height(ui_imgWatch2Cloudy, LV_SIZE_CONTENT);    /// 30
    lv_obj_set_x(ui_imgWatch2Cloudy, -27);
    lv_obj_set_y(ui_imgWatch2Cloudy, 40);
    lv_obj_set_align(ui_imgWatch2Cloudy, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_imgWatch2Cloudy, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_imgWatch2Cloudy, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_imgWatch2Cloudy, 200);

    ui_labTemp2 = lv_label_create(ui_scrWatch2);
    lv_obj_set_width(ui_labTemp2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_labTemp2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_labTemp2, -59);
    lv_obj_set_y(ui_labTemp2, 42);
    lv_obj_set_align(ui_labTemp2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_labTemp2, "25°");
    lv_obj_set_style_text_font(ui_labTemp2, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_labWeek2 = lv_label_create(ui_scrWatch2);
    lv_obj_set_width(ui_labWeek2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_labWeek2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_labWeek2, 46);
    lv_obj_set_y(ui_labWeek2, -56);
    lv_obj_set_align(ui_labWeek2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_labWeek2, "MON");

    ui_labDate2 = lv_label_create(ui_scrWatch2);
    lv_obj_set_width(ui_labDate2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_labDate2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_labDate2, 50);
    lv_obj_set_y(ui_labDate2, -33);
    lv_obj_set_align(ui_labDate2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_labDate2, "1 JULY");

    ui_labTimeHour2 = lv_label_create(ui_scrWatch2);
    lv_obj_set_width(ui_labTimeHour2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_labTimeHour2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_labTimeHour2, -73);
    lv_obj_set_y(ui_labTimeHour2, -34);
    lv_obj_set_align(ui_labTimeHour2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_labTimeHour2, "2");
    lv_obj_set_style_text_color(ui_labTimeHour2, lv_color_hex(0x393939), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_labTimeHour2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_labTimeHour2, &ui_font_Number_Large, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_labTimeHour1 = lv_label_create(ui_scrWatch2);
    lv_obj_set_width(ui_labTimeHour1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_labTimeHour1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_labTimeHour1, -10);
    lv_obj_set_y(ui_labTimeHour1, -33);
    lv_obj_set_align(ui_labTimeHour1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_labTimeHour1, "4");
    lv_obj_set_style_text_color(ui_labTimeHour1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_labTimeHour1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_labTimeHour1, &ui_font_Number_Large, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_labTimeMin = lv_label_create(ui_scrWatch2);
    lv_obj_set_width(ui_labTimeMin, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_labTimeMin, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_labTimeMin, 47);
    lv_obj_set_y(ui_labTimeMin, 36);
    lv_obj_set_align(ui_labTimeMin, LV_ALIGN_CENTER);
    lv_label_set_text(ui_labTimeMin, "27");
    lv_obj_set_style_text_color(ui_labTimeMin, lv_color_hex(0xFF0A0A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_labTimeMin, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_labTimeMin, &ui_font_Number_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_sec_dot = lv_img_create(ui_scrWatch2);
    lv_img_set_src(ui_sec_dot, &ui_img_sec_dot_png);
    lv_obj_set_width(ui_sec_dot, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_sec_dot, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_sec_dot, 0);
    lv_obj_set_y(ui_sec_dot, -190);
    lv_obj_set_align(ui_sec_dot, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_sec_dot, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_sec_dot, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_pivot(ui_sec_dot, 4, 194);
    lv_img_set_zoom(ui_sec_dot, 157);

    ui_imgWatch2Sunny = lv_img_create(ui_scrWatch2);
    lv_img_set_src(ui_imgWatch2Sunny, &ui_img_981806855);
    lv_obj_set_width(ui_imgWatch2Sunny, LV_SIZE_CONTENT);   /// 30
    lv_obj_set_height(ui_imgWatch2Sunny, LV_SIZE_CONTENT);    /// 30
    lv_obj_set_x(ui_imgWatch2Sunny, -29);
    lv_obj_set_y(ui_imgWatch2Sunny, 41);
    lv_obj_set_align(ui_imgWatch2Sunny, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_imgWatch2Sunny, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_imgWatch2Sunny, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_imgWatch2Rainy = lv_img_create(ui_scrWatch2);
    lv_img_set_src(ui_imgWatch2Rainy, &ui_img_dayu_png);
    lv_obj_set_width(ui_imgWatch2Rainy, LV_SIZE_CONTENT);   /// 30
    lv_obj_set_height(ui_imgWatch2Rainy, LV_SIZE_CONTENT);    /// 30
    lv_obj_set_x(ui_imgWatch2Rainy, -28);
    lv_obj_set_y(ui_imgWatch2Rainy, 43);
    lv_obj_set_align(ui_imgWatch2Rainy, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_imgWatch2Rainy, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_imgWatch2Rainy, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_imgWatch2Snow = lv_img_create(ui_scrWatch2);
    lv_img_set_src(ui_imgWatch2Snow, &ui_img_daxue_png);
    lv_obj_set_width(ui_imgWatch2Snow, LV_SIZE_CONTENT);   /// 30
    lv_obj_set_height(ui_imgWatch2Snow, LV_SIZE_CONTENT);    /// 30
    lv_obj_set_x(ui_imgWatch2Snow, -29);
    lv_obj_set_y(ui_imgWatch2Snow, 42);
    lv_obj_set_align(ui_imgWatch2Snow, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_imgWatch2Snow, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_imgWatch2Snow, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ArcPower2 = lv_arc_create(ui_scrWatch2);
    lv_obj_set_width(ui_ArcPower2, 231);
    lv_obj_set_height(ui_ArcPower2, 231);
    lv_obj_set_x(ui_ArcPower2, 8);
    lv_obj_set_y(ui_ArcPower2, -10);
    lv_obj_set_align(ui_ArcPower2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ArcPower2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_arc_set_value(ui_ArcPower2, 86);
    lv_arc_set_bg_angles(ui_ArcPower2, 88, 150);
    lv_arc_set_rotation(ui_ArcPower2, 20);
    lv_obj_set_style_arc_color(ui_ArcPower2, lv_color_hex(0x303030), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_ArcPower2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_ArcPower2, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_ArcPower2, lv_color_hex(0xB0E14A), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_ArcPower2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_ArcPower2, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui_ArcPower2, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_ArcPower2, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ArcPower2, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_dotWatch21 = lv_obj_create(ui_scrWatch2);
    lv_obj_set_width(ui_dotWatch21, 7);
    lv_obj_set_height(ui_dotWatch21, 7);
    lv_obj_set_x(ui_dotWatch21, 102);
    lv_obj_set_y(ui_dotWatch21, 6);
    lv_obj_set_align(ui_dotWatch21, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_dotWatch21, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_dotWatch21, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_dotWatch21, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dotWatch21, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_dotWatch21, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_dotWatch21, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dotWatch22 = lv_obj_create(ui_scrWatch2);
    lv_obj_set_width(ui_dotWatch22, 6);
    lv_obj_set_height(ui_dotWatch22, 6);
    lv_obj_set_x(ui_dotWatch22, 102);
    lv_obj_set_y(ui_dotWatch22, -6);
    lv_obj_set_align(ui_dotWatch22, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_dotWatch22, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_dotWatch22, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_dotWatch22, lv_color_hex(0x4A4A4A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dotWatch22, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_dotWatch22, lv_color_hex(0x4A4A4A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_dotWatch22, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_scrWatch2, ui_event_scrWatch2, LV_EVENT_ALL, NULL);

}
