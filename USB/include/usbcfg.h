/*----------------------------------------------------------------------------
 * U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    usbcfg.h
 * Purpose: USB Custom Configuration
 * Version: V1.20
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------
 * History:
 *          V1.20 Added vendor specific support
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

#ifndef __USBCFG_H__
#define __USBCFG_H__

/*
USB Configuration
*/

#define USB_POWER           0
#define USB_IF_NUM          1
#define USB_EP_NUM          32
#define USB_MAX_PACKET0     16
#define USB_DMA             0
#define USB_DMA_EP          0x00000000

/*
USB Event Handlers
*/

#define USB_POWER_EVENT     0
#define USB_RESET_EVENT     1
#define USB_SUSPEND_EVENT   0
#define USB_RESUME_EVENT    0
#define USB_WAKEUP_EVENT    0
#define USB_SOF_EVENT       0
#define USB_ERROR_EVENT     0
#define USB_EP_EVENT        0x0003
#define USB_CONFIGURE_EVENT 1
#define USB_INTERFACE_EVENT 0
#define USB_FEATURE_EVENT   0


/*
 USB Class Support
*/
#define USB_CLASS           1
#define USB_HID             1
#define USB_HID_IF_NUM      0
#define USB_MSC             0
#define USB_MSC_IF_NUM      0
#define USB_AUDIO           0
#define USB_ADC_CIF_NUM     0
#define USB_ADC_SIF1_NUM    1
#define USB_ADC_SIF2_NUM    2
#define USB_CDC  			0
#define USB_CDC_CIF_NUM     0
#define USB_CDC_DIF_NUM     1
#define USB_CDC_BUFSIZE     64

/*
 USB Vendor Support
*/
#define USB_VENDOR          0


#endif  /* __USBCFG_H__ */
