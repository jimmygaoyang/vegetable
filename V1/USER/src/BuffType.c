#include "BuffType.h"
#include <string.h>

void Init(void *pHandle,char *buf, unsigned int bufLen, unsigned int typeLen)
{
	circle_buffer_t *p= (circle_buffer_t*)pHandle;
	p->dataBuf = buf;
	p->maxLen = bufLen;
	p->typeLen= typeLen;
	p->head = 0;
	p->tail = 0;
	p->currentCnt = 0;
}
void AddNew(void *pHandle, char* pdat)
{
	circle_buffer_t *p= (circle_buffer_t*)pHandle;

	memcpy((void *)(p->dataBuf + p->tail* (p->typeLen)), pdat, p->typeLen);
	
	if(p->currentCnt < p->maxLen)
		p->currentCnt++;


	
	if(p->currentCnt == p->maxLen)
	{
		
		if(p->head+1 == p->maxLen)
			p->head = 0;
		else
			p->head++;
			
	}
		
		

			
	//获取下一个位置
	if(p->tail+1 == p->maxLen)
	{
		p->tail = 0;
	}
	else
		p->tail++;
	//是否头尾相等

	
}
void ReadAll(void *pHandle, char * output, unsigned int * outLen)
{
	circle_buffer_t *p= (circle_buffer_t*)pHandle;
	int pos;
	int realhead;
	int realtail;
	unsigned i = 0;

	if(p->currentCnt == 0)
	{
		*outLen = 0;
		return;
	}
		
	
	//真实头
	if (p->head == 0)
		realhead = 4;
	else
		realhead = p->head-1;
	//真实尾
	if (p->tail == 0)
		realtail = 4;
	else
		realtail = p->tail-1;
	
	pos = realhead;
		
	
	while(1)
	{
		memcpy(output+i*(p->typeLen), (void *)(p->dataBuf+pos*(p->typeLen)),p->typeLen);
//		*(output+i) = p->dataBuf[pos];
		i++;
		if(pos == realtail)
			break;		
		if(pos+1 == p->maxLen)
			pos = 0;
		else
			pos++;				
	}
	*outLen = i;

}

