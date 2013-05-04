/**
  ******************************************************************************
  * @file Remoter.c
  * @brief This file contains all the functions for the Remoter driver.
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
#include "remoter.h"
#include "myMath.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* to avoid collusion, this value can be updated for thin adjust*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public variables ---------------------------------------------------------*/

uint8_t Send_Operation_Ready = 0x00;
uint8_t Send_Operation_Completed =0x01;
uint8_t BitsSent_Counter = 0x00;

RemoterData remoterData;
/* Public functions ----------------------------------------------------------*/

/**
  * @addtogroup Remoter_Public_Functions
  * @{
  */

/**
  * @brief Generate the binary format of the Remoter frame.
  * @param[in] Remoter_Address : Select the device adress from @ref Remoter_Address_TypeDef enumeration.
	* @param[in] Remoter_Instruction : Select the device instruction from @ref Remoter_Instruction_TypeDef enumeration.
	* @param[in] Remoter_Ctrl : Select the device control bit status from @ref Remoter_Ctrl_TypeDef enumeration.
  * @retval Binary format of the Remoter Frame.
  */
void Remoter_BinFrameGeneration( void)
{
	uint8_t i=REMOTER_BUFF_SIZE;
	while(Send_Operation_Completed == 0x00) 
	{ 
  }
	Send_Operation_Ready = 0;
	while (i--){
		remoterData.Remoter_DataFrameFormat[i]=0;
		}
	switch (remoterData.remoteType){
		case NEC_STD1:
			NEC_STD1_BinFrameGeneration();
			break;
		case DTV_STD1:
			DTV_STD1_BinFrameGeneration();
			break;
		default :
			break;
		}
	
	

	
	
	//Remoter_FrameBinaryFormat =  ;
	/* Set the Send operation Ready flag to indicate that the frame is ready to be sent */
	Send_Operation_Ready = 1;
	return ;
}
/**
  * @brief Generate the binary format of the NEC_STD1 Remoter frame.
  * @param[in] Remoter_Address : Select the device adress from remoterData
  * @retval Binary format of the Remoter Frame.
  */
void DTV_STD1_BinFrameGeneration(void){
	uint32_t Remoter_RealData=0;
	uint8_t frame_length;
	uint8_t end_length ;
	uint8_t i=0;
	remoterData.carrfreq=38;
	remoterData.singleframe=560;
	remoterData.headFrame=1800;
	Remoter_RealData|=(uint32_t)remoterData.custom3<<16;
	Remoter_RealData|=(uint32_t)remoterData.custom2<<8;
	Remoter_RealData|=(uint32_t)remoterData.custom1;
	remoterData.CustomFrameLength= 0;
	for (i=0;i<24;i++){
		if(Remoter_RealData&0x01){
			Rshift(remoterData.Remoter_CustomFrameFormat,REMOTER_BUFF_SIZE, 3);
			remoterData.Remoter_CustomFrameFormat[REMOTER_BUFF_SIZE-1]|=0x04;
			remoterData.CustomFrameLength+=3;
			
			}
		else{
			Rshift(remoterData.Remoter_CustomFrameFormat,REMOTER_BUFF_SIZE, 2);
			remoterData.Remoter_CustomFrameFormat[REMOTER_BUFF_SIZE-1]|=0x02;
			remoterData.CustomFrameLength+=2;
			
			}
		Remoter_RealData>>=1;
		}
		
	end_length=32*REMOTER_BUFF_SIZE-remoterData.CustomFrameLength;
	Rshift(remoterData.Remoter_CustomFrameFormat,REMOTER_BUFF_SIZE, end_length);

	Remoter_RealData=0;


	Remoter_RealData|=(uint32_t)remoterData.data2<<8;
	Remoter_RealData|=(uint32_t)remoterData.data1;
	remoterData.DataFrameLength= 0;
	for (i=0;i<16;i++){
		if(Remoter_RealData&0x01){
			Rshift(remoterData.Remoter_DataFrameFormat,REMOTER_BUFF_SIZE, 3);
			remoterData.Remoter_DataFrameFormat[REMOTER_BUFF_SIZE-1]|=0x08;
			remoterData.DataFrameLength+=3;
			frame_length+=3;
			}
		else{
			Rshift(remoterData.Remoter_DataFrameFormat,REMOTER_BUFF_SIZE, 2);
			remoterData.Remoter_DataFrameFormat[REMOTER_BUFF_SIZE-1]|=0x02;
			remoterData.DataFrameLength+=2;
			frame_length+=2;
			}
		Remoter_RealData>>=1;
		}
	Rshift(remoterData.Remoter_DataFrameFormat,REMOTER_BUFF_SIZE, 1);
	remoterData.Remoter_DataFrameFormat[REMOTER_BUFF_SIZE-1]|=0x01;
        remoterData.DataFrameLength+=1;
		frame_length+=1;
	end_length=32*REMOTER_BUFF_SIZE-remoterData.DataFrameLength;
	Rshift(remoterData.Remoter_DataFrameFormat,REMOTER_BUFF_SIZE, end_length);

	remoterData.Remoter_headFrameFormat=0x06;
       remoterData.HeadFrameLength=3;

	remoterData.Remoter_headFrameFormat2=0x06;
       remoterData.HeadFrameLength2=3;
	

	
	remoterData.remoterStatus=REMOTER_HEAD1;
	Remoter_carrFreq_Set(remoterData.carrfreq);
	Remoter_frame_set(remoterData.headFrame);
	return ;
	
}

/**
  * @brief Generate the binary format of the NEC_STD1 Remoter frame.
  * @param[in] Remoter_Address : Select the device adress from remoterData
  * @retval Binary format of the Remoter Frame.
  */
void  NEC_STD1_BinFrameGeneration(void){
	uint32_t Remoter_RealData=0;
	uint8_t frame_length;
	uint8_t end_length ;
	uint8_t i=0;
	remoterData.carrfreq=38;
	remoterData.singleframe=560;
	remoterData.headFrame=2250;
	Remoter_RealData|=(uint32_t)remoterData.data2<<24;
	Remoter_RealData|=(uint32_t)remoterData.data1<<16;
	Remoter_RealData|=(uint32_t)remoterData.custom2<<8;
	Remoter_RealData|=(uint32_t)remoterData.custom1;
	remoterData.DataFrameLength= 0;
	for (i=0;i<32;i++){
		if(Remoter_RealData&0x01){
			Rshift(remoterData.Remoter_DataFrameFormat,REMOTER_BUFF_SIZE, 3);
			remoterData.Remoter_DataFrameFormat[REMOTER_BUFF_SIZE-1]|=0x08;
			remoterData.DataFrameLength+=4;
			frame_length+=4;
			}
		else{
			Rshift(remoterData.Remoter_DataFrameFormat,REMOTER_BUFF_SIZE, 2);
			remoterData.Remoter_DataFrameFormat[REMOTER_BUFF_SIZE-1]|=0x02;
			remoterData.DataFrameLength+=2;
			frame_length+=2;
			}
		Remoter_RealData>>=1;
		}
	Rshift(remoterData.Remoter_DataFrameFormat,REMOTER_BUFF_SIZE, 1);
	remoterData.Remoter_DataFrameFormat[REMOTER_BUFF_SIZE-1]|=0x01;
        remoterData.DataFrameLength+=1;
		frame_length+=1;
	end_length=32*REMOTER_BUFF_SIZE-remoterData.DataFrameLength;
	Rshift(remoterData.Remoter_DataFrameFormat,REMOTER_BUFF_SIZE, end_length);
	Remoter_carrFreq_Set(remoterData.carrfreq);
	Remoter_frame_set(remoterData.headFrame);
	return ;
	
}



/**
  * @brief Send by hardware Manchester Format Remoter Frame.
  * @param[in] Remoter_BinaryFrameFormat : the Remoter frame in binary format.
	* @retval  the Remoter frame in Manchester format.
  */
void Remoter_SendFrame(void)
{
	uint32_t bit_msg = 0;
	
	
	if( (Send_Operation_Ready == 1) && (BitsSent_Counter <= remoterData.DataFrameLength))
	{
		remoterData.remoterStatus= REMOTER_DATA;
		bit_msg=remoterData.Remoter_DataFrameFormat[0]&0x80000000;
		
		if (bit_msg)
		{
			TIM3_ForcedOC1Config(TIM3_ForcedAction_Active);
		}
		else
		{
			TIM3_ForcedOC1Config(TIM3_ForcedAction_Inactive);
		}
		Rshift(remoterData.Remoter_DataFrameFormat,REMOTER_BUFF_SIZE, 1);
		BitsSent_Counter++;
	}
	else
	{
		Send_Operation_Completed = 0x01;
		Send_Operation_Ready = 0;
		BitsSent_Counter=0;
		TIM3_ForcedOC1Config(TIM3_ForcedAction_Inactive);
	}
}

/**
  * @brief Generate and Send the Remoter frame.
  * @param[in] Remoter_Address : the Remoter Device destination 
	* (a member of @ref Remoter_Address_TypeDef enumeration).
  * @param[in] Remoter_Instruction : the Remoter command instruction 
	* (a member of @ref Remoter_Address_TypeDef enumeration).
	* @param[in] Remoter_Ctrl : the Remoter Control bit
	* (a member of @ref Remoter_Ctrl_TypeDef enumeration).
  * @retval  None
  */
void SendFrame(void)
{
	
	
 	GPIO_ResetBits(LEDS_PORT, LED_PIN);
	
	
	
	/* Disable Interrupts */
	disableInterrupts();
	
	
	/* Generate a binary format of the Frame */
	Remoter_BinFrameGeneration();
	
	
	
  /* Enable Interrupts */
	enableInterrupts();
	
	GPIO_SetBits(LEDS_PORT, LED_PIN);
	 
}



/**
  * @brief Reverse the Control bit of the Remoter Frame.
  * @param[in] Remoter_Ctrl : the Remoter Control present state (a member of the @ref Remoter_Ctrl_TypeDef enumeration).
	* @retval the new Remoter Control state (a member of the @ref Remoter_Ctrl_TypeDef enumeration).
  */
Remoter_Ctrl_TypeDef Remoter_CtrlBitReverse(Remoter_Ctrl_TypeDef Remoter_Ctrl)
{
	if(Remoter_Ctrl !=Remoter_Ctrl_Reset)
	{
		/* Reset the Control bit of the Remoter Frame*/
		Remoter_Ctrl = Remoter_Ctrl_Reset;
	}
	else
	{
		/* Set the Control bit of the Remoter Frame*/
		Remoter_Ctrl = Remoter_Ctrl_Set;
	}
	return (Remoter_Ctrl_TypeDef)Remoter_Ctrl;
}

/**
  * @brief Configurate TIM2.
  * @param[in] uint16_t freq kHz
  * @retval  None
  */
void Remoter_carrFreq_Set(uint16_t freq)
{

	uint16_t count;

	count = 16000/freq;

	/* DeInit TIM2 */
	TIM2_DeInit();
	
	/* TIM2 Time base configuration */
       TIM2_TimeBaseInit(TIM2_Prescaler_1, TIM2_CounterMode_Up, count );
	
	/* TIM2 channel 1 configuration */
	TIM2_OC1Init(TIM2_OCMode_PWM1, TIM2_OutputState_Enable, count/3, TIM2_OCPolarity_Low, TIM2_OCIdleState_Reset);
	
	/* TIM2 Counter Enable */
	TIM2_Cmd(ENABLE);
	
	/* Enable the TIM2 channel1 output to be connected internly to the IRTIM*/
	TIM2_CtrlPWMOutputs(ENABLE);
}





/**
  * @brief Remoter single frame set
  * @param[in] None
  * @retval  None
  */
void Remoter_frame_set(uint16_t frame_length)
{
	uint16_t count;
	/* DeInit TIM3 */
	TIM3_DeInit();

	count=frame_length*0x10;
  
	/* TIM3 Time base configuration */
	TIM3_TimeBaseInit(TIM3_Prescaler_1, TIM3_CounterMode_Up, count );
  
	/* TIM3 channel 1 configuration */
	TIM3_OC1Init(TIM3_OCMode_Timing, TIM3_OutputState_Enable,count+100, TIM3_OCPolarity_High, TIM3_OCIdleState_Reset );
	
	/* TIM3 interrupt Update Enable */
	TIM3_ITConfig(TIM3_IT_Update, ENABLE);
	
	/* TIM3 Counter Enable */
	TIM3_Cmd(ENABLE);
	/* Enable the TIM3 channel1 output to be connected internly to the IRTIM*/
	TIM3_CtrlPWMOutputs(ENABLE);
}




/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
