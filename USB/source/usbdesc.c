/*----------------------------------------------------------------------------
 * U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    usbdesc.c
 * Purpose: USB Descriptors
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
 *          V1.20 Changed string descriptor handling
 *                Changed HID Report Descriptor
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

#include "type.h"
#include "usb.h"
#include "usbcfg.h"
#include "hid.h"
#include "usbdesc.h"

#define HID_INPUT_REPORT_BYTES       8              /* size of report in Bytes */
#define HID_OUTPUT_REPORT_BYTES      8              /* size of report in Bytes */
#define HID_FEATURE_REPORT_BYTES     1              /* size of report in Bytes */

/*
*说明：返回的报告描述符有8字节
	   第一个字节：表特殊功能按键[E0:E7]
	   第二个字节：为保留值，写为0
	   第三至八字节：普通键键值数组，最多一次返回6个按键键值，超过返回0xFF
*/
const U8 HID_ReportDescriptor[] = {
 0x05, 0x01, //   USAGE_PAGE (Generic Desktop)
 0x09, 0x06, //   USAGE (Keyboard)
 0xa1, 0x01, //   COLLECTION (Application)
	
 0x05, 0x07, //   USAGE_PAGE (Keyboard/Keypad)
 0x19, 0xe0, //   USAGE_MINIMUM (Keyboard LeftControl)
 0x29, 0xe7, //   USAGE_MAXIMUM (Keyboard Right GUI)
 0x15, 0x00, //   LOGICAL_MINIMUM (0)
 0x25, 0x01, //   LOGICAL_MAXIMUM (1)
 0x95, 0x08, //   REPORT_COUNT (8)
 0x75, 0x01, //   REPORT_SIZE (1)
 0x81, 0x02, //   INPUT (Data,Var,Abs)
	
 0x95, 0x01, //   REPORT_COUNT (1)
 0x75, 0x08, //   REPORT_SIZE (8)
 0x81, 0x03, //   INPUT (Cnst,Var,Abs)
	
 0x95, 0x06, //   REPORT_COUNT (6)
 0x75, 0x08, //   REPORT_SIZE (8)
 0x15, 0x00,
 0x25, 0xFF, //   LOGICAL_MAXIMUM (255)
 0x05, 0x07,
 0x19, 0x00, //   USAGE_MINIMUM (Reserved (no event indicated))
 0x29, 0xff, //   USAGE_MAXIMUM (Keyboard Application)
 0x81, 0x00, //   INPUT (Data,Ary,Abs)
 
 0xc0        //   END_COLLECTION
};

const U16 HID_ReportDescSize = sizeof(HID_ReportDescriptor);


/* USB Standard Device Descriptor */
const U8 USB_DeviceDescriptor[] = {
  USB_DEVICE_DESC_SIZE,              /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,        /* bDescriptorType */
  WBVAL(0x0110), /* 2.00 */          /* bcdUSB */		 
  0x00,                              /* bDeviceClass */
  0x00,                              /* bDeviceSubClass */
  0x00,                              /* bDeviceProtocol */
  USB_MAX_PACKET0,                   /* bMaxPacketSize0 */
  WBVAL(0xC259),                     /* idVendor */
  WBVAL(0x2201),                     /* idProduct */
  WBVAL(0x0100), /* 1.00 */          /* bcdDevice */
  0x01,                              /* iManufacturer */
  0x02,                              /* iProduct */
  0x03,                              /* iSerialNumber */
  0x01                               /* bNumConfigurations: one possible configuration*/
};

/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor) */
const U8 USB_ConfigDescriptor[] = {
  USB_CONFIGUARTION_DESC_SIZE,       /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType */
  WBVAL(                             /* wTotalLength */
    USB_CONFIGUARTION_DESC_SIZE +
    USB_INTERFACE_DESC_SIZE     +
    HID_DESC_SIZE               +
    USB_ENDPOINT_DESC_SIZE	    +
	USB_ENDPOINT_DESC_SIZE
  ),
  0x01,                              /* bNumInterfaces */
  0x01,                              /* bConfigurationValue: 0x01 is used to select this configuration */
  0x00,                              /* iConfiguration: no string to describe this configuration */
  USB_CONFIG_BUS_POWERED /*|*/       /* bmAttributes */
/*USB_CONFIG_REMOTE_WAKEUP*/,
  USB_CONFIG_POWER_MA(100),          /* bMaxPower, device power consumption is 100 mA */

/* Interface 0, Alternate Setting 0, HID Class */
  USB_INTERFACE_DESC_SIZE,           /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,     /* bDescriptorType */
  0x00,                              /* bInterfaceNumber */
  0x00,                              /* bAlternateSetting */
  0x03,                              /* bNumEndpoints */
  USB_DEVICE_CLASS_HUMAN_INTERFACE,  /* bInterfaceClass */
  HID_SUBCLASS_NONE,                 /* bInterfaceSubClass */
  HID_PROTOCOL_NONE,                 /* bInterfaceProtocol */
  0x00,                              /* iInterface */
/* HID Class Descriptor */
/* HID_DESC_OFFSET = 0x0012 */
  HID_DESC_SIZE,                     /* bLength */
  HID_HID_DESCRIPTOR_TYPE,           /* bDescriptorType */
  WBVAL(0x0100), /* 1.00 */          /* bcdHID */
  0x00,                              /* bCountryCode */
  0x01,                              /* bNumDescriptors */
  HID_REPORT_DESCRIPTOR_TYPE,        /* bDescriptorType */
  WBVAL(HID_REPORT_DESC_SIZE),       /* wDescriptorLength */

/* Endpoint, HID Interrupt In */
  USB_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
  USB_ENDPOINT_IN(1),                /* bEndpointAddress */
  USB_ENDPOINT_TYPE_INTERRUPT,       /* bmAttributes */
  WBVAL(ENDPOINT1SIZE),              /* wMaxPacketSize */
  0x0a,         			         /* bInterval */

  /* Endpoint, HID Interrupt OUT */	
  USB_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
  USB_ENDPOINT_OUT(1),               /* bEndpointAddress */
  USB_ENDPOINT_TYPE_INTERRUPT,       /* bmAttributes */
  WBVAL(ENDPOINT1SIZE),              /* wMaxPacketSize */
  0x0a,         
  
  /* Endpoint, HID Interrupt In */
  USB_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
  USB_ENDPOINT_IN(4),                /* bEndpointAddress */
  USB_ENDPOINT_TYPE_INTERRUPT,       /* bmAttributes */
  WBVAL(ENDPOINT1SIZE),              /* wMaxPacketSize */
  0x0a,          
/* Terminator */

};


/* USB String Descriptor (optional) */
const U8 USB_StringDescriptor[] = {
/* Index 0x00: LANGID Codes */
  0x04,                              /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  WBVAL(0x0409), /* US English */    /* wLANGID */
/* Index 0x01: Manufacturer */
  (8*2 + 2),                        /* bLength (13 Char + Type + lenght) */
  USB_STRING_DESCRIPTOR_TYPE,       /* bDescriptorType */
  'A',0,
  'N',0,
  'A',0,
  'S',0,
  'O',0,
  'N',0,
  'I',0,
  'C',0,
/* Index 0x02: Product */
  (15*2 + 2),                        /* bLength (16 Char + Type + lenght) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  'K',0,
  'E',0,
  'Y',0,
  'B',0,
  'O',0,
  'A',0,
  'R',0,
  'D',0,
  ' ',0,
  'C',0,
  'O',0,
  'N',0,
  'F',0,
  'I',0,
  'G',0,
/* Index 0x03: Serial Number */
  (12*2 + 2),                        /* bLength (12 Char + Type + lenght) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  '0',0,                             /* allowed characters are       */
  '0',0,                             /*   0x0030 - 0x0039 ('0'..'9') */
  '0',0,                             /*   0x0041 - 0x0046 ('A'..'F') */
  '1',0,                             /*   length >= 26               */
  'A',0,
  '0',0,
  '0',0,
  '0',0,
  '0',0,
  '0',0,
  '0',0,
  '0',0,
/* Index 0x04: Interface 0, Alternate Setting 0 */
  ( 3*2 + 2),                        /* bLength (3 Char + Type + lenght) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  'H',0,
  'I',0,
  'D',0,
};
