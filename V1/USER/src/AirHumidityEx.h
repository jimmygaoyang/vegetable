/***********************************************************************
 * Module:  AirHumidityEx.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:38:45
 * Purpose: Declaration of the class AirHumidityEx
 * Comment: ����ʪ�ȿ���
 ***********************************************************************/

#if !defined(__AutoVeg_AirHumidityEx_h)
#define __AutoVeg_AirHumidityEx_h

#include <Expression.h>

class AirHumidityEx : public Expression
{
public:
   /* ִ��key��value�Ĳ��� */
   int excute(int key, std::string value);

protected:
private:

};

#endif