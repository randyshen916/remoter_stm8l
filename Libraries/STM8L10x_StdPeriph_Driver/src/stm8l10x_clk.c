/**
  ******************************************************************************
  * @file stm8l10x_clk.c
  * @brief This file contains all the functions for the CLK peripheral.
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

#include "stm8l10x_clk.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private Constants ---------------------------------------------------------*/

/**
  * @addtogroup CLK_Private_Constants
  * @{
  */

__CONST uint8_t HSIDivFactor[4] = {1, 2, 4, 8}; /*!< Holds the different HSI Dividor factors */

/**
  * @}
  */

/**
  * @addtogroup CLK_Public_Functions
  * @{
  */

/**
  * @brief Deinitializes the CLK peripheral registers to their default reset
  * values.
  * @par Parameters:
  * None
  * @retval None
  */
void CLK_DeInit(void)
{
    CLK->CKDIVR = CLK_CKDIVR_RESET_VALUE;
    CLK->PCKENR = CLK_PCKENR_RESET_VALUE;
    CLK->CCOR  = CLK_CCOR_RESET_VALUE;
}

/**
  * @brief Enables or disablle the Configurable Clock Output (CCO).
  * @param[in] NewState : New state of CCEN bit (CCO register).
	* This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void CLK_CCOCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set CCOEN bit */
        CLK->CCOR |= CLK_CCOR_CCOEN;
    }
    else
    {
        /* Reset CCOEN bit */
        CLK->CCOR &= (uint8_t)(~CLK_CCOR_CCOEN);
    }

}

/**
  * @brief  Enables or disables the specified peripheral CLK.
  * @param[in] CLK_Peripheral : This parameter specifies the peripheral clock to gate.
  * This parameter can be any of the  @ref CLK_Peripheral_TypeDef enumeration.
  * @param[in] NewState : New state of specified peripheral clock.
	* This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void CLK_PeripheralClockConfig(CLK_Peripheral_TypeDef CLK_Peripheral, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_CLK_PERIPHERAL(CLK_Peripheral));

    if (NewState != DISABLE)
    {
        /* Enable the peripheral Clock */
        CLK->PCKENR |= ((uint8_t)CLK_Peripheral);
    }
    else
    {
        /* Disable the peripheral Clock */
        CLK->PCKENR &= (uint8_t)(~(uint8_t)CLK_Peripheral);
    }
}

/**
  * @brief Configures the HSI master clock dividers.
  * @param[in] CLK_MasterPrescaler : Specifies the HSI clock divider to apply.
  * This parameter can be any of the @ref CLK_MasterPrescaler_TypeDef enumeration.
  * @retval None
  */
void CLK_MasterPrescalerConfig(CLK_MasterPrescaler_TypeDef CLK_MasterPrescaler)
{
    /* check teh parameters */
    assert_param(IS_CLK_MASTER_PRESCALER(CLK_MasterPrescaler));

    CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);
    CLK->CKDIVR = (uint8_t)CLK_MasterPrescaler;
}

/**
  * @brief Output the selected clock on a dedicated I/O pin.
  * @param[in] CLK_CCO : Specifies the clock source.
  * This parameter can be any of the  @ref CLK_Output_TypeDef enumeration.
  * @retval None
  * @par Required preconditions:
  * The dedicated I/O pin must be set at 1 in the corresponding Px_CR1 register \n
  * to be set as input with pull-up or push-pull output.
  */
void CLK_CCOConfig(CLK_Output_TypeDef CLK_Output)
{
    /* check teh parameters */
    assert_param(IS_CLK_OUTPUT(CLK_Output));

    /* Clears of the CCO type bits part */
    CLK->CCOR &= (uint8_t)(~CLK_CCOR_CCOSEL);

    /* Selects the source provided on cco_ck output */
    CLK->CCOR |= ((uint8_t)CLK_Output);

    /* Enable the clock output */
    CLK->CCOR |= CLK_CCOR_CCOEN;
}


/**
  * @brief This function returns the frequencies of different on chip clocks.
  * @par Parameters:
  * None
  * @retval uint32_t : The master clock frequency
  */
uint32_t CLK_GetClockFreq(void)
{
    uint32_t clockfrequency = 0;
    uint8_t tmp = 0, presc = 0;

    tmp = (uint8_t)(CLK->CKDIVR & CLK_CKDIVR_HSIDIV);
    presc = HSIDivFactor[tmp];
    clockfrequency = HSI_VALUE / presc;

    return((uint32_t)clockfrequency);
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
