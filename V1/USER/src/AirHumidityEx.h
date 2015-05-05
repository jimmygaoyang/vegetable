/***********************************************************************
 * Module:  AirHumidityEx.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:38:45
 * Purpose: Declaration of the class AirHumidityEx
 * Comment: 空气湿度控制
 ***********************************************************************/

#if !defined(__AutoVeg_AirHumidityEx_h)
#define __AutoVeg_AirHumidityEx_h

#include "Expression.h"

class AirHumidityEx : public Expression
{
public:
   /* 执行key和value的操作 */
   int excute(int key, char* value);

protected:
private:

};

#endif
