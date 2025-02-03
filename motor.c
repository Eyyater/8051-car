#include "timer.h"
#include <reg51.h>

// 引脚定义
sbit RIGHT_IN1 = P1^0;  // 右电机正转
sbit RIGHT_IN2 = P1^1;  // 右电机反转
sbit LEFT_IN3  = P1^2;  // 左电机正转
sbit LEFT_IN4  = P1^3;  // 左电机反转

// 标志
unsigned char flag_left = 0;// 左转标志
unsigned char flag_right = 0;// 右转标志
unsigned char flag_forward = 0;// 短暂直行标志

// 变量
unsigned char left_duty = 0, right_duty = 0;  // 占空比（0-100）
char left_dir = 0, right_dir = 0;             // 方向（1 正转，-1 反转，0 停止）
unsigned char pwm_count = 0;                  // PWM 计数器

// PWM 更新（定时器中断里调用）
void PWM_Update() {
    pwm_count = (pwm_count + 1) % 100;  // 100 级占空比

    // 右电机（IN1、IN2）
    RIGHT_IN1 = (right_dir == 1 && pwm_count < right_duty);
    RIGHT_IN2 = (right_dir == -1 && pwm_count < right_duty);

    // 左电机（IN3、IN4）
    LEFT_IN3 = (left_dir == 1 && pwm_count < left_duty);
    LEFT_IN4 = (left_dir == -1 && pwm_count < left_duty);
}

// 设定电机
void SetMotor(
	unsigned char motor,
	char dir,
	unsigned char duty
) {
    duty = (duty > 100) ? 100 : duty;  // 限制占空比范围

    if (motor == 1) {  // 右电机
        right_dir = dir;
        right_duty = (dir == 0) ? 0 : duty;
    } else {           // 左电机
        left_dir = dir;
        left_duty = (dir == 0) ? 0 : duty;
    }
}

// 直行
void Motor_Forward(
	unsigned char left_duty,
	unsigned char right_duty
){
	SetMotor(0, 1, left_duty);
	SetMotor(1, 1, right_duty);
}

// 后退
void Motor_Backward(
	unsigned char left_duty,
	unsigned char right_duty
){
	SetMotor(0, -1, left_duty);
	SetMotor(1, -1, right_duty);
}

// 停止
void  Motor_Stop(){
	SetMotor(0, 0, 0);
	SetMotor(1, 0, 0);
}

// 直行指定毫秒数
void Motor_TempForward(
	int time,
	unsigned char left_duty,
	unsigned char right_duty
) {
	if (flag_forward == 0){
		flag_forward = 1;

		SetMotor(0, 1, left_duty);
		SetMotor(1, 1, right_duty);

		DelayMs(time);
		Motor_Stop();
	}
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
	if (flag_left == 0){
		flag_left = 1;

		SetMotor(0, -1, left_duty);
		SetMotor(1, 1, right_duty);

		DelayMs(500);
		Motor_Stop();
	}
} 

// 右转
void Motor_TurnRight(
	unsigned char left_duty,
	unsigned char right_duty
){
	if (flag_right == 0){
		flag_right = 1;

		SetMotor(0, 1, left_duty);
		SetMotor(1, -1, right_duty);
		
		DelayMs(500);
		Motor_Stop();
	}
}