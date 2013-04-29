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
#include "stm8l10x.h"
#include "rc5.h"

/**
  * @addtogroup IRTIM_AN
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define BUTTON_PORT (GPIOA)
#define BUTTON_PIN  (GPIO_Pin_5)
#define SELECT_PORT (GPIOD)
#define SELECT_PIN  (GPIO_Pin_7)
#define LEDS_PORT (GPIOD)
#define LED2_PIN  (GPIO_Pin_4)
#define LED3_PIN  (GPIO_Pin_5)
#define LED4_PIN  (GPIO_Pin_6)
#define LEDS_PINS (GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
 RC5_Address_TypeDef Address;
 RC5_Instruction_TypeDef Instruction;
 RC5_Ctrl_TypeDef RC5_Ctrl1 = RC5_Ctrl_Reset;
 RC5_Ctrl_TypeDef RC5_Ctrl2 = RC5_Ctrl_Reset;

/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount);
void SendFrame(RC5_Address_TypeDef RC5_Address,
               RC5_Instruction_TypeDef RC5_Instruction, 
			         RC5_Ctrl_TypeDef RC5_Ctrl);
void	CLK_Config(void);
void	TIM2_Config(void);
void	TIM3_Config(void);
void	IRTIM_Config(void);

/* Public variables ---------------------------------------------------------*/
 extern uint8_t Send_Operation_Completed  ; /* RC5 Flag*/
 extern uint8_t Send_Operation_Ready ;      /* RC5 Flag*/
 extern uint32_t RC5_FrameManchestarFormat;
 
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
	/* Clock configuration */
	CLK_Config();
  
  /* TIM2 configuration */
	TIM2_Config();
	
	/* TIM3 configuration */
	TIM3_Config();
	
	/* IRTIM configuration */
	IRTIM_Config();
	
	/* Initialize I/Os in Output Mode */
  GPIO_Init(LEDS_PORT, LEDS_PINS, GPIO_Mode_Out_PP_Low_Fast);

	
	while(1)
	{
		
		/* Check button status */
    if ((GPIO_ReadInputData(BUTTON_PORT) & BUTTON_PIN) == (uint8_t)0x00)
    {
      /* Button is pressed */
      Address=RC5_Address_TV1; 
		  Instruction=RC5_Instruction_VolumeUp;
		  SendFrame(Address, Instruction, RC5_Ctrl1);
			
			/* LEDs reverse */
      GPIO_ToggleBits(LEDS_PORT, LEDS_PINS);
    }
		
		/* Check Joystick select status */
    if ((GPIO_ReadInputData(SELECT_PORT) & SELECT_PIN) == (uint8_t)0x00)
    {
      /* Joystick select is pressed */
			Address=RC5_Address_TV1; 
		  Instruction=RC5_Instruction_VolumeDown;
		  SendFrame(Address, Instruction, RC5_Ctrl2);
	
			/* LEDs reverse */
      GPIO_ToggleBits(LEDS_PORT, LEDS_PINS);  
    }
  }
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
void SendFrame(RC5_Address_TypeDef RC5_Address, 
                           RC5_Instruction_TypeDef RC5_Instruction, 
								           RC5_Ctrl_TypeDef RC5_Ctrl)
{
	uint16_t RC5_FrameBinaryFormat =0;
	
	/* Generate a binary format of the Frame */
	RC5_FrameBinaryFormat = RC5_BinFrameGeneration(RC5_Address, RC5_Instruction, RC5_Ctrl);
	
	/* Disable Interrupts */
	disableInterrupts();
	
	/* Generate a Manchester format of the Frame */
	RC5_FrameManchestarFormat = RC5_ManchesterConvert(RC5_FrameBinaryFormat);
	
	/* Set the Send operation Ready flag to indicate that the frame is ready to be sent */
	Send_Operation_Ready = 1;
	
  /* Enable Interrupts */
	enableInterrupts();

}

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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
