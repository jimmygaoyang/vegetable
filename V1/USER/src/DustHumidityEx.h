/***********************************************************************
 * Module:  DustHumidityEx.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:38:57
 * Purpose: Declaration of the class DustHumidityEx
 * Comment: ����ʪ�Ƚ���
 ***********************************************************************/

#if !defined(__AutoVeg_DustHumidityEx_h)
#define __AutoVeg_DustHumidityEx_h

#include <Expression.h>

class DustHumidityEx : public Expression
{
public:
   /* ִ��key��value�Ĳ��� */
   int excute(int key, std::string value);

protected:
private:

};

#endif