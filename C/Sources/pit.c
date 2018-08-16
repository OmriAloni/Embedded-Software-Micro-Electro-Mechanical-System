
#include "pit.h"

#define LDVAL1sec        0x0016E3600 //bus clock is 24M Hz
#define LDVAL1msecChange 0x0005DC0 //was 12C0
//#define LDVAL1msecChange 0x00012C0 //was 12C0
#define LDVAL200us      0x000012C5

int flagForDelay=0; //while flag=0 there is still more time to the end of delay. if flag=1, PIT interrupt occurred which indicate the delay is over

/*******************************************
 * Initial PIT  clock to interrupt in constant period according to LDVAL value 
 *******************************************/
void pit0_init(int LDVAL){
	// Enable PIT clock
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
	// Turn on PIT
		PIT_MCR = 0;
		//PIT_MCR |= PIT_MCR_MDIS_MASK;  //Disable the PIT module
		
		
		PIT_LDVAL0 = LDVAL; // setup timer 0 to value of LDVAL;
		PIT_MCR |= PIT_MCR_FRZ_MASK; // stop the pit when in debug mode
		PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK; // Enable interrupt and enable timer
		
		enable_irq(INT_PIT-16); //  //Enable PIT IRQ on the NVIC
		set_irq_priority(INT_PIT-16,0);  // Interrupt priority = 0 = max
}


/*	Handles PIT interrupt if enabled
 * 
 * 	Starts conversion in ADC0 with single ended channel 8 (PTB0) as input
 * 
 * */
void PIT_IRQHandler(void)
{	
	// Clear interrupt
	PIT_TFLG0 = PIT_TFLG_TIF_MASK;
	//Disable module- it's used only for one delay each time 
	PIT_TCTRL0 &=  ~PIT_TCTRL_TEN_MASK;
	//PIT_MCR |= PIT_MCR_MDIS_MASK;  //Disable the PIT module
	flagForDelay=1;
	
}


/********************************************************************
delay- this function get numberOf1msec which indicate the number of 1msec delay is needed
*********************************************************************/
void delayFunc(int numberOf1msec){
	volatile int LDVALdealy=numberOf1msec*LDVAL1msecChange;
	if(numberOf1msec == delay200us){
		LDVALdealy=LDVAL200us;
	}
	pit0_init(LDVALdealy);
	while (flagForDelay==0){
		wait();
	}
	flagForDelay=0;
	
}
void delayForUpdatetime(){
	volatile int LDVALdealy=LDVAL1msecChange*178956;
	pit0_init(LDVALdealy);

}









