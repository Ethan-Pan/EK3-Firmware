#include "encoder.h"

// 定义旋转编码器连接的引脚
const int pinA = 35; // 旋转编码器的A引脚连接到ESP32的GPIO 32
const int pinB = 34; // 旋转编码器的B引脚连接到ESP32的GPIO 33

// 创建一个ESP32Encoder对象
ESP32Encoder encoder;


void encoder_init(){
    // 初始化旋转编码器
    ESP32Encoder::useInternalWeakPullResistors=puType::down;
    // 附加引脚到旋转编码器对象
    encoder.attachSingleEdge(pinA, pinB);
    // 清零编码器
    encoder.clearCount();
}

int64_t read_encoder_count(){
    // 读取旋转编码器的当前位置
    int64_t count = encoder.getCount();
    return count;
}
