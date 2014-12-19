#include "LOGCTRL.h"

#ifndef NO_POS_DEBUG
#include <string.h>
#include <stdio.h>
#include "usart.h"
#include "pos_debug.h"



static char _dbg_buf_[1024];


void _dbg_file_ (const char * _file_name_,
						unsigned int _line_no_)
{ 
	 memset((void*) _dbg_buf_,0, sizeof(_dbg_buf_));
	 sprintf(_dbg_buf_,"%s %4d: ",_file_name_,_line_no_);
}

void _dbg_pargs_ (const char *fmt,...)
{
	 va_list args;	 
	 va_start(args, fmt);   
	 vsprintf(_dbg_buf_+strlen(_dbg_buf_), fmt, args);
	 va_end(args);
	 PUT(_dbg_buf_);
	 PUT("\r\n");
}


#endif
