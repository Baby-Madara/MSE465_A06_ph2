/**
 * @IDE: 		VSCode using platformIO extension
 * @AUTHORS: 	
 *  			(1) 	Ahmed Farahat 		203319
 *  			(2) 	Yasmin Ibrahim 		205177
 *  			(3) 	Mahmoud Hashim 		******
 *                   
 *                       _______|---|_______
 *              |  PB5  |D13    |___|    D12|          |
 *              |       |3v3             D11|  PB3     |
 *              |       |AREF            D10|  PB2     | MBen
 *           LL |  PC0  |A0               D9|  PB1     | MAen
 *           LR |  PC1  |A1               D8|  PB0     | MA1
 *       MB4    |  PC2  |A2    arduino    D7|  PD7     | MA2
 *              |  PC3  |A3      nano     D6|  PD6     | MB3
 *    ENCODER_R |  PC4  |A4      OBD      D5|PD5 TxLED | MB4   (old) --> BTRx black (new)
 *    ENCODER_L |  PC5  |A5    (is in)    D4|PD4 RxLED | MBen  (old) --> BTTx brown (new)
 *              |       |A6               D3|  PD3     |  BTTx brown myRX(old)
 *              |       |A7  ATMega328p   D2|  PD2     |  BTRx black myTX(old)
 *              |       |5V  (is inMdle) GND|          |
 *              |       |RST             RST|          |
 *              |       |GND    * * *    RX0|  PD0     |  BTTx brown (new)
 *              |       |VIN    * * *    TX1|  PD1     |  BTRx black (new)
 *              |       |___________________|          |
 *                   (hardware conection is outside)                         
 *                              ^
 *                           black (nano)
 *                           orange (uno)
 *                            
 *                   
 *                   
*/




// #define F_CPU 16000000UL 		//the default value in platformIO
#include "HAL/robotCtrl.h"
// #include <SoftwareSerial.h>
// #define myTX  2
// #define myRX  3 


#define MA1  DIO_B0
#define MA2  DIO_D7
#define MAen DIO_B1  	//OC1A

#define MB3  DIO_D6
#define MB4  DIO_C2
#define MBen DIO_B2  	//OC1B

#define LR DIO_C1
#define LL DIO_C0

#define BLINK_CYCLE 500

#define ENCODER_R DIO_C4
#define ENCODER_L DIO_C5

volatile unsigned long 	millis 			 = 0;

volatile unsigned long  prevTime 		 = 0,
						color    		 = 0;

volatile long 			prevEncoderReadR = 0,
						prevEncoderReadL = 0;

volatile long 			totalReadR 		 = 0,
						totalReadL 		 = 0;




// SoftwareSerial bt(myRX, myTX);



// ISR(TIMER1_COMPA_vect) {
// 	millis++; // Increment millis counter every 1 millisecond
// }

void timerSetup();
u8   UART_getc     ();
bool UART_available();

void robotForward  (int robospeed);
void robotBackward (int robospeed);
void robotTurnRight(int robospeed);
void robotTurnLeft (int robospeed);
void robotStop     ();
void updateEncoderReadings();

volatile u8 spd = 255;

int main()
{
	DIO_PinMode(MA1, OUTPUT); 
	DIO_PinMode(MA2, OUTPUT);
	DIO_PinMode(MAen,OUTPUT);

	DIO_PinMode(MB3, OUTPUT); 
	DIO_PinMode(MB4, OUTPUT); 
	DIO_PinMode(MBen,OUTPUT); 


	DIO_PinMode(LR, OUTPUT);
	DIO_PinMode(LL, OUTPUT);

	DIO_PinMode(ENCODER_L, INPUT);
	DIO_PinMode(ENCODER_R, INPUT);

	DIO_PinMode(DIO_B5, OUTPUT);		//internal LED 



	// initializing timer 1A & 1B as fast_PWM, non_inverting 
	
	
	UART_Init();

	// timerSetup();


	volatile u8 reading = 0;

while(1)
{

	updateEncoderReadings();
	reading = UART_RxChar();

	// switch case : F: forward , B: backward , R:right, L:left
	
	switch (reading)
	{
		case 'F':case 'f':    DIO_DigitalWritePin(DIO_B5, LOW);  robotForward   (spd);       break;    
		case 'B':case 'b':    DIO_DigitalWritePin(DIO_B5, LOW);  robotBackward  (spd);       break;    
		case 'R':case 'r':    DIO_DigitalWritePin(DIO_B5, LOW);  robotTurnRight (spd);       break;    
		case 'L':case 'l':    DIO_DigitalWritePin(DIO_B5, LOW);  robotTurnLeft  (spd);       break;    
		case 'S':case 's':    DIO_DigitalWritePin(DIO_B5, HIGH); robotStop      ();          break;    
		case '1':             spd = 30;          break;    
		case '2':             spd = 60;          break;    
		case '3':             spd = 90;          break;    
		case '4':             spd = 120;         break;    
		case '5':             spd = 150;         break;    
		case '6':             spd = 180;         break;    
		case '7':             spd = 200;         break;    
		case 'q':             spd = 255;         break;    
	}


}
}
//controlling the speed lesa 

//controlling directions 

void robotBackward (int robospeed)
{
	DIO_DigitalWritePin(MA1, HIGH);      
	DIO_DigitalWritePin(MA2, LOW);

	DIO_DigitalWritePin(MB3, HIGH);      
	DIO_DigitalWritePin(MB4, LOW);
	
	DIO_PWMWritePin(MAen, robospeed);
	DIO_PWMWritePin(MBen, robospeed);
	
	// if(totalReadL > totalReadR)
	// {
	// 	DIO_DigitalWritePin(MAen, 0);
	// }

	// else if(totalReadR > totalReadL)
	// {
	// 	DIO_DigitalWritePin(MBen, 0);
	// }
	
	// else
	// {
	// 	DIO_DigitalWritePin(MAen, HIGH);
	// 	DIO_DigitalWritePin(MBen, HIGH);
	// }

	DIO_DigitalWritePin(LR, LOW); 
	DIO_DigitalWritePin(LL, LOW);
}

void robotForward (int robospeed)
{
	DIO_DigitalWritePin(MA1, LOW);       
	DIO_DigitalWritePin(MA2, HIGH);

	DIO_DigitalWritePin(MB3, LOW);       
	DIO_DigitalWritePin(MB4, HIGH);

	DIO_PWMWritePin(MAen, robospeed);
	DIO_PWMWritePin(MBen, robospeed);
	
	// if(totalReadL > totalReadR)
	// {
	// 	DIO_DigitalWritePin(MAen, 0);
	// }
	// else if(totalReadR > totalReadL)
	// {
	// 	DIO_DigitalWritePin(MBen, 0);
	// }
	// else
	// {
	// 	DIO_DigitalWritePin(MAen, HIGH);
	// 	DIO_DigitalWritePin(MBen, HIGH);
	// }

	DIO_DigitalWritePin(LR, LOW); 
	DIO_DigitalWritePin(LL, LOW);
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

	DIO_DigitalWritePin(LL, LOW);
	DIO_DigitalWritePin(LR, HIGH);
	// if(time(&tm) - prevTime > BLINK_CYCLE ){ 
	// 	prevTime=time(&tm); DIO_DigitalWritePin(LR,  (color++)%2); 
	// }
}

void robotTurnLeft (int robospeed)
{
	
	DIO_PWMWritePin(MAen, robospeed);
	DIO_DigitalWritePin(MA1, LOW);       
	DIO_DigitalWritePin(MA2, HIGH);
	
	
	DIO_PWMWritePin(MBen, robospeed);
	DIO_DigitalWritePin(MB3, HIGH);      
	DIO_DigitalWritePin(MB4, LOW);

	DIO_DigitalWritePin(LL, HIGH);
	DIO_DigitalWritePin(LR, LOW);
	// if(time(&tm) - prevTime > BLINK_CYCLE )
	// {
	// 	prevTime=time(&tm); 
	// 	DIO_DigitalWritePin(LL,  (color++)%2); 
	// }
}

void robotStop ()
{
	DIO_DigitalWritePin(MA1, LOW);       
	DIO_DigitalWritePin(MA2, LOW);

	DIO_DigitalWritePin(MB3, LOW);       
	DIO_DigitalWritePin(MB4, LOW);

	DIO_DigitalWritePin(LR,  LOW);  
	DIO_DigitalWritePin(LL, LOW);
	totalReadL = totalReadR = 0;
}


void updateEncoderReadings()
{
	if(   DIO_DigitalReadPin(ENCODER_L) - prevEncoderReadL   )
	{    ++totalReadL; }

	if(   DIO_DigitalReadPin(ENCODER_R) - prevEncoderReadR   )
	{    ++totalReadR; }

	prevEncoderReadR = DIO_DigitalReadPin(ENCODER_R);
	prevEncoderReadL = DIO_DigitalReadPin(ENCODER_L);

}








bool UART_available(){

	if (UCSR0A & (1 << RXC0))	{		return 1;	}
	else 						{		return 0;	}

}




u8 UART_getc(void)
{
    // check if there is available
    
	return UDR0;

}


void timerSetup()
{
	cli(); // Disable interrupts

	// Configure Timer/Counter 1
	TCCR1A |= (1 << WGM12); // Set CTC mode (Clear Timer on Compare Match)
	OCR1A = 15; // Set compare match value for 1 millisecond interrupt
	// OCR1A = 15999; // Set compare match value for 1 millisecond interrupt
	TIMSK1 |= (1 << OCIE1A); // Enable Timer/Counter 1 Compare Match A interrupt

	sei(); // Enable interrupts
}

















// while (1)
	// {
	// 	for(int i=0; i<2000; i++){ robotForward(255);    updateEncoderReadings(); _delay_ms(1);}
	// 	for(int i=0; i<2000; i++){ robotBackward(255);   updateEncoderReadings(); _delay_ms(1);}
	// 	for(int i=0; i<2000; i++){ robotTurnRight(255);  updateEncoderReadings(); _delay_ms(1);}
	// 	for(int i=0; i<2000; i++){ robotTurnLeft(255);   updateEncoderReadings(); _delay_ms(1);}
	// 	for(int i=0; i<2000; i++){ robotStop();          updateEncoderReadings(); _delay_ms(1);}
	// }