#include "motor.h"
#include <reg51.h>

unsigned int timer_count = 0; 
// 定时器计数变量，用于记录定时器溢出次数

void Timer0Init(void) {
    TMOD |= 0x01; // 设置定时器模式：模式1（16位定时器）
    TL0 = (65536 - 1000) % 256; // 设置定时初始值，定时1ms
    TH0 = (65536 - 1000) / 256;
    TR0 = 1; // 启动定时器
    ET0 = 1; // 允许定时器调用中断函数
    EA = 1;  // 全局中断使能
}

// 定时器中断服务函数
void T0isp() interrupt 1 {
    TL0 = (65536 - 1000) % 256; // 重装载初值，定时1ms
    TH0 = (65536 - 1000) / 256;
    timer_count++; // 计数器累加
    PWM_Update();
}

// 独立计时器
void DelayMs(unsigned int ms) {
    unsigned int i;
    for (i = 0; i < ms; i++) {  // 执行 ms 次延时
        timer_count = 0;         // 每次都清零计数器
        while (timer_count < 1) {  // 等待 1ms
            // 等待中断触发，增加 timer_count
        }
    }
}
