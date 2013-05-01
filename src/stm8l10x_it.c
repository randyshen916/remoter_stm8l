/**
  ******************************************************************************
  * @file stm8l10x_it.c
  * @brief This file contains all the interrupt routines.
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
#include "stm8l10x_it.h"
#include "rc5.h"
#include "stm8l10x_exti.h"



#define LEDS_PORT (GPIOB)
#define LED_PIN  (GPIO_Pin_7)
extern uint32_t RC5_FrameManchestarFormat;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t Global_Counter1, Global_Counter2 =0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#ifdef _COSMIC_
/**
  * @brief Dummy interrupt routine
  * @par Parameters:
  * None
  * @retval
  * None
*/
@far @interrupt void NonHandledInterrupt(void)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif

/**
  * @brief TRAP interrupt routine
  * @par Parameters:
  * None
  * @retval
  * None
*/
#ifdef _COSMIC_
@far @interrupt void TRAP_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void TRAP_IRQHandler(void) interrupt 0
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=1
__interrupt void TRAP_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief FLASH Interrupt routine.
  * @par Parameters:
  * None
  * @retval None
  * None
  */
#ifdef _COSMIC_
@far @interrupt void FLASH_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void FLASH_IRQHandler(void) interrupt 1
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=3
__interrupt void FLASH_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief Auto Wake Up Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void AWU_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void AWU_IRQHandler(void) interrupt 4
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=6
__interrupt void AWU_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PORTB Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void EXTIB_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void EXTIB_IRQHandler(void) interrupt 6
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=8
__interrupt void EXTIB_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PORTD Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void EXTID_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void EXTID_IRQHandler(void) interrupt 7
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=9
__interrupt void EXTID_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN0 Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void EXTI0_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void EXTI0_IRQHandler(void) interrupt 8
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=10
__interrupt void EXTI0_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN1 Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void EXTI1_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void EXTI1_IRQHandler(void) interrupt 9
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=11
__interrupt void EXTI1_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN2 Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void EXTI2_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void EXTI2_IRQHandler(void) interrupt 10
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=12
__interrupt void EXTI2_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  /* LEDs reverse */
   GPIO_ToggleBits(LEDS_PORT, LED_PIN);  

  EXTI_ClearITPendingBit(EXTI_IT_Pin2);
}

/**
  * @brief External IT PIN3 Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void EXTI3_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void EXTI3_IRQHandler(void) interrupt 11
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=13
__interrupt void EXTI3_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN4 Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void EXTI4_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void EXTI4_IRQHandler(void) interrupt 12
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=14
__interrupt void EXTI4_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN5 Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void EXTI5_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void EXTI5_IRQHandler(void) interrupt 13
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=15
__interrupt void EXTI5_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN6 Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void EXTI6_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void EXTI6_IRQHandler(void) interrupt 14
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=16
__interrupt void EXTI6_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN7 Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void EXTI7_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void EXTI7_IRQHandler(void) interrupt 15
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=17
__interrupt void EXTI7_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief Comparator Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void COMP_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void COMP_IRQHandler(void) interrupt 18
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=20
__interrupt void COMP_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief Timer2 Update/Overflow/Trigger/Break Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void TIM2_UPD_OVF_TRG_BRK_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void TIM2_UPD_OVF_TRG_BRK_IRQHandler(void) interrupt 19
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=21
__interrupt void TIM2_UPD_OVF_TRG_BRK_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief Timer2 Capture/Compare Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void TIM2_CAP_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void TIM2_CAP_IRQHandler(void) interrupt 20
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=22
__interrupt void TIM2_CAP_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}


/**
  * @brief Timer3 Update/Overflow/Trigger/Break Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void TIM3_UPD_OVF_TRG_BRK_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void TIM3_UPD_OVF_TRG_BRK_IRQHandler(void) interrupt 21
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=23
__interrupt void TIM3_UPD_OVF_TRG_BRK_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
        RC5_SendFrame(RC5_FrameManchestarFormat);
	
	TIM3_ClearITPendingBit(TIM3_IT_Update);    
}
/**
  * @brief Timer3 Capture/Compare Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void TIM3_CAP_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void TIM3_CAP_IRQHandler(void) interrupt 22
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=24
__interrupt void TIM3_CAP_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief Timer4 Update/Overflow Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void TIM4_UPD_OVF_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void TIM4_UPD_OVF_IRQHandler(void) interrupt 25
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=27
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
#endif

/**
  * @brief SPI Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void SPI_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void SPI_IRQHandler(void) interrupt 26
#endif

#ifdef _IAR_SYSTEMS_
//#pragma vector=28
//__interrupt void SPI_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief USART TX Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void USART_TX_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void USART_TX_IRQHandler(void) interrupt 27
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=29
__interrupt void USART_TX_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief USART RX Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void USART_RX_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void USART_RX_IRQHandler(void) interrupt 28
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=30
__interrupt void USART_RX_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}


/**
  * @brief I2C Interrupt routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
#ifdef _COSMIC_
@far @interrupt void I2C_IRQHandler(void)
#endif

#ifdef _RAISONANCE_
void I2C_IRQHandler(void) interrupt 29
#endif

#ifdef _IAR_SYSTEMS_
#pragma vector=31
__interrupt void I2C_IRQHandler(void)
#endif
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

