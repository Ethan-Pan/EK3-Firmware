#include "ui_events.h"

/* create a black screen */
lv_obj_t *black_screen;

static void ui_event_timer_init();
static void ui_event_tomato_init();
static void ui_event_scr_timer_click(lv_event_t *e);
static void ui_event_scr_tomato_click(lv_event_t *e);
void create_black_screen(void);


/* ui event init */
void ui_event_init(){
    ui_event_timer_init();
    ui_event_tomato_init();
    create_black_screen();
}

/* timer event init */
static void ui_event_timer_init(){
    // hide the pause image
    lv_obj_add_flag(ui_imgTimerPause, LV_OBJ_FLAG_HIDDEN);

    // add the event 
    lv_obj_add_event_cb(ui_imgTimerPause, ui_event_scr_timer_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_imgTimerStart, ui_event_scr_timer_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_imgTimerRst, ui_event_scr_timer_click, LV_EVENT_CLICKED, NULL);
}

/* tomato event init */
static void ui_event_tomato_init(){
    // hide the pause image
    lv_obj_add_flag(ui_imgTomatoPause, LV_OBJ_FLAG_HIDDEN);

    // add the event
    lv_obj_add_event_cb(ui_imgTomatoPause, ui_event_scr_tomato_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_imgTomatoStart, ui_event_scr_tomato_click, LV_EVENT_CLICKED, NULL);
}

/* timer event function */
static void ui_event_scr_timer_click(lv_event_t *e){
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED){
        if(target == ui_imgTimerStart){
            lv_obj_add_flag(ui_imgTimerStart, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_imgTimerPause, LV_OBJ_FLAG_HIDDEN);
            globalData.flag_timer = 1;
        }
        if(target == ui_imgTimerPause){
            lv_obj_add_flag(ui_imgTimerPause, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_imgTimerStart, LV_OBJ_FLAG_HIDDEN);
            globalData.flag_timer = 0;
        }
        if(target == ui_imgTimerRst){
            globalData.flag_timer = 0;
            globalData.flag_timer_rst = 1;
            lv_obj_add_flag(ui_imgTimerPause, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_imgTimerStart, LV_OBJ_FLAG_HIDDEN);
        }
    }
}


/* tomato event function */
static void ui_event_scr_tomato_click(lv_event_t *e){
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED){
        if(target == ui_imgTomatoStart){
            lv_obj_add_flag(ui_imgTomatoStart, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_imgTomatoPause, LV_OBJ_FLAG_HIDDEN);
            globalData.flag_tomato = 1;
        }
        if(target == ui_imgTomatoPause){
            lv_obj_add_flag(ui_imgTomatoPause, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_imgTomatoStart, LV_OBJ_FLAG_HIDDEN);
            globalData.flag_tomato = 0;
        }
    }
}

/* create a whole black screen */
void create_black_screen() {
    black_screen = lv_obj_create(NULL);
    lv_obj_set_size(black_screen, 240, 240);
    lv_obj_set_pos(black_screen, 0, 0);
    lv_obj_set_style_bg_color(black_screen, lv_color_black(), LV_PART_MAIN);
}

/* switch to black screen */
void switch_to_black_screen() {
    lv_scr_load(black_screen);
}
