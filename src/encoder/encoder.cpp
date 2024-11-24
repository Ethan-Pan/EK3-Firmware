#include "encoder.h"

// 定义旋转编码器连接的引脚
const int pinA = 35; // 旋转编码器的A引脚连接到ESP32的GPIO 32
const int pinB = 34; // 旋转编码器的B引脚连接到ESP32的GPIO 33

// 创建一个ESP32Encoder对象
ESP32Encoder encoder;
void encoder_interrupt_init();

void encoder_init(){
    // 初始化旋转编码器
    ESP32Encoder::useInternalWeakPullResistors=puType::down;
    // 附加引脚到旋转编码器对象
    encoder.attachSingleEdge(pinA, pinB);
    // 清零编码器
    encoder.clearCount();
    // 初始化中断
    encoder_interrupt_init();
}

int64_t read_encoder_count(){
    // 读取旋转编码器的当前位置
    int64_t count = encoder.getCount();
    return count;
}


// 定义中断服务函数
void IRAM_ATTR encoderISR() {
    // 在中断中不进行复杂操作，只设置一个标志
    globalData.flag_encoder = 1;
}

// 初始化中断
void encoder_interrupt_init() {
    // 设置引脚为输入模式
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    
    // 为A引脚附加中断
    attachInterrupt(digitalPinToInterrupt(pinA), encoderISR, CHANGE);
    // 为B引脚附加中断
    attachInterrupt(digitalPinToInterrupt(pinB), encoderISR, CHANGE);
}
