/*
 * adc.c
 *
 * Created: 13.02.2017 02:04:10
 *  Author: Petter
 */ 

#include <avr/io.h>

void adc_init(){
	ADC0.CTRLA |= (ADC_RESSEL_8BIT_gc); //Set resolution, we choose 8 bits
	
	ADC0.CTRLB |= (ADC_SAMPLNUM_ACC4_gc); //OPTIONAL: We can use multiple samples if we like, example here with 4
	
	ADC0.CTRLC |= (ADC_REFSEL_VDDREF_gc); //We select to use the supply voltage (VDD) as voltage reference
	ADC0.CTRLC |= (ADC_PRESC_DIV2_gc); //ADC clock prescaler, best accuracy when run below 2MHz. (Here div2 ~1.46 MHz)
	
	ADC0.CTRLA |= (ADC_ENABLE_bm); //Enable the ADC
}


uint8_t adc_read(uint8_t channel){
	ADC0.MUXPOS = channel; //Select input on the ADC mux
	
	ADC0.INTFLAGS |= (ADC_RESRDY_bm); //Clear the results ready flag
	
	ADC0.COMMAND |= (ADC_STCONV_bm); //Start a conversion
	
	while(!(ADC0.INTFLAGS & ADC_RESRDY_bm)){	
		 //Wait for the results ready flag to be set
	}
	return ADC0.RESL; //Return 8 bit result

}
