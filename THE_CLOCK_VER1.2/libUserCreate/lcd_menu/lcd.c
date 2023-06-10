#include "lcd.h"

#include "stdio.h"

#define ERROR_NEED_FIX 1

// Change your handler here accordingly
I2C_HandleTypeDef *i2c_of_lcd;	

// Send command to the lcd
static void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	
	HAL_I2C_Master_Transmit (i2c_of_lcd, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

// Send data to the lcd
static void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (i2c_of_lcd, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

// initialize lcd
void lcd_init (I2C_HandleTypeDef *i2c) 
{	
	i2c_of_lcd = i2c;
	
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	lcd_send_cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	lcd_send_cmd (0x30);
	HAL_Delay(10);
	lcd_send_cmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // Dislay initialisation
	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcd_send_string (char *str) 
{
	while (*str) lcd_send_data (*str++);
}

// num: number
void lcd_send_number(int num) 
{
	char _buffer[50];
	
	sprintf(_buffer, "%d", num);
	lcd_send_string(_buffer);
}

#ifndef ERROR_NEED_FIX

// Clear screen
// Get point to location start
void lcd_clear() 
{
	lcd_send_cmd (0x01); //clear display
	lcd_send_cmd (0x80);
}

#endif

// Clear screen
// Using type write overwrite
// Not get point to location start
void lcd_clear_overwrite() 
{
	lcd_send_cmd (0x80);
	for (int i=0; i<70; i++) 
	{
		lcd_send_data (' ');
	}
}

//-----------------------------
// row, column 
// Serial start from 0, 1, 2, 3, 4...
//-----------------------------
void lcd_goto_xy (int row, int col) 
{
	// condition
	if(row < 0) row = 0;
	if(row > 3) row = 3;
	
	if(col < 0) col=0;
	if(col >15) col = 15;
	
	// goto xy
	uint8_t pos_Addr;

	if(row == 0) 
	{
		pos_Addr = 0x80 + row + col;
	}
	else if(row == 1)
	{
		pos_Addr = 0x80 | (0x40 + col);
	}
	else if(row == 2)
	{
		pos_Addr = 0x80 | (0x10 + col);
	}
	else if(row == 3)
	{
		pos_Addr = 0x80 | (0x50 + col);
	}

	lcd_send_cmd(pos_Addr);
}
//
void lcd_send_string_goto_xy(uint8_t x, uint8_t y, char *str)
{
	lcd_goto_xy(x, y);
	lcd_send_string(str);
}
//
void lcd_send_number_goto_xy(uint8_t x, uint8_t y, int number)
{
	lcd_goto_xy(x, y);
	lcd_send_number(number);
}

