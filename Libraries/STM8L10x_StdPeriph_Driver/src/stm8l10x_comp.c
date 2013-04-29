/**
  ******************************************************************************
  * @file stm8l10x_comp.c
  * @brief This file contains all the functions for the COMP peripheral.
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
#include "stm8l10x_comp.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @addtogroup COMP_Public_Functions
  * @{
  */

/**
  * @brief Deinitializes the COMP peripheral registers to their default reset values.
  * @par Parameters:
  * None
  * @retval None
  */
void COMP_DeInit(void)
{
    COMP->CR   = COMP_CR_RESET_VALUE;
    COMP->CSR  = COMP_CSR_RESET_VALUE;
    COMP->CCS  = COMP_CCS_RESET_VALUE;
}


/**
  * @brief Initializes the COMP according to the specified parameters
  * @param[in] COMP_Selection : The state of the COMP peripheral.
  * This parameter can be any of the @Ref COMP_Selection_TypeDef enumeration.
  * @param[in] COMP_Reference : The reference of the comparison
  * This parameter can be any of the @Ref COMP_Reference_TypeDef enumeration.
  * @param[in] COMP_Polarity : The desired comparator polarity
  * This parameter can be any of the @Ref COMP_Polarity_TypeDef enumeration.
  * @retval None
  * @par Required preconditions:
  * The function @ref COMP_Cmd() should be called to set the BIASEN bit in COMP_CR register, first.
  */
void COMP_Init(COMP_Selection_TypeDef COMP_Selection,
               COMP_Reference_TypeDef COMP_Reference,
               COMP_Polarity_TypeDef COMP_Polarity)
{
    /* Check the parameters */
    assert_param(IS_COMP_POLARITY(COMP_Polarity));
    assert_param(IS_COMP_REFERENCE(COMP_Reference));
    assert_param(IS_COMP_SELECTION(COMP_Selection));

    COMP->CR &= (uint8_t)(~((uint8_t)COMP_Polarity|(uint8_t)COMP_Reference|(uint8_t)COMP_Selection));
    /* Set the Configuration */
    COMP->CR |= (uint8_t)((uint8_t)COMP_Polarity|(uint8_t)COMP_Reference|(uint8_t)COMP_Selection);

}

/**
  * @brief Enables or disables the COMP.
  * @param[in] NewState : The New state of the COMP peripheral.
	* This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  * @par Required conditions:
  * this function must be used 4 µs before the function @ref COMP_SelectionConfig.
  */
void COMP_Cmd(FunctionalState NewState)
{

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* set  BIAS_EN  */
        COMP->CR |= COMP_CR_BIASEN;
    }
    else  /* NewState == DISABLE */
    {
        COMP->CR &= (uint8_t)(~COMP_CR_BIASEN);
    }
}

/**
  * @brief Enables or disables the desired COMP peripheral.
  * @param[in] COMP_Selection : The State of the COMP peripheral.
  * This parameter can be any of the @Ref COMP_Selection_TypeDef enumeration.
  * @param[in] NewState : The new state of the COMP peripheral.
	* This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  * @par Required preconditions:
  *  BIAS bit should be set 4µs before enabling the comparators.
  */
void COMP_SelectionConfig(COMP_Selection_TypeDef COMP_Selection,
                          FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_COMP_SELECTION(COMP_Selection));

    if (NewState != DISABLE)
    {
        COMP->CR |= (uint8_t)COMP_Selection;
    }
    else  /* NewState == DISABLE */
    {
        COMP->CR &= (uint8_t)(~(uint8_t)COMP_Selection);
    }
}

/**
  * @brief Enables or disables the specified COMP interrupts.
  * @param[in] COMP_IT : Specifies the COMP interrupts source.
  * This parameter can be any of the @Ref COMP_IT_TypeDef enumeration.
  * @param[in] NewState : The new state of the COMP peripheral.
  * This parameter can be any of the @ref FunctionalState enumeration.
  * @retval None
  */
void COMP_ITConfig(COMP_IT_TypeDef COMP_IT,
                   FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_COMP_IT(COMP_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Interrupt sources */
        COMP->CSR |= (uint8_t)COMP_IT;
    }
    else
    {
        /* Disable the Interrupt sources */
        COMP->CSR &= (uint8_t)(~(uint8_t)COMP_IT);
    }
}

/**
  * @brief Selection between Timer1 input capture1 or Timer1 break for first comparator output.
  * @param[in] COMP_TIM2Config : The TIM configartionfor first comparator output.
  * This parameter can be any of the @Ref COMP_TIM2Config_TypeDef enumeration.
  * @retval None
  */
void COMP_TIM2Config(COMP_TIM2Config_TypeDef COMP_TIM2Config)
{
    /* Check the parameters */
    assert_param(IS_COMP_TIM2CONFIG(COMP_TIM2Config));

    /* Clear the IC1_BK bit*/
    COMP->CR &= (uint8_t)(~(uint8_t)COMP_CR_IC1BK);

    /* Configure the  IC1_BK bit */
    COMP->CR |= (uint8_t)COMP_TIM2Config;
}

/**
  * @brief Enables or disables the specified Switch.
  * @param[in] NewState : The new state of the COMP peripheral.
  * This parameter can be any of the @ref FunctionalState enumeration.
  * @param[in] COMP_Switch : Specifies the COMP SWITCH to be enabled or disabled.
  * This parameter can be any of the @Ref COMP_Switch_TypeDef enumeration.
  * @retval None
  */
void COMP_SwitchConfig(COMP_Switch_TypeDef COMP_Switch,
                       FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_COMP_SWITCH(COMP_Switch));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the switch */
        COMP->CCS |= (uint8_t)COMP_Switch;
    }
    else
    {
        /* Disable the Switch */
        COMP->CCS &= (uint8_t)(~(uint8_t)COMP_Switch);
    }
}

/**
  * @brief Selects the COMP peripheral Output Connection with Timers peripheral inputs.
  * @param[in] COMP_TIMConnection : The TIM connection configuration.
  * This parameter can be any of the @Ref COMP_TimersConnection_TypeDef enumeration.
  * @retval None
  */
void COMP_TIMConnect(COMP_TimersConnection_TypeDef COMP_TIMConnection)
{
    /* Check the parameters */
    assert_param(IS_COMP_TIMCONNECTION(COMP_TIMConnection));

    /* Clear the TIM connection configuration bits */
    COMP->CR &= (uint8_t)(~(uint8_t)COMP_CR_CNFTIM);

    /* Configure the TIM connection */
    COMP->CR |= (uint8_t)COMP_TIMConnection;
}

/**
  * @brief Selects the polarity of both comparators.
  * @param[in] COMP_Polarity : The desired comparator polarity
	* This parameter can be any of the @Ref COMP_Polarity_TypeDef enumeration.
  * @retval None
  */
void COMP_SelectPolarity(COMP_Polarity_TypeDef COMP_Polarity)
{
    /* Check the parameters */
    assert_param(IS_COMP_POLARITY(COMP_Polarity));

    /* Clear Polarity bit */
    COMP->CR &= (uint8_t)(~(uint8_t)COMP_CR_POL);

    /* Write the polarity */
    COMP->CR |= (uint8_t)COMP_Polarity;

}

/**
  * @brief Selects the internal or external reference of both comparators.
  * @param[in] COMP_Reference : The desired comparator reference.
  * This parameter can be any of the @Ref COMP_Reference_TypeDef enumeration.
  * @retval None
  */
void COMP_SetReference(COMP_Reference_TypeDef COMP_Reference)
{
    /* Check the parameters */
    assert_param(IS_COMP_REFERENCE(COMP_Reference));

    /* Clear Polarity bit */
    COMP->CR &= (uint8_t)(~(uint8_t)COMP_CR_COMPREF);

    /* Write the polarity */
    COMP->CR |= (uint8_t)COMP_Reference;
}

/**
  * @brief Checks whether the specified COMP output is set or not.
  * @param[in] COMP_Output : specifies the output to check.
  * This parameter can be any of the @Ref COMP_Output_TypeDef enumeration.
  * @retval FlagStatus : The new state of Output.
	* This parameter can be any of the @ref FlagStatus enumeration.
  */
FlagStatus COMP_GetOutputStatus(COMP_Output_TypeDef COMP_Output)
{
    FlagStatus status = RESET;

    /* Check the parameters */
    assert_param(IS_COMP_OUTPUT(COMP_Output));

    if ((COMP->CSR & (uint8_t)COMP_Output) != 0)
    {
        status = SET;
    }
    else
    {
        status = RESET;
    }
    return status;
}

/**
  * @brief Checks whether the specified COMP flag is set or not.
  * @param[in] COMP_Flag : Specifies the flag to check.
  * This parameter can be any of the @Ref COMP_FLAG_TypeDef enumeration.
  * @retval FlagStatus : The new state of Flag.
	* This parameter can be any of the @ref FlagStatus enumeration.
  */
FlagStatus COMP_GetFlagStatus(COMP_FLAG_TypeDef COMP_Flag)
{
    FlagStatus status = RESET;

    /* Check the parameters */
    assert_param(IS_COMP_FLAG(COMP_Flag));

    if ((COMP->CSR & (uint8_t)COMP_Flag) != 0)
    {
        status = SET;
    }
    else
    {
        status = RESET;
    }
    return status;
}

/**
  * @brief Clears the specified COMP’s flag.
  * @param[in] COMP_Flag : Specifies the flag to clear.
  * This parameter can be any of the @Ref COMP_FLAG_TypeDef enumeration.
  * @retval None
  */
void COMP_ClearFlag(COMP_FLAG_TypeDef COMP_Flag)
{

    /* Check the parameters */
    assert_param(IS_COMP_FLAG(COMP_Flag));

    /* Clear the flags (rc_w0) clear this bit by writing 1. Writing ‘0’ has no effect*/
    COMP->CSR |= (uint8_t)COMP_Flag;
}

/**
  * @brief Checks whether the COMP interrupt has occurred or not.
  * @param[in] COMP_ITPendingBit : Specifies the COMP interrupt source to check.
  * This parameter can be any of the @Ref COMP_ITPendingBit_TypeDef enumeration.
  * @retval ITStatus : The new state of the COMP_IT.
	* This parameter can be any of the @ref ITStatus enumeration.
  */
ITStatus COMP_GetITStatus(COMP_IT_TypeDef COMP_ITPendingBit)
{
    ITStatus status = RESET;

    /* Check the parameters */
    assert_param(IS_COMP_ITPENDINGBIT(COMP_ITPendingBit));

    if (COMP->CSR & (uint8_t)COMP_ITPendingBit)
    {
        status = SET;
    }
    else
    {
        status = RESET;
    }
    return status;
}

/**
  * @brief Clears the COMP’s pending bits.
  * @param[in] ITPendingBit : Specifies the peding bit to clear.
  * This parameter can be any of the @Ref COMP_ITPendingBit_TypeDef enumeration.
  * @retval None
  */
void COMP_ClearITPendingBit(COMP_IT_TypeDef COMP_ITPendingBit)
{

    /* Check the parameters */
    assert_param(IS_COMP_ITPENDINGBIT(COMP_ITPendingBit));

    /* Clear the flags (rc_w0) clear this bit by writing 1. Writing ‘0’ has no effect*/
    COMP->CSR |= (uint8_t)COMP_ITPendingBit;
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
