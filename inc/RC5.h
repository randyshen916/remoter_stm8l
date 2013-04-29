/**
  ******************************************************************************
  * @file rc5.h
  * @brief This file contains all functions prototype and macros for the RC5 driver.
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

/** @addtogroup RC5_Exported_Types
  * @{
  */
	
/**
  * @brief Definition of the RC5 devices adresses.
  */	

typedef enum
{
  RC5_Address_TV1					      = ((uint8_t)0),
	RC5_Address_TV2					      = ((uint8_t)1),
	RC5_Address_VideoText			    = ((uint8_t)2),
	RC5_Address_ExtensionTV			  = ((uint8_t)3),
	RC5_Address_ExtensionVCR		  = ((uint8_t)9),
	RC5_Address_LaserVideoPlayer	= ((uint8_t)4),
	RC5_Address_VCR1				      = ((uint8_t)5),
	RC5_Address_VCR2				      = ((uint8_t)6),
	RC5_Address_Sat1				      = ((uint8_t)8),
	RC5_Address_Sat2				      = ((uint8_t)10),
	RC5_Address_CD					      = ((uint8_t)20),
	RC5_Address_CDVideo				    = ((uint8_t)12),
	RC5_Address_CDPhoto				    = ((uint8_t)14),
	RC5_Address_CDRW				      = ((uint8_t)26),
	RC5_Address_PreampliAudio1		= ((uint8_t)16),
	RC5_Address_PreampliAudio2		= ((uint8_t)19),
	RC5_Address_Tuner				      = ((uint8_t)17),
	RC5_Address_AnalogMagneto   	= ((uint8_t)18),
	RC5_Address_DDCMagneto			  = ((uint8_t)23),
	RC5_Address_RackAudio			    = ((uint8_t)21),
	RC5_Address_AudioSatReceiver	= ((uint8_t)22),
		
	RC5_Address_Reserved00		    = ((uint8_t)7),
	RC5_Address_Reserved01		    = ((uint8_t)11),
	RC5_Address_Reserved02		    = ((uint8_t)13),
	RC5_Address_Reserved03		    = ((uint8_t)15),
	RC5_Address_Reserved04		    = ((uint8_t)24),
	RC5_Address_Reserved05		    = ((uint8_t)25),
	RC5_Address_Reserved06		    = ((uint8_t)27),
	RC5_Address_Reserved07		    = ((uint8_t)28),
	RC5_Address_Reserved08		    = ((uint8_t)29),
	RC5_Address_Reserved09		    = ((uint8_t)30),
	RC5_Address_Reserved10		  	= ((uint8_t)31)
}RC5_Address_TypeDef;

/**
  * @brief Definition of the RC5 devices instructions.
  */	
typedef enum
{
/* Device general Instruction Code*/

  RC5_Instruction_Num0			           = ((uint8_t)0),
	RC5_Instruction_Num1			           = ((uint8_t)1),
	RC5_Instruction_Num2			           = ((uint8_t)2),
	RC5_Instruction_Num3			           = ((uint8_t)3),
	RC5_Instruction_Num4			           = ((uint8_t)4),
	RC5_Instruction_Num5			           = ((uint8_t)5),
	RC5_Instruction_Num6			           = ((uint8_t)6),
	RC5_Instruction_Num7			           = ((uint8_t)7),
	RC5_Instruction_Num8			           = ((uint8_t)8),
	RC5_Instruction_Num9			           = ((uint8_t)9),
	
	RC5_Instruction_VolumeUp		         = ((uint8_t)16),
	RC5_Instruction_VolumeDown	         = ((uint8_t)17),
	RC5_Instruction_BrightnessUp	       = ((uint8_t)18),
	RC5_Instruction_BrightnessDown	     = ((uint8_t)19),
	RC5_Instruction_ColorSaturUp	       = ((uint8_t)20),
	RC5_Instruction_ColorSaturDown	     = ((uint8_t)21),
	RC5_Instruction_BassUp		           = ((uint8_t)22),
	RC5_Instruction_BassDown		         = ((uint8_t)23),
	RC5_Instruction_TrebleUp		         = ((uint8_t)24),
	RC5_Instruction_TrebleDown	         = ((uint8_t)25),
	RC5_Instruction_BalanceRigh	         = ((uint8_t)26),
	RC5_Instruction_BalanceLeft	         = ((uint8_t)27),
	RC5_Instruction_SystemSelect	       = ((uint8_t)63),
	RC5_Instruction_DIMLocalDisplay      = ((uint8_t)71),
	
	RC5_Instruction_LinearFCTNInc	       = ((uint8_t)77),
	RC5_Instruction_LinearFCTNDec	       = ((uint8_t)78),
	RC5_Instruction_StepUp		           = ((uint8_t)80),
	RC5_Instruction_StepDown		         = ((uint8_t)81),
	RC5_Instruction_StepLeft		         = ((uint8_t)85),
	RC5_Instruction_StepRight		         = ((uint8_t)86),
	RC5_Instruction_MenuOn		           = ((uint8_t)82),
	RC5_Instruction_MenuOff		           = ((uint8_t)83),
	RC5_Instruction_AVStatus		         = ((uint8_t)84),
	RC5_Instruction_Acknowledge	         = ((uint8_t)87),
	RC5_Instruction_StrobeOnOff	         = ((uint8_t)91),
	RC5_Instruction_MultiStrobe	         = ((uint8_t)92),
	RC5_Instruction_MainFrozen	         = ((uint8_t)93),
	RC5_Instruction_3Div9Multiscan       = ((uint8_t)94),
	
	RC5_Instruction_MultiPIP		         = ((uint8_t)96),
	RC5_Instruction_PictureDNR	         = ((uint8_t)97),
	RC5_Instruction_MainStored	         = ((uint8_t)98),
	RC5_Instruction_RecallMainPict       = ((uint8_t)100),
	RC5_Instruction_PIPOnOff		         = ((uint8_t)88),
	RC5_Instruction_PIPShift		         = ((uint8_t)89),
	RC5_Instruction_PIPMainSwap	         = ((uint8_t)90),
	RC5_Instruction_PIPStrobe		         = ((uint8_t)99),
	RC5_Instruction_PIPSelect		         = ((uint8_t)95),
	RC5_Instruction_PIPFreeze		         = ((uint8_t)101),
	RC5_Instruction_PIPStepUp		         = ((uint8_t)102),
	RC5_Instruction_PIPStepDown	         = ((uint8_t)103),
	
	RC5_Instruction_SubMode		           = ((uint8_t)118),
	RC5_Instruction_OptionSubMode	       = ((uint8_t)119),
	
	RC5_Instruction_Connect		           = ((uint8_t)123),
	RC5_Instruction_Disconnect	         = ((uint8_t)124),

	/* Special TV1/TV2  Instruction Code*/
  RC5_Instruction_TVDigits			       = ((uint8_t)10),
	RC5_Instruction_TVFreq			         = ((uint8_t)11),
	RC5_Instruction_TVStandBy		         = ((uint8_t)12),
	RC5_Instruction_TVMuteOnOff		       = ((uint8_t)13),
	RC5_Instruction_TVPREFERENCE	       = ((uint8_t)14),
	RC5_Instruction_TVDISPLAY		         = ((uint8_t)15),
	
	RC5_Instruction_TVContrastUp		     = ((uint8_t)28),
	RC5_Instruction_TVContrastDown	     = ((uint8_t)29),
	RC5_Instruction_TVSearchUp		       = ((uint8_t)30),
	RC5_Instruction_TVTINTHUEDown	       = ((uint8_t)31),
	RC5_Instruction_TVCHProgUp		       = ((uint8_t)32),
	RC5_Instruction_TVCHProgDown		     = ((uint8_t)33),
	
	RC5_Instruction_TVSpacialStereo      = ((uint8_t)36),
	RC5_Instruction_TVStereoMono		     = ((uint8_t)37),
	RC5_Instruction_TVSleepTimer		     = ((uint8_t)38),
	RC5_Instruction_TVTINHUEUp		       = ((uint8_t)39),
	RC5_Instruction_TVRFSwitch		       = ((uint8_t)40),
	RC5_Instruction_TVStoreEXEVOTE	     = ((uint8_t)41),
	RC5_Instruction_TVTime			         = ((uint8_t)42),
	RC5_Instruction_TVScanFwdInc		     = ((uint8_t)43),
	RC5_Instruction_TVDecrement		       = ((uint8_t)44),
	
	RC5_Instruction_TVSECCONMenu		     = ((uint8_t)46),
	RC5_Instruction_TVShowClock		       = ((uint8_t)47),
	RC5_Instruction_TVPause			         = ((uint8_t)48),
	RC5_Instruction_TVEraseCorrect	     = ((uint8_t)49),
	
	RC5_Instruction_TVRewind			       = ((uint8_t)50),
	RC5_Instruction_TVGoto			         = ((uint8_t)51),
	RC5_Instruction_TVWind			         = ((uint8_t)52),
	RC5_Instruction_TVPlay			         = ((uint8_t)53),
	RC5_Instruction_TVStop			         = ((uint8_t)54),
	RC5_Instruction_TVRecord			       = ((uint8_t)55),
	RC5_Instruction_TVExternal1	         = ((uint8_t)56),
	RC5_Instruction_TVExternal2		       = ((uint8_t)57),
	RC5_Instruction_TVAdvance		         = ((uint8_t)59),
	RC5_Instruction_TVTXTSubMode		     = ((uint8_t)60),
	RC5_Instruction_TVSysStandBy		     = ((uint8_t)61),
	RC5_Instruction_TVCRISPENER		       = ((uint8_t)62),
	
	RC5_Instruction_TVSpeechMusic	       = ((uint8_t)70),
	RC5_Instruction_TVSoundScroll	       = ((uint8_t)79),
	RC5_Instruction_TVPIPSize		         = ((uint8_t)104),
	RC5_Instruction_TVPicScroll		       = ((uint8_t)105),
	RC5_Instruction_TVActOnOff		       = ((uint8_t)106),
	RC5_Instruction_TVRed			           = ((uint8_t)107),
	RC5_Instruction_TVGreen			         = ((uint8_t)108),
	RC5_Instruction_TVYellow			       = ((uint8_t)109),
	RC5_Instruction_TVCyan			         = ((uint8_t)110),
	RC5_Instruction_TVIndexWhite		     = ((uint8_t)111),
	RC5_Instruction_TVNext			         = ((uint8_t)112),
	RC5_Instruction_TVPrevious		       = ((uint8_t)113),
	RC5_Instruction_TVStoreOpenClose	   = ((uint8_t)122),
	RC5_Instruction_TVMovieExpand	       = ((uint8_t)126),
	RC5_Instruction_TVParentalAccess	   = ((uint8_t)127)
}RC5_Instruction_TypeDef;

/**
  * @brief Definition of the RC5 Control bit value.
  */	

typedef enum
{
  RC5_Ctrl_Reset			= ((uint16_t)0),
	RC5_Ctrl_Set		  	= ((uint16_t)0x0800)
}RC5_Ctrl_TypeDef;



/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
/** @addtogroup RC5_Exported_Functions
  * @{
  */


uint16_t RC5_BinFrameGeneration(RC5_Address_TypeDef RC5_Address, 
                           RC5_Instruction_TypeDef RC5_Instruction, 
								           RC5_Ctrl_TypeDef RC5_Ctrl);

uint32_t RC5_ManchesterConvert(uint16_t RC5_BinaryFrameFormat);

void RC5_SendFrame(uint32_t RC5_ManchestarFrameFormat);

RC5_Ctrl_TypeDef RC5_CtrlBitReverse(RC5_Ctrl_TypeDef RC5_Ctrl);
/**
  * @}
  */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/	
