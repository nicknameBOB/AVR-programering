/*
 * adc.h
 *
 * Created: 27.02.2017 16:51:27
 *  Author: Petter
 */ 


#ifndef ADC_H_
#define ADC_H_

void adc_init(void);

uint8_t adc_read(uint8_t channel);

#endif /* ADC_H_ */