/*****************************|DAG 2|************************************/
/***************************|OPPGAVE 2|**********************************/
/*Puls width modulation*/


/***************************|Define's|***********************************/
#define F_CPU 3333333UL									//3.33... MHz
/************************************************************************/


/***************************|Include|************************************/
#include <avr/io.h>										// includes AVR lib.
#include <util/delay.h>									// includes delay...
#include <avr/interrupt.h>								// includes interrupts
#include <stdbool.h>									// includes bool functionality
#include <util/delay.h>									// includes delay...
/************************************************************************/

/***************************|Define I\O|*********************************/
#define LED1 0											// port B,   PB0
#define LED2 1											// port B,	 PB1
#define LED3 4											// Port B,	 PB4, also LED0

#define SW0 	 5									    // port B,   PB5
#define BUTTON_1 5										// port A,   PA5
#define BUTTON_2 6										// port A,   PA6
#define BUTTON_3 7										// port A,   PA7
/************************************************************************/

/***************************|LED initierers|*****************************/
void LEDINIT(void){//initierer LED's
	
	PORTB.DIR |= (1 << LED3);							//Set LED0/LED3 as output
	PORTB.DIR |= (1 << LED1);							//Set LED1 as output
	PORTB.DIR |= (1 << LED2);							//Set LED2 as output
}		
/************************************************************************/

/***************************|LED inverted|*******************************/
void LEDSTATUS(void){//initierer LED's value(status)
	
	//Because the LEDs are active low, we invert the output
	PORTB.PIN0CTRL |= (1 << PORT_INVEN_bp);				// LED0/LED3 status modifier
	PORTB.PIN1CTRL |= (1 << PORT_INVEN_bp);				// LED1 status modifier
	PORTB.PIN4CTRL |= (1 << PORT_INVEN_bp);				// LED2 status modifier
}
/************************************************************************/

/***************************|Pullups|************************************/
void PULLUPEN(void){//initierer pullups
	
	PORTA.PIN5CTRL |= (1 << PORT_PULLUPEN_bp); 			//Enable pull-up on button BUTTON_1 (pin PA5)
	PORTA.PIN6CTRL |= (1 << PORT_PULLUPEN_bp); 			//Enable pull-up on button BUTTON_1 (pin PA6)
	PORTA.PIN7CTRL |= (1 << PORT_PULLUPEN_bp); 			//Enable pull-up on button BUTTON_1 (pin PA7)
}
/************************************************************************/

/************************************************************************/
bool BUTTON_1_pressed;									//Keeping track of button1 status
bool BUTTON_2_pressed;									//Keeping track of button2 status
/************************************************************************/


int main(void)
{
	LEDINIT();											//initializer LED's
	LEDSTATUS();										// LED's are now Active high
	PULLUPEN();											//initializer pull-ups
	
	
	//We will be using a timer overflow interupt with timer A
	
	TCA0.SINGLE.CTRLA |= (TCA_SINGLE_CLKSEL_DIV8_gc);							//Set clock prescaler div8
	TCA0.SINGLE.CTRLA |= (TCA_SINGLE_ENABLE_bm);								//Enable timer
	
	TCA0.SINGLE.CTRLB |= (0x05 << TCA_SINGLE_WGMODE0_bp);						//Set/enable mode to single slope
	
	TCA0.SINGLE.CTRLB |= (TCA_SINGLE_CMP0EN_bm) | (TCA_SINGLE_CMP1EN_bm);		//Set/enable PB0 and PB1
	
	TCA0.SINGLE.PER = 0x0fff; //We set our top to have a sufficiently high frequency (Top at 16 bit (0xffff) ~25Hz, 12 bit (0x0fff) ~400Hz)
	
	TCA0.SINGLE.CMP0 = 0x0000;						// We sett all fo (PB0)
	TCA0.SINGLE.CMP1 = 0x0fff;						// We sett all on (PB1)
	

	TCA0.SINGLE.INTCTRL |= (TCA_SINGLE_OVF_bm);		//Next we Enable timer interupts on overflow

	sei();											//Enable global interrupts
	
	
	while(1){/*infinet*/}
}

ISR(TCA0_OVF_vect){

/*--------------------------------------------------------------------------*/			
		if (!(PORTA.IN & (1 << BUTTON_2))){										//when butten2 is pressed do
			
				TCA0.SINGLE.CMP1 = (((TCA0.SINGLE.CMP1 << 1) + 1) & (0x0fff));  //Shift in a 1, and cut off excess to 12 bit	
				TCA0.SINGLE.CMP0 >>= 1;											//dims light on LED1
		}
		else{TCA0.SINGLE.INTFLAGS |= ( TCA_SINGLE_OVF_bm);}						//reset int-flag
/*--------------------------------------------------------------------------*/			
			if (!(PORTA.IN & (1 << BUTTON_1))){									//when butten1 is pressed do
				
				TCA0.SINGLE.CMP0 = (((TCA0.SINGLE.CMP0 << 1) + 1) & (0x0fff));  //Shift in a 1, and cut off excess to 12 bit
				TCA0.SINGLE.CMP1 >>= 1;											//dims light on LED2
				
			}
			else{TCA0.SINGLE.INTFLAGS |= ( TCA_SINGLE_OVF_bm);}					//reset int-flag
/*--------------------------------------------------------------------------*/									
}
