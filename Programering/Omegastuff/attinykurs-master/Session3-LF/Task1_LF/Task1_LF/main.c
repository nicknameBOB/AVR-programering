/*
 * Task1_LF.c
 *
 * Created: 27.02.2017 16:43:03
 * Author : Petter
 */ 

#define F_CPU 3333333UL
#define BAUD_9600 ((4UL*F_CPU)/9600)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "adc.h"
#include "uart.h"


#define LIGHT 6 // Light sensor is connected to ADC channel 6 (which is on port A pin 6)

uint8_t data, ones, tens, hundreds;

int main(void)
{
	uart_init(BAUD_9600);
	
	adc_init();
	
	sei();
	
	while (1)
	{
		data = adc_read(6);
		data = 0xff - data;
		
		ones = (data%10);
		data /= 10;
		tens = (data%10);
		data /= 10;
		hundreds = (data%10);
		
		uart_transmit(hundreds + 48);
		uart_transmit(tens + 48);
		uart_transmit(ones + 48);
		uart_transmit(0x20); //Space
		
		
		_delay_ms(1000); //Wait a little before next read 
	}
}
