/**
  ******************************************************************************
  * @file stm8l10x_flash.c
  * @brief This file contains all the functions for the FLASH peripheral.
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
#include "stm8l10x_flash.h"

/* Private TypeDef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define FLASH_CLEAR_BYTE (uint8_t)0x00;
#define FLASH_SET_BYTE   (uint8_t)0xFF;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private Constants ---------------------------------------------------------*/
#define  OPERATION_TIMEOUT  ((uint16_t)0x1000)
/* Public functions ----------------------------------------------------------*/

/** @addtogroup FLASH_Public_functions
  * @{
  */
/**
  * @brief Unlocks the program or data EEPROM memory
  * @param[in] FLASH_MemType : Memory type to unlock
	* This parameter can be any of the @ref FLASH_MemType_TypeDef enumeration.
  * @retval
  * None
  */
void FLASH_Unlock(FLASH_MemType_TypeDef FLASH_MemType)
{
    /* Check parameter */
    assert_param(IS_MEMORY_TYPE(FLASH_MemType));

    /* Unlock program memory */
    if (FLASH_MemType == FLASH_MemType_Program)
    {
        FLASH->PUKR = FLASH_RASS_KEY1;
        FLASH->PUKR= FLASH_RASS_KEY2;
    }
    /* Unlock data memory */
    if (FLASH_MemType == FLASH_MemType_Data)
    {
        FLASH->DUKR = FLASH_RASS_KEY2; /* Warning: keys are reversed on data memory !!! */
        FLASH->DUKR = FLASH_RASS_KEY1;
    }

}
/**
  * @brief Locks the program or data EEPROM memory
  * @param[in] FLASH_MemType : Memory type
	* This parameter can be any of the @ref FLASH_MemType_TypeDef enumeration.
  * @retval
  * None
  */
void FLASH_Lock(FLASH_MemType_TypeDef FLASH_MemType)
{
    /* Check parameter */
    assert_param(IS_MEMORY_TYPE(FLASH_MemType));
    /* Lock memory */
    FLASH->IAPSR &= FLASH_MemType;
}
/**
  * @brief Deinitializes the FLASH peripheral registers to their default reset values.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void FLASH_DeInit(void)
{
    uint8_t temp;
    FLASH->CR1 = FLASH_CR1_RESET_VALUE;
    FLASH->CR2 = FLASH_CR2_RESET_VALUE;
    FLASH->IAPSR = FLASH_IAPSR_RESET_VALUE;
    temp = FLASH->IAPSR; /* Reading of this register causes the clearing of status flags */
}
/**
  * @brief Enables or Disables the Flash interrupt mode
  * @param[in] NewState : The new state of the flash interrupt mode
	* This parameter can be any of the @ref FunctionalState enumeration.
  * @retval
  * None
  */
void FLASH_ITConfig(FunctionalState NewState)
{

    /* Check parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        FLASH->CR1 |= FLASH_CR1_IE; /* Enables the interrupt sources */
    }
    else
    {
        FLASH->CR1 &= (uint8_t)(~FLASH_CR1_IE); /* Disables the interrupt sources */
    }
}
/**
  * @brief Erases one byte in the program or data EEPROM memory
  * @param[in] Address : Address of the byte to erase
  * @retval @ref FLASH_Status_TypeDef : State of the last operation
  * @par Required preconditions:
  * PointerAttr define is declared in the stm8l10x.h file to select the pointer that declared
  *	as near (2 bytes).
  */
void FLASH_EraseByte(uint16_t Address)
{
    /* Check parameter */
    assert_param(IS_FLASH_ADDRESS(Address));

    *((PointerAttr uint8_t*) Address) = FLASH_CLEAR_BYTE; /* Erase byte */

}
/**
  * @brief Programs one byte in program or data EEPROM memory
  * @param[in] Address : Adress where the byte is written
  * @param[in] Data : Value to be written
  * @retval @ref FLASH_Status_TypeDef : State of the last operation
  * @par Required preconditions:
  * PointerAttr define is declared in the stm8l10x.h file to select the pointer that declared
  *	as near (2 bytes).
  */
void FLASH_ProgramByte(uint16_t Address, uint8_t Data)
{
    /* Check parameters */
    assert_param(IS_FLASH_ADDRESS(Address));
    *((PointerAttr uint8_t*) Address) = Data;
}

/**
  * @brief Programs one word (4 bytes) in program or data EEPROM memory
  * @param[in] Address : The address where the data will be written
  * @param[in] Data : Value to be written
  * @retval
  * None.
  * @par Required preconditions:
  * PointerAttr define is declared in the stm8l10x.h file to select the pointer that declared
  *	as near (2 bytes).
  */
void FLASH_ProgramWord(uint16_t Address, uint32_t Data)
{
    /* Check parameters */
    assert_param(IS_FLASH_ADDRESS(Address));

    /* Enable Word Write Once */
    FLASH->CR2 |= FLASH_CR2_WPRG;

    *((PointerAttr uint8_t*)Address)       = *((uint8_t*)(&Data)); /* Write one byte - from lowest address*/
    *(((PointerAttr uint8_t*)Address) + 1) = *((uint8_t*)(&Data)+1); /* Write one byte*/
    *(((PointerAttr uint8_t*)Address) + 2) = *((uint8_t*)(&Data)+2); /* Write one byte*/
    *(((PointerAttr uint8_t*)Address) + 3) = *((uint8_t*)(&Data)+3); /* Write one byte - from higher address*/
}

/**
  * @brief Reads any byte from flash memory
  * @param[in] Address : Address to read
  * @retval uint8_t : Value read
  * @par Required preconditions:
  * PointerAttr define is declared in the stm8l10x.h file to select the pointer that declared
  *	as near (2 bytes).
  */
uint8_t FLASH_ReadByte(uint16_t Address)
{
    /* Check parameter */
    assert_param(IS_FLASH_ADDRESS(Address));
    return(*((PointerAttr uint8_t*) Address)); /* Read byte */

}
/**
  * @brief Sets the fixed programming time
  * @param[in] FLASH_ProgramTime : Indicates the programming time to be fixed
	* This parameter can be any of the @ref FLASH_ProgramTime_TypeDef enumeration.
  * @retval
  * None
  */
void FLASH_SetProgrammingTime(FLASH_ProgramTime_TypeDef FLASH_ProgramTime)
{
    /* Check parameter */
    assert_param(IS_FLASH_PROGRAM_TIME(FLASH_ProgramTime));

    FLASH->CR1 &= (uint8_t)(~FLASH_CR1_FIX);
    FLASH->CR1 |= (uint8_t)FLASH_ProgramTime;
}
/**
  * @brief Returns the fixed programming time
  * @par Parameters:
  * None
  * @retval @ref FLASH_ProgramTime_TypeDef : Fixed programming time value
  */
FLASH_ProgramTime_TypeDef FLASH_GetProgrammingTime(void)
{
    return((FLASH_ProgramTime_TypeDef)(FLASH->CR1 & FLASH_CR1_FIX));
}
/**
  * @brief Returns the FLASH Read Out Protection Status.
  * @par Parameters:
  * None
  * @retval FunctionalState: Indicates the FLASH Read Out Protection Status.
	* This parameter can be any of the @ref FunctionalState enumeration.
  */
FunctionalState FLASH_GetReadOutProtectionStatus(void)
{
    if (OPT->OPT0_LOCKBYTE == FLASH_READOUTPROTECTION_KEY)
    {
        /* The status of the Flash read out protection is enabled*/
        return ENABLE;
    }
    else
    {
        /* The status of the Flash read out protection is disabled*/
        return DISABLE;
    }
}

/**
  * @brief Returns the Boot memory size in bytes
  * @par Parameters:
  * None
  * @retval uint16_t : Boot memory size in bytes
  */
uint16_t FLASH_GetBootSize(void)
{
    uint16_t temp;

    /* Calculates the number of bytes */
    temp = (uint16_t)(OPT->OPT2_BOOTSIZE * (uint16_t)64);

    /* Correction because size upper 8kb doesn't exist */
    if (OPT->OPT2_BOOTSIZE > 0x7F)
    {
        temp = 8192;
    }

    /* Return value */
    return(temp);

}

/**
  * @brief Returns the Data EEPROM Area size in bytes
  * @par Parameters:
  * None
  * @retval uint16_t : Data EEPROM Area size in bytes
  */
uint16_t FLASH_GetDataSize(void)
{
    uint16_t temp;
    /* Calculates the number of bytes */
    temp = (uint16_t)(OPT->OPT3_DATASIZE * (uint16_t)64);

    /* Correction because size upper of 2kb doesn't exist */
    if (OPT->OPT3_DATASIZE > 0x20)
    {
        temp = 2048;
    }

    /* Return value */
    return(temp);
}
/**
  * @brief Checks whether the specified FLASH flag is set or not.
  * @param[in] FLASH_FLAG : specifies the Flash Flag to check.
  * This parameter can be any of the @ref FLASH_FLAG_TypeDef enumeration.
  * @retval FlagStatus : Indicates the state of the Flash_Flag.
  * This parameter can be any of the @ref FlagStatus enumeration.
  */
FlagStatus FLASH_GetFlagStatus(FLASH_FLAG_TypeDef FLASH_FLAG)
{
    FlagStatus status = RESET;
    assert_param(IS_FLASH_FLAGS(FLASH_FLAG));

    /* Check the status of the specified flash flag*/
    if ((FLASH->IAPSR  & (uint8_t)FLASH_FLAG) != (uint8_t)RESET)
    {
        status = SET; /* FLASH_FLAG is set*/
    }
    else
    {
        status = RESET; /* FLASH_FLAG is reset*/
    }

    /* Return the Flash_Flag status*/
    return status;
}
/**
  * @brief Wait for a Flash operation to complete.
  * @par Parameters:
  * None
  * @retval FLASH_Status_TypeDef State of the last operation
  * @par Required preconditions:
  * The FLASH_WaitForLastOperation function should be executed from RAM.
  * This function return the FLASH status and clears the EOP, WR_PG_DIS flags in the IAPSR register.
  */
FLASH_Status_TypeDef FLASH_WaitForLastOperation(void)
{
    uint32_t timeout = OPERATION_TIMEOUT;
    uint8_t My_FlagStatus = 0x00;

    /* Wait until operation completion or write protected page occured */
    while ((My_FlagStatus == 0x00) && (timeout != 0x00))
    {
        My_FlagStatus = (uint8_t)(FLASH->IAPSR & (FLASH_IAPSR_EOP | FLASH_IAPSR_WR_PG_DIS));
        timeout--;
    }

    if (timeout == 0x00 )
    {
        My_FlagStatus = FLASH_Status_TimeOut;
    }

    return((FLASH_Status_TypeDef)My_FlagStatus);
}

/* *****************************************************************************************/
/*                    Uncomment the line below to use these functions 	                   */
/*                                                                                         */
/* *****************************************************************************************/
/* LINKER SECTIONS DEFINITION FOR THIS FILE ONLY */
#ifdef USE_COSMIC_SECTIONS
#pragma section (FLASH_CODE)
#pragma section const {FLASH_CONST}
#pragma section @near [FLASH_URAM]
#pragma section @near {FLASH_IRAM}
#pragma section @tiny [FLASH_UZRAM]
#pragma section @tiny {FLASH_IZRAM}
#endif
/**
  * @brief Erases one Block in the program or data EEPROM memory
  * @param[in] BlockNum : The Block number
	* @retval
  * None
  * @par Required preconditions:
  * The FLASH_EraseBlock function Should be executed from RAM.
  * PointerAttr define is declared in the stm8l10x.h file to select the pointer that declared
  *	as near (2 bytes).
  */
void FLASH_EraseBlock(uint8_t BlockNum)
{
    uint32_t *pwFlash;
    uint16_t StartAddress = 0;
    /* Check parameters */
    assert_param(IS_FLASH_BLOCK_NUMBER(BlockNum));

    StartAddress = FLASH_START_PHYSICAL_ADDRESS;
    /* Point to the first block address */
    pwFlash = (PointerAttr uint32_t *)(StartAddress + ((uint16_t)BlockNum * (uint16_t)FLASH_BLOCK_SIZE));

    /* Enable Word Write Once */
    FLASH->CR2 |= FLASH_CR2_ERASE;

    *pwFlash = (uint32_t)0;
}
/**
  * @brief Programs a memory block
  * @param[in] BlockNum : The Block number
  * @param[in] FLASH_ProgramMode : The programming mode.
  * @param[in] Buffer : The buffer address of source data.
  * @retval
  * None
  * @par Required preconditions:
  * The FLASH_ProgramBlock function should be executed from RAM.
  * PointerAttr define is declared in the stm8l10x.h file to select the pointer that declared
  *	as near (2 bytes).
  */
void FLASH_ProgramBlock(uint8_t BlockNum, FLASH_ProgramMode_TypeDef FLASH_ProgramMode, uint8_t *Buffer)
{
    uint16_t Count = 0;
    uint16_t StartAddress;

    /* Check parameters */
    assert_param(IS_FLASH_BLOCK_NUMBER(BlockNum));
    assert_param(IS_FLASH_PROGRAM_MODE(FLASH_ProgramMode));

    /* Selection of Standard or Fast programming mode */
    if (FLASH_ProgramMode == FLASH_ProgramMode_Standard)
    {
        /* Standard programming mode */
        FLASH->CR2 |= FLASH_CR2_PRG;
    }
    else
    {
        /* Fast programming mode */
        FLASH->CR2 |= FLASH_CR2_FPRG;
    }
    StartAddress = FLASH_START_PHYSICAL_ADDRESS;
    /* Point to the first Block address */
    StartAddress = StartAddress + ((uint16_t)BlockNum * (uint16_t)FLASH_BLOCK_SIZE);

    /* Copy data bytes from RAM to FLASH memory */
    for (Count = 0; Count < FLASH_BLOCK_SIZE; Count++)
    {
        *((PointerAttr uint8_t*)StartAddress + Count) = ((uint8_t)(Buffer[Count]));
    }
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/