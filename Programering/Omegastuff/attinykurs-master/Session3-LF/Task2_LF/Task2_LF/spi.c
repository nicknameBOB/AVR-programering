//
// spi.c
//


// System headers
#include <avr/io.h>

// Project headers
#include "spi.h"

// In this file, you will need to write the contents of the SPI communication routines.
// You need to setup SPI communication in SPI_MasterInit() and
// transmit data in SPI_MasterTransmit(...).
//
// HINT: Check out the defines in the file defines.h to see defines
// such as data direction registers and bit positions, and as always:
// RTFD

//Oled is connected to alternate SPI pins
#define MOSI_BIT 2 //on port C
#define SCK_BIT 0 //on port C
#define SS_BIT 3 //on port C
#define SPI_PORT PORTC //



void SPI_MasterInit()
{
	// Initialize the SPI port as master
	// You will need to set MOSI, SCK, SS (slave select) as outputs
	
	PORTMUX.CTRLB |= (1 << PORTMUX_SPI0_bp); //To use alternative SPI pins
	
	SPI_PORT.DIR |= (1 << MOSI_BIT) | (1 << SCK_BIT) | (1 << SS_BIT); //Set pins as output

	SPI_PORT.OUTSET = (1 << SS_BIT); //Set SS high -> OLED inactive
	
	
	// Now enable SPI, Master and set clock rate
	
	SPI0.CTRLA |= (1 << SPI_ENABLE_bp) | (1 << SPI_MASTER_bp); //Default clock divisor of 4 is fine
	
	

	//Make sure SS does not disable master mode
	SPI0.CTRLB |= (1 << SPI_SSD_bp);
}


void SPI_MasterTransmit(char cData)
{
	// First select the correct slave by setting the slave select (SS) bit LOW
	PORTC.OUTCLR = (1 << SS_BIT);

	// Then start the transmission by assigning the data to the SPI data register
	SPI0.DATA = cData;

	// Now wait for the data transmission to complete by periodically checking the SPI status register
	//the SPI_IF is the only interupt flag with a function in non-buffered mode.
	while(!(SPI0.INTFLAGS & (1 << SPI_IF_bp)));
	SPI0.DATA; //Dummy read to clear flag

	// Finally set the slave select bit HIGH before leaving the function
	PORTC.OUTSET = (1 << SS_BIT);
}
