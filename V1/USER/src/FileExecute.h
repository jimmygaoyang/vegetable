/***********************************************************************
 * Module:  FileExecute.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:19:06
 * Purpose: Declaration of the class FileExecute
 * Comment: 文件执行类
 ***********************************************************************/

#if !defined(__AutoVeg_FileExecute_h)
#define __AutoVeg_FileExecute_h

class Expression;

class FileExecute
{
public:
   /* 执行方案文件 */
   int ExecuteFile(std::string content);

   Expression** expression;

protected:
private:

};

#endif