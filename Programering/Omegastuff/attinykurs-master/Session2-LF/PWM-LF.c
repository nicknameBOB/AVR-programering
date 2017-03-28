/*
 * PWM-LF.c
 *
 * Created: 29.01.2017 23:43:39
 * Author : Petter
 */ 

#define F_CPU 3333333UL


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define LED1 0 // port B, connected to WO0
#define LED2 1 // port B, connected to WO1
#define LED3 4 // Port B
#define SW1 5 // Port A
#define SW2 6 // Port A
#define SW3 7 // Port A


bool SW1_pressed,SW2_pressed; //Keeping track of button status

int main(void)
{
	//Set LED pins as output
	PORTB.DIRSET = (1 << LED1) | (1 << LED2) | (1 << LED3);
	
	//Because the LEDs are active low, we invert the output
	PORTB.PIN0CTRL |= (1 << PORT_INVEN_bp);
	PORTB.PIN1CTRL |= (1 << PORT_INVEN_bp);
	PORTB.PIN4CTRL |= (1 << PORT_INVEN_bp);
	
	//Pullups
	PORTA.PIN5CTRL |= (1 << PORT_PULLUPEN_bp);
	PORTA.PIN6CTRL |= (1 << PORT_PULLUPEN_bp);
	PORTA.PIN7CTRL |= (1 << PORT_PULLUPEN_bp);	
	
	//Set clock prescaler div256
	TCA0.SINGLE.CTRLA |= (TCA_SINGLE_ENABLE_bm); //Enable timer
	TCA0.SINGLE.CTRLB |= (0x05 << TCA_SINGLE_WGMODE0_bp); //Set mode to single slope
	
	TCA0.SINGLE.CTRLB |= (TCA_SINGLE_CMP0EN_bm) | (TCA_SINGLE_CMP1EN_bm);
	
	TCA0.SINGLE.PER = 0x0fff; //We set our top to have a sufficiently high frequency (Top at 16 bit (0xffff) ~25Hz, 12 bit (0x0fff) ~400Hz)
	TCA0.SINGLE.CMP0 = 0x0000;
	TCA0.SINGLE.CMP1 = 0x0fff;
	
	
    while(1){
		
		if (!(PORTA.IN & (1 << SW1))){
			if(!SW1_pressed){
				TCA0.SINGLE.CMP0 = (((TCA0.SINGLE.CMP0 << 1) + 1) & (0x0fff)); //Shift in a 1, and cut off excess to 12 bit
				TCA0.SINGLE.CMP1 >>= 1;
				SW1_pressed = true;
			}
		}
		
		else{
			SW1_pressed = false;
		}
		
		if (!(PORTA_IN & (1 << SW2))){
			if(!SW2_pressed){
				TCA0.SINGLE.CMP1 = (((TCA0.SINGLE.CMP1 << 1) + 1) & (0x0fff)); //Shift in a 1, and cut off excess to 12 bit
				TCA0.SINGLE.CMP0 >>= 1;
				SW2_pressed = true;
			}
		}
		
		else{
			SW2_pressed = false;
		}
		
    }
}

