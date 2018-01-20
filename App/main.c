
#include "LPC17xx.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_nvic.h"
#include "usbhw.h"
#include "uart.h"
#include "dispose.h"
#include "hidio.h"

int main(void)
{
  SystemInit();
  NVIC_DeInit();
  NVIC_SCBDeInit();
  NVIC_SetPriorityGrouping(0x02);
  UartInit();
  USB_Init();
  USB_Connect(__TRUE);
  InitInFrame();

   while(1)
   {
	  Dispose();
   }
}































/**以下部分请勿删**/

#ifdef  DEBUG
/*******************************************************************************
* @brief		Reports the name of the source file and the source line number
* 				where the CHECK_PARAM error has occurred.
* @param[in]	file Pointer to the source file name
* @param[in]    line assert_param error line source number
* @return		None
*******************************************************************************/
void check_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while(1);
}
#endif

/*
 * @}
 */


