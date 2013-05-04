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
#include "myMath.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* to avoid collusion, this value can be updated for thin adjust*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public variables ---------------------------------------------------------*/

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

  
void Lshift(uint32_t *p,uint8_t len,uint8_t w)//左移w位，前面补0   
{  
     uint32_t *n=(uint32_t*)p;  
     int i,j=1,k=w;  
     if(w>len<<5)  
       w%=len<<5;  
     else if(w>=32)  
     {  
              j=w/32;k=w&0x1f;  
              for(i=len-1;i>=j;i--)  
              n[i]=n[i-j];  
              for(i=0;i<j;i++)  
              n[i]=0;  
     }  
     if(k>0)  
     {  
              for(i=len-1;i>=j;i--)  
              n[i]=n[i]>>k|n[i-1]<<(32-k);  
              n[i]>>=k;  
     }  
}  
  
void Rshift(uint32_t *p,int len,int w)//右移w位，后面补0   
{  
     uint32_t *n=(uint32_t*)p;  
     int i,j=1,k=w;  
     if(w>len<<5)  
       w%=len<<5;  
     else if(w>=32)  
     {  
              j=w/32;k=w&0x1f;  
              for(i=0;i<len-j;i++)  
              n[i]=n[i+j];  
              for(;i<=len;i++)  
              n[i]=0;  
     }  
     if(k>0)  
     {  
              for(i=0;i<len-j;i++)  
              n[i]=n[i]<<k|n[i+1]>>(32-k);  
              n[i]<<=k;  
     }  
}  


/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
