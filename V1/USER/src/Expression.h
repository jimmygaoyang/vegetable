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
#include <string.h>
#define CONTRL_LIGHT_TIME 1
#define AIR_TEMPRATURE 2
#define AIR_HUMIDITY 3



class Expression
{
public:
   /* 执行key和value的操作 */
   virtual int excute(int key, char* value)=0;

protected:
private:

};

#endif
