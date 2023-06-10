#include "uart_lcd_app.h"

#include "string.h"

static Uart_TypDef_t *uartLcd;

void uartLcdApp_init(Uart_TypDef_t *uartIn)
{
	uartLcd = uartIn;
}

void uartLcdApp_update_data_send(char *str)
{
	char _str[] = "      Data      ";
	
	strcpy(str, _str);
}


void uartLcdApp_update_data_receive(char *str)
{
	char _str[] = "      Data      ";
	
	strcpy(str, _str);
}


void uartLcdApp_update_state_conncet(char *str)
{
	char _str[] = "    Disconnect  ";
	uint8_t _posStart = 4;
	
	if(uartLcd->flag == UART_LOST_CONNECT)
	{
		_str[_posStart]   = 'D';
		_str[_posStart+1] = 'i';
		_str[_posStart+2] = 's';
		_str[_posStart+3] = 'c';
		_str[_posStart+4] = 'o';
		_str[_posStart+5] = 'n';
		_str[_posStart+6] = 'n';
		_str[_posStart+7] = 'e';
	  _str[_posStart+8] = 'c';
		_str[_posStart+9] = 't';
	}
	else
	{
		_str[_posStart]   = ' ';
		_str[_posStart+1] = ' ';
		_str[_posStart+2] = ' ';
		_str[_posStart+3] = 'C';
		_str[_posStart+4] = 'o';
		_str[_posStart+5] = 'n';
		_str[_posStart+6] = 'n';
		_str[_posStart+7] = 'e';
	  _str[_posStart+8] = 'c';
		_str[_posStart+9] = 't';
	}
	
	strcpy(str, _str);
}

// baudrate
void uartLcdApp_update_baudrate(char *str)
{
	char _str[] = "                ";
	uint8_t _posStart = 4;
	
	switch(uartLcd->baudrate)
	{
		case Uart_Baudrate_600:
			_str[_posStart]   = ' ';
			_str[_posStart+1] = ' ';
			_str[_posStart+2] = ' ';
			_str[_posStart+3] = '6';
			_str[_posStart+4] = '0';
			_str[_posStart+5] = '0';
			_str[_posStart+6] = 'H';
			_str[_posStart+7] = 'Z';
			break;
		
		case Uart_Baudrate_1200:
			_str[_posStart]   = ' ';
			_str[_posStart+1] = ' ';
			_str[_posStart+2] = '1';
			_str[_posStart+3] = '2';
			_str[_posStart+4] = '0';
			_str[_posStart+5] = '0';
			_str[_posStart+6] = 'H';
			_str[_posStart+7] = 'Z';
			break;
		
		case Uart_Baudrate_2400:
			_str[_posStart]   = ' ';
			_str[_posStart+1] = ' ';
			_str[_posStart+2] = '2';
			_str[_posStart+3] = '4';
			_str[_posStart+4] = '0';
			_str[_posStart+5] = '0';
			_str[_posStart+6] = 'H';
			_str[_posStart+7] = 'Z';
			break;
		
		case Uart_Baudrate_4800:
			_str[_posStart]   = ' ';
			_str[_posStart+1] = ' ';
			_str[_posStart+2] = '4';
			_str[_posStart+3] = '8';
			_str[_posStart+4] = '0';
			_str[_posStart+5] = '0';
			_str[_posStart+6] = 'H';
			_str[_posStart+7] = 'Z';
			break;
		
		case Uart_Baudrate_9600:
			_str[_posStart]   = ' ';
			_str[_posStart+1] = ' ';
			_str[_posStart+2] = '9';
			_str[_posStart+3] = '6';
			_str[_posStart+4] = '0';
			_str[_posStart+5] = '0';
			_str[_posStart+6] = 'H';
			_str[_posStart+7] = 'Z';
			break;
		
		case Uart_Baudrate_14400:
			_str[_posStart]   = ' ';
			_str[_posStart+1] = '1';
			_str[_posStart+2] = '4';
			_str[_posStart+3] = '4';
			_str[_posStart+4] = '0';
			_str[_posStart+5] = '0';
			_str[_posStart+6] = 'H';
			_str[_posStart+7] = 'Z';
			break;
		
		case Uart_Baudrate_19200:
			_str[_posStart]   = ' ';
			_str[_posStart+1] = '1';
			_str[_posStart+2] = '9';
			_str[_posStart+3] = '2';
			_str[_posStart+4] = '0';
			_str[_posStart+5] = '0';
			_str[_posStart+6] = 'H';
			_str[_posStart+7] = 'Z';
			break;
		
		case Uart_Baudrate_38400:
			_str[_posStart]   = ' ';
			_str[_posStart+1] = '3';
			_str[_posStart+2] = '8';
			_str[_posStart+3] = '4';
			_str[_posStart+4] = '0';
			_str[_posStart+5] = '0';
			_str[_posStart+6] = 'H';
			_str[_posStart+7] = 'Z';
			break;
		
		case Uart_Baudrate_56000:
			_str[_posStart]   = ' ';
			_str[_posStart+1] = '5';
			_str[_posStart+2] = '6';
			_str[_posStart+3] = '0';
			_str[_posStart+4] = '0';
			_str[_posStart+5] = '0';
			_str[_posStart+6] = 'H';
			_str[_posStart+7] = 'Z';
			break;
		
		case Uart_Baudrate_57600:
			_str[_posStart]   = ' ';
			_str[_posStart+1] = '5';
			_str[_posStart+2] = '7';
			_str[_posStart+3] = '6';
			_str[_posStart+4] = '0';
			_str[_posStart+5] = '0';
			_str[_posStart+6] = 'H';
			_str[_posStart+7] = 'Z';
			break;
		
		case Uart_Baudrate_115200:
			_str[_posStart]   = '1';
			_str[_posStart+1] = '1';
			_str[_posStart+2] = '5';
			_str[_posStart+3] = '2';
			_str[_posStart+4] = '0';
			_str[_posStart+5] = '0';
			_str[_posStart+6] = 'H';
			_str[_posStart+7] = 'Z';
			break;
	}
	
	strcpy(str, _str);
}

void uartLcdApp_edit_baudrate(char *str)
{
	uint8_t _posStart = 4;
	
	static uint8_t _state = 0;
	_state = 1-_state;
	
	if(_state == 1) return;
	
	str[_posStart]   = ' ';
	str[_posStart+1] = ' ';
	str[_posStart+2] = ' ';
	str[_posStart+3] = ' ';
	str[_posStart+4] = ' ';
	str[_posStart+5] = ' ';
	str[_posStart+6] = ' ';
	str[_posStart+7] = ' ';
}

void uartLcdApp_edit_update_baudrate(char *str)
{
	uartLcdApp_update_baudrate(str);
	
	if(uartLcd->changeBaudrate == 1)
	{
		uartLcdApp_edit_baudrate(str);
	}
}

