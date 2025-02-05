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
			if (SENSOR == 0)
				flag_ball = 0;
			else
				Motor_Forward(3, 3);
			// 电机直行
		} 

		if (flag_ball == 0){
			// 若进球，关门、暂停、右转、直行至安全区
      		// Door_Close();
       		Motor_TempStop(1000);
       		Motor_TurnRight(3, 3);

			Motor_TempStop(500);
			Motor_TempForward(3000, 3, 3); //直行3秒
			// Motor_Stop();
		}

    	DelayMs(100);  // 每 100ms 循环一次
    	DelayMs(100);  // 每 100ms 循环一次
    }
}
