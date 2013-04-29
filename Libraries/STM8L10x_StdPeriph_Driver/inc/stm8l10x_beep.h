/**
  ******************************************************************************
  * @file stm8l10x_beep.h
  * @brief This file contains all functions prototype and macros for the BEEP peripheral.
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
#ifndef __STM8L10x_BEEP_H
#define __STM8L10x_BEEP_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/

/** @addtogroup BEEP_Exported_Types
  * @{
  */

/**
  * @brief BEEP Frequency selection
  */
typedef enum {
    BEEP_Frequency_1KHz = (uint8_t)0x00,  /*!< Beep signal output frequency equals to 1 KHz */
    BEEP_Frequency_2KHz = (uint8_t)0x40,  /*!< Beep signal output frequency equals to 2 KHz */
    BEEP_Frequency_4KHz = (uint8_t)0x80   /*!< Beep signal output frequency equals to 4 KHz */
} BEEP_Frequency_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @addtogroup BEEP_Exported_Constants
  * @{
  */

#define BEEP_CALIBRATION_DEFAULT ((uint8_t)0x01)   /*!< Default value when calibration is not done */
#define LSI_FREQUENCY_MIN ((uint32_t)25000)             /*!< LSI minimum value in Hertz */
#define LSI_FREQUENCY_MAX ((uint32_t)75000)             /*!< LSI maximum value in Hertz */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup BEEP_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function to check the different functions parameters.
  */

/**
  * @brief Macro used by the assert function to check the BEEP frequencies.
  */
#define IS_BEEP_FREQUENCY(FREQ) \
  (((FREQ) == BEEP_Frequency_1KHz) || \
   ((FREQ) == BEEP_Frequency_2KHz) || \
   ((FREQ) == BEEP_Frequency_4KHz))

/**
  * @brief  Macro used by the assert function to check the LSI frequency (in Hz).
  */
#define IS_LSI_FREQUENCY(FREQ) \
  (((FREQ) >= LSI_FREQUENCY_MIN) && \
   ((FREQ) <= LSI_FREQUENCY_MAX))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup BEEP_Exported_Functions
  * @{
  */

void BEEP_DeInit(void);
void BEEP_Init(BEEP_Frequency_TypeDef BEEP_Frequency);
void BEEP_Cmd(FunctionalState NewState);
void BEEP_LSICalibrationConfig(uint32_t LSIFreqHz);

/**
  * @}
  */

#endif /* __STM8L10x_BEEP_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
