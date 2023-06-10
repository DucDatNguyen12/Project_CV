//----------------------------------------------------------------
// 	NguyenDucDat
//	22/11/2022
//----------------------------------------------------------------

#ifndef LCD_H
#define LCD_H

#include "main.h"

#define LCD_1602 1
//#define LCD_2004 1
 
// Change this according to ur setup
// Address default module PCF85741
// 0x27 << 1	== 0x4E 
#define SLAVE_ADDRESS_LCD 0x27 << 1
 
void lcd_init (I2C_HandleTypeDef *i2c) ;

void lcd_goto_xy (int row, int col);

void lcd_send_string (char *str) ;
void lcd_send_string_goto_xy(uint8_t x, uint8_t y, char *str);

void lcd_send_number(int num) ;
void lcd_send_number_goto_xy(uint8_t x, uint8_t y, int number);


void lcd_clear_overwrite(void) ;

#endif
