#ifndef _BUFFTYPE_H
#define _BUFFTYPE_H

typedef struct CIRCLE_BUFFER_T
{
	unsigned int volatile  head;
	unsigned int volatile  tail;  
	char *    dataBuf;
	unsigned int volatile maxLen;
	unsigned int volatile typeLen;
	unsigned int volatile currentCnt;
	void (*Init)(void *, char *,unsigned int,unsigned int);
	void (*AddNew)(void *,char *);
	void (*ReadAll)(void *,char *,unsigned int *);
}circle_buffer_t;

void Init(void *pHandle,char *buf,unsigned int bufLen,unsigned int typeLen);
void AddNew(void *pHandle,char *pDat);
void ReadAll(void *pHandle, char * output, unsigned int * outLen);


#define CIRCLE_BUFFER_DEFAULTS    { 0,\
        0,\
        (char *)NULL,\
        0,\
        0,\
        0,\
        Init,\
        AddNew,\
        ReadAll} 

typedef struct GPS_LOCATION_T
{
	double  latitude;//γ��
	double 	longitude;//����
	double  hightitude;//�߶�

}gps_location_t;

typedef struct GSM_LOCATION_T
{
	unsigned short  cellID;//��վ��
	unsigned short lac;//С����
	unsigned short rssi;//�źŽ���ǿ��

}gsm_location_t;


typedef struct LOCATION_BUFFER_T
{
	int gpsMode;
	char gsmNum;
	gps_location_t gpsLocation;
	gsm_location_t gsmLocation[3];
}location_buffer_t;

//դ����Χ����
typedef struct FENCE_BUFFER_T
{
	double centerLng;
	double centerLat;
	double radius;
		
}fence_buffer_t;

struct STATUS{//�ܹ��ܿ���
		char reserve:4;
		char initFlag:1;
		char infoUpdate:1;
		char tripMode:1;
		char frequceyMode:1;
	};
typedef union STATUS_WORD{
	char all;
	struct STATUS bit;
	}status_word_t;






#endif
