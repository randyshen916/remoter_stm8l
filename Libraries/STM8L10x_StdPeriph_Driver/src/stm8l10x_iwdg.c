/**
  ********************************************************************************
  * @file stm8l10x_iwdg.c
  * @brief This file contains all the functions for the IWDG peripheral.
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
#include "stm8l10x_iwdg.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/** @addtogroup IWDG_Public_Functions
  * @{
  */

/**
  * @brief Enables or disables write access to Prescaler and Reload registers.
  * @param[in] IWDG_WriteAccess : New state of write access to Prescaler and Reload registers.
  * This parameter can be one of the @ref IWDG_WriteAccess_TypeDef enumeration.
  * @retval None
  */
void IWDG_WriteAccessCmd(IWDG_WriteAccess_TypeDef IWDG_WriteAccess)
{
    /* Check the parameters */
    assert_param(IS_IWDG_WRITEACCESS_MODE(IWDG_WriteAccess));
    IWDG->KR = IWDG_WriteAccess; /* Write Access */
}

/**
  * @brief Sets IWDG Prescaler value.
  * @param[in] IWDG_Prescaler : Specifies the IWDG Prescaler value.
  * This parameter can be one of the @ref IWDG_Prescaler_TypeDef enumeration.
  * @retval None
  * @par Required preconditions:
  * Write access enabled
  */
void IWDG_SetPrescaler(IWDG_Prescaler_TypeDef IWDG_Prescaler)
{
    /* Check the parameters */
    assert_param(IS_IWDG_PRESCALER_VALUE(IWDG_Prescaler));
    IWDG->PR = IWDG_Prescaler;
}

/**
  * @brief Sets IWDG Reload value.
  * @param[in] IWDG_Reload : Reload register value.
  * This parameter must be a number between 0 and 0xFF.
  * @retval None
  * @par Required preconditions:
  * Write access enabled
  */
void IWDG_SetReload(uint8_t IWDG_Reload)
{
    IWDG->RLR = IWDG_Reload;
}

/**
  * @brief Reload IWDG counter
  * @par Parameters:
  * None
  * @retval None
  * @par Required preconditions:
  * Write access enabled
  */
void IWDG_ReloadCounter(void)
{
    IWDG->KR = IWDG_KEY_REFRESH;
}

/**
  * @brief Enable IWDG registers access.
  * @par Parameters:
  * None
  * @retval None
  */
void IWDG_Enable(void)
{
    IWDG->KR = IWDG_KEY_ENABLE;
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
