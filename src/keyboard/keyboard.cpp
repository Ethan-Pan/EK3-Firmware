/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */

#include "keyboard.h"

static void keyboard_X_write_single(char* key);

static BleKeyboard bleKeyboard;


void ble_keyboard_init() {
  Serial.println("Starting BLE work!");
  char name[50];
  sprintf(name, "%s's EK3", gJsonData.user_name);
  bleKeyboard.setName(name);
  bleKeyboard.begin();
}

void keyboard_finger() {
    if(bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_ESC);
        delay(1000);
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

void keyboard_up() {
    if(bleKeyboard.isConnected()) {
        for(int i = 0; i < 3; i++){
            bleKeyboard.write(KEY_UP_ARROW);
        }
    }
}

void keyboard_down() {
    if(bleKeyboard.isConnected()) {
        for(int i = 0; i < 3; i++){
            bleKeyboard.write(KEY_DOWN_ARROW);
        }
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


void keyboard_X_input() {
    if(bleKeyboard.isConnected()) {
        char x_input[50];
        strcpy(x_input, gJsonData.x_input);
        char *token = strtok(x_input, "+");
        
        while(token != NULL) {
            Serial.println("token: " + String(token));
            keyboard_X_write_single(token);
            token = strtok(NULL, "+");
        }
        delay(100);
        bleKeyboard.releaseAll();
    }
}


static void keyboard_X_write_single(char* token) {
    if(bleKeyboard.isConnected()) {
        // token may be SHIFT, CTRL, ALT, DELETE, WIN, HOME, END, RETURN, ESC, F1-F12 etc
        if(strcmp(token, "SHIFT") == 0) {
            bleKeyboard.press(KEY_LEFT_SHIFT);
        }
        else if(strcmp(token, "CTRL") == 0) {
            bleKeyboard.press(KEY_LEFT_CTRL);
        }
        else if(strcmp(token, "ALT") == 0) {
            bleKeyboard.press(KEY_LEFT_ALT);
        }
        else if(strcmp(token, "WIN") == 0) {
            bleKeyboard.press(KEY_LEFT_GUI);
        }
        else if(strcmp(token, "DELETE") == 0) {
            bleKeyboard.press(KEY_DELETE);
        }
        else if(strcmp(token, "HOME") == 0) {
            bleKeyboard.press(KEY_HOME);
        }
        else if(strcmp(token, "END") == 0) {
            bleKeyboard.press(KEY_END);
        }
        else if(strcmp(token, "RETURN") == 0) {
            bleKeyboard.press(KEY_RETURN);
        }
        else if(strcmp(token, "ESC") == 0) {
            bleKeyboard.press(KEY_ESC);
        }
        else if(strcmp(token, "F1") == 0) {
            bleKeyboard.press(KEY_F1);
        }
        else if(strcmp(token, "F2") == 0) {
            bleKeyboard.press(KEY_F2);
        }
        else if(strcmp(token, "F3") == 0) {
            bleKeyboard.press(KEY_F3);
        }
        else if(strcmp(token, "F4") == 0) {
            bleKeyboard.press(KEY_F4);
        }
        else if(strcmp(token, "F5") == 0) {
            bleKeyboard.press(KEY_F5);
        }
        else if(strcmp(token, "F6") == 0) {
            bleKeyboard.press(KEY_F6);
        }
        else if(strcmp(token, "F7") == 0) {
            bleKeyboard.press(KEY_F7);
        }
        else if(strcmp(token, "F8") == 0) {
            bleKeyboard.press(KEY_F8);
        }
        else if(strcmp(token, "F9") == 0) {
            bleKeyboard.press(KEY_F9);
        }
        else if(strcmp(token, "F10") == 0) {
            bleKeyboard.press(KEY_F10);
        }
        else if(strcmp(token, "F11") == 0) {
            bleKeyboard.press(KEY_F11);
        }
        else if(strcmp(token, "F12") == 0) {
            bleKeyboard.press(KEY_F12);
        }
        else if(strlen(token) == 1) {
            bleKeyboard.press(tolower(token[0]));
        }
    }       
}
