#include "customUART.h"












void UART_Init()
{
    // SET_BIT(  DDRD, PIN_1);    //TX output
	// CLEAR_BIT(DDRD, PIN_0);    //RX input
    
    // SET_BIT(  PORTD, PIN_5);    //TX output
	// CLEAR_BIT(PORTD, PIN_4);    //RX input

    // SET_BIT(  PORTD, PIN_1);    //TX output
	// CLEAR_BIT(PORTD, PIN_0);    //RX input
    
    // UCSR0A=0;

	UBRR0H = 0;		                // Load upper 8-bits
	UBRR0L = 103;			        // Load lower 8-bits of the baud rate 

	UCSR0B |=  (1 << TXEN0)  | (1 << RXEN0);	    // Turn on transmission and reception 
	UCSR0C |=  (1 << UCSZ01) | (1 << UCSZ00);// Use 8-bit char size 
	// UCSRC |= (1 << UBRRH_URSEL) | (1 << UCSRC_UCSZ0) | (1 << UCSRC_UCSZ1);// Use 8-bit char size 
	// UCSR0C |= (1 << URSEL) | (1 << UCSZ00) | (1 << UCSZ01);// Use 8-bit char size 
	// UBRRL = BAUD_PRESCALE;			        // Load lower 8-bits of the baud rate 
	// UBRRH = (BAUD_PRESCALE >> 8);		    // Load upper 8-bits
}



void UART_TxChar(char ch)
{
	while (! (UCSR0A & (1<<UDRE0)));          // Wait for empty transmit buffer 
	UDR0 = ch ;
}

bool UART_IsAvailable()
{
    if((UCSR0A & (1 << RXC0)) == 0)
    {   
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}


u8 UART_RxChar()
{
	while(!(UCSR0A & (1<<RXC0)));
    
    return UDR0;
}


