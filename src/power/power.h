// power.h 文件
#ifndef __POWER_H__
#define __POWER_H__

#include <Arduino.h>
#include <esp_adc_cal.h>
#include <driver/adc.h>

#define POWER_MAX 2530
#define POWER_MIN 2240
#define CHARGE_PIN 36

extern void power_init(void);
extern uint32_t read_power(void);
extern uint32_t get_charge_state(void);

#endif