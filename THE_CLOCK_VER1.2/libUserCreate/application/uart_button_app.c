#include "uart_button_app.h"

#include "uart.h"

static void value_incre(uint8_t *value)
{
	(*value)++;
	if((*value) > Uart_Baudrate_115200)
	{
		(*value) = Uart_Baudrate_600;
	}
}

static void value_decre(uint8_t *value)
{
	if((*value) > Uart_Baudrate_600)
	{
		(*value)--;
	}
}

void uart_button_incre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, Uart_TypDef_t *uartIn)
{
	if(lcdMenuIn->level != MENU_LEVEL_FINISH)	return;
	if(lcdMenuIn->count_1 != MENU_ROW_FORE) return;
	
	switch(lcdMenuIn->count_2)
	{
		case MENU_ROW_ONE:
			
			break;
		
		case MENU_ROW_TWO:
			
			break;
		
		case MENU_ROW_THREE:
			
			break;
		
		case MENU_ROW_FORE:
			if(uartIn->changeBaudrate == UART_CHANGE)
			{
				value_incre(&uartIn->baudrate);
			}
			break;
	}
}

void uart_button_decre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, Uart_TypDef_t *uartIn)
{
	if(lcdMenuIn->level != MENU_LEVEL_FINISH)	return;
	if(lcdMenuIn->count_1 !=  MENU_ROW_FORE) return;
	
	switch(lcdMenuIn->count_2)
	{
		case  MENU_ROW_ONE:
			
			break;
		
		case  MENU_ROW_TWO:
			
			break;
		
		case  MENU_ROW_THREE:
			
			break;
		
		case  MENU_ROW_FORE:
			if(uartIn->changeBaudrate == UART_CHANGE)
			{
				value_decre(&uartIn->baudrate);
			}
			break;
	}
}

void uart_button_slow(Lcd_Menu_TypDef_t *lcdMenuIn, Uart_TypDef_t *uartIn)
{
	if(lcdMenuIn->level !=  MENU_LEVEL_FINISH)	return;
	if(lcdMenuIn->count_1 !=  MENU_ROW_FORE) return;
	
	switch(lcdMenuIn->count_2)
	{
		case  MENU_ROW_ONE:
			
			break;
		
		case  MENU_ROW_TWO:
			
			break;
		
		case  MENU_ROW_THREE:
			
			break;
		
		case  MENU_ROW_FORE:
			uartIn->changeBaudrate++;
			if(uartIn->changeBaudrate > UART_CHANGE)
			{
				uartIn->saveBaudrate = 1;
				
				uartIn->changeBaudrate = UART_CHANGE_NOT;
			}
			break;
	}
}




