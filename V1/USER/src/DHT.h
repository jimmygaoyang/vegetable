//   
//    FILE: dht.h  
// VERSION: 0.1.01  
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino  
//  
//     URL: http://arduino.cc/playground/Main/DHTLib  
//  
// HISTORY:  
// see dht.cpp file  
//   
  
#ifndef dht_h  
#define dht_h  

  
#define DHT_LIB_VERSION "0.1.01"  
  
class dht  
{  
public:  
    int read11(unsigned char pin);  
    int read22(unsigned char pin);  
    double humidity;  
    double temperature;  
  
private:  
    unsigned char  bits[5];  // buffer to receive data  
    int read(unsigned char pin);  
};  
#endif  
//  
// END OF FILE  
//  
