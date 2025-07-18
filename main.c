#include "motor.h"
#include "motor_door.h"
#include "timer.h"
#include <reg51.h>

sbit SENSOR = P2^6;  // 传感器连接 P27坏了

// 串口初始化
void UART_Init() {
    TMOD = 0x20;   // 定时器1，模式2（8位自动重载）
    TH1 = 0xFD;    // 波特率 9600
    TL1 = 0xFD;
    TR1 = 1;       // 启动定时器1
    SCON = 0x50;   // 串口模式1，8位数据，接收使能
    EA = 1;        // 开启总中断
}
// 串口发送数据
void UART_SendByte(unsigned char byte) {
    SBUF = byte;       // 发送数据
    while (TI == 0);   // 等待发送完成
    TI = 0;            // 清除发送标志
}


// 主函数开始
void main() {
    char flag_ball = 1;// 进球标志
	unsigned char sensorState = 0;

    Motor_Init();// 初始化电机
	UART_Init();  // 初始化串口
    Timer0Init();// 初始化定时器

    // 主循环
	while (1) {
		if (flag_ball == 1) {
			if (SENSOR == 0)
				flag_ball = 0;// 触发进球行为
			else
				Motor_Forward(3, 3);// 电机直行
		} 

		if (flag_ball == 0){
			flag_ball = -1;// 自主部分结束
			// 若进球，暂停、右转、直行至安全区
      		// Door_Close();
       		Motor_TempStop(1000);
       		Motor_TurnRight(3, 3);

			Motor_TempStop(500);
			Motor_TempForward(3000, 3, 3); //直行3秒
		}

		sensorState = SENSOR;  // 读取传感器状态
	    if (sensorState) {
		   UART_SendByte('1');  // 发送高电平 '1'
		} else {
			UART_SendByte('0');  // 发送低电平 '0'
		}
		UART_SendByte('\n');  // 发送换行符，方便串口调试工具显示

    	DelayMs(100);  // 每 100ms 循环一次
    }
}
