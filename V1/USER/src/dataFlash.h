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

#define MACHINE_NUM_ADRESS 0x801FC00   	//机器编号127K
#define MACHINE_NUM_LEN 10	
#define CURRENT_VER_ADRESS 0x801FC14			//当前程序版本号
#define VER_LEN 4
#define NEW_VER_ADRESS 0x801FC18			//新程序版本号
#define FILE_LEN 0x801FC1C			//新程序大小
#define CURRENT_BLOCK_NUM 0x801FC20			//当前升级到那一个程序块了
#define VEG_FILE_LEN 0x801FC24			//种植文件长度
#define VEG_FILE 0x801FC28			//种植文件起始地址


int Flash_Read(unsigned int  iAddress, unsigned char *buf, int iNbrToRead) ;
int Flash_Write(unsigned  iAddress, unsigned char *buf, unsigned iNbrToWrite);


	 #ifdef __cplusplus
}
#endif

#endif



