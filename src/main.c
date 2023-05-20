/**
 * @IDE: 		VSCode using platformIO extension
 * @AUTHORS: 	
 *  			(1) 	Ahmed Farahat 		203319
 *  			(2) 	Yasmin Ibrahim 		205177
 *  			(3) 	Mahmoud Hashim 		******
 *                   
 *                                  _______|---|_______
 *                         |  PB5  |D13    |___|    D12|          |
 *                         |       |3v3             D11|  PB3     |
 *                         |       |AREF            D10|  PB2     | MBen
 *             ANALOG_PIN  |  PC0  |A0               D9|  PB1     | MAen
 *                     LR  |  PC1  |A1               D8|  PB0     | MA1
 *                 MB4     |  PC2  |A2    arduino    D7|  PD7     | MA2
 *            ()           |  PC3  |A3      uno      D6|  PD6     | MB3
 *              ENCODER_R  |  PC4  |A4      nBD      D5|PD5 TxLED | MB4   (old) --> BTRx black (new)
 *              ENCODER_L  |  PC5  |A5    (is in)    D4|PD4 RxLED | MBen  (old) --> BTTx brown (new)
 *                         |       |A6               D3|  PD3     |  S0
 *                         |       |A7  ATMega328p   D2|  PD2     |  S1
 *                         |       |5V  (is inMdle) GND|          |
 *                         |       |RST             RST|          |
 *                         |       |GND    * * *    RX0|  PD0     |  BTTx brown (new)
 *                         |       |VIN    * * *    TX1|  PD1     |  BTRx black (new)
 *                         |       |___________________|          |
 *                              (hardware conection is outside)                         
 *                                         ^
 *                                      black (nano)
 *                                      orange (uno)
 *                                       
 *                              
 *                   
*/





// #define F_CPU 16000000UL 		//the default value in platformIO

#include "HAL/robotCtrl.h"
#include "HAL/LCD_I2C/LCD_I2C.h"
#include "HAL/Mux/Mux.h"










int main()
{
	carInit();
    timerSetup();


    i2c_init();
    lcd_init();
    _delay_ms(100);



    lcd_Clear();

while(1)
{
    lcd_GoTo(0, 1);
    lcd_WriteString("Temp_Avg: ");
    lcd_WriteInt(Temp_Avg());
    if(Temp_Avg() > 23)
    {
        robotForward(255);
    }
    else
    {
        robotStop();
    }
    _delay_ms(100);
    lcd_Clear();

}
}








/*
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define SLAVE_ADDRESS_LCD 0x27  // Set the slave address of the LCD

void I2C_Init()
{
    TWSR = 0x00;   // Set prescalar to 1 and clear status register
    TWBR = 0x0C;   // Set bit rate generator value for 100khz
}

void I2C_Start()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);  // Send start condition
    while (!(TWCR & (1 << TWINT)));  // Wait for start condition to be transmitted
}

void I2C_Stop()
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);  // Send stop condition
    _delay_us(10);
}

void I2C_Write(unsigned char data)
{
    TWDR = data;   // Load data into data register
    TWCR = (1 << TWINT) | (1 << TWEN);  // Start transmission
    while (!(TWCR & (1 << TWINT)));  // Wait for transmission to complete
}

void LCD_Init()
{
    I2C_Start();  // Initiate start condition
    I2C_Write(SLAVE_ADDRESS_LCD);  // Send slave address
    I2C_Write(0x00);  // Set register to command mode
    I2C_Write(0x38);  // Initialize 2 lines and 5x8 dot format
    I2C_Write(0x06);  // Increment cursor and don't shift display
    I2C_Write(0x0C);  // Turn on display, cursor, and blinking
    I2C_Stop();  // Initiate stop condition
}

void LCD_Clear()
{
    I2C_Start();  // Initiate start condition
    I2C_Write(SLAVE_ADDRESS_LCD);  // Send slave address
    I2C_Write(0x00);  // Set register to command mode
    I2C_Write(0x01);  // Clear display
    I2C_Stop();  // Initiate stop condition
}

void LCD_Write_Char(char data)
{
    I2C_Start();  // Initiate start condition
    I2C_Write(SLAVE_ADDRESS_LCD);  // Send slave address
    I2C_Write(0x40);  // Set register to data mode
    I2C_Write(data);  // Write data to display
    I2C_Stop();  // Initiate stop condition
}

void LCD_Write_String(char* string)
{
    while (*string)  // Loop through each character in the string
    {
        LCD_Write_Char(*string++);  // Write character to display
    }
}

int main()
{
    I2C_Init();  // Initialize I2C communication
    LCD_Init();  // Initialize LCD
    LCD_Clear();  // Clear LCD screen
    LCD_Write_String("Hello, world!");  // Write string to LCD

    while (true)
    {
        // Do nothing
    }

    return 0;
}


*/

































/*

#include "HAL/robotCtrl.h"

int main()
{
	volatile u8 spd = 255;
	carInit();

	// initializing timer 1A & 1B as fast_PWM, non_inverting 
	timerSetup();
	
	UART_Init();
	volatile u8 reading = 0;

while(1)
{

	// updateEncoderReadings();
	reading = UART_RxChar();

	// switch case : F: forward , B: backward , R:right, L:left
	
	switch (reading)
	{
		case 'F':case 'f':    DIO_DigitalWritePin(DIO_B5, LOW);  robotForward   (spd);       break;    
		case 'B':case 'b':    DIO_DigitalWritePin(DIO_B5, LOW);  robotBackward  (spd);       break;    
		case 'R':case 'r':    DIO_DigitalWritePin(DIO_B5, LOW);  robotTurnRight (spd);       break;    
		case 'L':case 'l':    DIO_DigitalWritePin(DIO_B5, LOW);  robotTurnLeft  (spd);       break;    
		case 'S':case 's':    DIO_DigitalWritePin(DIO_B5, HIGH); robotStop      ();          break;    
		case '1':             spd = 60;          break;    
		case '2':             spd = 85;          break;    
		case '3':             spd = 110;         break;    
		case '4':             spd = 135;         break;    
		case '5':             spd = 160;         break;    
		case '6':             spd = 185;         break;    
		case '7':             spd = 210;         break;    
		case 'q':             spd = 255;         break;    
	}


}
}

*/




