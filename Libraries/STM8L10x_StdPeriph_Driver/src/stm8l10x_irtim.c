/**
  ******************************************************************************
  * @file stm8l10x_irtim.c
  * @brief This file contains all the functions for the IRTIM peripheral.
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
#include "stm8l10x_irtim.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/**
  * @addtogroup IRTIM_Public_Functions
  * @{
  */

/**
  * @brief Deinitializes the IRTIM peripheral registers to their default reset values.
  * @par Parameters:
  * None
  * @retval None
  */
void IRTIM_DeInit(void)
{
    IRTIM->CR = IRTIM_CR_RESET_VALUE;
}


/**
  * @brief Enables or disables the IRTIM peripheral.
  * @param[in] NewState : The new state of the IRTIM peripheral.
	* This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void IRTIM_Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* set or Reset the EN Bit */
    if (NewState == 	DISABLE)
    {
        IRTIM->CR &= (uint8_t)(~IRTIM_CR_EN) ;
    }
    else
    {
        IRTIM->CR |= IRTIM_CR_EN ;
    }
}

/**
  * @brief Enables or disables the High sink open drain buffer IRTIM peripheral.
  * @param[in] NewState : The new state of the High sink open drain buffer IRTIM peripheral.
  * This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void IRTIM_HighSinkODCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* set or Reset the EN Bit */
    if (NewState == DISABLE)
    {
        IRTIM->CR &= (uint8_t)(~IRTIM_CR_HSEN) ;
    }
    else
    {
        IRTIM->CR |= IRTIM_CR_HSEN ;
    }
}

/**
  * @brief Checks whether the IRTIM device is enabled or not.
  * @par Parameters:
  * None
  * @retval FunctionalState : The new state of the IRTIM device.
	* This parameter can be any of the @ref FunctionalState enumeration.
  */

FunctionalState IRTIM_GetStatus(void)
{
    return ((FunctionalState) (IRTIM->CR & IRTIM_CR_EN));
}

/**
  * @brief Checks whether the IRTIM High Sink Open Drain buffer is Enabled or not.
  * @par Parameters:
  * None
  * @retval FunctionalState : The state of High Sink Open Drain buffer.
	* This parameter can be any of the @ref FunctionalState enumeration.
  */

FunctionalState IRTIM_GetHighSinkODStatus(void)
{
    return ((FunctionalState)(IRTIM->CR & IRTIM_CR_HSEN));
}


/**
  * @}
  */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
