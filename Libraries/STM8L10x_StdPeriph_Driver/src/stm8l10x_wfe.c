/**
  ******************************************************************************
  * @file stm8l10x_wfe.c
  * @brief This file contains all the functions for the WFE.
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
#include "stm8l10x_wfe.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/** @addtogroup WFE_Public_Functions
  * @{
  */

/**
  * @brief Deinitializes the WFE registers to their default reset value.
  * @par Parameters:
  * None
  * @retval None
  */
void WFE_DeInit(void)
{
    WFE->CR1 = WFE_CR1_RESET_VALUE;
    WFE->CR2 = WFE_CR2_RESET_VALUE;
}

/**
  * @brief Set the source that can generate the wake-up event.
  * @param[in] WFE_Source: The wake-up event source .
	* It can be set of the values of @ref WFE_Source_TypeDef
  * @param[in] NewState : The source wake up new state.
  * This parameter can be any of the @ref FunctionalState enumeration.
  */
void WFE_WakeUpSourceEventCmd(WFE_Source_TypeDef WFE_Source, FunctionalState NewState)
{
    uint8_t register_index = 0;
    /* Check function parameters */
    assert_param(IS_WFE_SOURCE_OK(WFE_Source));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* The mask is reversed in order to  */
    register_index = (uint8_t)(WFE_Source >> (uint8_t)0x08);

    if (NewState != DISABLE)
    {
        switch (register_index)
        {
        case 1:
            WFE->CR1 |= (uint8_t)WFE_Source;
            break;

        case 2:
            WFE->CR2 |= (uint8_t)WFE_Source;
            break;

        default:
            break;
        }
    }
    else
    {
        switch (register_index)
        {
        case 1:
            WFE->CR1 &= (uint8_t)(~(uint8_t)WFE_Source);
            break;

        case 2:
            WFE->CR2 &= (uint8_t)(~ (uint8_t)WFE_Source);
            break;

        default:
            break;
        }
    }
}

/**
  * @brief Get the status of the specified source event.
  * @param[in] WFE_Source: The wake-up event source.
	* It can be set of the values of @ref WFE_Source_TypeDef
  * @retval
	* @param[in] NewState : Source Event state.
  * This parameter can be any of the @ref FunctionalState enumeration.
  */
FunctionalState WFE_GetWakeUpSourceEventStatus(WFE_Source_TypeDef WFE_Source)
{
    FunctionalState status = DISABLE;
    /* Check function parameters */
    assert_param(IS_WFE_SOURCE_OK(WFE_Source));

    switch (WFE_Source)
    {
    case WFE_Source_TIM2_EV0:
    case WFE_Source_TIM2_EV1:
    case WFE_Source_EXTI_EV0:
    case WFE_Source_EXTI_EV1:
    case WFE_Source_EXTI_EV2:
    case WFE_Source_EXTI_EV3:

        if ((WFE->CR1 & (uint8_t)WFE_Source) != (uint8_t)0x00)
        {
            /* The wake-up event source is enabled*/
            status = ENABLE;
        }
        else
        {
            /* The wake-up event source is disabled*/
            status = DISABLE;
        }
        break;

    case WFE_Source_EXTI_EV4:
    case WFE_Source_EXTI_EV5:
    case WFE_Source_EXTI_EV6:
    case WFE_Source_EXTI_EV7:
    case WFE_Source_EXTI_EVB:
    case WFE_Source_EXTI_EVD:

        if ((WFE->CR2 & (uint8_t)WFE_Source) != (uint8_t)0x00)
        {
            /* The wake-up event source is enabled*/
            status = ENABLE;
        }
        else
        {
            /* The wake-up event source is disabled*/
            status = DISABLE;
        }
        break;
    default:
        break;
    }
    return status;
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
