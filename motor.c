#include "timer.h"
#include <reg51.h>

sbit RF = P0^1;
sbit RB = P0^2;
sbit LF = P0^3;
sbit LB = P0^4;

int flag_left = 0;// 左转标志
int flag_right = 0;// 右转标志

void Motor_Init() {
    // 初始化电机
    LF = 0;
	RF = 0;
	LB = 0;
	RB = 0;
}

void Motor_Forward(){// 直行
	LF = 1;
	LB = 0;
	RF = 1;
	RB = 0;
}

void Motor_Backward(){// 后退
	LF = 0;
	LB = 1;
	RF = 0;
	RB = 1;
}

void  Motor_Stop(){// 两电机停止
	LF = 0;
	LB = 0;
	RF = 0;
	RB = 0;
}

void Motor_TempForward(int time) {// 直行指定毫秒数
	LF = 1;
	LB = 0;
	RF = 1;
	RB = 0;

	DelayMs(time);
	Motor_Stop();
}

void Motor_TempStop(int time){// 暂停指定毫秒数
	Motor_Stop();
    DelayMs(time);
}

void Motor_TurnLeft(){// 左转
	if (flag_left == 0){
		flag_left = 1;

		LF = 0;
		LB = 1;
		RF = 1;
		RB = 0;

		DelayMs(500);
		Motor_Stop();
	}
	
	else if (flag_left == 1)
		Motor_Stop();
} 

void Motor_TurnRight(){// 右转
	if (flag_right == 0){
		flag_right = 1;

		LF = 1;
		LB = 0;
		RF = 0;
		RB = 1;
		
		DelayMs(500);
		Motor_Stop();
	}

	else if (flag_right == 1)
		Motor_Stop();
}
