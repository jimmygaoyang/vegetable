/***********************************************************************
 * Module:  LightControlEx.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:42:44
 * Purpose: Declaration of the class LightControlEx
 * Comment: �ƹ⿪�տ���
 ***********************************************************************/

#if !defined(__AutoVeg_LightControlEx_h)
#define __AutoVeg_LightControlEx_h

#include <Expression.h>

class LightControlEx : public Expression
{
public:
   /* ִ��key��value�Ĳ��� */
   int excute(int key, std::string value);

protected:
private:

};

#endif