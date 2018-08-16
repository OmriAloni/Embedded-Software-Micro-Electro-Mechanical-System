#include <stdint.h>
#include "TFC.h"

#ifndef BOARDSUPPORT_H_
#define BOARDSUPPORT_H_


#define TFC_HBRIDGE_EN_LOC			(uint32_t)(1<<21)
#define TFC_HBRIDGE_FAULT_LOC     	(uint32_t)(1<<20)

#define TFC_HBRIDGE_ENABLE			GPIOE_PSOR = TFC_HBRIDGE_EN_LOC	
#define TFC_HBRIDGE_DISABLE			GPIOE_PCOR = TFC_HBRIDGE_EN_LOC	

#define TFC_DIP_SWITCH0_LOC			((uint32_t)(1<<2))
#define TFC_DIP_SWITCH1_LOC			((uint32_t)(1<<3))
#define TFC_DIP_SWITCH2_LOC			((uint32_t)(1<<4))
#define TFC_DIP_SWITCH3_LOC			((uint32_t)(1<<5))

#define TFC_PUSH_BUTT0N0_LOC		((uint32_t)(1<<13))
#define TFC_PUSH_BUTT0N1_LOC		((uint32_t)(1<<17))	

#define TFC_BAT_LED0_LOC			((uint32_t)(1<<8))
#define TFC_BAT_LED1_LOC			((uint32_t)(1<<9))
#define TFC_BAT_LED2_LOC			((uint32_t)(1<<10))
#define TFC_BAT_LED3_LOC			((uint32_t)(1<<11))
//-------------  RGB LEDs ---------------------------------------------
#define RED_LED_LOC	         		((uint32_t)(1<<18))
#define GREEN_LED_LOC	         	((uint32_t)(1<<19))
#define BLUE_LED_LOC	         	((uint32_t)(1<<1))
#define PORT_LOC(x)        	        ((uint32_t)(1<<x))

#define RED_LED_OFF          		GPIOB_PSOR |= RED_LED_LOC
#define GREEN_LED_OFF	         	GPIOB_PSOR |= GREEN_LED_LOC
#define BLUE_LED_OFF	            GPIOD_PSOR |= BLUE_LED_LOC
#define RGB_LED_OFF	                RED_LED_OFF,GREEN_LED_OFF,BLUE_LED_OFF

#define RED_LED_TOGGLE          	GPIOB_PTOR |= RED_LED_LOC
#define GREEN_LED_TOGGLE	        GPIOB_PTOR |= GREEN_LED_LOC
#define BLUE_LED_TOGGLE	            GPIOD_PTOR |= BLUE_LED_LOC
#define RGB_LED_TOGGLE	            RED_LED_TOGGLE,GREEN_LED_TOGGLE,BLUE_LED_TOGGLE

#define RED_LED_ON          		GPIOB_PCOR |= RED_LED_LOC
#define GREEN_LED_ON	         	GPIOB_PCOR |= GREEN_LED_LOC
#define BLUE_LED_ON	                GPIOD_PCOR |= BLUE_LED_LOC
#define RGB_LED_ON	                RED_LED_ON,GREEN_LED_ON,BLUE_LED_ON

#define SW_POS 0x80  //PTD7
//---------------------------------------------------------------------
#define TFC_BAT_LED0_ON				GPIOB_PSOR = TFC_BAT_LED0_LOC
#define TFC_BAT_LED1_ON				GPIOB_PSOR = TFC_BAT_LED1_LOC
#define TFC_BAT_LED2_ON				GPIOB_PSOR = TFC_BAT_LED2_LOC
#define TFC_BAT_LED3_ON				GPIOB_PSOR = TFC_BAT_LED3_LOC

#define TFC_BAT_LED0_OFF			GPIOB_PCOR = TFC_BAT_LED0_LOC
#define TFC_BAT_LED1_OFF			GPIOB_PCOR = TFC_BAT_LED1_LOC
#define TFC_BAT_LED2_OFF			GPIOB_PCOR = TFC_BAT_LED2_LOC
#define TFC_BAT_LED3_OFF			GPIOB_PCOR = TFC_BAT_LED3_LOC

#define TFC_BAT_LED0_TOGGLE			GPIOB_PTOR = TFC_BAT_LED0_LOC
#define TFC_BAT_LED1_TOGGLE			GPIOB_PTOR = TFC_BAT_LED1_LOC
#define TFC_BAT_LED2_TOGGLE			GPIOB_PTOR = TFC_BAT_LED2_LOC
#define TFC_BAT_LED3_TOGGLE			GPIOB_PTOR = TFC_BAT_LED3_LOC

#define TFC_PUSH_BUTTON_0_PRESSED	((GPIOC_PDIR&TFC_PUSH_BUTT0N0_LOC)>0)
#define TFC_PUSH_BUTTON_1_PRESSED	((GPIOC_PDIR&TFC_PUSH_BUTT0N1_LOC)>0)

//LCD
#define E_ON	  GPIOD_PSOR = ((uint32_t)(1<<3))
#define RW_ON	  GPIOA_PSOR = ((uint32_t)(1<<16))
#define RS_ON	  GPIOC_PSOR = ((uint32_t)(1<<9))
#define DB0_ON	  GPIOC_PSOR = ((uint32_t)(1<<17))
#define DB1_ON	  GPIOD_PSOR = ((uint32_t)(1<<2))
#define DB2_ON	  GPIOC_PSOR = ((uint32_t)(1<<16))
#define DB3_ON	  GPIOD_PSOR = ((uint32_t)(1))
#define DB4_ON	  GPIOC_PSOR = ((uint32_t)(1<<13))
#define DB5_ON	  GPIOD_PSOR = ((uint32_t)(1<<5))
#define DB6_ON	  GPIOC_PSOR = ((uint32_t)(1<<12))
#define DB7_ON	  GPIOA_PSOR = ((uint32_t)(1<<13))

#define E_OFF	  GPIOD_PCOR = ((uint32_t)(1<<3))
#define RW_OFF	  GPIOA_PCOR = ((uint32_t)(1<<16))
#define RS_OFF	  GPIOC_PCOR = ((uint32_t)(1<<9))
#define DB0_OFF	  GPIOC_PCOR = ((uint32_t)(1<<17))
#define DB1_OFF	  GPIOD_PCOR = ((uint32_t)(1<<2))
#define DB2_OFF	  GPIOC_PCOR = ((uint32_t)(1<<16))
#define DB3_OFF	  GPIOD_PCOR = ((uint32_t)(1))
#define DB4_OFF	  GPIOC_PCOR = ((uint32_t)(1<<13))
#define DB5_OFF	  GPIOD_PCOR = ((uint32_t)(1<<5))
#define DB6_OFF	  GPIOC_PCOR = ((uint32_t)(1<<12))
#define DB7_OFF	  GPIOA_PCOR = ((uint32_t)(1<<13))

#define LCDfirstLine 0x02
#define LCDsecondeLine 0xC0
#define LCDclear 0x01

//End


void  InitGPIO();
void ClockSetup();
void InitDAC();
void initalizeLCD();
void lcd_strobe();
void lcd_cmd(char command);
void toData (char c);
void lcd_data(char c);
lcd_put_string( char* string, int length );
void int32_t_float_to_bytes(float temp, uint8_t * dest);
void int16_t_float_to_bytes(float temp, uint8_t * dest);	
void IntTostring (int x);




#endif /* BOARDSUPPORT_H_ */
