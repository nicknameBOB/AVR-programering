/*
 * Task1.c
 *
 * Created: 11.02.2017 23:37:53
 * Author : Petter
 */ 


/**
 * F_CPU tells the timer what the CPU's clock frequency is, such that the timer will count correctly.
 * Note that this DOES NOT set the clock speed, it just informs the timer.
 * If this is set wrong, the chip will work as normal, but software delays will be too long (if set too low) or too short (if set too high).
 * Example: set F_CPU to 2 MHz => "#define F_CPU 2000000UL". UL = unsigned long
 * F_CPU must be defined before including headers.
 */

#define F_CPU 3333333UL //The ATtiny817 operates at 20MHz with a default scaling factor of 6: 20/6 = 3.333333MHz

/**
 * System headers bellow
 */

#include <avr/io.h>
#include <util/delay.h>

/**
 * Define helpers for pin bit positions.
 * The LED0 on the ATtiny817 main board is connected to pin 4 on port B.
 * Check the datasheet to find out which pins on which ports the different LEDs and buttons are connected to.
 */

#define LED0 4 // LED0 is connected to pin 4 on port B

int main(void){
	/**
	 * We want to send signals to the LEDs, in order to turn the off and on.
	 * In the AVR world we have the following:
	 * PORTx.DIR: 1 is output, 0 is input
 	 * LED: 1 LED is off, 0 LED is on, this is called active-low
	 * Button: 1 button is open, 0 button is pressed, this is called active-low
	 *
	 * Remember bit set logic:
	 * Set to 1: FLAG |= ( 1 << BIT_POS ) - using 'or' so we only change the one we want and leave the others untouched
	 * Set to 0: FLAG &= ~( 1 << BIT_POS ) - same thing here but using 'and', find paper and a logic-table, and try it out if you want to know how it works
	 */

	PORTB.DIR |= (1 << LED0); // Set LED0 as output - Using "B" in PORTx.DIR since the LED is connected to port B on the microcontroller
	
	/*
	* The usual way to run microcontrollers is using a simple infinite loop
	*/

    while (1) 
    {
		PORTB.OUT ^= (1 << LED0); // Changes the state of LED0 by XOR-ing the last state. Check the XOR-table to find out how this works. 
		// Non-compressed: PORTB.OUT = PORTB.OUT ^ (1 << LED0);
		_delay_ms(500);
    }
}
