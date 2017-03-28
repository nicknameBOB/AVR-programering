/*
 * uart.c
 *
 * Created: 13.02.2017 04:55:46
 *  Author: Petter
 */ 

#define F_CPU 3333333UL

#include <avr/io.h>
#include <avr/interrupt.h>


void uart_init(unsigned long baud){
	
	//From chapter 24.3 in datasheet
	PORTB.OUTSET = (1 << PIN2_bp);
	PORTB.DIRSET = (1 << PIN2_bp); 		//Setting up TX pin as output
	USART0.BAUDH = (baud >> 8); 	//Shift register right by 8 bits
	USART0.BAUDL = baud; 			//Set baud rate
	//USART.CTRLC CMODE bits default to: async, 1 stop bit, 8 bit character size
	USART0.CTRLB |= (1 << USART_RXEN_bp) | (1 << USART_TXEN_bp);	//Enable RX and TX
	
	
	USART0.CTRLA |= (1 << USART_RXCIE_bp); //Enable interupts on RX
}


// function to transmit data
void uart_transmit(unsigned char data){
	while (!(USART0.STATUS & (1 << USART_DREIF_bp)));
	USART0.TXDATAH = 0x00; //Is required!
	USART0.TXDATAL = data;
}

//Interrupt service routine for the receiver.
ISR(USART0_RXC_vect){
	
	uint8_t data = USART0.RXDATAL; //We must read the data to clear the interrupt flag
	//Do things with data (if you want)
	uart_transmit(data + 1);
}