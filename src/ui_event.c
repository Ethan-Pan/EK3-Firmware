#include "ui_events.h"

/* create a black screen */
lv_obj_t *black_screen;

static void ui_event_timer_init();
static void ui_event_tomato_init();
static void ui_event_led_mode_init();
static void ui_event_open_init();
static void ui_event_scr_timer_click(lv_event_t *e);
static void ui_event_scr_tomato_click(lv_event_t *e);
static void ui_event_led_mode_click(lv_event_t *e);
static void ui_event_scr_open_loaded(lv_event_t *e);


/* ui event init */
void ui_event_init(){
    ui_event_timer_init();
    ui_event_tomato_init();
    ui_event_led_mode_init();
    // ui_event_open_init();
}

static void ui_event_open_init(){
    printf("Registering open screen event callback\n");
    // lv_obj_add_event_cb(ui_scrOpen, ui_event_scr_open_loaded, LV_EVENT_SCREEN_LOADED, NULL); 
    lv_obj_add_event_cb(ui_scrOpen, ui_event_scr_open_loaded, LV_EVENT_ALL, NULL);
}

/* open screen event */
static void ui_event_scr_open_loaded(lv_event_t *e)
{
    printf("Open screen event triggered, flag_config = %d\n", globalData.flag_config);
    
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        /* already config */
        if(globalData.flag_config == 0){    
            printf("Switching to Watch1 screen\n");
            _ui_screen_change(&ui_scrWatch1, LV_SCR_LOAD_ANIM_FADE_ON, 50, 3000, &ui_scrWatch1_screen_init);
        }
        /* first time to config */
        else{
            printf("Showing first time config animation\n");
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, ui_logo);
            lv_anim_set_values(&a, 0, -20);
            lv_anim_set_time(&a, 2000);
            lv_anim_set_path_cb(&a, lv_anim_path_linear);
            lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
            lv_anim_start(&a);
            lv_obj_clear_flag(ui_labOpen, LV_OBJ_FLAG_HIDDEN);
        }
    }
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

/* led mode event init */
static void ui_event_led_mode_init(){
    lv_obj_add_event_cb(ui_PalLightBreath, ui_event_led_mode_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_PalLightStay, ui_event_led_mode_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_PalLightRainbow, ui_event_led_mode_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_PalLightSky, ui_event_led_mode_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_PalLightWave, ui_event_led_mode_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_PalLightSetting, ui_event_led_mode_click, LV_EVENT_CLICKED, NULL);
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


/* led mode click event */
static void ui_event_led_mode_click(lv_event_t *e){
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED){
        if(target == ui_PalLightBreath){
            globalData.led_mode = 1;
        }
        if(target == ui_PalLightStay){
            globalData.led_mode = 2;
        }
        if(target == ui_PalLightRainbow){
            globalData.led_mode = 3;
        }
        if(target == ui_PalLightSky){
            globalData.led_mode = 4;
        }
        if(target == ui_PalLightWave){
            globalData.led_mode = 5;
        }
        if(target == ui_PalLightSetting){
            globalData.led_mode = 0;
        }
    }
}
