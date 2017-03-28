/*
 * Initial_test.c
 *
 * Created: 29.01.2017 23:43:39
 * Author : Petter
 */ 

#define F_CPU 3333333UL


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>


void uart_init(int baud){
	int baudRate = ((4UL*F_CPU)/baud);	//CLK_PER = CLK_CPU, see tabell 24-2
	
	//From chapter 24.3 in datasheet
	PORTB_OUT |= (1 << 2); 
	PORTB_DIR |= (1 << 2); 				//Setting up TX pin as output
	USART0_BAUDH = (baudRate >> 8); 	//Shift register right by 8 bits
	USART0_BAUDL = baudRate; 			//Set baud rate
	//control bits default async, 1 stop bit, 8 bit character size
	USART0_CTRLB |= (1 << USART_RXEN_bp) | (1 << USART_TXEN_bp);	//Enable RX and TX
}

// function to recieve data
unsigned char uart_recieve (void){
	while (!(USART0_STATUS & (1 << USART_RXCIF_bp)));
	return 	USART0_RXDATAL;
}

// function to transmit data
void uart_transmit(unsigned char data){
	while (!(USART0_STATUS & (1 << USART_DREIF_bp)));
	USART0_TXDATAL = data;
}


int main(void)
{
	unsigned char a; // to hold the data
	uart_init(9600); //start uart with baudrate of 9600
	
	PORTB_DIR |= (1 << PIN4_bp); //Setup onboard led for signaling
	PORTB_OUT |= (1 << PIN4_bp);
	
	
    while (1) 
    {
		a = uart_recieve();			// save the recieved data in varible a
		PORTB_OUT &= ~(1 << PIN4_bp);
		uart_transmit(a);			// transmit the recieved data back
		_delay_ms(100);
		PORTB_OUT |= (1 << PIN4_bp);
    }
}
