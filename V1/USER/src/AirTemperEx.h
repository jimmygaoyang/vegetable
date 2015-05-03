/***********************************************************************
 * Module:  AirTemperEx.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:37:56
 * Purpose: Declaration of the class AirTemperEx
 * Comment: 空气温度解析
 ***********************************************************************/

#if !defined(__AutoVeg_AirTemperEx_h)
#define __AutoVeg_AirTemperEx_h

#include <Expression.h>

class AirTemperEx : public Expression
{
public:
   /* 执行key和value的操作 */
   int excute(int key, std::string value);

protected:
private:

};

#endif