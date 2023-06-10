#ifndef UART_BUTTON_APP_H
#define UART_BUTTON_APP_H

#include "main.h"

#include "lcd_menu.h"
#include "uart.h"

void uart_button_incre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, Uart_TypDef_t *uartIn);

void uart_button_decre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, Uart_TypDef_t *uartIn);

void uart_button_slow(Lcd_Menu_TypDef_t *lcdMenuIn, Uart_TypDef_t *uartIn);

#endif


