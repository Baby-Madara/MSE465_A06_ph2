#include "LCD_I2C.h"

#define SLAVE_ADDRESS_LCD 0x27




u8 LCD_cursorTracer =0;



void i2c_init()
{
	TWSR &= ~(1 << TWPS0);
	TWSR &= ~(1 << TWPS1);
	TWBR = ((F_CPU / 100000UL) - 16) / 2;
}

void i2c_start()
{
	
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	while (!     (TWCR & (1 << TWINT))) {}
}

void i2c_stop() {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	while ((TWCR & (1 << TWSTO))) {}
}

void i2c_write(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT))) {}
}

void lcd_send_cmd(char cmd) {
	char data_u, data_l;
	unsigned char data_t[4];
	data_u = (cmd & 0xf0);
	data_l = ((cmd << 4) & 0xf0);
	data_t[0] = data_u | 0x0C; // en=1, rs=0
	data_t[1] = data_u | 0x08; // en=0, rs=0
	data_t[2] = data_l | 0x0C; // en=1, rs=0
	data_t[3] = data_l | 0x08; // en=0, rs=0

	i2c_start();
	i2c_write(SLAVE_ADDRESS_LCD << 1); // write to the device
	i2c_write(data_t[0]);
	i2c_write(data_t[1]);
	i2c_write(data_t[2]);
	i2c_write(data_t[3]);
	i2c_stop();
}

void lcd_send_data(char data) {
	char data_u, data_l;
	unsigned char data_t[4];
	data_u = (data & 0xf0);
	data_l = ((data << 4) & 0xf0);
	data_t[0] = data_u | 0x0D; // en=1, rs=1
	data_t[1] = data_u | 0x09; // en=0, rs=1
	data_t[2] = data_l | 0x0D; // en=1, rs=1
	data_t[3] = data_l | 0x09; // en=0, rs=1

	i2c_start();
	i2c_write(SLAVE_ADDRESS_LCD << 1); // write to the device
	i2c_write(data_t[0]);
	i2c_write(data_t[1]);
	i2c_write(data_t[2]);
	i2c_write(data_t[3]);
	// _delay_ms(100);
    i2c_stop();

	++LCD_cursorTracer;
	if(LCD_cursorTracer== 16){
		lcd_GoTo(1,0);
	}
	else if(LCD_cursorTracer==32){
		lcd_GoTo(0,0);
		LCD_cursorTracer=0;
	}


}



void lcd_init() {
	lcd_send_cmd(0x02); // return home
	_delay_ms(2);
	lcd_send_cmd(0x28); // 4-bit mode, 2 lines, 5x8 font
	_delay_ms(2);
	lcd_send_cmd(0x0C); // display on, cursor off, blink off
	_delay_ms(2);
	lcd_send_cmd(0x01); // clear display
	_delay_ms(2);
}

void lcd_WriteString (char *str)
{
	while (*str) lcd_send_data (*str++);
    _delay_ms(100);
}

// Function to clear the LCD display
void lcd_Clear()
{
	lcd_send_cmd(0x01);  // Send clear display command
	_delay_ms(2);     // Delay to allow LCD to clear the display
}

void lcd_String_With_Length (char row, char pos, char str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	lcd_send_cmd((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	
	
	else if (row == 1 && pos<16) 
	lcd_send_cmd((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	lcd_WriteString(str);		/* Call LCD string function */
	
}


void lcd_GoTo(u8 line, u8 col){
	lcd_send_cmd(0x80 + (line*64 + col));
	LCD_cursorTracer = line*16 + col;
}




void lcd_WriteInt(s64 num){
	u8 num_str[10]={0};
	sprintf((char*)num_str, 	"%d", 	(int)num);
	lcd_WriteString(num_str);
}



void lcd_WriteFloat(float64 num, u8 digits){
	u8 res[20] = {0};
	ftoa(num, res, digits);
	lcd_WriteString(res);
}



void lcd_WriteNumWithLength(float64 num, u8 len){
	u8 res[len];
	ftoa(num, res, 5);
	lcd_WriteStringWithLength(res, len);
}

