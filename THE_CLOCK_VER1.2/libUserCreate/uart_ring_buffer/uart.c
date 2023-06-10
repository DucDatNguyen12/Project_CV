#include "uart.h"

static Uart_TypDef_t *uart;

static void uart_start(void)
{
	uart->flag = UART_STATE_DISCONNECT;
	uart->baudrate = Uart_Baudrate_9600;
}

void uart_init( Uart_TypDef_t *uartIn)
{
	uart = uartIn;
	
	uart_start();
}


