/***********************************************************************
 * Module:  AirTemperEx.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:37:56
 * Purpose: Declaration of the class AirTemperEx
 * Comment: �����¶Ƚ���
 ***********************************************************************/

#if !defined(__AutoVeg_AirTemperEx_h)
#define __AutoVeg_AirTemperEx_h

#include "Expression.h"

class AirTemperEx : public Expression
{
public:
   /* ִ��key��value�Ĳ��� */
   int excute(int key, char* value);

protected:
private:

};

#endif
