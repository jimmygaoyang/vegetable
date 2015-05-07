#ifndef   __DATAFLASH_H__
#define   __DATAFLASH_H__


#include "stm32f10x.h"
#include "stm32f10x_flash.h"

#ifdef __cplusplus
 extern "C" {
#endif

/*#if defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
  #define FLASH_PAGE_SIZE    ((uint16_t)0x800)
  
#else*/
  #define FLASH_PAGE_SIZE    ((uint16_t)0x400)
//#endif

#define MACHINE_NUM_ADRESS 0x801FC00   	//�������127K
#define MACHINE_NUM_LEN 10	
#define CURRENT_VER_ADRESS 0x801FC14			//��ǰ����汾��
#define VER_LEN 4
#define NEW_VER_ADRESS 0x801FC18			//�³���汾��
#define FILE_LEN 0x801FC1C			//�³����С
#define CURRENT_BLOCK_NUM 0x801FC20			//��ǰ��������һ���������
#define VEG_FILE_LEN 0x801FC24			//��ֲ�ļ�����
#define VEG_FILE 0x801FC28			//��ֲ�ļ���ʼ��ַ


int Flash_Read(unsigned int  iAddress, unsigned char *buf, int iNbrToRead) ;
int Flash_Write(unsigned  iAddress, unsigned char *buf, unsigned iNbrToWrite);


	 #ifdef __cplusplus
}
#endif

#endif



