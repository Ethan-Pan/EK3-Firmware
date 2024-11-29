#ifndef __CONNECT_H__
#define __CONNECT_H__

#include <Arduino.h>
#include "common/common.h"
#include "flash/flash.h"
#include "bluetooth/bluetooth.h"
#include "keyboard/keyboard.h"

extern void connect_init(void);
extern void send_weather_update(void);
extern void send_version(void);
extern void send_update_start(void);
extern void send_check_connect(void);
extern void send_update_download(void);


#endif