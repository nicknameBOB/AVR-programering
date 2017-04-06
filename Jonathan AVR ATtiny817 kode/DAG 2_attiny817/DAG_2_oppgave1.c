/*****************************|DAG 2|************************************/
/***************************|OPPGAVE 1|**********************************/
/*I denne oppgaven skal du lage en timer som lett kan modifiseres til ˚a produsere avbrytelser
p˚a selvvalgte tidsintervaler*/

/***************************|Define's|***********************************/
#define F_CPU 3333333UL									//3.33... MHz
/************************************************************************/

/***************************|Include|************************************/
#include <avr/io.h>										// includes AVR lib.
#include <util/delay.h>									// includes delay...
#include <avr/interrupt.h>								// includes interrupts
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

/***************************|Main Prgram Loop|***************************/
int main(void){
	
	LEDINIT();											//initializer LED's
	LEDSTATUS();										// LED's are now Active high
	PULLUPEN();											//initializer pull-ups
	
/*---We will be using a timer overflow interrupt with timer A, TCA0 ----*/
	
														//(TCA_SINGLE_CLKSEL_DIV256_gc) We set the pre-scaler to clk=clk/256
	TCA0.SINGLE.CTRLA |= (TCA_SINGLE_CLKSEL_DIV256_gc);	//clock is set to clock/256
	
														//(TCA_SINGLE_ENABLE_bm) is used to enable timer
	TCA0.SINGLE.CTRLA |= (TCA_SINGLE_ENABLE_bm);		//Enable timer

														//Next we Enable timer interrupts on overflow
	TCA0.SINGLE.INTCTRL |= (TCA_SINGLE_OVF_bm);			//0x01 Overflow Interrupt bit mask.
	
	
	uint16_t counterTop = 0x4000;						//16384
	
	TCA0.SINGLE.PER = counterTop;						// Setts period equal to countertop
	
	sei();												//Enable global interrupts. Makes the interrupt work (set global interrupt enabler)
	
	while(1){/*Empty*/}
}
/************************************************************************/

/***************************|Interoupt|**********************************/
ISR(TCA0_OVF_vect){

	PORTB.OUTTGL |= (1 << LED3) | (1<<LED2) | (1<<LED1);	 // toggle LED3,LED2 and LED1
	
	TCA0.SINGLE.INTFLAGS |= (TCA_SINGLE_OVF_bm);		     //Clear the interrupt flag
}
/***********************************************************************/