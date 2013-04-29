/**
  ******************************************************************************
  * @file stm8l10x_rst.h
  * @brief This file contains all functions prototype and macros for the RST peripherals.
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
#ifndef __STM8L10x_RST_H
#define __STM8L10x_RST_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/
/** @addtogroup RST_Exported_Types
  * @{
  */

/**
  * @brief RST Flag possible values
  */
typedef enum {
    RST_FLAG_POR_PDR     = (uint8_t)0x01, 	/*!< POR/PDR reset flag */
    RST_FLAG_SWIMF       = (uint8_t)0x08, 	/*!< SWIM reset flag */
    RST_FLAG_ILLOPF      = (uint8_t)0x04, 	/*!< Illigal opcode reset flag */
    RST_FLAG_IWDGF       = (uint8_t)0x02  	/*!< Independent watchdog reset flag */
} RST_Flag_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup RST_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function to check the different functions parameters.
  */
/**
  * @brief Macro used by the assert function to check the different RST flags.
  */
#define IS_RST_FLAG(FLAG) \
   (((FLAG) == RST_FLAG_POR_PDR) || \
    ((FLAG) == RST_FLAG_IWDGF)   || \
    ((FLAG) == RST_FLAG_ILLOPF)  || \
    ((FLAG) == RST_FLAG_SWIMF))

/**
  * @}
  */


/* Exported functions ------------------------------------------------------- */
/** @addtogroup RST_Exported_Functions
  * @{
  */
FlagStatus RST_GetFlagStatus(RST_Flag_TypeDef RST_Flag);
void RST_ClearFlag(RST_Flag_TypeDef RST_Flag);
void RST_GPOutputEnable(void);

/**
  * @}
  */


#endif /* __STM8L10x_RST_H */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
