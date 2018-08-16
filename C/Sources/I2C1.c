#include "derivative.h" 
#include "I2C1.h"
#include "TFC.h"


/******************************************************************************
* MCU initialization function
******************************************************************************/ 

void MCU_Init1(void)
{
	
	//I2C1 module initialization
	SIM_SCGC4 |= SIM_SCGC4_I2C1_MASK;		// Turn on clock to I2C1 module 
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;		// Turn on clock to Port C module 
	PORTC_PCR1 = PORT_PCR_MUX(2);			// PTC1 pin is I2C1 SCL line //serial clock
	PORTC_PCR2 = PORT_PCR_MUX(2);			// PTC2 pin is I2C1 SDA line  serial address
	I2C1_F  = 0x14; 						// SDA hold time = 2.125us, SCL start hold time = 4.25us, SCL stop hold time = 5.125us *
	I2C1_C1 = I2C_C1_IICEN_MASK;    		// Enable I2C1 module 
	
}



// Wire.h read and write protocols
void writeByte(uint8_t u8SlaveAddress, uint8_t u8RegisterAddress, uint8_t u8Data)
{
	    I2C1_Start();	          
		I2C1_D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
		I2C1_Wait();

		I2C1_D = u8RegisterAddress;										/* Send register address */
		I2C1_Wait();

		I2C1_D = u8Data;												/* Send the data */
		I2C1_Wait();

		I2C1_Stop();

		delay(50);
}





uint8_t readByte(uint8_t u8SlaveAddress, uint8_t u8RegisterAddress)
{
    uint8_t result;     
    I2C1_Start();	          
  	I2C1_D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
  	I2C1_Wait();										

  	I2C1_D = u8RegisterAddress;										/* Send register address */
  	I2C1_Wait();

  	I2C1_RepeatedStart();
  	
  	I2C1_D = (u8SlaveAddress << 1) | 0x01;							/* Send I2C device address this time with W/R bit = 1 */ 
  	I2C1_Wait();	

  	I2C1_EnterRxMode();
  	I2C1_DisableAck();

  	result = I2C1_D;												
  	I2C1_Wait();
  	I2C1_Stop();  
  	result = I2C1_D;
  	delay(50);
  	return result;
  }



void readBytes(uint8_t u8SlaveAddress, uint8_t u8RegisterAddress, uint8_t n, uint8_t *r)
{
	char i;
	
	I2C1_Start();	          
	I2C1_D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
	I2C1_Wait();										

	I2C1_D = u8RegisterAddress;										/* Send register address */
	I2C1_Wait();

	I2C1_RepeatedStart();
		
	I2C1_D = (u8SlaveAddress << 1) | 0x01;							/* Send I2C device address this time with W/R bit = 1 */ 
	I2C1_Wait();	

	I2C1_EnterRxMode();
	I2C1_EnableAck();
	
	i = I2C1_D;
	I2C1_Wait();
	
	for(i=0; i<n-2; i++) 
	{
	    *r = I2C1_D;
	    r++;
	    I2C1_Wait();
	}
	
	I2C1_DisableAck();
	*r = I2C1_D;
	r++;
	I2C1_Wait();
	I2C1_Stop();
	*r = I2C1_D; 
	delay(50);		
}


void delay(int number){
	int cnt;
		for(cnt=0; cnt<number; cnt++)
		{
			asm("nop");
		};
}





















































