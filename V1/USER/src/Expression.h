/***********************************************************************
 * Module:  Expression.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:27:30
 * Purpose: Declaration of the class Expression
 * Comment: 解释器
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
   /* 执行key和value的操作 */
   virtual int excute(int key, std::string value)=0;

protected:
private:

};

#endif