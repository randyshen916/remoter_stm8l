/**
  ******************************************************************************
  * @file main.c
  * @brief This file contains the main function for AN.
  * @author STMicroelectronics - MCD Application Team
  * @version V1.1.0
  * @date    09/14/2009
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  * @image html logo.bmp
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

#include "remoter.h"

//#include "myMath.h"

 extern RemoterData remoterData;


/**
  * @brief Application main entry point.
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  * @par Library functions called:
  */
void main(void)
{
//	uint32_t buf[4]={0x55,0x55,0x55,0x55};
	//uint8_t i;
	stm8l_initial();

	
	while(1)
	{

//	Rshift(buf,4,56);
//	Remoter_BinFrameGeneration();
	
		/* Check button status */
    if ((GPIO_ReadInputData(BUTTON_PORT) & BUTTON_PIN) == (uint8_t)0x00)
    {
      /* Button is pressed */
 	 //    Address=RC5_Address_TV1; 
	//	  Instruction=RC5_Instruction_VolumeUp;
	remoterData.remoteType=DTV_STD1;
	remoterData.custom1=0x57;
	remoterData.custom2=0x59;
	remoterData.custom3=0x58;
	remoterData.data1=0xaa;
	remoterData.data2=0xa0;
		  SendFrame();
			
			/* LEDs reverse */
     // GPIO_ToggleBits(LEDS_PORT, LED_PIN);
    }

   
   
 
	
//	 halt();
  }
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
