/*****************************|DAG 2|************************************/
/***********************|OPPGAVE 2 til 3|********************************/
/*Lag et program som f˚ar timer til ˚a stoppe ˚a telle n˚ar du trykker p˚a en knapp*/


/***************************|Define's|***********************************/
#define F_CPU 3333333UL									//3.33... MHz
/************************************************************************/

/***************************|Include|************************************/
#include <avr/io.h>										// includes AVR lib.
#include <util/delay.h>									// includes delay...
#include <avr/interrupt.h>								// includes interrupts
#include <stdbool.h>									// includes bool functionality
/************************************************************************/

/***************************|Define I\O|*********************************/
#define LED1 0											// port B,   PB0
#define LED2 1											// port B,	 PB1
#define LED3 4											// Port B,	 PB4, also LED0
//ALT:
// #define LED1 0b00000001 // Port B
// #define LED2 0b00000010 // Port B
// #define LED3 0b00010000 // Port B


#define SW0 	 5									    // port B,   PB5
#define BUTTON_1 5										// port A,   PA5
#define BUTTON_2 6										// port A,   PA6
#define BUTTON_3 7										// port A,   PA7
// ALT:
// #define button1 0b00100000 // Port A
// #define button2 0b01000000 // Port A
// #define button3 0b10000000 // Port A
/************************************************************************/

#define timer1 t1	// Creates timer1 with value from t1
#define timer2 t2	// Creates timer2 with value from t2
#define timer3 t3	// Creates timer3 with value from t3


/***************************| VARIABLES |********************************/
uint8_t buttonflag1 = false;	// Set flag to false from begineing(defult)
uint8_t buttonflag2 = false;	// Set flag to false from begineing(defult)
uint8_t buttonflag3 = false;	// Set flag to false from begineing(defult)
uint8_t blinkon = false;		// Set flag to false from begineing(defult)

uint16_t counterTop = 1300;		// Set countertop to 1300, ca. 0,1s

uint8_t t1 = 50;				//
uint8_t t2 = 150;				//
uint8_t t3 = 255;				//

bool SW1_pressed,SW2_pressed;	//Keeping track of button status
/************************************************************************/


/********************| LED INITIALIZE FUNCTION |*************************/
void init_LED()// LED INITIALIZE FUNCTION //{
	
	PORTB.DIR = LED1|LED2|LED3;		// LEDs as output
	PORTB.OUTTGL = LED1|LED2|LED3; 	// Start with LEDs off

	PORTB.PIN0CTRL |= 0b1000000;	// Invert LED to act like active HIGH
	PORTB.PIN1CTRL |= 0b1000000;	// Invert LED to act like active HIGH
	PORTB.PIN4CTRL |= 0b1000000;	// Invert LED to act like active HIGH
}
/************************************************************************/


/********************| BUTTON INITIALIZE FUNCTION |**********************/
void init_button()// BUTTON INITIALIZE FUNCTION //{
	
	PORTA.DIR &= ~(button1);		// Enables input button 1 on OLED1
	PORTA.DIR &= ~(button2);		// Enables input button 2 on OLED1
	PORTA.DIR &= ~(button3);		// Enables input button 3 on OLED1
	
	PORTA.PIN5CTRL |= 0b00001000;	// Enables pullup on button 1
	PORTA.PIN6CTRL |= 0b00001000;	// Enables pullup on button 2
	PORTA.PIN7CTRL |= 0b00001000;	// Enables pullup on button 3
}
/************************************************************************/


/*********************** |INIT BUTTON PRESS |****************************/
void button_press()// INIT BUTTON PRESS //{	
	if (!(PORTA.IN & (button1))){
		if(!SW1_pressed){
			TCA0.SINGLE.CMP0 = (((TCA0.SINGLE.CMP0 << 1) + 1) & (0x0fff)); //Shift in a 1, and cut off excess to 12 bit
			TCA0.SINGLE.CMP1 >>= 1;
			SW1_pressed = true;
		}
	}
	
	else{
		SW1_pressed = false;			//debaunce
	}
	
	if (!(PORTA_IN & (button2))){
		if(!SW2_pressed){
			TCA0.SINGLE.CMP1 = (((TCA0.SINGLE.CMP1 << 1) + 1) & (0x0fff)); //Shift in a 1, and cut off excess to 12 bit
			TCA0.SINGLE.CMP0 >>= 1;
			SW2_pressed = true;
		}
	}
	
	else{
		SW2_pressed = false;		//debaunce
	}
}
/************************************************************************/


/****************| TIMER OVERFLOW INITIALIZE FUNCTION |******************/
void init_ovf_timer()// TIMER OVERFLOW INITIALIZE FUNCTION //
{
	TCA0.SINGLE.CTRLA |= 0b00001101;	// Enables prescaler and set it to 256
	TCA0.SINGLE.INTCTRL |= 0b00000001;	// Enables timer interrupt on overflow
	TCA0.SINGLE.PER = counterTop;		// Set overflow TOP to value of counterTop
}
/************************************************************************/

/**************| TIMER COMPARE INITIALIZE FUNCTION |*********************/
void init_compare_timer()
{
	TCA0.SINGLE.CTRLA |= (TCA_SINGLE_ENABLE_bm); 			//Enable timer
	TCA0.SINGLE.CTRLB |= (0x05 << TCA_SINGLE_WGMODE0_bp); 	//Set mode to single slope
	
	TCA0.SINGLE.CTRLB |= (TCA_SINGLE_CMP0EN_bm); 			// Enable CMP0
	TCA0.SINGLE.CTRLB |=(TCA_SINGLE_CMP1EN_bm);	 			// Enable CMP1
	
	TCA0.SINGLE.CMP0 = 0x0000;								//Set all LOW (PB0)
 	TCA0.SINGLE.CMP1 = 0xffff;								//Set all HIGE (PB1)
}
/************************************************************************/


/****************************| MAIN LOOP |*******************************/
int main(void){
    init_LED();					//INITIALIZE LED
	init_ovf_timer();			//INITIALIZE OVERFLOW
	init_compare_timer();		//INITIALIZE TIMER
	init_button();				//BUTTON INITIALIZE FUNCTION
	
	sei();						//Enable global interrupts. Makes the interrupt work (set global interrupt enabler)
	
    while (1) 
    {
		button_press();			//INIT BUTTON PRESS
    }
}
/************************************************************************/


/**************************| INTERUPT OVERFLOW |*************************/
ISR(TCA0_OVF_vect)
{
	PORTB.OUTTGL = LED3;						// Toggle LED3
	
	TCA0.SINGLE.INTFLAGS |= 0b00000001;			// Clear the interrupt flag
}
/************************************************************************/

