#include "Mux.h"

u8 Temp_Avg(void)
{
    CLEAR_BIT(DDRC,PC0);  //Initialize ADC channel 0 as INPUT
    CLEAR_BIT(PORTC,PC0);
    ADC_init();
    // return ADC_read();
    volatile float Temp_Avg_Data = 0;

    // Selection
    SET_BIT(DDRD,Selection_A);
    SET_BIT(DDRD,Selection_B);

    // Set Selection to 0
    CLEAR_BIT(PORTD,Selection_A);
    CLEAR_BIT(PORTD,Selection_B);
    

    Temp_Avg_Data += MAP(ADC_read(),0,1023,0, 5.0)*100;

    // Set Selection to 1
    CLEAR_BIT(PORTD,Selection_B);
    SET_BIT(  PORTD,Selection_A);

    Temp_Avg_Data +=  MAP(ADC_read(),0,1023,0, 5.0)*100;
    
    // Set Selection to 2
    SET_BIT(PORTD,Selection_A);
    SET_BIT(PORTD,Selection_B);

    Temp_Avg_Data +=  MAP(ADC_read(),0,1023,0, 5.0)*100;

    return Temp_Avg_Data/3.0;
}