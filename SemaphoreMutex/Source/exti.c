#include "exti.h"



void p13_interrupt_init(void)
{
	//Enable clock access to GPIOC
	RCC->AHB1ENR|=4;//4 = OB0100
	//Enable SYSCFG clock
	RCC->APB2ENR|=0x4000;
	//configure PC13 for push button interrupt
	GPIOC->MODER&=~0x0C000000;
	//Clear port selection EXTI13
	SYSCFG->EXTICR[3]&=~0x00F0;
	//Select port C for EXTI13
	SYSCFG->EXTICR[3]|=0x0020;
	//Unmask EXTI13
	EXTI->IMR|=0x2000;
	//Selection falling edge trigger
	EXTI->FTSR|=0x2000;

	NVIC_SetPriority(EXTI15_10_IRQn,6);

	NVIC_EnableIRQ(EXTI15_10_IRQn);
}
void gpio_init(void)
{
	//Enable clock access to GPIOC
		RCC->AHB1ENR|=4;//4 = OB0100
}
uint8_t read_digital_sensor(void)
{
	if(GPIOC->IDR & 0x2000)
	{

		return 1;
	}
	else
	{
		return 0;
	}

}
