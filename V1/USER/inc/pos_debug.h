/*! \file pos_debug.h
   \brief ���ļ���Ҫ������һЩͨ�õ��Խӿ�,����������ڡ����ڵ��Խӿ�
		  ��ͨ������Ϣ��ӡ�ӿڣ����Խӿ�
   \author zyk
   \version  1.0
   \date    20060620
 */

#ifndef POS_DEBUG_ZYK_H
#define POS_DEBUG_ZYK_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdlib.h>
#include <stdarg.h>


#ifdef NO_POS_DEBUG
#undef POS_DBGPRN_ON
#endif

#if !defined(POS_DBGPRN_ON)
#define NO_POS_DEBUG
#endif
	
#ifndef NO_POS_DEBUG

	extern void _dbg_file_ (const char * _file_name_,
						unsigned int _line_no_);	/*! \brief ��¼�ļ������кš��ؼ�����Ϣ
		\param[in] _keyword_ �ؼ���
		\param[in] _file_name_ �ļ���
		\param[in] _line_no_ �к�
	*/
	extern void _dbg_pargs_ (const char *fmt,...);
#endif

#ifndef POS_DBGPRN_ON
	#define DBG_PRN(X)
	#define PUT(x) 
#else
//	#define DBG_PRN(fmt,...)   { memset((void*) _dbg_buf_,0,sizeof(_dbg_buf_)); sprintf( _dbg_buf_,"%s %4d: \"fmt\"\r\n", __FILE__, __LINE__, ##__VA_ARGS__);PUT(_dbg_buf_);}
#define DBG_PRN(X) {_dbg_file_(__FILE__,__LINE__); _dbg_pargs_ X; }


	#define PUT(x) {usart3_send_str(x);}
#endif


#define DBG_NPRINT_HEX(buf, n)		\
{\
	int i;\
	int row = n/8;\
	int remain = n%8;\
	for (i=0; i<row; i++)\
		DBG_PRN(("%02x %02x %02x %02x %02x %02x %02x %02x", \
				buf[i*8], buf[i*8+1], buf[i*8+2], buf[i*8+3], buf[i*8+4], buf[i*8+5], buf[i*8+6], buf[i*8+7]));\
	switch(remain) {\
		case 1:\
			DBG_PRN(("%02x", buf[row*8]));\
			break;\
		case 2:\
			DBG_PRN(("%02x %02x", buf[row*8], buf[row*8+1]));\
			break;\
		case 3:\
			DBG_PRN(("%02x %02x %02x", \
				buf[row*8], buf[row*8+1], buf[row*8+2]));\
			break;\
		case 4:\
			DBG_PRN(("%02x %02x %02x %02x", \
				buf[row*8], buf[row*8+1], buf[row*8+2], buf[row*8+3]));\
			break;\
		case 5:\
			DBG_PRN(("%02x %02x %02x %02x %02x", \
				buf[row*8], buf[row*8+1], buf[row*8+2], buf[row*8+3], buf[row*8+4]));\
			break;\
		case 6:\
			DBG_PRN(("%02x %02x %02x %02x %02x %02x", \
				buf[row*8], buf[row*8+1], buf[row*8+2], buf[row*8+3], buf[row*8+4], buf[row*8+5]));\
			break;\
		case 7:\
			DBG_PRN(("%02x %02x %02x %02x %02x %02x %02x", \
				buf[row*8], buf[row*8+1], buf[row*8+2], buf[row*8+3], buf[row*8+4], buf[row*8+5], buf[row*8+6]));\
			break;\
		default:\
			break;\
	}\
}


#ifdef __cplusplus
}
#endif


#endif

