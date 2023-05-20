#ifndef ROBOT_CTRL_H
#define ROBOT_CTRL_H

#include <avr/interrupt.h>
#include <time.h>
#include "MCAL/DIO/DIO.h"
#include "MCAL/customUART/customUART.h"



#define MA1  DIO_B0
#define MA2  DIO_D7
#define MAen DIO_B1  	//OC1A

#define MB3  DIO_D6
#define MB4  DIO_C2
#define MBen DIO_B2  	//OC1B

#define LR DIO_B5
#define LL DIO_B3

#define BLINK_CYCLE 500

#define ENCODER_R DIO_C4
#define ENCODER_L DIO_C5






void robotForward  (int robospeed);
void robotBackward (int robospeed);
void robotTurnRight(int robospeed);
void robotTurnLeft (int robospeed);
void robotStop     ();
void updateEncoderReadings();

void carInit();

void timerSetup();

#endif