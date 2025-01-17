#include "timer.h"
#include <reg51.h>

sbit OP = P0^3; 
sbit CL = P0^4;

int flag_open = 1;// 开关门标志

void Door_Open(){// 控制开门
	if (flag_open == 0){
		timer_count = 0;
		OP = 1;
		CL = 0;
	
		while (timer_count < 500){
		}
	
		OP = 0;
		flag_open = 1;
	}
	else{
		OP = 0;
		CL = 0;
	}
}

void Door_Close(){// 控制关门
	if (flag_open == 1){
		timer_count = 0;
		OP = 0;
		CL = 1;
	
		while (timer_count < 500){
		}
	
		CL = 0;
		flag_open = 0;}
	
	else{
		OP = 0;
		CL = 0;
	}
}
