/**
  ******************************************************************************
  * @file stm8l10x_awu.h
  * @brief This file contains all functions prototype and macros for the AWU peripheral.
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
#ifndef __STM8L10x_AWU_H
#define __STM8L10x_AWU_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/


/** @addtogroup AWU_Exported_Types
  * @{
  */

/**
  * @brief AWU TimeBase selection
  */

typedef enum
{
    AWU_Timebase_No_IT  = (uint8_t)0,    /*!< No AWU interrupt selected */
    AWU_Timebase_250us 	= (uint8_t)1,    /*!< AWU Timebase equals 0.25 ms */
    AWU_Timebase_500us 	= (uint8_t)2,    /*!< AWU Timebase equals 0.5 ms */
    AWU_Timebase_1ms   	= (uint8_t)3,    /*!< AWU Timebase equals 1 ms */
    AWU_Timebase_2ms   	= (uint8_t)4,    /*!< AWU Timebase equals 2 ms */
    AWU_Timebase_4ms   	= (uint8_t)5,    /*!< AWU Timebase equals 4 ms */
    AWU_Timebase_8ms   	= (uint8_t)6,    /*!< AWU Timebase equals 8 ms */
    AWU_Timebase_16ms  	= (uint8_t)7,    /*!< AWU Timebase equals 16 ms */
    AWU_Timebase_32ms  	= (uint8_t)8,    /*!< AWU Timebase equals 32 ms */
    AWU_Timebase_64ms  	= (uint8_t)9,    /*!< AWU Timebase equals 64 ms */
    AWU_Timebase_128ms 	= (uint8_t)10,   /*!< AWU Timebase equals 128 ms */
    AWU_Timebase_256ms 	= (uint8_t)11,   /*!< AWU Timebase equals 256 ms */
    AWU_Timebase_512ms 	= (uint8_t)12,   /*!< AWU Timebase equals 512 ms */
    AWU_Timebase_1s    	= (uint8_t)13,   /*!< AWU Timebase equals 1 s */
    AWU_Timebase_2s    	= (uint8_t)14,   /*!< AWU Timebase equals 2 s */
    AWU_Timebase_12s   	= (uint8_t)15,   /*!< AWU Timebase equals 12 s */
    AWU_Timebase_30s   	= (uint8_t)16    /*!< AWU Timebase equals 30 s */
} AWU_Timebase_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @addtogroup AWU_Exported_Constants
  * @{
  */
#define LSI_FREQUENCY_MIN ((uint32_t)25000)   /*!< LSI minimum value in Hertz */
#define LSI_FREQUENCY_MAX ((uint32_t)75000)   /*!< LSI maximum value in Hertz */
/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup AWU_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function to check the different functions parameters.
  */

/**
  * @brief  Macro used by the assert function to check the AWU timebases
  */
#define IS_AWU_TIMEBASE(TB) \
   (((TB) == AWU_Timebase_No_IT) || \
    ((TB) == AWU_Timebase_250us) || \
    ((TB) == AWU_Timebase_500us) || \
    ((TB) == AWU_Timebase_1ms)   || \
    ((TB) == AWU_Timebase_2ms)   || \
    ((TB) == AWU_Timebase_4ms)   || \
    ((TB) == AWU_Timebase_8ms)   || \
    ((TB) == AWU_Timebase_16ms)  || \
    ((TB) == AWU_Timebase_32ms)  || \
    ((TB) == AWU_Timebase_64ms)  || \
    ((TB) == AWU_Timebase_128ms) || \
    ((TB) == AWU_Timebase_256ms) || \
    ((TB) == AWU_Timebase_512ms) || \
    ((TB) == AWU_Timebase_1s)    || \
    ((TB) == AWU_Timebase_2s)    || \
    ((TB) == AWU_Timebase_12s)   || \
    ((TB) == AWU_Timebase_30s))


/**
  * @brief   Macro used by the assert function to check the LSI frequency (in Hz)
  */
#define IS_LSI_FREQUENCY(FREQ) \
   (((FREQ) >= LSI_FREQUENCY_MIN) && \
	  ((FREQ) <= LSI_FREQUENCY_MAX))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup AWU_Exported_Functions
  * @{
  */

void AWU_DeInit(void);
void AWU_Init(AWU_Timebase_TypeDef AWU_TimeBase);
void AWU_Cmd(FunctionalState NewState);
void AWU_LSICalibrationConfig(uint32_t LSIFreqHz);
void AWU_IdleModeEnable(void);
void AWU_ReInitCounter(void);
FlagStatus AWU_GetFlagStatus(void);

/**
  * @}
  */

#endif /* __STM8L10x_AWU_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
