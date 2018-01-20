#ifndef _HIDIO_H
#define _HIDIO_H

#include <stdint.h>

#include "usbdesc.h"
#include "usbcfg.h"
 
typedef union   
{
	struct
	{
			uint8_t		Addr;  
			uint8_t		Sort; 
			uint8_t		Len;	
			uint8_t		Data[ENDPOINT1SIZE-3];		
	}Formate;  
	uint8_t Buffer[ENDPOINT1SIZE];	
}HIDFrame;


extern uint8_t   InReport[ENDPOINT1SIZE];                                                 
extern HIDFrame  gInFrame;  
extern HIDFrame  gOutFrame;			 
extern uint8_t   usbOutFlag;
extern uint8_t   usbInBusy;

void InitInFrame(void);
void SetInFrame(uint8_t funsort, uint8_t len, uint8_t *dat);
void SendInFrameToEndpoint(void);
void SetOutFrame(void);

#endif


