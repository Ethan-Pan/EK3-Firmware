#include "power.h"

#define DEFAULT_VREF    1100    // 默认1.1V的参考电压
#define NO_OF_SAMPLES   64      // ADC采样次数
#define ADC_WIDTH       ADC_WIDTH_12Bit  // ADC 12位宽度
#define ADC_ATTEN       ADC_ATTEN_11db    // 11dB衰减器
#define ADC_PIN         ADC1_CHANNEL_3

esp_adc_cal_characteristics_t *adc_chars;
void power_init(void);
uint32_t read_power(void);
uint32_t get_charge_state(void);

void power_init(){
    pinMode(CHARGE_PIN, INPUT);
    adc1_config_width(ADC_WIDTH);  // 设置ADC为12位宽度
    adc1_config_channel_atten(ADC_PIN, ADC_ATTEN);  // 配置ADC通道为11dB衰减器
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN); 

    // 使用eFuse校准ADC，并获取校准值
    adc_chars = (esp_adc_cal_characteristics_t *) malloc(sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN, ADC_WIDTH, DEFAULT_VREF, adc_chars);
    // 使能外部0引脚唤醒
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_2, 0); 
}

uint32_t read_power(){
    uint32_t adc_reading = 0;
    for (int i = 0; i < NO_OF_SAMPLES; i++) {
        adc_reading += adc1_get_raw((adc1_channel_t) ADC_PIN);
        delay(1);
    }

    adc_reading /= NO_OF_SAMPLES;
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    
    return voltage;
}

uint32_t get_charge_state(){
    uint32_t adc_reading = 0;
    for (int i = 0; i < NO_OF_SAMPLES; i++) {
        adc_reading += adc1_get_raw((adc1_channel_t) ADC1_CHANNEL_0);
        delay(1);
    }

    adc_reading /= NO_OF_SAMPLES;
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    
    return voltage;
}

/* calculate the init charge voltage percent */
int get_voltage_base_percent(int baseVoltage){
    if(baseVoltage >= POWER_MAX){
        return 100;
    }
    else{
        return (baseVoltage - POWER_MIN) / (POWER_MAX - POWER_MIN) * 100;
    }
    // if(baseVoltage >= POWER_20){
    //     return (baseVoltage - POWER_20) / (POWER_MAX - POWER_20) * 80 + 20;
    // }
    // else{
    //     return (baseVoltage - POWER_20) / (POWER_20 - POWER_MIN) * 20;
    // }
}

/* calculate the additional charge power pecent per sencond */
int get_add_bat_charge(int chargeVoltage){
    int chargeRes = 1200;  // the charge resistence of TP4056 is 1.2k ohm
    return (chargeVoltage / chargeRes) / 72;
}