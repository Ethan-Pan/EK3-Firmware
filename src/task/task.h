#ifndef __TASK_H__
#define __TASK_H__

#include <Arduino.h>
#include "motor/motor.h"
#include "LED/led.h"
#include "flash/flash.h"
#include "ui.h"
#include "ui_helpers.h"
#include "ui_events.h"
#include "common/common.h"
#include "power/power.h"
#include "finger/finger.h"
#include "encoder/encoder.h"
#include "display/display.h"
#include "bluetooth/bluetooth.h"
#include "keyboard/keyboard.h"
#include "wifi/wifi.h"
#include "connect/connect.h"

extern void task_init(void);

#endif