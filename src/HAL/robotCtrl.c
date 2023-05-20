#include "robotCtrl.h"







void robotBackward (int robospeed)
{
	DIO_DigitalWritePin(MA1, HIGH);      
	DIO_DigitalWritePin(MA2, LOW);

	DIO_DigitalWritePin(MB3, HIGH);      
	DIO_DigitalWritePin(MB4, LOW);
	
	DIO_PWMWritePin(MAen, robospeed);
	DIO_PWMWritePin(MBen, robospeed);


	// DIO_DigitalWritePin(LR, LOW); 
	// DIO_DigitalWritePin(LL, LOW);
}

void robotForward (int robospeed)
{
	DIO_DigitalWritePin(MA1, LOW);       
	DIO_DigitalWritePin(MA2, HIGH);

	DIO_DigitalWritePin(MB3, LOW);       
	DIO_DigitalWritePin(MB4, HIGH);

	DIO_DigitalWritePin(MBen, HIGH);       
	DIO_DigitalWritePin(MAen, HIGH);

	// DIO_PWMWritePin(MAen, robospeed);
	// DIO_PWMWritePin(MBen, robospeed);
	
	// DIO_DigitalWritePin(LR, LOW); 
	// DIO_DigitalWritePin(LL, LOW);
}


//MA ---- Left & MB -----Right
void robotTurnRight (int robospeed)
{


	DIO_PWMWritePin(MAen, robospeed);
	DIO_DigitalWritePin(MA1, HIGH);      
	DIO_DigitalWritePin(MA2, LOW);

	
	DIO_PWMWritePin(MBen, robospeed);
	DIO_DigitalWritePin(MB3, LOW);       
	DIO_DigitalWritePin(MB4, HIGH);

	// DIO_DigitalWritePin(LL, LOW);
	// DIO_DigitalWritePin(LR, HIGH);
	
}

void robotTurnLeft (int robospeed)
{
	
	DIO_PWMWritePin(MAen, robospeed);
	DIO_DigitalWritePin(MA1, LOW);       
	DIO_DigitalWritePin(MA2, HIGH);
	
	
	DIO_PWMWritePin(MBen, robospeed);
	DIO_DigitalWritePin(MB3, HIGH);      
	DIO_DigitalWritePin(MB4, LOW);

	// DIO_DigitalWritePin(LL, HIGH);
	// DIO_DigitalWritePin(LR, LOW);

}

void robotStop ()
{
	DIO_DigitalWritePin(MA1, LOW);       
	DIO_DigitalWritePin(MA2, LOW);

	DIO_DigitalWritePin(MB3, LOW);       
	DIO_DigitalWritePin(MB4, LOW);

	// DIO_DigitalWritePin(LR,  LOW);  
	// DIO_DigitalWritePin(LL, LOW);
	// totalReadL = totalReadR = 0;
}





void carInit()
{
    DIO_PinMode(MA1, OUTPUT); 
	DIO_PinMode(MA2, OUTPUT);
	DIO_PinMode(MAen,OUTPUT);

	DIO_PinMode(MB3, OUTPUT); 
	DIO_PinMode(MB4, OUTPUT); 
	DIO_PinMode(MBen,OUTPUT); 


	// DIO_PinMode(LR, OUTPUT);
	// DIO_PinMode(LL, OUTPUT);

	// DIO_PinMode(ENCODER_L, INPUT);
	// DIO_PinMode(ENCODER_R, INPUT);

	// DIO_PinMode(DIO_B5, OUTPUT);		//internal LED 


}



void timerSetup()
{
	
	// SET_BIT(DDRB, 1);
	// SET_BIT(DDRB, 2);


	// TCCR1A = (1<< WGM11) | (1<<COM1A1) | (1<<COM1B1) | (1<<COM1A0) | (1<<COM1B0);
	// TCCR1B = (1<< WGM13) | (1<<WGM12) | (1<<CS10);
	
	// ICR1 = 255;


	// OCR1A = 128;
	// OCR1B = 128;
	
}














////////////////////////       NOT USED:           /////////////////////



/*
void updateEncoderReadings()
{
	if(   DIO_DigitalReadPin(ENCODER_L) - prevEncoderReadL   )
	{    ++totalReadL; }

	if(   DIO_DigitalReadPin(ENCODER_R) - prevEncoderReadR   )
	{    ++totalReadR; }

	prevEncoderReadR = DIO_DigitalReadPin(ENCODER_R);
	prevEncoderReadL = DIO_DigitalReadPin(ENCODER_L);

}
*/

