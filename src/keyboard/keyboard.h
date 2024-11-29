// keyboard.h 文件
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <Arduino.h>
#include <BleKeyboard.h>
#include "flash/flash.h"

extern void ble_keyboard_init();
extern void keyboard_finger();
extern void keyboard_volume_up();
extern void keyboard_volume_down();
extern void keyboard_up();
extern void keyboard_down();
extern void keyboard_mute();
extern void keyboard_unmute();
extern void keyboard_next();
extern void keyboard_prev();
extern void keyboard_play_pause();
extern void keyboard_deinit();
extern void keyboard_X_input();
#endif