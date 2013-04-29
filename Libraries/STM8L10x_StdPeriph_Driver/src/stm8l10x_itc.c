/**
  ******************************************************************************
  * @file stm8l10x_itc.c
  * @brief This file contains all the functions for the ITC peripheral.
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
#include "stm8l10x_itc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @addtogroup ITC_Private_Functions
  * @{
  */

/**
  * @brief Utility function used to read CC register.
  * @par Parameters:
  * None
  * @retval uint8_t : Content of CC register.
  */

uint8_t ITC_GetCPUCC(void)
{
#ifdef _COSMIC_
    _asm("push cc");
    _asm("pop a");
    return; /* Ignore compiler warning, the returned value is in A register */
#endif
    
#ifdef _RAISONANCE_
    return _getCC_();
#endif

#ifdef _IAR_SYSTEMS_
    __asm("push cc");
    __asm("pop a");
#endif
}

/**
  * @}
  */

/* Public functions ----------------------------------------------------------*/

/** @addtogroup ITC_Public_Functions
  * @{
  */

/**
  * @brief Deinitializes the ITC registers to their default reset value.
  * @par Parameters:
  * None
  * @retval None
  */
void ITC_DeInit(void)
{
    ITC->ISPR1 = ITC_SPR1_RESET_VALUE;
    ITC->ISPR2 = ITC_SPR2_RESET_VALUE;
    ITC->ISPR3 = ITC_SPR3_RESET_VALUE;
    ITC->ISPR4 = ITC_SPR4_RESET_VALUE;
    ITC->ISPR5 = ITC_SPR5_RESET_VALUE;
    ITC->ISPR6 = ITC_SPR6_RESET_VALUE;
    ITC->ISPR7 = ITC_SPR7_RESET_VALUE;
    ITC->ISPR8 = ITC_SPR8_RESET_VALUE;
}

/**
  * @brief Get the software interrupt priority bits (I1, I0) value from CPU CC register.
  * @par Parameters:
  * None
  * @retval uint8_t : The software interrupt priority bits value.
  */
uint8_t ITC_GetSoftIntStatus(void)
{
    return ((uint8_t)(ITC_GetCPUCC() & CPU_SOFT_INT_DISABLED));
}

/**
  * @brief Get the software priority of the specified interrupt source.
  * @param[in] IRQn : The IRQ to access.
  * @retval ITC_PriorityLevel_TypeDef : The software priority of the interrupt source.
  */
ITC_PriorityLevel_TypeDef ITC_GetSoftwarePriority(IRQn_TypeDef IRQn)
{
    uint8_t Value = 0;
    uint8_t Mask;

    /* Check function parameters */
    assert_param(IS_ITC_IRQ((uint8_t)IRQn));

    /* Define the mask corresponding to the bits position in the SPR register */
    Mask = (uint8_t)(0x03U << (((uint8_t)IRQn % 4U) * 2U));

    switch (IRQn)
    {
    case FLASH_IRQn:
        Value = (uint8_t)(ITC->ISPR1 & Mask); /* Read software priority */
        break;

    case AWU_IRQn:
    case EXTIB_IRQn:
    case EXTID_IRQn:
        Value = (uint8_t)(ITC->ISPR2 & Mask); /* Read software priority */
        break;

    case EXTI0_IRQn:
    case EXTI1_IRQn:
    case EXTI2_IRQn:
    case EXTI3_IRQn:
        Value = (uint8_t)(ITC->ISPR3 & Mask); /* Read software priority */
        break;

    case EXTI4_IRQn:
    case EXTI5_IRQn:
    case EXTI6_IRQn:
    case EXTI7_IRQn:
        Value = (uint8_t)(ITC->ISPR4 & Mask); /* Read software priority */
        break;

    case COMP_IRQn:
    case TIM2_UPD_OVF_TRG_BRK_IRQn:
        Value = (uint8_t)(ITC->ISPR5 & Mask); /* Read software priority */
        break;

    case TIM2_CAP_IRQn:
    case TIM3_UPD_OVF_TRG_BRK_IRQn:
    case TIM3_CAP_IRQn:
        Value = (uint8_t)(ITC->ISPR6 & Mask); /* Read software priority */
        break;

    case TIM4_UPD_OVF_IRQn:
    case SPI_IRQn:
    case USART_TX_IRQn:
        Value = (uint8_t)(ITC->ISPR7 & Mask); /* Read software priority */
        break;

    case USART_RX_IRQn:
    case I2C_IRQn:
        Value = (uint8_t)(ITC->ISPR8 & Mask); /* Read software priority */
        break;

    default:
        break;
    }

    Value >>= (uint8_t)(((uint8_t)IRQn % 4u) * 2u);

    return((ITC_PriorityLevel_TypeDef)Value);

}

/**
  * @brief Set the software priority of the specified interrupt source.
  * @param[in] IRQn: The interrupt source to access.
  * @param[in] ITC_PriorityLevel : The software priority value to set.
  * @retval ITC_PriorityLevel_TypeDef : The software priority of the interrupt source.
  * @par Required preconditions:
  * - The modification of the software priority is only possible when the interrupts are disabled.
  * - The normal behavior is to disable the interrupts before calling this function, and re-enable it after.
  * - The priority level 0 cannot be set (see product specification for more details).
*/
void ITC_SetSoftwarePriority(IRQn_TypeDef IRQn, ITC_PriorityLevel_TypeDef ITC_PriorityLevel)
{
    uint8_t Mask;
    uint8_t NewPriority;

    /* Check function parameters */
    assert_param(IS_ITC_IRQ((uint8_t)IRQn));
    assert_param(IS_ITC_PRIORITY(ITC_PriorityLevel));

    /* Check if interrupts are disabled */
    assert_param(IS_ITC_INTERRUPTS_DISABLED);

    /* Define the mask corresponding to the bits position in the SPR register */
    /* The mask is reversed in order to clear the 2 bits after more easily */
    Mask = (uint8_t)(~(uint8_t)(0x03U << (((uint8_t)IRQn % 4U) * 2U)));

    /* Define the new priority to write */
    NewPriority = (uint8_t)((uint8_t)(ITC_PriorityLevel) << (((uint8_t)IRQn % 4U) * 2U));

    switch (IRQn)
    {
    case FLASH_IRQn:
        ITC->ISPR1 &= Mask;
        ITC->ISPR1 |= NewPriority;
        break;

    case AWU_IRQn:
    case EXTIB_IRQn:
    case EXTID_IRQn:
        ITC->ISPR2 &= Mask;
        ITC->ISPR2 |= NewPriority;
        break;

    case EXTI0_IRQn:
    case EXTI1_IRQn:
    case EXTI2_IRQn:
    case EXTI3_IRQn:
        ITC->ISPR3 &= Mask;
        ITC->ISPR3 |= NewPriority;
        break;

    case EXTI4_IRQn:
    case EXTI5_IRQn:
    case EXTI6_IRQn:
    case EXTI7_IRQn:
        ITC->ISPR4 &= Mask;
        ITC->ISPR4 |= NewPriority;
        break;

    case COMP_IRQn:
    case TIM2_UPD_OVF_TRG_BRK_IRQn:
        ITC->ISPR5 &= Mask;
        ITC->ISPR5 |= NewPriority;
        break;

    case TIM2_CAP_IRQn:
    case TIM3_UPD_OVF_TRG_BRK_IRQn:
    case TIM3_CAP_IRQn:
        ITC->ISPR6 &= Mask;
        ITC->ISPR6 |= NewPriority;
        break;

    case TIM4_UPD_OVF_IRQn:
    case SPI_IRQn:
    case USART_TX_IRQn:
        ITC->ISPR7 &= Mask;
        ITC->ISPR7 |= NewPriority;
        break;

    case USART_RX_IRQn:
    case I2C_IRQn:
        ITC->ISPR8 &= Mask;
        ITC->ISPR8 |= NewPriority;
        break;

    default:
        break;
    }
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
