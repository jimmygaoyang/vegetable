#include "DelayFun.h" 

 void delay_us(u16 time) {
	u16 i=0;      
	while(time--)    
	{        
		i=10;  //自己定义       
		while(i--)	{}	
	} 
}

void delay_ms(u16 time) {
	u16 i=0;      
	while(time--)    
	{        
		i=10000;  //自己定义       
		while(i--)	{}	
	} 
}

