#ifndef TEMP_BUTTON_APP_H
#define TEMP_BUTTON_APP_H

#include "main.h"

#include "lcd_menu.h"
#include "ds18b20.h"

void temp_button_incre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, DS18B20_Name* ds18b20In);

void temp_button_decre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, DS18B20_Name* ds18b20In);

void temp_button_slow(Lcd_Menu_TypDef_t *lcdMenuIn, DS18B20_Name* ds18b20In);

#endif



