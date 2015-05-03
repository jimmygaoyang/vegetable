/***********************************************************************
 * Module:  LightControlEx.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:42:44
 * Purpose: Declaration of the class LightControlEx
 * Comment: 灯光开闭控制
 ***********************************************************************/

#if !defined(__AutoVeg_LightControlEx_h)
#define __AutoVeg_LightControlEx_h

#include <Expression.h>

class LightControlEx : public Expression
{
public:
   /* 执行key和value的操作 */
   int excute(int key, std::string value);

protected:
private:

};

#endif