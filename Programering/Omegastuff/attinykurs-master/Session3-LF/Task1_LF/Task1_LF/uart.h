/*
 * uart.h
 *
 * Created: 27.02.2017 16:51:11
 *  Author: Petter
 */ 


#ifndef UART_H_
#define UART_H_

void uart_init(unsigned long baud);

void uart_transmit(unsigned char data);

#endif /* UART_H_ */