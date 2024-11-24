/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include "keyboard.h"


static BleKeyboard bleKeyboard;

void ble_keyboard_init() {
  Serial.println("Starting BLE work!");
  bleKeyboard.setName("Ehthan's EK3");
  bleKeyboard.begin();
}

void keyboard_finger() {
    if(bleKeyboard.isConnected()) {
        bleKeyboard.print(gJsonData.finger_pin);
        bleKeyboard.write(KEY_RETURN);
    }
}

void keyboard_volume_up() {
    if(bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
    }
}

void keyboard_volume_down() {
    if(bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
    }
}

void keyboard_mute() {
    if(bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_MEDIA_MUTE);
    }
}

void keyboard_unmute() {
    if(bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_MEDIA_MUTE);
    }
}

void keyboard_next() {
    if(bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
    }
}

void keyboard_prev() {
    if(bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
    }
}

void keyboard_play_pause() {
    if(bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    }
} 

void keyboard_deinit() {
    bleKeyboard.end();
}
