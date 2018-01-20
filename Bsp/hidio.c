
#include "hidio.h"
#include "usb.h"
#include "usbcore.h"
#include "usbhw.h"
#include "hiduser.h"
                                           
HIDFrame  gInFrame;  
HIDFrame  gOutFrame;			 

uint8_t usbOutFlag = 0;
uint8_t usbInBusy = 1;


void InitInFrame(void)
{
	uint8_t i;
	
 	gInFrame.Formate.Addr = 0xAA;

 	for(i=1;i<ENDPOINT1SIZE;i++)
	{
		gInFrame.Buffer[i] = 0;
	}

	return;
}


void SetInFrame(uint8_t funsort, uint8_t len, uint8_t *dat)
{
	uint8_t i;

	if(len>(ENDPOINT1SIZE-3))
	{
		return;
	}

	gInFrame.Formate.Sort = funsort;
	gInFrame.Formate.Len = len;

	for(i=0;i<len;i++)
	{
		gInFrame.Formate.Data[i]=dat[i];
	}

	return ;
}


void SendInFrameToEndpoint(void)
{ 
	USB_WriteEP(HID_EP_IN, gInFrame.Buffer, 8);
    usbInBusy = 1;
}


void SetOutFrame(void)
{
	uint8_t i;

	gOutFrame.Formate.Addr = EP0Buf[0];
	gOutFrame.Formate.Sort = EP0Buf[1];
	gOutFrame.Formate.Len  = EP0Buf[2];

	for(i=0;i<gOutFrame.Formate.Len;i++)
	{
		gOutFrame.Formate.Data[i] = EP0Buf[3+i]; 
	}

	usbOutFlag = 1;	 

	return ;
}



