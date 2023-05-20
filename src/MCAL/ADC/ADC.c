#include "ADC.h"

void ADC_init(){
	
	//  choose the AVCC pin with a capacitor at the AREF pin.
	SET_BIT(ADMUX,REFS0);
	
	// Choosing Channel One at A0 pin.
	CLEAR_BIT(ADMUX, MUX0);
	CLEAR_BIT(ADMUX, MUX1);
	CLEAR_BIT(ADMUX, MUX2);
	CLEAR_BIT(ADMUX, MUX3);
	
	// Enable the ADC
	SET_BIT(ADCSRA,ADEN);
	
	// Choosing the Data to be (Right) Adjusted in the Data Reg.
	CLEAR_BIT(ADMUX,ADLAR);
	
	// Choosing Prescaler (2) for the ADC clock.
    SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
	
	// Start continuous conversion mode
    ADCSRA |= (1 << ADATE);
    // Start first conversion
    ADCSRA |= (1 << ADSC);
}


/*ADC_Read(): to read data from the temperature sensor */

int ADC_read(){
	
	volatile int data;
	
	// Start Conversion
	SET_BIT(ADCSRA,ADSC);
	
	// Wait for interrupt flag to be set to indicate finishing conversion
	
	while(GET_BIT(ADCSRA, ADIF)==0);
	ADCSRA |= (1 << ADIF);			//clear interrupt

	
	// Read Data from the ADC Data Register (LOW First)
	data  = ADCL;
	data |= (ADCH<<8);
	
	// Clear Flag (As we are not using the interrupt)
	// It won't be cleared automatically!
	SET_BIT(ADCSRA, ADIF);
	
	return data;
}