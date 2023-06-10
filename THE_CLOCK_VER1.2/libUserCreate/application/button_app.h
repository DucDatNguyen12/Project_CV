#ifndef BUTTON_APP_H
#define BUTTON_APP_H

#include "main.h"

#include "lcd_menu.h"
#include "ds1307.h"
#include "ds18b20.h"
#include "uart.h"

void up_buttonApp_Fast(void);
void up_buttonApp_Slow(void);
void up_buttonApp_Long_Slow(void);
void up_buttonApp_Keep(void);
//
void down_buttonApp_Fast(void);
void down_buttonApp_Slow(void);
void down_buttonApp_Long_Slow(void);
void down_buttonApp_Keep(void);

void buttonApp_init(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t *ds1307In, DS18B20_Name *ds18b20In, Uart_TypDef_t *uartIn);

#endif



