#include <reg51.h>

sbit signal = P2^7;

int Sensor_Get(){// 获取进球信息 
	int flag;
	if (signal == 0)
		flag = 1;
	else if(signal == 1)
		flag = 0; 
	return flag;
}
