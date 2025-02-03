#include "timer.h"
#include <reg51.h>

sbit RF = P0^1;
sbit RB = P0^2;
sbit LF = P0^3;
sbit LB = P0^4;

unsigned char flag_left = 0;// 左转标志
unsigned char flag_right = 0;// 右转标志
unsigned char flag_forward = 0;// 短暂直行标志

// 初始化电机
void Motor_Init() {
    LF = 0;
	RF = 0;
	LB = 0;
	RB = 0;
}

// 直行
void Motor_Forward(){
	LF = 1;
	LB = 0;
	RF = 1;
	RB = 0;
}

// 后退
void Motor_Backward(){
	LF = 0;
	LB = 1;
	RF = 0;
	RB = 1;
}

// 停止
void  Motor_Stop(){
	LF = 0;
	LB = 0;
	RF = 0;
	RB = 0;
}

// 直行指定毫秒数
void Motor_TempForward(int time) {
	if (flag_forward == 0){
		LF = 1;
		LB = 0;
		RF = 1;
		RB = 0;

		DelayMs(time);
		Motor_Stop();

		flag_forward = 1;
	}
}

// 暂停指定毫秒数
void Motor_TempStop(int time){
	Motor_Stop();
    DelayMs(time);
}

// 左转
void Motor_TurnLeft(){
	if (flag_left == 0){
		flag_left = 1;

		LF = 0;
		LB = 1;
		RF = 1;
		RB = 0;

		DelayMs(500);
		Motor_Stop();
	}
} 

// 右转
void Motor_TurnRight(){
	if (flag_right == 0){
		flag_right = 1;

		LF = 1;
		LB = 0;
		RF = 0;
		RB = 1;
		
		DelayMs(500);
		Motor_Stop();
	}
}
