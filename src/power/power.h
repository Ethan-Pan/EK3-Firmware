// power.h 文件
#ifndef __POWER_H__
#define __POWER_H__

#include <Arduino.h>
#include <esp_adc_cal.h>
#include <driver/adc.h>

#define POWER_MAX 2080
#define POWER_MIN 1400
#define POWER_20 1700    // 剩余20%提示点
#define POWER_CHARGE_MIN 1550
#define POWER_CHARGE_MAX 2140
#define CHARGE_PIN 36
#define CHANGE_STAY_COUNT 10

extern void power_init(void);
extern uint32_t read_power(void);
extern uint32_t get_charge_state(void);
extern int get_voltage_base_percent(int baseVoltage);
extern int get_add_bat_charge(int chargeVoltage);

#endif