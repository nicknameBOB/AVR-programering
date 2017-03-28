/*
 * Task3-LF.c
 *
 * Created: 29.01.2017 23:43:39
 * Author : Petter
 */ 

#define F_CPU 3333333UL //3.33... MHz

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

//LED
#define LED0 4 //on port B

//Button
#define SW0 5 //on port B

int main(void)
{
	/*
	 * PORTx.DIR: set direction - 1 is output, 0 is input
	 * PORTx.OUT: set value of pins
	 * PORTx.IN: read value of pins
	 * LED: 1 LED is off, 0 LED is on
	 * SW: 1 Button is open, 0 button is pressed
	 * Set to 1: REG |= ( 1 << BIT_POS )
	 * Set to 0: REG &= ~( 1 << BIT_POS )
	 * This is called "read-modify-write". 
	 *
	 * The ATtiny817 also has special port registers that can do some of this for you.
	 * Read what PORTx.DIRSET, .DIRCLR and .DIRTGL do to the PORTx.DIR register, 
	 * And similarly what PORTx.OUTSET, .OUTCLR and .OUTTGL do to PORTx.OUT 
	 * (HINT: see chapter 16.5 of the datasheet)

	LF: They set clear and toggle bit in the register. eks: PORTB.DIRCLR = (1 << 5); to clear bit 5



	*/

	PORTB.DIRSET = (1 << LED0); // Set LED0 as output
	//Alt: PORTB.DIR |= (1 << LED0); 

	PORTB.DIRCLR = (1 << SW0); // Set SW0 as input (default)
	//Alt: PORTB.DIR &= ~(1 << SW0); 
	
	PORTB.PIN5CTRL |= (1 << 3); // Enable pull-up on button SW
	//eller bruk PORT_PULLUPEN_bp som er lik 3 (_bp = Bit Position)

	
	int buttonState = 0; // To hold the button pressed state
	
    while (1) 
    {
		if(!(PORTB.IN & (1 << SW0))){
			if(buttonState == 0){
				
				PORTB.OUTTGL = ( 1 << LED0);
				//Alt: PORTB.OUT ^= (1 << LED0);

				buttonState = 1;
			}
		}
		
		else{
			buttonState = 0;
		}
		_delay_ms(1); // For deboucing
    }
}
