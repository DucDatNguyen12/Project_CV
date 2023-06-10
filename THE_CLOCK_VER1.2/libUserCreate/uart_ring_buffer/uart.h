#ifndef UART_H
#define UART_H

#include "main.h"

typedef enum
{
	UART_STATE_DISCONNECT = 0,
	UART_STATE_CONNECT
}Uart_State_TypDef_e;

typedef enum
{
	Uart_Baudrate_600 = 0,
	Uart_Baudrate_1200,
	Uart_Baudrate_2400,
	Uart_Baudrate_4800,
	Uart_Baudrate_9600,
	Uart_Baudrate_14400,
	Uart_Baudrate_19200,
	Uart_Baudrate_38400,
	Uart_Baudrate_56000,
	Uart_Baudrate_57600,
	Uart_Baudrate_115200
}Uart_Baudrate_TypDef_e;

typedef enum 
{
	UART_LOST_CONNECT = 0,
	UART_CONNECT
}Uart_Flag_e;

typedef enum
{
	UART_CHANGE_NOT,
	UART_CHANGE
}Uart_Change_e;

typedef struct
{
	uint8_t flag; // have connect / lost connect
	
	uint8_t baudrate, changeBaudrate, saveBaudrate;
}Uart_TypDef_t;

void uart_init( Uart_TypDef_t *uartIn);

#endif

