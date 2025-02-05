#include "motor.h"
#include "motor_door.h"
#include "timer.h"
#include <reg51.h>

sbit SENSOR = P2^7;  // 传感器连接 P27

// 主函数开始
void main() {
    unsigned int flag_ball = 1;// 进球标志

    Motor_Init();// 初始化马达
    Timer0Init();// 初始化定时器

    // 主循环
	while (1) {
		if (flag_ball == 1) {
			flag_ball = SENSOR;// 获取红外进球信息
			Motor_Forward();
			// 电机直行
		} 

		if (flag_ball == 0){
			// 若进球，关门、暂停、右转、直行至安全区
      		// Door_Close();
       		Motor_TempStop(1000);
       		Motor_TurnRight();

			Motor_TempStop(500);
			Motor_TempForward(3000); //直行3秒
			// Motor_Stop();
		}

    	DelayMs(100);  // 每 100ms 循环一次
    }
}
