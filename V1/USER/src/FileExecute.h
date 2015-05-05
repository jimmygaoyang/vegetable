/***********************************************************************
 * Module:  FileExecute.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:19:06
 * Purpose: Declaration of the class FileExecute
 * Comment: 文件执行类
 ***********************************************************************/

#if !defined(__AutoVeg_FileExecute_h)
#define __AutoVeg_FileExecute_h

#include <string.h>
#include "Expression.h"

class FileExecute
{
public:
   /* 执行方案文件 */
   int ExecuteFile(char* content);

   Expression* expression;

protected:
private:
	/* 获取下一条命令*/
	int GetNextCmd(char *cmd, int &cmdLen);
	/* 执行命令*/
	int ExecuteCmd(char *cmd, int cmdLen);

	char * pStar;//文件首地址
	char * pCurrent;//文件当前地址
	int length;
	

};

#endif
