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
#define LED1_bm (1 << 0)								// Port B,   PB0
#define LED2_bm (1 << 1)								// Port B,	 PB1
#define LED3_bm (1 << 4)								// Port B,	 PB4, also LED0

#define SW0 	 5									    // port B,   PB5
#define button1_bm (1 << 5)								// port A,   PA5
#define button2_bm (1 << 6)								// port A,   PA6
#define button3_bm (1 << 7)								// port A,   PA7

#define timer1 t1										// Creates timer1 with value from t1
#define timer2 t2										// Creates timer2 with value from t2
#define timer3 t3										// Creates timer3 with value from t3

#define t1 1000											// gives t1 the value of 1000

#define button1_check (!(PORTA.IN & button1_bm))		// (!(PORTA.IN & button1_bm)) returns true if statment is coreckt
#define button2_check (!(PORTA.IN & button2_bm))		// (!(PORTA.IN & button2_bm)) returns true if statment is coreckt
#define button3_check (!(PORTA.IN & button3_bm))		// (!(PORTA.IN & button3_bm)) returns true if statment is coreckt
/************************************************************************/


/***************************| Variables |********************************/
bool button1_pressed;									// boolean value asigne to button1_pressed
uint16_t timer1;										// unasigned integer 16 bit
/************************************************************************/

/***************************| IO init |**********************************/
void IO_init(void){
	PORTB.DIR |= LED1_bm|LED2_bm|LED3_bm;
	PORTB.OUTTGL = LED1_bm|LED2_bm|LED3_bm;
	PORTA.DIR &= ~button1_bm & ~button2_bm & ~button3_bm;
	PORTA.PIN5CTRL |= PORT_PULLUPEN_bm; 
	PORTA.PIN6CTRL |= PORT_PULLUPEN_bm;
	PORTA.PIN7CTRL |= PORT_PULLUPEN_bm;
}
/************************************************************************/



/***************************| Timer init |*******************************/
void timer_init(void){
	TCA0.SINGLE.CTRLA |= (TCA_SINGLE_CLKSEL_DIV256_gc|(1 <<TCA_SINGLE_ENABLE_bp));
	TCA0.SINGLE.INTCTRL |= (1 << TCA_SINGLE_OVF_bp);
	TCA0.SINGLE.PER = 13;
	
	sei();
	timer1 = t1;
}
/************************************************************************/


/***************************| Timer check |******************************/
void timer_check(void){
	if(timer1 == 0)
	{
		PORTB.OUT ^= LED1_bm;				// togels LED1
		timer1 = t1;						// resetts timer1
	}
}
/************************************************************************/


/****************************| Button press |****************************/
void button_press(void){
	if (button1_check)				// if (!(PORTA.IN & button1_bm))
	{
		button1_pressed = true;		// sett button1_pressed flag true(1), initiates the while
		while(button1_pressed)		// While button1_pressed flag true, 
		{
			TCA0.SINGLE.INTFLAGS &= ~(1 << TCA_SINGLE_OVF_bp);
			if(button1_check)
			{
				button1_pressed = false;			//debounsce
			}
		}
	}
}
/************************************************************************/

/****************************| MAIN |************************************/
int main(void){
    IO_init();									//
	timer_init();								//
	

    while (1){
		timer_check();
		button_press();
    }
}
/************************************************************************/



/***************************| INTERUPT |**********************************/
ISR(TCA0_OVF_vect){
	if(timer1 > 0)
	{
		timer1 = timer1-1;
	}

	TCA0.SINGLE.INTFLAGS |= (1 << TCA_SINGLE_OVF_bp);
}
/************************************************************************/