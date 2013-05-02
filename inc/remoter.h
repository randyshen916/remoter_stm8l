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
#include "stm8l10x_tim3.h"


/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/

/** @addtogroup Remoter_Exported_Types
  * @{
  */
	
/**
  * @brief Definition of the Remoter devices adresses.
  */	

typedef enum
{
  Remoter_Address_TV1					      = ((uint8_t)0),
	Remoter_Address_TV2					      = ((uint8_t)1),
	Remoter_Address_VideoText			    = ((uint8_t)2),
	Remoter_Address_ExtensionTV			  = ((uint8_t)3),
	Remoter_Address_ExtensionVCR		  = ((uint8_t)9),
	Remoter_Address_LaserVideoPlayer	= ((uint8_t)4),
	Remoter_Address_VCR1				      = ((uint8_t)5),
	Remoter_Address_VCR2				      = ((uint8_t)6),
	Remoter_Address_Sat1				      = ((uint8_t)8),
	Remoter_Address_Sat2				      = ((uint8_t)10),
	Remoter_Address_CD					      = ((uint8_t)20),
	Remoter_Address_CDVideo				    = ((uint8_t)12),
	Remoter_Address_CDPhoto				    = ((uint8_t)14),
	Remoter_Address_CDRW				      = ((uint8_t)26),
	Remoter_Address_PreampliAudio1		= ((uint8_t)16),
	Remoter_Address_PreampliAudio2		= ((uint8_t)19),
	Remoter_Address_Tuner				      = ((uint8_t)17),
	Remoter_Address_AnalogMagneto   	= ((uint8_t)18),
	Remoter_Address_DDCMagneto			  = ((uint8_t)23),
	Remoter_Address_RackAudio			    = ((uint8_t)21),
	Remoter_Address_AudioSatReceiver	= ((uint8_t)22),
		
	Remoter_Address_Reserved00		    = ((uint8_t)7),
	Remoter_Address_Reserved01		    = ((uint8_t)11),
	Remoter_Address_Reserved02		    = ((uint8_t)13),
	Remoter_Address_Reserved03		    = ((uint8_t)15),
	Remoter_Address_Reserved04		    = ((uint8_t)24),
	Remoter_Address_Reserved05		    = ((uint8_t)25),
	Remoter_Address_Reserved06		    = ((uint8_t)27),
	Remoter_Address_Reserved07		    = ((uint8_t)28),
	Remoter_Address_Reserved08		    = ((uint8_t)29),
	Remoter_Address_Reserved09		    = ((uint8_t)30),
	Remoter_Address_Reserved10		  	= ((uint8_t)31)
}Remoter_Address_TypeDef;

/**
  * @brief Definition of the Remoter devices instructions.
  */	
typedef enum
{
/* Device general Instruction Code*/

  Remoter_Instruction_Num0			           = ((uint8_t)0),
	Remoter_Instruction_Num1			           = ((uint8_t)1),
	Remoter_Instruction_Num2			           = ((uint8_t)2),
	Remoter_Instruction_Num3			           = ((uint8_t)3),
	Remoter_Instruction_Num4			           = ((uint8_t)4),
	Remoter_Instruction_Num5			           = ((uint8_t)5),
	Remoter_Instruction_Num6			           = ((uint8_t)6),
	Remoter_Instruction_Num7			           = ((uint8_t)7),
	Remoter_Instruction_Num8			           = ((uint8_t)8),
	Remoter_Instruction_Num9			           = ((uint8_t)9),
	
	Remoter_Instruction_VolumeUp		         = ((uint8_t)16),
	Remoter_Instruction_VolumeDown	         = ((uint8_t)17),
	Remoter_Instruction_BrightnessUp	       = ((uint8_t)18),
	Remoter_Instruction_BrightnessDown	     = ((uint8_t)19),
	Remoter_Instruction_ColorSaturUp	       = ((uint8_t)20),
	Remoter_Instruction_ColorSaturDown	     = ((uint8_t)21),
	Remoter_Instruction_BassUp		           = ((uint8_t)22),
	Remoter_Instruction_BassDown		         = ((uint8_t)23),
	Remoter_Instruction_TrebleUp		         = ((uint8_t)24),
	Remoter_Instruction_TrebleDown	         = ((uint8_t)25),
	Remoter_Instruction_BalanceRigh	         = ((uint8_t)26),
	Remoter_Instruction_BalanceLeft	         = ((uint8_t)27),
	Remoter_Instruction_SystemSelect	       = ((uint8_t)63),
	Remoter_Instruction_DIMLocalDisplay      = ((uint8_t)71),
	
	Remoter_Instruction_LinearFCTNInc	       = ((uint8_t)77),
	Remoter_Instruction_LinearFCTNDec	       = ((uint8_t)78),
	Remoter_Instruction_StepUp		           = ((uint8_t)80),
	Remoter_Instruction_StepDown		         = ((uint8_t)81),
	Remoter_Instruction_StepLeft		         = ((uint8_t)85),
	Remoter_Instruction_StepRight		         = ((uint8_t)86),
	Remoter_Instruction_MenuOn		           = ((uint8_t)82),
	Remoter_Instruction_MenuOff		           = ((uint8_t)83),
	Remoter_Instruction_AVStatus		         = ((uint8_t)84),
	Remoter_Instruction_Acknowledge	         = ((uint8_t)87),
	Remoter_Instruction_StrobeOnOff	         = ((uint8_t)91),
	Remoter_Instruction_MultiStrobe	         = ((uint8_t)92),
	Remoter_Instruction_MainFrozen	         = ((uint8_t)93),
	Remoter_Instruction_3Div9Multiscan       = ((uint8_t)94),
	
	Remoter_Instruction_MultiPIP		         = ((uint8_t)96),
	Remoter_Instruction_PictureDNR	         = ((uint8_t)97),
	Remoter_Instruction_MainStored	         = ((uint8_t)98),
	Remoter_Instruction_RecallMainPict       = ((uint8_t)100),
	Remoter_Instruction_PIPOnOff		         = ((uint8_t)88),
	Remoter_Instruction_PIPShift		         = ((uint8_t)89),
	Remoter_Instruction_PIPMainSwap	         = ((uint8_t)90),
	Remoter_Instruction_PIPStrobe		         = ((uint8_t)99),
	Remoter_Instruction_PIPSelect		         = ((uint8_t)95),
	Remoter_Instruction_PIPFreeze		         = ((uint8_t)101),
	Remoter_Instruction_PIPStepUp		         = ((uint8_t)102),
	Remoter_Instruction_PIPStepDown	         = ((uint8_t)103),
	
	Remoter_Instruction_SubMode		           = ((uint8_t)118),
	Remoter_Instruction_OptionSubMode	       = ((uint8_t)119),
	
	Remoter_Instruction_Connect		           = ((uint8_t)123),
	Remoter_Instruction_Disconnect	         = ((uint8_t)124),

	/* Special TV1/TV2  Instruction Code*/
  Remoter_Instruction_TVDigits			       = ((uint8_t)10),
	Remoter_Instruction_TVFreq			         = ((uint8_t)11),
	Remoter_Instruction_TVStandBy		         = ((uint8_t)12),
	Remoter_Instruction_TVMuteOnOff		       = ((uint8_t)13),
	Remoter_Instruction_TVPREFERENCE	       = ((uint8_t)14),
	Remoter_Instruction_TVDISPLAY		         = ((uint8_t)15),
	
	Remoter_Instruction_TVContrastUp		     = ((uint8_t)28),
	Remoter_Instruction_TVContrastDown	     = ((uint8_t)29),
	Remoter_Instruction_TVSearchUp		       = ((uint8_t)30),
	Remoter_Instruction_TVTINTHUEDown	       = ((uint8_t)31),
	Remoter_Instruction_TVCHProgUp		       = ((uint8_t)32),
	Remoter_Instruction_TVCHProgDown		     = ((uint8_t)33),
	
	Remoter_Instruction_TVSpacialStereo      = ((uint8_t)36),
	Remoter_Instruction_TVStereoMono		     = ((uint8_t)37),
	Remoter_Instruction_TVSleepTimer		     = ((uint8_t)38),
	Remoter_Instruction_TVTINHUEUp		       = ((uint8_t)39),
	Remoter_Instruction_TVRFSwitch		       = ((uint8_t)40),
	Remoter_Instruction_TVStoreEXEVOTE	     = ((uint8_t)41),
	Remoter_Instruction_TVTime			         = ((uint8_t)42),
	Remoter_Instruction_TVScanFwdInc		     = ((uint8_t)43),
	Remoter_Instruction_TVDecrement		       = ((uint8_t)44),
	
	Remoter_Instruction_TVSECCONMenu		     = ((uint8_t)46),
	Remoter_Instruction_TVShowClock		       = ((uint8_t)47),
	Remoter_Instruction_TVPause			         = ((uint8_t)48),
	Remoter_Instruction_TVEraseCorrect	     = ((uint8_t)49),
	
	Remoter_Instruction_TVRewind			       = ((uint8_t)50),
	Remoter_Instruction_TVGoto			         = ((uint8_t)51),
	Remoter_Instruction_TVWind			         = ((uint8_t)52),
	Remoter_Instruction_TVPlay			         = ((uint8_t)53),
	Remoter_Instruction_TVStop			         = ((uint8_t)54),
	Remoter_Instruction_TVRecord			       = ((uint8_t)55),
	Remoter_Instruction_TVExternal1	         = ((uint8_t)56),
	Remoter_Instruction_TVExternal2		       = ((uint8_t)57),
	Remoter_Instruction_TVAdvance		         = ((uint8_t)59),
	Remoter_Instruction_TVTXTSubMode		     = ((uint8_t)60),
	Remoter_Instruction_TVSysStandBy		     = ((uint8_t)61),
	Remoter_Instruction_TVCRISPENER		       = ((uint8_t)62),
	
	Remoter_Instruction_TVSpeechMusic	       = ((uint8_t)70),
	Remoter_Instruction_TVSoundScroll	       = ((uint8_t)79),
	Remoter_Instruction_TVPIPSize		         = ((uint8_t)104),
	Remoter_Instruction_TVPicScroll		       = ((uint8_t)105),
	Remoter_Instruction_TVActOnOff		       = ((uint8_t)106),
	Remoter_Instruction_TVRed			           = ((uint8_t)107),
	Remoter_Instruction_TVGreen			         = ((uint8_t)108),
	Remoter_Instruction_TVYellow			       = ((uint8_t)109),
	Remoter_Instruction_TVCyan			         = ((uint8_t)110),
	Remoter_Instruction_TVIndexWhite		     = ((uint8_t)111),
	Remoter_Instruction_TVNext			         = ((uint8_t)112),
	Remoter_Instruction_TVPrevious		       = ((uint8_t)113),
	Remoter_Instruction_TVStoreOpenClose	   = ((uint8_t)122),
	Remoter_Instruction_TVMovieExpand	       = ((uint8_t)126),
	Remoter_Instruction_TVParentalAccess	   = ((uint8_t)127)
}Remoter_Instruction_TypeDef;

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


uint16_t Remoter_BinFrameGeneration(Remoter_Address_TypeDef Remoter_Address, 
                           Remoter_Instruction_TypeDef Remoter_Instruction, 
								           Remoter_Ctrl_TypeDef Remoter_Ctrl);

uint32_t Remoter_ManchesterConvert(uint16_t Remoter_BinaryFrameFormat);

void Remoter_SendFrame(uint32_t Remoter_ManchestarFrameFormat);

Remoter_Ctrl_TypeDef Remoter_CtrlBitReverse(Remoter_Ctrl_TypeDef Remoter_Ctrl);
/**
  * @}
  */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/	
