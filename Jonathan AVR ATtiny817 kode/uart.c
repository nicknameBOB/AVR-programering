

/***************************|Define's|************************************/
#define F_CPU 3333333UL
#define BAUD_9600 ((4UL*F_CPU)/9600)
/************************************************************************/


/***************************|Include|************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
/************************************************************************/


/*****************************|uart|*************************************/
void uart_init(unsigned long baud){
	
	//From chapter 24.3 in data sheet
	PORTB.OUTSET = (1 << PIN2_bp); 
	PORTB.DIRSET = (1 << PIN2_bp);											//Setting up TX pin as output
	USART0.BAUDH = (baud >> 8); 											//Shift register right by 8 bits
	USART0.BAUDL = baud; 													//Set baud rate
	
	//USART.CTRLC CMODE bits default to async, 1 stop bit, 8 bit character size
	USART0.CTRLB |= (1 << USART_RXEN_bp) | (1 << USART_TXEN_bp);			//Enable RX and TX
	USART0.CTRLA |= (1 << USART_RXCIE_bp);									//Enable interrupts on incoming data
}
/***********************************************************************/



/*************************|function to transmit data|******************/
void uart_transmit(unsigned char data){
	while (!(USART0.STATUS & (1 << USART_DREIF_bp))){						//wait for previous transmit to finish
	};
	USART0.TXDATAH = 0x00; //Is needed!
	USART0.TXDATAL = data;
}
/*********************************************************************/


/**********************************|main|*****************************/
int main(void){
	uart_init(BAUD_9600);												//start uart with baud rate of 9600
	sei();																//Important for anything here to work
	
    while (1){															//Do nothing, interrupts handle everything
    }
}
/********************************************************************/



/*********|Interrupt service routine for the receiver|***************/
ISR(USART0_RXC_vect){
	
	uint8_t data = USART0_RXDATAL;										//Do things with data:
	uart_transmit(data + 1);											//Example: Shift all characters by one step A -> B, B -> C etc.
}
/*******************************************************************/