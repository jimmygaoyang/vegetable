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
#include "GlobalIOSet.h"
  
class dht  
{  
public:  
    int read11(CIOObject * pin);  
    int read22(CIOObject * pin);  
    double humidity;  
    double temperature;  
  
private:  
    unsigned char  bits[5];  // buffer to receive data  
    int read(CIOObject * pin);  
};  
#endif  
//  
// END OF FILE  
//  
