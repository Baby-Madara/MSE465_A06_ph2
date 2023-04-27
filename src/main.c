/**
 * @IDE: 		VSCode using platformIO extension
 * @AUTHORS: 	(1) 	Ahmed Farahat 		203319
 *  			(2) 	Yasmin Ibrahim 		205177
 *  			(3) 	Mahmoud Hashim 		
 *                   
 *                       ______|---|______
 *              |       |D13   |___|   D12|       |
 *              |       |3v3           D11|       |
 *              |       |AREF          D10|       |
 *           LL |  PC0  |A0             D9|  PB1  | MAen
 *           LR |  PC1  |A1             D8|  PB0  | MA1
 *              |  PC2  |A2   arduino   D7|  PD7  | MA2
 *              |  PC3  |A3     nano    D6|  PD6  | MB3
 *    ENCODER_R |  PC4  |A4     OBD     D5|  PD5  | MB4
 *    ENCODER_L |  PC5  |A5   (is in)   D4|  PD4  | MBen
 *              |       |A6             D3|  PD3  |  BTTx brown myRX(old)
 *              |       |A7 ATMega328p  D2|  PD2  |  BTRx black myTX(old)
 *              |       |5V (is inMdle)GND|       |
 *              |       |RST           RST|       |
 *              |       |GND   * * *   RX0|  PD0  |  BTTx brown (new)
 *              |       |VIN   * * *   TX1|  PD1  |  BTRx black (new)
 *                      |_________________|
 *                (hardware conection is outside)                         
 *                   
 *                   
 *                   
*/




// #define F_CPU 16000000UL 		//the default value in platformIO
#include "MCAL/DIO/DIO.h"
#include <avr/interrupt.h>
#include <time.h>


// #include <SoftwareSerial.h>
// #define myTX  2
// #define myRX  3 


#define MA1  DIO_B0
#define MA2  DIO_D7
#define MAen DIO_B1

#define MB3  DIO_D6
#define MB4  DIO_D5
#define MBen DIO_D4

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



time_t tm;

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



int main()
{
	DIO_PinMode(MA1,OUTPUT); 
	DIO_PinMode(MA2,OUTPUT);
	DIO_PinMode(MAen,OUTPUT);
	DIO_PinMode(MB3,OUTPUT); 
	DIO_PinMode(MB4,OUTPUT); 
	DIO_PinMode(MBen,OUTPUT); 

	DIO_PinMode(LR, OUTPUT);
	DIO_PinMode(LL, OUTPUT);

	DIO_PinMode(ENCODER_L, INPUT);
	DIO_PinMode(ENCODER_R, INPUT);

	
	// Serial.begin(9600);
	// bt.begin(9600);


  //for UART enable:   {  UBBRn = ( fosc / (16*BAUD)  ) -1  } >> BAUD ~= 103.12
	// write to lower byte
    UBRR0L = (u8)(103 & 0xFF);

    // write to higher byte
    UBRR0H = (u8)(103 >> 8);

	// enable the transmitter and receiver
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

	// timerSetup();


	volatile u8 reading = 0;

while(1)
{
	// while (1)
	// {
	// 	for(int i=0; i<2000; i++){ robotForward(255);    _delay_ms(1);}
	// 	for(int i=0; i<2000; i++){ robotBackward(255);   _delay_ms(1);}
	// 	for(int i=0; i<2000; i++){ robotTurnRight(255);  _delay_ms(1);}
	// 	for(int i=0; i<2000; i++){ robotTurnLeft(255);   _delay_ms(1);}
	// 	for(int i=0; i<2000; i++){ robotStop();          _delay_ms(1);}
	// }
	


	// read from serial port
	// if(UART_available()){
		// store reading in 'reading'
		reading = UART_getc();
		// Serial.print(reading);
	// }

	
	updateEncoderReadings();
	

	// switch case : F: forward , B: backward , R:right, L:left
	switch (reading) {
		case 'F':case 'f':    robotForward(255);    break;    
		case 'B':case 'b':    robotBackward(255);   break;    
		case 'R':case 'r':    robotTurnRight(255);  break;    
		case 'L':case 'l':    robotTurnLeft(255);   break;    
		case 'S':case 's':    robotStop();          break;    
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
	
	if(totalReadL > totalReadR)
	{
		DIO_DigitalWritePin(MAen, 0);
	}

	else if(totalReadR > totalReadL)
	{
		DIO_DigitalWritePin(MBen, 0);
	}
	
	else{
		DIO_DigitalWritePin(MAen, HIGH);
		DIO_DigitalWritePin(MBen, HIGH);
	}

	DIO_DigitalWritePin(LR, LOW); 
	DIO_DigitalWritePin(LL, LOW);
}

void robotForward (int robospeed)
{
	DIO_DigitalWritePin(MA1, LOW);       
	DIO_DigitalWritePin(MA2, HIGH);

	DIO_DigitalWritePin(MB3, LOW);       
	DIO_DigitalWritePin(MB4, HIGH);

	if(totalReadL > totalReadR)
	{
		DIO_DigitalWritePin(MAen, 0);
	}
	else if(totalReadR > totalReadL)
	{
		DIO_DigitalWritePin(MBen, 0);
	}
	else
	{
		DIO_DigitalWritePin(MAen, HIGH);
		DIO_DigitalWritePin(MBen, HIGH);
	}

	DIO_DigitalWritePin(LR, LOW); 
	DIO_DigitalWritePin(LL, LOW);
}


//MA ---- Left & MB -----Right
void robotTurnRight (int robospeed)
{
	DIO_DigitalWritePin(MAen, HIGH);     
	DIO_DigitalWritePin(MA1, HIGH);      
	DIO_DigitalWritePin(MA2, LOW);

	DIO_DigitalWritePin(MBen, HIGH);     
	DIO_DigitalWritePin(MB3, LOW);       
	DIO_DigitalWritePin(MB4, HIGH);

	if(time(&tm) - prevTime > BLINK_CYCLE ){ 
		prevTime=time(&tm); DIO_DigitalWritePin(LR,  (color++)%2); 
	}
}

void robotTurnLeft (int robospeed)
{
	DIO_DigitalWritePin(MAen, HIGH);     
	DIO_DigitalWritePin(MA1, LOW);       
	DIO_DigitalWritePin(MA2, HIGH);
	
	DIO_DigitalWritePin(MBen, HIGH);     
	DIO_DigitalWritePin(MB3, HIGH);      
	DIO_DigitalWritePin(MB4, LOW);

	if(time(&tm) - prevTime > BLINK_CYCLE )
	{
		prevTime=time(&tm); 
		DIO_DigitalWritePin(LL,  (color++)%2); 
	}
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


