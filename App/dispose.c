
#include "uart.h"
#include "dispose.h"
#include "hidio.h"

typedef struct
{
	uint8_t cmd;
	uint8_t data;

}ComData;

ComData g_ComData;
static uint8_t cmd_flag=0;

/*
功  能：从缓冲区读取数据
参  数： 1、数据存放地址
		 2、要读多少字节0~128

说  明：此处无校验，请自行注意数据存放区域大小
*/
int32_t InquireUartRecvBuffer(uint8_t *pBuf, int8_t MaxBuffCount)
{
	int8_t i = 0;
	int8_t RcvCount = 0;

	while((FifoHead != FifoTail) && (MaxBuffCount > 0))
	{
		pBuf[i++] = FifoBuff[FifoTail];
		FifoBuff[FifoTail] = 0;
		FifoTail = (FifoTail + 1)%FIFO_SIZE;
		MaxBuffCount--;
		RcvCount++;
	}
	
	return RcvCount;
}

/*
功  能：校验读出的数据
参  数：待解析字节
*/
void CheckData(uint8_t byte)
{
	static uint8_t state=0;

	switch(state)
	{
		case 0:
		{
			 if(byte==0xaa)
			 {
			 	state=1;
			 }
			 else
			 {
			 	state=0;
			 }
		}
		break;

		case 1:
		{
			 g_ComData.data=byte;
			 state=2;
		}
		break;

		case 2:
		{
			 g_ComData.cmd=byte;
			 cmd_flag=1;
			 state=0;
		}
		break;

		default:
			break;
	}

	return;

}

/*
*功  能: 对接收的数据进行解析

*说  明：此处请按照通信协议，重写
*/
void Dispose(void)
{
	uint8_t tmp[8]={0};
	uint8_t count;
	uint8_t i;

	count=InquireUartRecvBuffer(tmp,8);
	if(count==0)
	{
		return;
	}

	for(i=0;i<count;i++)
	{
		CheckData(tmp[i]);
	}

	if(cmd_flag == 1)
	{	
		switch(g_ComData.cmd)
		{
			case 0x01:
			{
				gInFrame.Formate.Addr=0x00;
				gInFrame.Formate.Sort=0x00;
				gInFrame.Formate.Len=0x05;
				SendInFrameToEndpoint();
				UART3SendData(0x04);
			}
			break;
			
			case 0x02:
			{

			}
			break;
			
			case 0x03:
			{

			}
			break;
			
			default:
				break;	
		}

		cmd_flag=0;
	}
}




