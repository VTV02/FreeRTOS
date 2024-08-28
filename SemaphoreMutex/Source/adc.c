#include "adc.h"


void adc_init(void)
{
	RCC->AHB1ENR|=(1U<<0);
	RCC->APB2ENR|= (1U<<8);
	GPIOA->MODER|=0x0C;

	ADC1->CR2=0;
	ADC1->SQR3=1;//conversion sequence starts at ch 1
	ADC1->SQR1=0;//conversion sequence length 1
	ADC1->CR2|=1;//Enable ADC1
}

uint32_t read_analog_sensor(void)
{
	ADC1->CR2|=(1U<<30);//Start conversion
	while(!(ADC1->SR & 2)){}//Wait for conversion complete
	return ADC1->DR;
}
