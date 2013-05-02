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

/**
  * @addtogroup IRTIM_AN
  * @{
  */

/* Private typedef -----------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/





/* Public variables ---------------------------------------------------------*/

/**
  * @brief Application main entry point.
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  * @par Library functions called:
  */
void stm8l_initial(void)
{
	uint8_t i;
	
	/* Clock configuration */
	CLK_Config();
  
  /* TIM2 configuration */
	TIM2_Config();
	
	/* TIM3 configuration */
	TIM3_Config();
	
	/* TIM4 configuration */
	TIM4_Config();
	
	/* IRTIM configuration */
	IRTIM_Config();
	
	/* Initialize I/Os in Output Mode */
  GPIO_Init(LEDS_PORT, LED_PIN, GPIO_Mode_Out_PP_High_Fast);
  GPIO_Init(AUDIO_PORT, AUDIO_OUT, GPIO_Mode_Out_PP_Low_Fast);	
  GPIO_Init(BUTTON_PORT,BUTTON_PIN,GPIO_Mode_In_PU_No_IT);
  GPIO_Init(AUDIO_PORT,AUDIO_IN,GPIO_Mode_In_FL_IT);	 	
  EXTI_SetPinSensitivity(AUDIO_IN_EXTI, EXTI_Trigger_Falling_Low);
    /* Enable Interrupts */
	enableInterrupts();
	
//	 halt();
 
}
/* Private functions ---------------------------------------------------------*/
/**
  * @brief Generate a delay
  * @param[in] nCount : value of the delay
  * @retval  None
  */
void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}
/**
  * @brief Generate and Send the RC5 frame.
  * @param[in] RC5_Address : the RC5 Device destination 
	* (a member of @ref RC5_Address_TypeDef enumeration).
  * @param[in] RC5_Instruction : the RC5 command instruction 
	* (a member of @ref RC5_Address_TypeDef enumeration).
	* @param[in] RC5_Ctrl : the RC5 Control bit
	* (a member of @ref RC5_Ctrl_TypeDef enumeration).
  * @retval  None
  */

/**
  * @brief Configurate the Clock & enable the clock of TIM2 and TIM3.
  * @param[in] None
  * @retval  None
  */
void CLK_Config(void)
{
	/* Clock Master = 16 Mhz */
	CLK_MasterPrescalerConfig(CLK_MasterPrescaler_HSIDiv1);
  
	/* Enable TIM2 clock */
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
	
	/* Enable TIM3 clock */
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, ENABLE);
	
	/* Enable TIM4 clock */
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
}
/**
  * @brief Configurate TIM2.
  * @param[in] None
  * @retval  None
  */
void TIM2_Config(void)
{
	/* DeInit TIM2 */
	TIM2_DeInit();
	
	/* TIM2 Time base configuration */
       TIM2_TimeBaseInit(TIM2_Prescaler_1, TIM2_CounterMode_Up, 438 );
	
	/* TIM2 channel 1 configuration */
	TIM2_OC1Init(TIM2_OCMode_PWM1, TIM2_OutputState_Enable, 110, TIM2_OCPolarity_High, TIM2_OCIdleState_Reset );
	
	/* TIM2 Counter Enable */
	TIM2_Cmd(ENABLE);
	
	/* Enable the TIM2 channel1 output to be connected internly to the IRTIM*/
	TIM2_CtrlPWMOutputs(ENABLE);
}
/**
  * @brief Configurate TIM3.
  * @param[in] None
  * @retval  None
  */
void TIM3_Config(void)
{
	/* DeInit TIM3 */
	TIM3_DeInit();
  
	/* TIM3 Time base configuration */
	TIM3_TimeBaseInit(TIM3_Prescaler_1, TIM3_CounterMode_Up, 14224 );
  
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
  * @brief Configurate IRTIM.
  * @param[in] None
  * @retval  None
  */
void IRTIM_Config(void)
{
	/* DeInit IRTIM */
	IRTIM_DeInit();
	/* Enable IRTIM */
	IRTIM_Cmd(ENABLE);
}

void TIM4_Config(void)
{
	/* DeInit TIM4 */
	TIM4_DeInit();
  
	/* TIM4 Time base configuration */

  
  	TIM4_TimeBaseInit(TIM4_Prescaler_4,0);

	TIM4_SetAutoreload(100);
	
 	TIM4_ARRPreloadConfig(ENABLE);

	TIM4_ClearFlag(TIM4_FLAG_Update);
	
	/* TIM4 Counter Enable */
	TIM4_Cmd(ENABLE);
	
	
}



/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
