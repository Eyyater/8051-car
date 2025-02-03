#ifndef MOTOR_H
#define MOTOR_H

void PWM_Update(void);
void Motor_Forward(unsigned char left_duty, unsigned char right_duty);
void Motor_Backward(unsigned char left_duty, unsigned char right_duty);
void Motor_Stop(void);
void Motor_TempForward(int time, unsigned char left_duty, unsigned char right_duty);
void Motor_TempStop(int time);
void Motor_TurnLeft(unsigned char left_duty, unsigned char right_duty);
void Motor_TurnRight(unsigned char left_duty, unsigned char right_duty); 
extern int flag_right;
extern int flag_left;

#endif

