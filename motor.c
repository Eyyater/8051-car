#include "timer.h"
#include <reg51.h>

// 引脚定义
sbit LF = P3^4; // 右电机正转
sbit LB = P3^5; // 右电机反转
sbit RF  = P3^6;  // 左电机反转
sbit RB  = P3^7;  // 左电机正转

// 变量
char left_dir = 0, right_dir = 0;// 方向
unsigned char left_duty = 0, right_duty = 0;// 目标PWM
unsigned char PWM_count = 0;// 实际PWM

// 初始化电机
void Motor_Init(){
	LF = 0;
	LB = 0;
	RF = 0;
	RB = 0;
}

// PWM 更新
void PWM_Update(){
    PWM_count = (PWM_count + 1) % 10;

    // 左电机
	LF = (left_dir == 1 && PWM_count < left_duty);
	LB = (left_dir == -1 && PWM_count < left_duty);

    //右电机
    RF = (right_dir == 1 && PWM_count < right_duty);
	RB = (right_dir == -1 && PWM_count < right_duty);
}

// 设置电机
void SetLeftMotor(char set_dir, unsigned char set_duty){
    left_dir = set_dir;
    left_duty = set_duty;
}

void SetRightMotor(char set_dir, unsigned char set_duty){
    right_dir = set_dir;
    right_duty = set_duty;
}

// 直行
void Motor_Forward(
	unsigned char left_duty,
	unsigned char right_duty
){
	SetLeftMotor(1, left_duty);
	SetRightMotor(1, right_duty);
}

// 后退
void Motor_Backward(
	unsigned char left_duty,
	unsigned char right_duty
){
	SetLeftMotor(-1, left_duty);
	SetRightMotor(-1, right_duty);
}

// 停止
void  Motor_Stop(){
	SetLeftMotor(0, 0);
	SetRightMotor(0, 0);
}

// 直行指定毫秒数
void Motor_TempForward(
	int time,
	unsigned char left_duty,
	unsigned char right_duty
) {
	SetLeftMotor(1, left_duty);
	SetRightMotor(1, right_duty);

	DelayMs(time);
	Motor_Stop();
}

// 暂停指定毫秒数
void Motor_TempStop(int time){
	Motor_Stop();
    DelayMs(time);
}

// 左转
void Motor_TurnLeft(
	unsigned char left_duty,
	unsigned char right_duty
){
	SetLeftMotor(-1, left_duty);
	SetRightMotor(1, right_duty);

	DelayMs(200);
	Motor_Stop();
} 

// 右转
void Motor_TurnRight(
	unsigned char left_duty,
	unsigned char right_duty
){
	SetLeftMotor(1, left_duty);
	SetRightMotor(-1, right_duty);
		
	DelayMs(200);
	Motor_Stop();
}