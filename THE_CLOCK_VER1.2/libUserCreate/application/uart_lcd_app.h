#ifndef UART_LCD_APP_H
#define UART_LCD_APP_H

#include "main.h"

#include "uart.h"

void uartLcdApp_init(Uart_TypDef_t *uartIn);


void uartLcdApp_update_data_send(char *str);

void uartLcdApp_update_data_receive(char *str);

void uartLcdApp_update_state_conncet(char *str);

void uartLcdApp_edit_update_baudrate(char *str);

#endif


