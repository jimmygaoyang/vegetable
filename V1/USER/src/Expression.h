/***********************************************************************
 * Module:  Expression.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:27:30
 * Purpose: Declaration of the class Expression
 * Comment: ������
 ***********************************************************************/
/***********************************************************************
 * Module:  Expression.java
 * Author:  Thinkpad
 * Purpose: Defines the Class Expression
 ***********************************************************************/

#if !defined(__AutoVeg_Expression_h)
#define __AutoVeg_Expression_h

class Expression
{
public:
   /* ִ��key��value�Ĳ��� */
   virtual int excute(int key, std::string value)=0;

protected:
private:

};

#endif