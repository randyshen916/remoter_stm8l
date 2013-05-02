/**
  ******************************************************************************
  * @file Remoter.c
  * @brief This file contains all the functions for the Remoter driver.
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
#include "remoter.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* to avoid collusion, this value can be updated for thin adjust*/
#define CollusionAvoidAjust ((uint8_t)0)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public variables ---------------------------------------------------------*/
uint8_t Remoter_RealFrameLength = 14;
uint8_t Remoter_GlobalFrameLength = 64;
uint16_t Remoter_FrameBinaryFormat=0;
uint32_t Remoter_FrameManchestarFormat = 0;
uint8_t Send_Operation_Ready = 0x00;
uint8_t Send_Operation_Completed =0x01;
uint8_t BitsSent_Counter = 0x00;
/* Public functions ----------------------------------------------------------*/

/**
  * @addtogroup Remoter_Public_Functions
  * @{
  */

/**
  * @brief Generate the binary format of the Remoter frame.
  * @param[in] Remoter_Address : Select the device adress from @ref Remoter_Address_TypeDef enumeration.
	* @param[in] Remoter_Instruction : Select the device instruction from @ref Remoter_Instruction_TypeDef enumeration.
	* @param[in] Remoter_Ctrl : Select the device control bit status from @ref Remoter_Ctrl_TypeDef enumeration.
  * @retval Binary format of the Remoter Frame.
  */
uint16_t Remoter_BinFrameGeneration(Remoter_Address_TypeDef Remoter_Address, 
                           Remoter_Instruction_TypeDef Remoter_Instruction, 
									         Remoter_Ctrl_TypeDef Remoter_Ctrl)
{
	uint16_t star1 = 0x2000;
	uint16_t star2 = 0x1000;
	uint16_t addr = 0;
	
	while(Send_Operation_Completed == 0x00) 
	{ 
  }

	Send_Operation_Ready = 0;
	Remoter_FrameManchestarFormat = 0;
	Remoter_FrameBinaryFormat=0;
	addr = ((uint16_t)(Remoter_Address))<<6;
	Remoter_FrameBinaryFormat =  (star1)|(star2)|(Remoter_Ctrl)|(addr)|(Remoter_Instruction);
	return (Remoter_FrameBinaryFormat);
}


/**
  * @brief Convert the Remoter frame from binary to Manchester Format.
  * @param[in] Remoter_BinaryFrameFormat : the Remoter frame in binary format.
	* @retval  the Remoter frame in Manchester format.
  */

uint32_t Remoter_ManchesterConvert(uint16_t Remoter_BinaryFrameFormat)
{
	uint8_t i=0;
	uint16_t Mask = 1;
	uint16_t bit_format = 0;
	uint32_t ConvertedMsg =0;
  
	for (i=0;i<Remoter_RealFrameLength;i++)
	{
		bit_format =((((uint16_t)(Remoter_BinaryFrameFormat))>>i)& Mask)<<i;
		ConvertedMsg = ConvertedMsg << 2;
		
		if(bit_format != 0 )
		{
			ConvertedMsg|=0x02;
		}
		else        
		{
			ConvertedMsg|= 0x01;
    }
	}
	return (ConvertedMsg);
}

/**
  * @brief Send by hardware Manchester Format Remoter Frame.
  * @param[in] Remoter_BinaryFrameFormat : the Remoter frame in binary format.
	* @retval  the Remoter frame in Manchester format.
  */
void Remoter_SendFrame(uint32_t Remoter_ManchestarFrameFormat)
{
	uint8_t bit_msg = 0;
	
	if( (Send_Operation_Ready == 1) && (BitsSent_Counter <= ( (Remoter_GlobalFrameLength * 2)-CollusionAvoidAjust)))
	{
		Send_Operation_Completed = 0x00;
		bit_msg = (uint8_t)((Remoter_ManchestarFrameFormat >> BitsSent_Counter)& 1);
		
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
  * @brief Generate and Send the Remoter frame.
  * @param[in] Remoter_Address : the Remoter Device destination 
	* (a member of @ref Remoter_Address_TypeDef enumeration).
  * @param[in] Remoter_Instruction : the Remoter command instruction 
	* (a member of @ref Remoter_Address_TypeDef enumeration).
	* @param[in] Remoter_Ctrl : the Remoter Control bit
	* (a member of @ref Remoter_Ctrl_TypeDef enumeration).
  * @retval  None
  */
void SendFrame(Remoter_Address_TypeDef Remoter_Address, 
                           Remoter_Instruction_TypeDef Remoter_Instruction, 
								           Remoter_Ctrl_TypeDef Remoter_Ctrl)
{
	uint16_t Remoter_FrameBinaryFormat =0;
	
 //	GPIO_ResetBits(LEDS_PORT, LED_PIN);
	
	/* Generate a binary format of the Frame */
	Remoter_FrameBinaryFormat = Remoter_BinFrameGeneration(Remoter_Address, Remoter_Instruction, Remoter_Ctrl);
	
	/* Disable Interrupts */
	disableInterrupts();
	
	/* Generate a Manchester format of the Frame */
	Remoter_FrameManchestarFormat = Remoter_ManchesterConvert(Remoter_FrameBinaryFormat);
	
	/* Set the Send operation Ready flag to indicate that the frame is ready to be sent */
	Send_Operation_Ready = 1;
	
  /* Enable Interrupts */
	enableInterrupts();
	
//	 GPIO_SetBits(LEDS_PORT, LED_PIN);
	 
}



/**
  * @brief Reverse the Control bit of the Remoter Frame.
  * @param[in] Remoter_Ctrl : the Remoter Control present state (a member of the @ref Remoter_Ctrl_TypeDef enumeration).
	* @retval the new Remoter Control state (a member of the @ref Remoter_Ctrl_TypeDef enumeration).
  */
Remoter_Ctrl_TypeDef Remoter_CtrlBitReverse(Remoter_Ctrl_TypeDef Remoter_Ctrl)
{
	if(Remoter_Ctrl !=Remoter_Ctrl_Reset)
	{
		/* Reset the Control bit of the Remoter Frame*/
		Remoter_Ctrl = Remoter_Ctrl_Reset;
	}
	else
	{
		/* Set the Control bit of the Remoter Frame*/
		Remoter_Ctrl = Remoter_Ctrl_Set;
	}
	return (Remoter_Ctrl_TypeDef)Remoter_Ctrl;
}

/**
  * @brief Configurate TIM2.
  * @param[in] uint16_t freq kHz
  * @retval  None
  */
void Remoter_carrFreq_Set(uint16_t freq)
{

	uint16_t count;

	count = 16000/freq;

	/* DeInit TIM2 */
	TIM2_DeInit();
	
	/* TIM2 Time base configuration */
       TIM2_TimeBaseInit(TIM2_Prescaler_1, TIM2_CounterMode_Up, count );
	
	/* TIM2 channel 1 configuration */
	TIM2_OC1Init(TIM2_OCMode_PWM1, TIM2_OutputState_Enable, 110, TIM2_OCPolarity_High, TIM2_OCIdleState_Reset );
	
	/* TIM2 Counter Enable */
	TIM2_Cmd(ENABLE);
	
	/* Enable the TIM2 channel1 output to be connected internly to the IRTIM*/
	TIM2_CtrlPWMOutputs(ENABLE);
}





/**
  * @brief Remoter single frame set
  * @param[in] None
  * @retval  None
  */
void Remoter_frame_set(uint16_t frame_length)
{
	uint16_t count;
	/* DeInit TIM3 */
	TIM3_DeInit();

	count=frame_length*0x10;
  
	/* TIM3 Time base configuration */
	TIM3_TimeBaseInit(TIM3_Prescaler_1, TIM3_CounterMode_Up, count );
  
	/* TIM3 channel 1 configuration */
	TIM3_OC1Init(TIM3_OCMode_Timing, TIM3_OutputState_Enable, 14000, TIM3_OCPolarity_High, TIM3_OCIdleState_Reset );
	
	/* TIM3 interrupt Update Enable */
	TIM3_ITConfig(TIM3_IT_Update, ENABLE);
	
	/* TIM3 Counter Enable */
	TIM3_Cmd(ENABLE);
	/* Enable the TIM3 channel1 output to be connected internly to the IRTIM*/
	TIM3_CtrlPWMOutputs(ENABLE);
}
/**



/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
