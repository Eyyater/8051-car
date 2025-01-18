#ifndef MOTOR_H
#define MOTOR_H

void Motor_Init(void);
void Motor_Forward(void);
void Motor_Backward(void);
void Motor_TempForward(int time);
void Motor_Stop(void);
void Motor_TurnLeft(void);
void Motor_TurnRight(void); 
void Motor_TempStop(int time);
extern int flag_right;

#endif

