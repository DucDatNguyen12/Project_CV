#include "temp_button_app.h"

void number_incre(uint8_t *value)
{
	(*value)++;
	if((*value) > 99)
	{
		(*value) = 0;
	}
}

void number_decre(uint8_t *value)
{
	if((*value) > 0)
	{
		(*value)--;
	}
}

void temp_button_incre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, DS18B20_Name* ds18b20In)
{
	if(lcdMenuIn->level != MENU_LEVEL_FINISH)	return;
	if(lcdMenuIn->count_1 != MENU_ROW_THREE) return;
	
	switch(lcdMenuIn->count_2)
	{
		case MENU_ROW_ONE:
			
			break;
		
		case MENU_ROW_TWO:
			if(ds18b20In->changeTempSet == 1)
			{
				number_incre(&ds18b20In->tempSet);
			}
			break;
		
		case MENU_ROW_THREE:
			
			break;
		
		case MENU_ROW_FORE:
			if(ds18b20In->changeNumSensor == 1)
			{
				number_incre(&ds18b20In->numSensor);
			}
			break;
	}
}

void temp_button_decre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, DS18B20_Name* ds18b20In)
{
	if(lcdMenuIn->level != MENU_LEVEL_FINISH)	return;
	if(lcdMenuIn->count_1 !=  MENU_ROW_THREE) return;
	
	
	switch(lcdMenuIn->count_2)
	{
		case  MENU_ROW_ONE:
			
			break;
		
		case  MENU_ROW_TWO:
				
			if(ds18b20In->changeTempSet == 1)
			{
				number_decre(&ds18b20In->tempSet);
			}
			break;
		
		case  MENU_ROW_THREE:
			
			break;
		
		case  MENU_ROW_FORE:
			if(ds18b20In->changeNumSensor == 1)
			{
				number_decre(&ds18b20In->numSensor);
			}
			break;
	}
}

void temp_button_slow(Lcd_Menu_TypDef_t *lcdMenuIn, DS18B20_Name* ds18b20In)
{
	if(lcdMenuIn->level !=  MENU_LEVEL_FINISH)	return;
	if(lcdMenuIn->count_1 !=  MENU_ROW_THREE) return;
	
	switch(lcdMenuIn->count_2)
	{
		case  MENU_ROW_ONE:
			
			break;
		
		case  MENU_ROW_TWO:
			ds18b20In->changeTempSet++;
			if(ds18b20In->changeTempSet > 1)
			{
				ds18b20In->saveTempSet = 1;
				ds18b20In->changeTempSet = 0;
			}
			break;
		
		case  MENU_ROW_THREE:
			
			break;
		
		case  MENU_ROW_FORE:
			ds18b20In->changeNumSensor++;
			if(ds18b20In->changeNumSensor > 1)
			{
				ds18b20In->saveNumSensor = 1;
				ds18b20In->changeNumSensor = 0;
			}
			break;
	}
}


