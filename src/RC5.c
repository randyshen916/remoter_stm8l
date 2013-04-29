/**
  ******************************************************************************
  * @file rc5.c
  * @brief This file contains all the functions for the RC5 driver.
  * @author STMicroelectronics - MCD Application Team
  * @version V1.1.0
  * @date    09/14/2009
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  * @image html logo.bmp
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/	
#include "rc5.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* to avoid collusion, this value can be updated for thin adjust*/
#define CollusionAvoidAjust ((uint8_t)0)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public variables ---------------------------------------------------------*/
uint8_t RC5_RealFrameLength = 14;
uint8_t RC5_GlobalFrameLength = 64;
uint16_t RC5_FrameBinaryFormat=0;
uint32_t RC5_FrameManchestarFormat = 0;
uint8_t Send_Operation_Ready = 0x00;
uint8_t Send_Operation_Completed =0x01;
uint8_t BitsSent_Counter = 0x00;
/* Public functions ----------------------------------------------------------*/

/**
  * @addtogroup RC5_Public_Functions
  * @{
  */

/**
  * @brief Generate the binary format of the RC5 frame.
  * @param[in] RC5_Address : Select the device adress from @ref RC5_Address_TypeDef enumeration.
	* @param[in] RC5_Instruction : Select the device instruction from @ref RC5_Instruction_TypeDef enumeration.
	* @param[in] RC5_Ctrl : Select the device control bit status from @ref RC5_Ctrl_TypeDef enumeration.
  * @retval Binary format of the RC5 Frame.
  */
uint16_t RC5_BinFrameGeneration(RC5_Address_TypeDef RC5_Address, 
                           RC5_Instruction_TypeDef RC5_Instruction, 
									         RC5_Ctrl_TypeDef RC5_Ctrl)
{
	uint16_t star1 = 0x2000;
	uint16_t star2 = 0x1000;
	uint16_t addr = 0;
	
	while(Send_Operation_Completed == 0x00) 
	{ 
  }

	Send_Operation_Ready = 0;
	RC5_FrameManchestarFormat = 0;
	RC5_FrameBinaryFormat=0;
	addr = ((uint16_t)(RC5_Address))<<6;
	RC5_FrameBinaryFormat =  (star1)|(star2)|(RC5_Ctrl)|(addr)|(RC5_Instruction);
	return (RC5_FrameBinaryFormat);
}


/**
  * @brief Convert the RC5 frame from binary to Manchester Format.
  * @param[in] RC5_BinaryFrameFormat : the RC5 frame in binary format.
	* @retval  the RC5 frame in Manchester format.
  */

uint32_t RC5_ManchesterConvert(uint16_t RC5_BinaryFrameFormat)
{
	uint8_t i=0;
	uint16_t Mask = 1;
	uint16_t bit_format = 0;
	uint32_t ConvertedMsg =0;
  
	for (i=0;i<RC5_RealFrameLength;i++)
	{
		bit_format =((((uint16_t)(RC5_BinaryFrameFormat))>>i)& Mask)<<i;
		ConvertedMsg = ConvertedMsg << 2;
		
		if(bit_format != 0 )
		{
		//	ConvertedMsg|= 0b10;
		}
		else        
		{
		//	ConvertedMsg|= 0b01;
    }
	}
	return (ConvertedMsg);
}

/**
  * @brief Send by hardware Manchester Format RC5 Frame.
  * @param[in] RC5_BinaryFrameFormat : the RC5 frame in binary format.
	* @retval  the RC5 frame in Manchester format.
  */
void RC5_SendFrame(uint32_t RC5_ManchestarFrameFormat)
{
	uint8_t bit_msg = 0;
	
	if( (Send_Operation_Ready == 1) && (BitsSent_Counter <= ( (RC5_GlobalFrameLength * 2)-CollusionAvoidAjust)))
	{
		Send_Operation_Completed = 0x00;
		bit_msg = (uint8_t)((RC5_ManchestarFrameFormat >> BitsSent_Counter)& 1);
		
		if (bit_msg== 1)
		{
			TIM3_ForcedOC1Config(TIM3_ForcedAction_Active);
		}
		else
		{
			TIM3_ForcedOC1Config(TIM3_ForcedAction_Inactive);
		}
		BitsSent_Counter++;
	}
	else
	{
		Send_Operation_Completed = 0x01;
		Send_Operation_Ready = 0;
		BitsSent_Counter=0;
		TIM3_ForcedOC1Config(TIM3_ForcedAction_Inactive);
	}
}

/**
  * @brief Reverse the Control bit of the RC5 Frame.
  * @param[in] RC5_Ctrl : the RC5 Control present state (a member of the @ref RC5_Ctrl_TypeDef enumeration).
	* @retval the new RC5 Control state (a member of the @ref RC5_Ctrl_TypeDef enumeration).
  */
RC5_Ctrl_TypeDef RC5_CtrlBitReverse(RC5_Ctrl_TypeDef RC5_Ctrl)
{
	if(RC5_Ctrl !=RC5_Ctrl_Reset)
	{
		/* Reset the Control bit of the RC5 Frame*/
		RC5_Ctrl = RC5_Ctrl_Reset;
	}
	else
	{
		/* Set the Control bit of the RC5 Frame*/
		RC5_Ctrl = RC5_Ctrl_Set;
	}
	return (RC5_Ctrl_TypeDef)RC5_Ctrl;
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
