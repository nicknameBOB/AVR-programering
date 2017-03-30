/***************************|Define's|***********************************/
#define F_CPU 3333333UL														//3.33... MHz
/************************************************************************/


/***************************|Include|************************************/
#include <avr/io.h>															// includes AVR lib.
#include <util/delay.h>														// includes delay...
/************************************************************************/


/***************************|Define's I/O|*******************************/
#define LED0 0																//On port B   PB0
#define LED1 1																//On port B   PB1
#define LED2 4																//On port B	  PB4

#define SW0 5																//On port B	  PB5
#define BUTTON_1 5															//On port A   PA5
#define BUTTON_2 6															//On port A   PA6
#define BUTTON_3 7															//On port A   PA7

/************************************************************************/


/*************************|Main loop|************************************/
int main(void)
{
	PORTB.DIR |= (1 << LED0);												//Set LED0 as output
	PORTB.DIR &= ~(1 << SW0);												//Set SW0 as input
	
	PORTA.DIR &= ~(1 << BUTTON_1);											//Set BUTTON_1 as input
	PORTA.DIR &= ~(1 << BUTTON_2);											//Set BUTTON_2 as input
	PORTA.DIR &= ~(1 << BUTTON_3);											//Set BUTTON_3 as input
	
	PORTB.PIN5CTRL |= (1 << PORT_PULLUPEN_bp);								//Enable pull-up on button SW0 (pin5)
	PORTA.PIN5CTRL |= (1 << PORT_PULLUPEN_bp);								//Enable pull-up on button BUTTON_1 (pin PA5)
	PORTA.PIN6CTRL |= (1 << PORT_PULLUPEN_bp);								//Enable pull-up on button BUTTON_2 (pin PA6)
	PORTA.PIN7CTRL |= (1 << PORT_PULLUPEN_bp);								//Enable pull-up on button BUTTON_3 (pin PA7)
    
	PORTB.DIR |= (1 << LED0);												//Set LED0 as output
	PORTB.DIR |= (1 << LED1);												//Set LED1 as output
	PORTB.DIR |= (1 << LED2);												//Set LED2 as output
	
	int buttonState = 0;													// Definerer buttonstate verdi
	
    while (1) {
		
	/*-------------------------------------------------------------------*/
		if(!(PORTB.IN & (1 << SW0))){										// If button is pressed (0 - LOW
			PORTB.OUT &= ~(1 << LED0);										// Sets output to 0, turns LED0 on
		}
			else{
				PORTB.OUT |= (1 << LED0);									// Sets output to 1, turns LED off
				}
	/*-------------------------------------------------------------------*/
		if(!(PORTA.IN & (1 << BUTTON_1))){									// If button is pressed (0 - LOW
			
			if(buttonState == 0){											// If button is pressed (0 - LOW
				
				PORTB.OUTTGL = ( 1 << LED1);								// Toggels the LED1 ,Alt: PORTB.OUT ^= (1 << LED0);

				buttonState = 1;
			}
		}
		
		else{
			buttonState = 0;
		}
			
	/*-------------------------------------------------------------------*/
		if(!(PORTA.IN & (1 << BUTTON_2))){									// If button is pressed (0 - LOW
			PORTB.OUT &= ~(1 << LED2);										// Sets output to 0, turns LED2 on
		}
			else{
			PORTB.OUT |= (1 << LED2);										// Sets output to 1, turns LED off
				}
	/*-------------------------------------------------------------------*/
		if(!(PORTA.IN & (1 << BUTTON_3))){									// If button is pressed (0 - LOW
			PORTB.OUT &= ~(1 << LED2);										// Sets output to 0, turns LED2 on
			PORTB.OUT &= ~(1 << LED1);										// Sets output to 0, turns LED1 on
			PORTB.OUT &= ~(1 << LED0);										// Sets output to 0, turns LED0 on
			
			_delay_ms(500);													//delay 500ms (purpose to make them blink)
			PORTB.OUT |= (1 << LED0);										// Sets output to 1, turns LED off
			PORTB.OUT |= (1 << LED1);										// Sets output to 1, turns LED off
			PORTB.OUT |= (1 << LED2);										// Sets output to 1, turns LED off
			_delay_ms(500);													//delay 500ms (purpose to make them blink)
		}
	/*-------------------------------------------------------------------*/	
    }
}/************************************************************************/
