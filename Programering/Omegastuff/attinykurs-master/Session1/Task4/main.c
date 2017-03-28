/*
 * Task4.c
 *
 * Created: 11.02.2017 23:56:53
 * Author : Petter
 */ 

/*
* This time you'll have to do all the setup and coding yourself. 
* You are going connect the "OLED1 Xplained Pro" extension card to the ATtiny817 kit, 
* and make the LEDs and buttons work on the extension card.
*/

/*
* Connect the OLED1 extension board to EXT1 on the ATtiny board.
* Set the proper ports and pins for the LEDs and the buttons on the OLED1, don't enable the LED0 and SW0 on the ATtiny
* Checkout the datasheet for the OLED1 extension card to see which pins the different LEDs/buttons are connected to
* Checkout the datasheet for the ATtiny to see which ports and pins on the microcontroller that corresponds to those pins from EXT1
* Remember: The ports (A/B/C) on the ATtiny can be different for the LEDs/buttons located on the same extension card (EXT1).
*/

// F_CPU
/* Define F_CPU here */

// System headers
/* Define system headers here */

// LEDs - OLED1 Xplained Pro
/* Define LED pins here */

// Buttons - OLED1 Xplained Pro
/* Define button pins here */

int main(void){
	
    /* 
	* Do the following:
	* Set the LEDs as output
	* Set buttons as input
	* Enable pull-ups on the buttons 
	*/
	
    while (1){
		/*
		* Check if the different buttons are pressed, and turn on the corresponding LED if it is pressed
		*/
    }
}

