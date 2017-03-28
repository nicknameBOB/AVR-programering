/*
 * TIMER-LF.c
 *
 * Created: 29.01.2017 23:43:39
 * Author : Petter
 */ 

#define F_CPU 3333333UL


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED1 0 // port B, connected to WO0
#define LED2 1 // port B, connected to WO1
#define LED3 4 // Port B


int main(void)
{
	/*	In this exercise we will get LEDs to blink at even intervals using interrupts
		First set up the LEDs like in the previous exercise. You can either copy paste from the previous exercise or start fresh.
	*/

	PORTB.DIR = (1 << LED1) | (1 << LED2);
	PORTB.OUTTGL = (1 << LED1); //Only to start with LEDs off	
	
	//We will be using a timer overflow interupt with timer A
	//We set the prescaler to clk=clk/256
	TCA0.SINGLE.CTRLA |= (TCA_SINGLE_CLKSEL_DIV256_gc) | (TCA_SINGLE_ENABLE_bm);
	

	//Next we Enable timer interupts on overflow 
	TCA0.SINGLE.INTCTRL |= (TCA_SINGLE_OVF_bm);
	

	uint16_t counterTop = 0x4000;
	
	TCA0.SINGLE.PER = counterTop;
	
	//Enable global interrupts
	sei();
	
    while(1){
		//Do other things?
    }
}

ISR(TCA0_OVF_vect){

	PORTB.OUTTGL = (1 << LED1) | (1 << LED2);
	
	TCA0.SINGLE.INTFLAGS |= ( TCA_SINGLE_OVF_bm); //Clear the interupt flag
	
}