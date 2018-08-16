#include "TFC.h"
#include "mcg.h"



//-----------------------------------------------------------------
//  GPIO Setup
//-----------------------------------------------------------------
void InitGPIO()
{
	//enable Clocks to all ports - page 206, enable clock to Ports
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;

	
	//LCD Configuration - 
		
		PORTD_PCR3 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;  //ENABLE
		PORTD_PCR0 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;  //DB3
		PORTD_PCR2 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;  //DB1
		PORTD_PCR5 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;  //DB5
		GPIOD_PDDR |= 0x0000002D;
		
		PORTC_PCR9  = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;  //RS
		PORTC_PCR17 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //DB0
		PORTC_PCR16 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //DB2
		PORTC_PCR13 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //DB4
		PORTC_PCR12 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //DB6
		GPIOC_PDDR |= 0x00033200;
		
		PORTA_PCR16 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //RW
		PORTA_PCR13 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //DB7
		GPIOA_PDDR |= 0x00012000;
		
		InitDAC(); // For screen brightness (PTE30)
}


//-----------------------------------------------------------------
//  Clock Setup
//-----------------------------------------------------------------
void ClockSetup(){
	    
	    pll_init(8000000, LOW_POWER, CRYSTAL,4,24,MCGOUT); //Core Clock is now at 48MHz using the 8MHZ Crystal
		
	    //Clock Setup for the TPM requires a couple steps.
	    //1st,  set the clock mux
	    //See Page 124 of f the KL25 Sub-Family Reference Manual
	    SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;// We Want MCGPLLCLK/2=24MHz (See Page 196 of the KL25 Sub-Family Reference Manual
	    SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);
	    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); //We want the MCGPLLCLK/2 (See Page 196 of the KL25 Sub-Family Reference Manual
		//Enable the Clock to the TPM0 and PIT Modules
		//See Page 207 of f the KL25 Sub-Family Reference Manual
		SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK + SIM_SCGC6_TPM2_MASK;
	    // TPM_clock = 24MHz , PIT_clock = 48MHz
	    
}



//-----------------------------------------------------------------
//InitDAC for send LCD 
//-----------------------------------------------------------------
void InitDAC(){
//When the DAC is enabled and the buffer is not enabled, 
//the DAC module always converts the data in DAT0 to analog output voltage.
// pin PTE30 is by default (ALT0) configured as DAC0_OUT
	//VDDA reference voltage (Use this option for the best ADC operation).
	SIM_SCGC6 |= SIM_SCGC6_DAC0_MASK; //DAC0 Clock Gate Control
	DAC0_C0 |= DAC_C0_DACEN_MASK + DAC_C0_DACRFS_MASK + DAC_C0_DACTRGSEL_MASK + DAC_C0_LPEN_MASK; 
	DAC0_DAT0H = 4;
}


// LCD



//-----------------------------------------------------------------
//InitDAC for send LCD 
//-----------------------------------------------------------------

void initalizeLCD()
{ 
	RS_OFF;
	RW_OFF;
	E_OFF;
	delayFunc(15); //15ms
	toData(0x3f);
	lcd_strobe();
	delayFunc(5); //5ms
	toData(0x3f);
	lcd_strobe();
	delayFunc(delay200us); //99999 value is a code for 200us
	toData(0x3f);
	lcd_strobe();
	lcd_cmd(0x3c);
	lcd_cmd(0x0f);
	lcd_cmd(0x01);
	lcd_cmd(0x06);
	lcd_cmd(0x80);
	lcd_cmd(0x02);	
}


//-----------------------------------------------------------------
//lcd_strobe
//-----------------------------------------------------------------
void lcd_strobe(){
	E_ON;
	asm("nop");
	asm("nop");
	E_OFF;
}

//-----------------------------------------------------------------
//lcd_cmd
//-----------------------------------------------------------------
void lcd_cmd(char command){
	delayFunc(5); //5ms
	toData(command);
	lcd_strobe();
}


//-----------------------------------------------------------------
//toData
//-----------------------------------------------------------------
void toData (char c)
{   
	if((c & 0x01) != 0){
		    DB0_ON;}		
	    else{
		    DB0_OFF;}
	if((c & 0x02) != 0){
			DB1_ON;}
		else{
			DB1_OFF;}
	if((c & 0x04) != 0){
			DB2_ON;}
		else{
			DB2_OFF;}
	if((c & 0x08) != 0){
			DB3_ON;}
		else{
			DB3_OFF;}
	if((c & 0x10) != 0){
			DB4_ON;}
		else{
			DB4_OFF;}
	if((c & 0x20)!= 0){
			DB5_ON;}
		else{
			DB5_OFF;}
	if((c & 0x40) != 0){
			DB6_ON;}
		else{
			DB6_OFF;}
	if((c & 0x80) != 0){
			DB7_ON;}
		else{
			DB7_OFF;}
}


//-----------------------------------------------------------------
//lcd_data
//-----------------------------------------------------------------
void lcd_data(char c){
	delayFunc(5);
	toData(0);
	RS_ON;
	toData(c);
	lcd_strobe();
	RS_OFF;
}


lcd_put_string( char* string, int length ){ 
	lcd_cmd(LCDfirstLine);
	lcd_cmd(LCDclear);
volatile int LCDpointer=1; // pointer for where the pointer of the LCD is.
char temp;
volatile int i;
for(i=0; i<length ;i++){
	temp=string[i];
	if(temp==13){  // /r=13 in ASCII
		  if(LCDpointer>=17)//if we are in the second line
		  {
			  delayFunc(500);//one  0.5 seconde delay
			  lcd_cmd(LCDfirstLine);
			  lcd_cmd(LCDclear);
			  LCDpointer=1;
		  }
		  else //else- we are in the first line.
		  {
			  lcd_cmd(LCDsecondeLine); 
			  LCDpointer=17;
		  }
		  i++; ////if enter is press we get /r and then /n. thefore, we will skeep /n
}
    else{
      if(LCDpointer==17){
        lcd_cmd(LCDsecondeLine);
        }
      lcd_data(temp);
      LCDpointer++;
        if(LCDpointer==33){
         delayFunc(500);//one  0.5 seconde delay
         lcd_cmd(LCDfirstLine);
         lcd_cmd(LCDclear);
         LCDpointer=1;
         }
        }
}
}

//-----------------------------------------------------------------
//int32_t_float_to_bytes
//-----------------------------------------------------------------
void int32_t_float_to_bytes(float temp, uint8_t * dest)
{
  int32_t tempOut = temp * 10000000;
  dest[0] = (tempOut & 0xFF000000) >> 24;
  dest[1] = (tempOut & 0x00FF0000) >> 16;
  dest[2] = (tempOut & 0x0000FF00) >> 8;
  dest[3] = (tempOut & 0x000000FF);
}

//-----------------------------------------------------------------
//int16_t_float_to_bytes
//-----------------------------------------------------------------
void int16_t_float_to_bytes(float temp, uint8_t * dest)
{
  int32_t tempOut = temp * 50;
  dest[0] = (tempOut & 0xFF00) >> 8;
  dest[1] = (tempOut & 0x00FF);
}


void IntTostring (int x){
	char string [7]={0,0,0,0,0,0,0};
	volatile int i, temp;
	if(x<0)
		string[0]='-';
		else
			string[0]='0';
	x=abs(x);
	for(i=6; i>=1; i--)
	{
		string[i]=x%10+48;
		x=x/10;
	}
	sendData(string, 7);
}









