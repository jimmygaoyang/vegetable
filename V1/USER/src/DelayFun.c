#include "DelayFun.h" 

 void delay_us(u16 time) {
	u16 i=0;      
	while(time--)    
	{        
		i=10;  //�Լ�����       
		while(i--)	{}	
	} 
}

void delay_ms(u16 time) {
	u16 i=0;      
	while(time--)    
	{        
		i=10000;  //�Լ�����       
		while(i--)	{}	
	} 
}

