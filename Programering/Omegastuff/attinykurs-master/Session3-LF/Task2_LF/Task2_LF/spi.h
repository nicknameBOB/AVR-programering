/*
 * spi.h
 *
 * Created: 23.02.2017 00:25:51
 *  Author: Petter
 */ 


#ifndef SPI_H_
#define SPI_H_

// Function for initializing SPI
void SPI_MasterInit(void);

// Function for transmitting SPI data
void SPI_MasterTransmit(char cData);


#endif /* SPI_H_ */