#ifndef ADC_H
#define ADC_H
#include <avr/io.h>
// #include "../USART/USART.h"	/* include USART library */
#include "../../UTILS/BitMath.h"

/*Initializing ADC channel 0*/
void ADC_init();
int ADC_read();



#endif