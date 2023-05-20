#ifndef LCD_I2C_H
#define LCD_I2C_H
#include <avr/io.h>
#include <util/delay.h>
#include "../../UTILS/Maths.h"
#include "../../UTILS/STD_Types.h"
#include <stdio.h>



void i2c_init();

void i2c_start();
void i2c_write_data(uint8_t data);
void i2c_stop();


void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_init();
void lcd_WriteString(char *str);
void lcd_Clear();
void lcd_String_With_Length (char row, char pos, char str);

void lcd_String_With_Length (char row, char pos, char str);	/* Send string to LCD with xy position */

void lcd_GoTo(u8 line, u8 col);





void lcd_WriteStringWithLength(u8* str, s8 len);	//Write string (many char) with specific Length
void lcd_WriteInt(s64 num);	//Write integer number (0 ==> 9)
void lcd_WriteFloat(float64 num, u8 digits);	//Write Float Number (EX. 10.5)

void lcd_WriteNumWithLength(float64 num, u8 len); //Write integer numbers (0 ==> 9)



#endif