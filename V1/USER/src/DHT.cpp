//  
//    FILE: dht.cpp  
// VERSION: 0.1.01  
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino  
//  
// DATASHEET:   
//  
// HISTORY:  
// 0.1.01 added support for Arduino 1.0, fixed typos (31/12/2011)  
// 0.1.0 by Rob Tillaart (01/04/2011)  
// inspired by DHT11 library  
//  
  
#include "DHT.h"  
#include "DelayFun.h" 
  
#define TIMEOUT 10000  
  
/////////////////////////////////////////////////////  
//  
// PUBLIC  
//  
  
  
// return values:  
//  0 : OK  
// -1 : checksum error  
// -2 : timeout  
int dht::read11(CIOObject * pin)  
{  
    // READ VALUES  
    int rv = read(pin); 
	
    if (rv != 0) return rv;  
  
    // CONVERT AND STORE  
    humidity    = bits[0];  // bit[1] == 0;  
    temperature = bits[2];  // bits[3] == 0;  
  
    // TEST CHECKSUM  
    unsigned char sum = bits[0] + bits[2]; // bits[1] && bits[3] both 0  
    if (bits[4] != sum) return -1;  
  
    return 0;  
}  
  
// return values:  
//  0 : OK  
// -1 : checksum error  
// -2 : timeout  
int dht::read22(CIOObject * pin)  
{  
    // READ VALUES  
    int rv = read(pin);  
    if (rv != 0) return rv;  
  
    // CONVERT AND STORE  
//    humidity    = word(bits[0], bits[1]) * 0.1;  
   humidity    = (bits[0]*256+ bits[1])* 0.1; 
    int sign = 1;  
    if (bits[2] & 0x80) // negative temperature  
    {  
        bits[2] = bits[2] & 0x7F;  
        sign = -1;  
    }  
    temperature = sign * (bits[2]*256+ bits[3]) * 0.1;  
  
  
    // TEST CHECKSUM  
    uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];  
    if (bits[4] != sum) return -1;  
  
    return 0;  
}  
  
/////////////////////////////////////////////////////  
//  
// PRIVATE  
//  
  
// return values:  
//  0 : OK  
// -2 : timeout  
int dht::read(CIOObject * pin)  
{  
    // INIT BUFFERVAR TO RECEIVE DATA  
    unsigned char cnt = 7;  
    unsigned char idx = 0;  
  
    // EMPTY BUFFER  
    for (int i=0; i< 5; i++) bits[i] = 0;  
  
    // REQUEST SAMPLE 
    pin->SetMode(OUT);
 //   pinMode(pin, OUTPUT);
 	pin->SetDigitalOut(LOW);
//    digitalWrite(pin, LOW); 
	Delay_ms(30);
//    delay(20);
	pin->SetDigitalOut(HIGH);
//    digitalWrite(pin, HIGH);
	Delay_us(60);
//    delayMicroseconds(40); 
	pin->SetMode(IN);
//    pinMode(pin, INPUT);  
  
    // GET ACKNOWLEDGE or TIMEOUT 
    //等待电平变高，设置200us超时控制
    unsigned int loopCnt = 20;  
    while(pin->ReadDigitalIn() == LOW)
    {
    	Delay_us(10);
		if (loopCnt-- == 0) return -2; 
    }
 
  	//等待电平变低，设置150us超时控制
    loopCnt = 15;  
    while(pin->ReadDigitalIn() == HIGH)
    {
		Delay_us(10);
		if (loopCnt-- == 0) return -2;   
    }

  
    // READ THE OUTPUT - 40 BITS => 5 BYTES  
    for (int i=0; i<40; i++)  
    {  
        loopCnt = 6;  
        while(pin->ReadDigitalIn() == LOW)
		{
			Delay_us(10);
			if (loopCnt-- == 0) return -2;
		}  
              
  
//        unsigned long t = micros();  
 
        loopCnt = 10;  
        while(pin->ReadDigitalIn() == HIGH)
        {
       		Delay_us(10);
        	if (loopCnt-- == 0) return -2;
        } 
  		if(loopCnt<=5) bits[idx] |= (1 << cnt);
		
//        if ((micros() - t) > 40) bits[idx] |= (1 << cnt);  
        if (cnt == 0)   // next byte?  
        {  
            cnt = 7;     
            idx++;        
        }  
        else cnt--;  
    }  
  
    return 0;  
}  
//  
// END OF FILE  
//  