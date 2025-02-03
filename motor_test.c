#include "timer.h"
#include <reg51.h>

// 引脚定义
sbit RF = P1^1;  // 右电机正转
sbit RB = P1^2;  // 右电机反转
sbit LF  = P1^3;  // 左电机正转
sbit LB  = P1^4;  // 左电机反转

// 标志
unsigned char flag_left = 0;// 左转标志
unsigned char flag_right = 0;// 右转标志
unsigned char flag_forward = 0;// 短暂直行标志

// 变量
char left_dir = 0, right_dir = 0;// 方向
unsigned char left_duty = 0, right_duty = 0;// 目标PWM
unsigned char PWM_count = 0;//实际PWM

// PWM 更新
void PWM_Update(){
    PWM_count = (PWM_count + 1) % 100;

    // 左电机
    if (PWM_count < left_duty && left_dir == 1){
        LF = 1;
        LB = 0;
    }
    else if (PWM_count < left_duty && left_dir == -1){
        LF = 0;
        LB = 1;
    }
    else{
        LF = 0;
        LB = 0;
    }

    //右电机
    if (PWM_count < right_duty && right_dir == 1){
        RF = 1;
        RB = 0;
    }
    else if (PWM_count < right_duty && right_dir == -1){
        RF = 0;
        RB = 1;
    }
    else{
        RF = 0;
        RB = 0;
    }
}

void SetLeftMotor(char set_dir, unsigned char set_duty){
    left_dir = set_dir;
    left_duty = set_duty;
}

void SetRightMotor(char set_dir, unsigned char set_duty){
    right_dir = set_dir;
    right_duty = set_duty;
}