#include "ui_events.h"

/* create a black screen */
lv_obj_t *black_screen;

static void ui_event_timer_init();
static void ui_event_tomato_init();
static void ui_event_led_mode_init();
static void ui_event_music_init();
static void ui_event_update_init();
static void ui_event_scr_timer_click(lv_event_t *e);
static void ui_event_scr_tomato_click(lv_event_t *e);
static void ui_event_led_mode_click(lv_event_t *e);
static void ui_event_scr_open_loaded(lv_event_t *e);
static void ui_event_scr_music_click(lv_event_t *e);
static void ui_event_update_click(lv_event_t *e);
static void ui_event_update_scr_loaded(lv_event_t *e);


/* ui event init */
void ui_event_init(){
    ui_event_timer_init();
    ui_event_tomato_init();
    ui_event_led_mode_init();
    ui_event_music_init();
    ui_event_update_init();
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

/* music event init */
static void ui_event_music_init(){
    lv_obj_add_event_cb(ui_imgStartMusic, ui_event_scr_music_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_imgEndMusic, ui_event_scr_music_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_imgNextMusic, ui_event_scr_music_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_imgLastMusic, ui_event_scr_music_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_imgSound, ui_event_scr_music_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_imgMute, ui_event_scr_music_click, LV_EVENT_CLICKED, NULL);
}

/* update event init */
static void ui_event_update_init(){
    lv_obj_add_event_cb(ui_buttonUpdate, ui_event_update_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_buttonCancel, ui_event_update_click, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_scrUpdate, ui_event_update_scr_loaded, LV_EVENT_SCREEN_LOADED, NULL);
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


/* music click event */
static void ui_event_scr_music_click(lv_event_t *e){
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED){
        if(target == ui_imgEndMusic){
            lv_obj_add_flag(ui_imgEndMusic, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_imgStartMusic, LV_OBJ_FLAG_HIDDEN);
            globalData.music_state = 1;
        }
        if(target == ui_imgStartMusic){
            lv_obj_add_flag(ui_imgStartMusic, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_imgEndMusic, LV_OBJ_FLAG_HIDDEN);
            globalData.music_state = 2;
        }
        if(target == ui_imgNextMusic){
            lv_obj_add_flag(ui_imgStartMusic, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_imgEndMusic, LV_OBJ_FLAG_HIDDEN);
            globalData.music_state = 3;
        }
        if(target == ui_imgLastMusic){
            lv_obj_add_flag(ui_imgStartMusic, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_imgEndMusic, LV_OBJ_FLAG_HIDDEN);
            globalData.music_state = 4;
        }
        if(target == ui_imgSound){
            lv_obj_add_flag(ui_imgSound, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_imgMute, LV_OBJ_FLAG_HIDDEN);
            globalData.music_state = 5;
        }
        if(target == ui_imgMute){
            lv_obj_add_flag(ui_imgMute, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_imgSound, LV_OBJ_FLAG_HIDDEN);
            globalData.music_state = 6;
        }
    }
}

static void ui_event_update_click(lv_event_t *e){
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED){
        if(target == ui_buttonUpdate){
            globalData.flag_update_confirm = 1;
        }   
        if(target == ui_buttonCancel){
            globalData.flag_update_confirm = 0;
            _ui_screen_change(&ui_scrMenu, LV_SCR_LOAD_ANIM_FADE_ON, 50, 0, &ui_scrMenu_screen_init);
        }
    }   
}

static void ui_event_update_scr_loaded(lv_event_t *e){
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED){
        if(target == ui_scrUpdate){
            globalData.flag_update_scr_loaded = 1;
            lv_label_set_text(ui_labUpdate1, "正在检测更新");
            lv_obj_add_flag(ui_panelNoConnect, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_panelCheckUpdate, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_panelNewVersion, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_panelAlready, LV_OBJ_FLAG_HIDDEN);
        }   
    }
}
