/**
  ******************************************************************************
  * @file stm8l10x_flash.h
  * @brief This file contains all functions prototype and macros for the FLASH peripheral.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8L10x_FLASH_H__
#define __STM8L10x_FLASH_H__

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported constants --------------------------------------------------------*/

/** @addtogroup FLASH_Exported_Constants
  * @{
  */

/**
  * @brief Macro used by the assert function to check the different functions parameters.
  */

#define FLASH_START_PHYSICAL_ADDRESS 	((uint16_t)0x8000)		/*!< Flash: start address */
#define FLASH_END_PHYSICAL_ADDRESS   	((uint16_t)0x9FFF)   /*!< Flash: end address */
#define FLASH_BLOCK_NUMBER           	((uint8_t)128)       /*!< Flash memory and Data EEprom: total number of Block */
#define FLASH_BLOCK_SIZE              ((uint8_t)64)       	/*!< Number of bytes in a Block (common for Program and Data EEprom memories) */
#define FLASH_RASS_KEY1 							((uint8_t)0x56) 			/*!< First RASS key */
#define FLASH_RASS_KEY2 							((uint8_t)0xAE) 			/*!< Second RASS key */
#define FLASH_READOUTPROTECTION_KEY 	((uint8_t)0xAA)   		/*!< Read out protection key */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/** @addtogroup FLASH_Exported_Types
  * @{
  */

/**
  * @brief FLASH Memory types
  */
typedef enum
{
    FLASH_MemType_Program      = (uint8_t)0xFD, /*!< Program memory */
    FLASH_MemType_Data         = (uint8_t)0xF7  /*!< Data EEPROM memory */
} FLASH_MemType_TypeDef;

/**
  * @brief FLASH programming modes
  */
typedef enum
{
    FLASH_ProgramMode_Standard = (uint8_t)0x00, /*!< Standard programming mode */
    FLASH_ProgramMode_Fast     = (uint8_t)0x10  /*!< Fast programming mode */
} FLASH_ProgramMode_TypeDef;

/**
  * @brief FLASH fixed programming time
  */
typedef enum
{
    FLASH_ProgramTime_Standard = (uint8_t)0x00, /*!< Standard programming time fixed at 1/2 tprog */
    FLASH_ProgramTime_TProg    = (uint8_t)0x01  /*!< Programming time fixed at tprog */
} FLASH_ProgramTime_TypeDef;

/**
  * @brief FLASH status of the last operation
  */
typedef enum
{
    FLASH_Status_Write_Protection_Error = (uint8_t)0x01, /*!< Write attempted to protected Block */
    FLASH_Status_TimeOut = (uint8_t)0x02, /*!< Time out error */
    FLASH_Status_Successful_Operation   = (uint8_t)0x04  /*!< End of operation flag */
} FLASH_Status_TypeDef;

/**
  * @brief FLASH flags definition
 * - Warning : FLAG value = mapping position register
  */
typedef enum {
    FLASH_FLAG_DUL       = (uint8_t)0x08,     /*!< Data EEPROM unlocked flag */
    FLASH_FLAG_EOP       = (uint8_t)0x04,     /*!< End of programming (write or erase operation) flag */
    FLASH_FLAG_PUL       = (uint8_t)0x02,     /*!< Flash Program memory unlocked flag */
    FLASH_FLAG_WR_PG_DIS = (uint8_t)0x01      /*!< Write attempted to protected page flag */
} FLASH_FLAG_TypeDef;

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup FLASH_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function in order to check the different sensitivity values for the flash Address
  */

#define IS_FLASH_ADDRESS(ADDRESS) (((ADDRESS) >= FLASH_START_PHYSICAL_ADDRESS) && \
	                                 ((ADDRESS) <= FLASH_END_PHYSICAL_ADDRESS))

/**
  * @brief Macro used by the assert function in order to check the different sensitivity values for the flash Block number
  */
#define IS_FLASH_BLOCK_NUMBER(BLOCKNUM) ((BLOCKNUM) < FLASH_BLOCK_NUMBER)

/**
  * @brief Macro used by the assert function in order to check the different sensitivity values for the flash memory type
  */
#define IS_MEMORY_TYPE(MEMTYPE) (((MEMTYPE) == FLASH_MemType_Program) || \
                                 ((MEMTYPE) == FLASH_MemType_Data))

/**
  * @brief Macro used by the assert function in order to check the different sensitivity values for the flash program block mode
  */
#define IS_FLASH_PROGRAM_MODE(MODE) (((MODE) == FLASH_ProgramMode_Standard) || \
                                     ((MODE) == FLASH_ProgramMode_Fast))

/**
  * @brief Macro used by the assert function in order to check the program time mode
  */
#define IS_FLASH_PROGRAM_TIME(TIME) (((TIME) == FLASH_ProgramTime_Standard) || \
                                     ((TIME) == FLASH_ProgramTime_TProg))

/**
  * @brief Macro used by the assert function in order to check the different flags values
  */
#define IS_FLASH_FLAGS(FLAG) (((FLAG) == FLASH_FLAG_EOP) || \
	                            ((FLAG) == FLASH_FLAG_PUL) || \
			                        ((FLAG) == FLASH_FLAG_DUL) || \
	                            ((FLAG) == FLASH_FLAG_WR_PG_DIS))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
/** @addtogroup FLASH_Exported_Functions
  * @{
  */
void FLASH_DeInit(void);
void FLASH_Unlock(FLASH_MemType_TypeDef FLASH_MemType);
void FLASH_Lock(FLASH_MemType_TypeDef FLASH_MemType);

void FLASH_ITConfig(FunctionalState NewState);
void FLASH_ProgramBlock(uint8_t BlockNum, FLASH_ProgramMode_TypeDef FLASH_ProgramMode, uint8_t *Buffer);
void FLASH_EraseBlock(uint8_t BlockNum);
void FLASH_ProgramByte(uint16_t Address, uint8_t Data);
void FLASH_EraseByte(uint16_t Address);
void FLASH_ProgramWord(uint16_t Address, uint32_t Data);
uint8_t FLASH_ReadByte(uint16_t Address);
FLASH_ProgramTime_TypeDef FLASH_GetProgrammingTime(void);
void FLASH_SetProgrammingTime(FLASH_ProgramTime_TypeDef FLASH_ProgramTime);
FunctionalState FLASH_GetReadOutProtectionStatus(void);
uint16_t FLASH_GetBootSize(void);
uint16_t FLASH_GetDataSize(void);
FlagStatus FLASH_GetFlagStatus(FLASH_FLAG_TypeDef FLASH_FLAG);
FLASH_Status_TypeDef FLASH_WaitForLastOperation(void);

/**
  * @}
  */

#endif /*__STM8L10x_FLASH_H__*/

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
