#include "motor.h"
#include "IR_sensor.h"
#include "motor_door.h"
#include "timer.h"
#include <reg51.h>

void main() {
	int auto_start = 1;// 开始自主部分
    int flag_ball = 0;// 是否进球

    Motor_Init();// 初始化马达
    Timer0Init();// 初始化定时器

    while (auto_start == 1) {
		

		if (flag_ball == 0){
			flag_ball = Sensor_Get();// 获取红外进球信息
			Motor_Forward();
			// 电机直行
		} 

		if (flag_ball == 1){
			// 若进球，关门、暂停、右转、直行至安全区
//       		Door_Close();
       		Motor_TempStop(500);
       		// Motor_TurnRight();

			// Motor_TempStop(500);
			// Motor_TempForward(3000); //直行3秒
			// Motor_Stop();
			auto_start = 0;// 自主部分结束
		}
		
    }
}
