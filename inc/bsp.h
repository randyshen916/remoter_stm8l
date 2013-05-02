/**
  ******************************************************************************
  * @file rc5.h
  * @brief This file contains all functions prototype and macros for the RC5 driver.
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
#include "stm8l10x_tim3.h"
#include "remoter.h"
#include "stm8l10x_tim4.h"
#include "stm8l10x_exti.h"
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define BUTTON_PORT (GPIOA)
#define BUTTON_PIN  (GPIO_Pin_2)
#define SELECT_PORT (GPIOD)
#define SELECT_PIN  (GPIO_Pin_7)
#define LEDS_PORT (GPIOB)
#define LED_PIN  (GPIO_Pin_7)
#define AUDIO_PORT (GPIOC)
#define AUDIO_IN  (GPIO_Pin_2)
#define AUDIO_IN_EXTI  (EXTI_Pin_2)
#define AUDIO_OUT (GPIO_Pin_3)


/* Exported functions ------------------------------------------------------- */
/** @addtogroup RC5_Exported_Functions
  * @{
  */
/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount);
void	CLK_Config(void);
void	TIM2_Config(void);
void	TIM3_Config(void);
void	TIM4_Config(void);
void	IRTIM_Config(void);


/**
  * @}
  */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/	
