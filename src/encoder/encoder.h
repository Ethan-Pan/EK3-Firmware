// encoder.h 文件
#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <Arduino.h>
#include <ESP32Encoder.h>
#include "common/common.h"

extern int64_t read_encoder_count(void);
extern void encoder_init(void);

#endif