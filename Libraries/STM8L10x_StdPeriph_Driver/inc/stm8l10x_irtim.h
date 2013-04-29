/**
  ******************************************************************************
  * @file stm8l10x_irtim.h
  * @brief This file contains all functions prototype and macros for the IRTIM peripheral.
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
#ifndef __STM8L10x_IRTIM_H
#define __STM8L10x_IRTIM_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup IRTIM_Exported_Functions
  * @{
  */

void IRTIM_DeInit(void);
void IRTIM_Cmd(FunctionalState NewState);
FunctionalState IRTIM_GetStatus(void);
void IRTIM_HighSinkODCmd(FunctionalState Newstate);
FunctionalState IRTIM_GetHighSinkODStatus(void);


/**
  * @}
  */
#endif /* __STM8L10x_IRTIM_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
