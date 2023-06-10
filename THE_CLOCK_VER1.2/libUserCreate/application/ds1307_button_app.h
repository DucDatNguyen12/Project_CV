#ifndef DS1307_BUTTON_APP_H
#define DS1307_BUTTON_APP_H

#include "main.h"

#include "ds1307.h"
#include "lcd_menu.h"

void rtc_button_incre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t* ds1307In);
void rtc_button_decre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t* ds1307In);
void rtc_button_slow(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t* ds1307In);

void alarm_button_incre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t* ds1307In);
void alarm_button_decre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t* ds1307In);
void alarm_button_slow(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t* ds1307In);

#endif





