/***********************************************************************
 * Module:  DustHumidityEx.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:38:57
 * Purpose: Declaration of the class DustHumidityEx
 * Comment: 土壤湿度解析
 ***********************************************************************/

#if !defined(__AutoVeg_DustHumidityEx_h)
#define __AutoVeg_DustHumidityEx_h

#include <Expression.h>

class DustHumidityEx : public Expression
{
public:
   /* 执行key和value的操作 */
   int excute(int key, std::string value);

protected:
private:

};

#endif