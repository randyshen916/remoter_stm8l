/**
  ******************************************************************************
  * @file Remoter.h
  * @brief This file contains all functions prototype and macros for the Remoter driver.
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
#include "bsp.h"


/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/



/**
  * @brief Definition of the Remoter decode type
 */	

typedef enum
{
   	NEC_STD1					      = ((uint8_t)0),
	NEC_STD2					      = ((uint8_t)1),
	NEC_STD3			    = ((uint8_t)2),
	DTV_STD1			  = ((uint8_t)3),
	
	
}RemoteType;

typedef enum
{
       REMOTER_END					      = ((uint8_t)0),
	REMOTER_HEAD1					      = ((uint8_t)1),
	REMOTER_HEAD2					      = ((uint8_t)2),
	REMOTER_CUSTOM			    = ((uint8_t)3),
	REMOTER_DATA			  = ((uint8_t)4),
	REMOTER_REPEAT			  = ((uint8_t)5),
	
}RemoteStatus;


/**
  * @brief Definition of the Remoter send data
  */	
#define REMOTER_BUFF_SIZE 4

typedef struct _RemoterData
{
	RemoteType      remoteType;
	uint8_t       carrfreq;		                                           /*  载波频率             */
	uint16_t      headFrame;		                                       /* 头帧长度             */   
	uint16_t       singleframe;												 /* 单帧长度                  */
	uint8_t       custom1;		                                          /*客户码1  */
	uint8_t       custom2;		                                            /*客户码2  */                                 
	uint8_t       custom3;			                                            /*客户码3  */    
	uint8_t       custom4;			                                            /*客户码4  */    
	uint8_t       data1;			                                            /*数据码1*/    
	uint8_t       data2;			                                            /*数据码2 */    
	uint8_t       data3;			                                            /*数据码3*/    
	uint8_t       data4;			                                            /*数据码4 */    
	RemoteStatus remoterStatus;						/*remoter sender status indicate*/
	uint8_t      isHead;
	uint8_t	 isRepeat;
	uint16_t    Remoter_headFrameFormat;				/*head frame send data*/	
	uint8_t    HeadFrameLength;						/*head frame send length*/	
	uint16_t    Remoter_headFrameFormat2;				/*head frame send data*/	
	uint8_t    HeadFrameLength2;						/*head frame send length*/	
	uint8_t    CustomFrameLength;
	uint32_t  Remoter_CustomFrameFormat[REMOTER_BUFF_SIZE];				  /*remote code data ready to send,side by side*/    
	uint8_t    DataFrameLength;
	uint32_t  Remoter_DataFrameFormat[REMOTER_BUFF_SIZE];				  /*remote code data ready to send,side by side*/    
	
}RemoterData;



/**
  * @brief Definition of the Remoter Control bit value.
  */	

typedef enum
{
  Remoter_Ctrl_Reset			= ((uint16_t)0),
	Remoter_Ctrl_Set		  	= ((uint16_t)0x0800)
}Remoter_Ctrl_TypeDef;



/**
  * @}
  */



/* Exported functions ------------------------------------------------------- */
/** @addtogroup Remoter_Exported_Functions
  * @{
  */


void  Remoter_BinFrameGeneration(void );

void  NEC_STD1_BinFrameGeneration(void);

void  DTV_STD1_BinFrameGeneration(void);


uint32_t Remoter_ManchesterConvert(uint16_t Remoter_BinaryFrameFormat);

void Remoter_SendFrame(void);

void SendFrame(void);

Remoter_Ctrl_TypeDef Remoter_CtrlBitReverse(Remoter_Ctrl_TypeDef Remoter_Ctrl);


void Remoter_carrFreq_Set(uint16_t freq);

void Remoter_frame_set(uint16_t frame_length);

/**
  * @}
  */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/	
