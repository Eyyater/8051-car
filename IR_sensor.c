#include <reg51.h>

sbit flag = P2^7;

int Sensor_Get(){// 获取进球信息 
	if (flag == 0)
		return 1;
	else if(flag == 1)
		return 0; 
}
