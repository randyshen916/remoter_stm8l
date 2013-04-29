/**
  ******************************************************************************
  * @file stm8l10x_i2c.h
  * @brief This file contains all functions prototype and macros for the I2C peripheral.
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
#ifndef __STM8L10x_I2C_H
#define __STM8L10x_I2C_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/

/** @addtogroup I2C_Exported_Types
  * @{
  */

/**
  * @brief I2C duty cycle (fast mode only)
  */
typedef enum
{
    I2C_DutyCycle_2    = (uint8_t)0x00,  /*!< Fast mode Tlow/THigh = 2 */
    I2C_DutyCycle_16_9 = (uint8_t)0x40   /*!< Fast mode Tlow/Thigh = 16/9 */
} I2C_DutyCycle_TypeDef;

/**
  * @brief I2C Acknowledgement configuration
  */
typedef enum
{
    I2C_Ack_Disable = (uint8_t)0x00,  /*!< No acknowledge */
    I2C_Ack_Enable  = (uint8_t)0x04   /*!< Acknowledge Enabled */
} I2C_Ack_TypeDef;

/**
  * @brief I2C Acknowledgement position configuration
  */
typedef enum
{
	  I2C_AckPosition_Current = (uint8_t)0x00,   /*!< Acknowledge on the current byte */
    I2C_AckPosition_Next    = (uint8_t)0x08    /*!< Acknowledge on the next byte */
} I2C_AckPosition_TypeDef;


/**
  * @brief I2C Addressing Mode (slave mode only)
  */
typedef enum
{
    I2C_AcknowledgedAddress_7bit  = (uint8_t)0x00,  /*!< 7-bit slave address (10-bit address not acknowledged) */
    I2C_AcknowledgedAddress_10bit = (uint8_t)0x80   /*!< 10-bit slave address (7-bit address not acknowledged) */
} I2C_AcknowledgedAddress_TypeDef;

/**
  * @brief I2C transfer direction
  * Warning: the values correspond to the ADD0 bit position in the OARL register
  */
typedef enum
{
    I2C_Direction_Transmitter = (uint8_t)0x00,  /*!< Transmission direction */
    I2C_Direction_Receiver    = (uint8_t)0x01   /*!< Reception direction */
} I2C_Direction_TypeDef;

/**
  * @brief I2C Flags
  * Elements values convention: 0xXY
  *  X = choice between the SRx registers
  *      X = 1 : SR1
  *      X = 2 : SR2
  *      X = 3 : SR3
  *  Y = Flag position in the register 
  */

typedef enum
{
    /* SR1 register flags */
    I2C_FLAG_TXE       = (uint16_t)0x0180,  /*!< Transmit Data Register Empty flag */
    I2C_FLAG_RXNE      = (uint16_t)0x0140,  /*!< Read Data Register Not Empty flag */
    I2C_FLAG_STOPF     = (uint16_t)0x0110,  /*!< Stop detected flag */
    I2C_FLAG_ADD10     = (uint16_t)0x0108,  /*!< 10-bit Header sent flag */
    I2C_FLAG_BTF       = (uint16_t)0x0104,  /*!< Data Byte Transfer Finished flag */
    I2C_FLAG_ADDR      = (uint16_t)0x0102,  /*!< Address Sent/Matched (master/slave) flag */
    I2C_FLAG_SB        = (uint16_t)0x0101,  /*!< Start bit sent flag */

    /* SR2 register flags */
    I2C_FLAG_WUFH     = (uint16_t)0x0220,  /*!< Wake Up From Halt Flag */
    I2C_FLAG_OVR      = (uint16_t)0x0208,  /*!< Overrun/Underrun flag */
    I2C_FLAG_AF       = (uint16_t)0x0204,  /*!< Acknowledge Failure Flag */
    I2C_FLAG_ARLO     = (uint16_t)0x0202,  /*!< Arbitration Loss Flag */
    I2C_FLAG_BERR     = (uint16_t)0x0201,  /*!< Misplaced Start or Stop condition */

    /* SR3 register flags */
    I2C_FLAG_GENCALL  = (uint16_t)0x0310,  /*!< General Call header received Flag */
    I2C_FLAG_TRA      = (uint16_t)0x0304,  /*!< Transmitter Receiver Flag */
    I2C_FLAG_BUSY     = (uint16_t)0x0302,  /*!< Bus Busy Flag */
    I2C_FLAG_MSL      = (uint16_t)0x0301   /*!< Master Slave Flag */
} I2C_FLAG_TypeDef;


/**
  * @brief I2C Pending bits
  * Elements values convention: 0xXYZZ
  *  X = choice between the SRx registers
	*      X = 0 : ITR
  *      X = 1 : SR1
  *      X = 2 : SR2
	*  Y = Position of the corresponding Interrupt
  *  ZZ = flag mask in the dedicated register(X register)
  */

typedef enum
{
		I2C_IT_ERR             = (uint16_t)0x0001, 	/*!< Error Interruption */
    I2C_IT_EVT             = (uint16_t)0x0002, 	/*!< Event Interruption */
    I2C_IT_BUF             = (uint16_t)0x0004, 	/*!< Buffer Interruption */
    /* SR1 register flags */
    I2C_IT_TXE             = (uint16_t)0x1680, 	/*!< Transmit Data Register Empty  */
    I2C_IT_RXNE            = (uint16_t)0x1640, 	/*!< Read Data Register Not Empty  */
    I2C_IT_STOPF           = (uint16_t)0x1210, 	/*!< Stop detected  */
    I2C_IT_ADD10           = (uint16_t)0x1208, 	/*!< 10-bit Header sent */
    I2C_IT_BTF             = (uint16_t)0x1204, 	/*!< Data Byte Transfer Finished  */
    I2C_IT_ADDR            = (uint16_t)0x1202, 	/*!< Address Sent/Matched (master/slave)  */
    I2C_IT_SB              = (uint16_t)0x1201, 	/*!< Start bit sent  */

    /* SR2 register flags */
    I2C_IT_WUFH            = (uint16_t)0x2220, 	/*!< Wake Up From Halt  */
    I2C_IT_OVR             = (uint16_t)0x2108, 	/*!< Overrun/Underrun  */
    I2C_IT_AF              = (uint16_t)0x2104, 	/*!< Acknowledge Failure  */
    I2C_IT_ARLO            = (uint16_t)0x2102, 	/*!< Arbitration Loss  */
    I2C_IT_BERR            = (uint16_t)0x2101  	/*!< Misplaced Start or Stop condition */
} I2C_IT_TypeDef;

/**
  * @brief I2C possible events
  * Values convention: 0xXXYY
  * XX = Event SR3 corresponding value
	* YY = Event SR1 corresponding value
	* @note if Event = EV3_2 the rule above does not apply
	* YY = Event SR2 corresponding value
  */
typedef enum
{
    I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED= (uint16_t)0x0682,  /*!< EV1: TRA, BUSY, TXE and ADDR flags */
    I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED   = (uint16_t)0x0202,  /*!< EV1: BUSY and ADDR flags */
    I2C_EVENT_SLAVE_BYTE_RECEIVED              = (uint16_t)0x0240,  /*!< EV2: BUSY and RXNE flags */
    I2C_EVENT_SLAVE_BYTE_TRANSMITTED           = (uint16_t)0x0684,  /*!< EV3: TRA, BUSY, TXE and BTF flags */
    I2C_EVENT_SLAVE_STOP_DETECTED              = (uint16_t)0x0010,  /*!< EV4: STOPF flag */
		I2C_EVENT_SLAVE_ACK_FAILURE                = (uint16_t)0x0004,  /*!< EV3_2: AF flag */
		
    I2C_EVENT_MASTER_MODE_SELECT               = (uint16_t)0x0301,  /*!< EV5: BUSY, MSL and SB flag */
    I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED = (uint16_t)0x0782,  /*!< EV6: BUSY, MSL, ADDR, TXE and TRA flags*/
    I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED    = (uint16_t)0x0302,  /*!< EV6: BUSY, MSL and ADDR flags */
		I2C_EVENT_MASTER_BYTE_RECEIVED             = (uint16_t)0x0340,  /*!< EV7: BUSY, MSL and RXNE flags */
    I2C_EVENT_MASTER_BYTE_TRANSMITTING         = (uint16_t)0x0780,  /*!< EV8: TRA, BUSY, MSL, TXE flags */
    I2C_EVENT_MASTER_BYTE_TRANSMITTED          = (uint16_t)0x0784,  /*!< EV8_2: TRA, BUSY, MSL, TXE and BTF flags */
    I2C_EVENT_MASTER_MODE_ADDRESS10            = (uint16_t)0x0308   /*!< EV9: BUSY, MSL and ADD10 flags */
} I2C_Event_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @addtogroup I2C_Exported_Constants
  * @{
  */
#define I2C_MAX_STANDARD_FREQ ((uint32_t)100000)
#define I2C_MAX_FAST_FREQ     ((uint32_t)400000)
#define I2C_MAX_INPUT_FREQ    ((uint8_t)16)

/**
  *@}
  */

/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup I2C_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function to check the different functions parameters.
  */

/**
  * @brief  Macro used by the assert function to check the different I2C duty cycles.
  */
#define IS_I2C_DUTY_CYCLE(CYCLE)(((CYCLE) == I2C_DutyCycle_2) || \
                                 ((CYCLE) == I2C_DutyCycle_16_9))

/**
  * @brief  Macro used by the assert function to check the different acknowledgement state
  */
#define IS_I2C_ACK_STATE(STATE) (((STATE) == I2C_Ack_Disable) || \
                                 ((STATE) == I2C_Ack_Enable))

/**
  * @brief  Macro used by the assert function to check the different acknowledgement position
  */
#define IS_I2C_ACK_POSITION(POSITION) (((POSITION) == I2C_AckPosition_Next) || \
                                       ((POSITION) == I2C_AckPosition_Current))

/**
  * @brief  Macro used by the assert function to check the different I2C addressing modes.
  */
#define IS_I2C_ACKNOWLEDGE_ADDRESS(ADDMODE) (((ADDMODE) == I2C_AcknowledgedAddress_7bit) || \
                                             ((ADDMODE) == I2C_AcknowledgedAddress_10bit))

/**
  * @brief  Macro used by the assert function to check the different I2C communcation direction.
  */
#define IS_I2C_DIRECTION(DIR)(((DIR) == I2C_Direction_Transmitter) || \
                              ((DIR) == I2C_Direction_Receiver ))

/**
  * @brief  Macro used by the assert function to check the different I2C flags.
  */
#define IS_I2C_GET_FLAG(FLAG) (((FLAG) == I2C_FLAG_TXE)    || ((FLAG) == I2C_FLAG_RXNE) || \
                               ((FLAG) == I2C_FLAG_STOPF)  || ((FLAG) == I2C_FLAG_ADD10)|| \
															 ((FLAG) == I2C_FLAG_BTF)    || ((FLAG) == I2C_FLAG_ADDR) || \
                               ((FLAG) == I2C_FLAG_SB)     || ((FLAG) == I2C_FLAG_WUFH) || \
                               ((FLAG) == I2C_FLAG_OVR)    || ((FLAG) == I2C_FLAG_AF)   || \
                               ((FLAG) == I2C_FLAG_ARLO)   || ((FLAG) == I2C_FLAG_BERR) || \
                               ((FLAG) == I2C_FLAG_GENCALL)|| ((FLAG) == I2C_FLAG_TRA) || \
                               ((FLAG) == I2C_FLAG_BUSY)   || ((FLAG) == I2C_FLAG_MSL))

/**
  * @brief  Macro used by the assert function to check the I2C flags to clear.
  */
#define IS_I2C_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xDDE0) == (uint16_t)0x00) && ((FLAG) != (uint16_t)0x00))

/**
  * @brief Macro used by the assert_param function in order to check the different sensitivity values for the Interrupts
  */
#define IS_I2C_CONFIG_IT(IT) ((((IT) & (uint8_t)0xF8) == 0x00) && ((IT) != 0x00))

/**
  * @brief  Macro used by the assert function to check the different I2C possible pending bits to clear by writing 0.
  */
#define IS_I2C_CLEAR_IT(IT) ((((IT) & (uint16_t)0xDCD0) == (uint16_t)0x00) && ((IT) != (uint16_t)0x00))

/**
  * @brief  Macro used by the assert function to check the different I2C possible pending bits.
  */
#define IS_I2C_GET_IT(IT) (((IT) == I2C_IT_OVR) ||((IT) == I2C_IT_AF) || \
                           ((IT) == I2C_IT_ARLO) ||((IT) == I2C_IT_BERR) || \
													 ((IT) == I2C_IT_TXE) ||((IT) == I2C_IT_RXNE) || \
													 ((IT) == I2C_IT_STOPF) ||((IT) == I2C_IT_ADD10) || \
													 ((IT) == I2C_IT_BTF) || ((IT) == I2C_IT_ADDR) || \
													 ((IT) == I2C_IT_SB) || ((IT) == I2C_IT_WUFH ))

/**
  * @brief  Macro used by the assert function to check the different I2C possible events.
  */
#define IS_I2C_EVENT(EVENT) (((EVENT) == I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_BYTE_RECEIVED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_BYTE_TRANSMITTED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_STOP_DETECTED) || \
                             ((EVENT) == I2C_EVENT_MASTER_MODE_SELECT) || \
                             ((EVENT) == I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) || \
                             ((EVENT) == I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) || \
                             ((EVENT) == I2C_EVENT_MASTER_BYTE_RECEIVED) || \
                             ((EVENT) == I2C_EVENT_MASTER_BYTE_TRANSMITTED) || \
                             ((EVENT) == I2C_EVENT_MASTER_BYTE_TRANSMITTING) || \
                             ((EVENT) == I2C_EVENT_MASTER_MODE_ADDRESS10) || \
                             ((EVENT) == I2C_EVENT_SLAVE_ACK_FAILURE))
/**
  * @brief  Macro used by the assert function to check the different I2C possible own address.
  */
#define IS_I2C_OWN_ADDRESS(ADDRESS) ((ADDRESS) <= (uint16_t)0x03FF)

/* The address must be even */
#define IS_I2C_ADDRESS(ADD) (((ADD) & (uint8_t)0x01) == (uint8_t)0x00)

/**
  * @brief  Macro used by the assert function to check that I2C Output clock frequency must be between 1Hz and 400kHz.
  */
#define IS_I2C_OUTPUT_CLOCK_FREQ(FREQ) (((FREQ) >= (uint8_t)1) && ((FREQ) <= I2C_MAX_FAST_FREQ))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
/** @addtogroup I2C_Exported_Functions
  * @{
  */

void I2C_DeInit(void);
void I2C_Init(uint32_t OutputClockFrequency, uint16_t OwnAddress, 
              I2C_DutyCycle_TypeDef I2C_DutyCycle, I2C_Ack_TypeDef I2C_Ack, 
              I2C_AcknowledgedAddress_TypeDef I2C_AcknowledgedAddress);
void I2C_Cmd(FunctionalState NewState);
void I2C_GeneralCallCmd(FunctionalState NewState);
void I2C_GenerateSTART(FunctionalState NewState);
void I2C_GenerateSTOP(FunctionalState NewState);
void I2C_SoftwareResetCmd(FunctionalState NewState);
void I2C_StretchClockCmd(FunctionalState NewState);
void I2C_AcknowledgeConfig(FunctionalState NewState);
void I2C_AckPositionConfig(I2C_AckPosition_TypeDef I2C_AckPosition);
void I2C_FastModeDutyCycleConfig(I2C_DutyCycle_TypeDef I2C_DutyCycle);
void I2C_ITConfig(I2C_IT_TypeDef I2C_IT, FunctionalState NewState);
ErrorStatus I2C_CheckEvent(I2C_Event_TypeDef I2C_Event);
I2C_Event_TypeDef I2C_GetLastEvent(void);
uint8_t I2C_ReceiveData(void);
void I2C_SendData(uint8_t Data);
void I2C_Send7bitAddress(uint8_t Address, I2C_Direction_TypeDef I2C_Direction);
FlagStatus I2C_GetFlagStatus(I2C_FLAG_TypeDef I2C_FLAG);
void I2C_ClearFlag(I2C_FLAG_TypeDef I2C_FLAG);
ITStatus I2C_GetITStatus(I2C_IT_TypeDef I2C_IT);
void I2C_ClearITPendingBit(I2C_IT_TypeDef I2C_IT);

/**
  * @}
  */

#endif /* __STM8L10x_I2C_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
