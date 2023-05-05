#ifndef CUSTOM_UART_H
#define CUSTOM_UART_H

#include <avr/io.h>
#include <util/delay.h>
#include "../../MCAL/DIO/DIO.h"
#include "../../UTILS/STD_Types.h"
#include "../../UTILS/BitMath.h"
#include "../../UTILS/Maths.h"





#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)	




void UART_Init();
bool UART_IsAvailable();
u8   UART_RxChar();
void UART_TxChar(char ch);











#endif