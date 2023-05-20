#ifndef MUX_H
#define MUX_H
#include <avr/io.h>
#include "../../UTILS/BitMath.h"
#include "../../UTILS/Maths.h"
#include "../../UTILS/STD_Types.h"
#include "../../MCAL/ADC/ADC.h"

/*Selection Pins*/
#define Selection_A PD2
#define Selection_B PD3

/*Enable Pin (Inverted)*/
#define Enable_1 PD2

/*Mux Output Pin to Arduino*/
#define Mux_Out PC0 //ADC 0

/*
    First Temp Sensor  ==> Input1
    Second Temp Sensor ==> Input2
    Third Temp Sensor  ==> Input3
*/

// Get First value and save it in Variable and change selection to get second value then add it to Variable and same with third value then divide by 3 to get average Temp.

u8 Temp_Avg(void);

#endif