/***********************************************************************
 * Module:  FileExecute.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:19:06
 * Purpose: Declaration of the class FileExecute
 * Comment: �ļ�ִ����
 ***********************************************************************/

#if !defined(__AutoVeg_FileExecute_h)
#define __AutoVeg_FileExecute_h

#include <string.h>

class FileExecute
{
public:
   /* ִ�з����ļ� */
   int ExecuteFile(char* content);

   Expression* expression;

protected:
private:
	/* ��ȡ��һ������*/
	int GetNextCmd();
	/* ִ������*/
	int ExecuteCmd();

	char * pStar;//�ļ��׵�ַ
	char * pCurrent;//�ļ���ǰ��ַ
	int length;
	

};

#endif
