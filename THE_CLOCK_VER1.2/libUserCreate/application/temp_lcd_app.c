#include "temp_lcd_app.h" 

#include "string.h"

static DS18B20_Name *dsTemp;

void tempLcdApp_init(DS18B20_Name *dsTempIn)
{
	dsTemp = dsTempIn;
}

// tempCur: temp current
void tempLcdApp_update_basic_tempCur(char *str)
{
	uint8_t posStart = 9;
	
	int _temp = dsTemp->tempRead * 100;

	str[posStart]     = _temp/1000       + '0';
	str[posStart + 1] = (_temp%1000)/100 + '0';
	str[posStart + 3] = (_temp%100)/10   + '0';
	str[posStart + 4] = _temp%10         + '0';
}

// tempCur: temp current
void tempLcdApp_update_tempCur(char *str)
{
	char _str[] =  "    00.00 Do    ";
	uint8_t posStart = 4;
	int _temp;
	
	_temp = dsTemp->tempRead * 100;

	_str[posStart]     = _temp/1000       + '0';
	_str[posStart + 1] = (_temp%1000)/100 + '0';
	_str[posStart + 3] = (_temp%100)/10   + '0';
	_str[posStart + 4] = _temp%10         + '0';
	
	strcpy(str, _str);
}

// temp set
static void tempLcdApp_update_temp_set(char *str)
{
	uint8_t _posStart = 6;
	char _str[] =  "      00   *C   ";
	
	_str[_posStart]   = dsTemp->tempSet/10 + '0';
	_str[_posStart+1] = dsTemp->tempSet%10 + '0';
	
	strcpy(str, _str);
}

static void tempLcdApp_edit_temp_set(char *str)
{
	uint8_t _posStart = 6;
	
	static uint8_t _state = 0;
	_state = 1-_state;
	
	if(_state == 1) return;
	
	str[_posStart]   = ' ';
	str[_posStart+1] = ' ';
}

void tempLcdApp_update_edit_temp_set(char *str)
{
	tempLcdApp_update_temp_set(str);
	
	if(dsTemp->changeTempSet == 1)
	{
		tempLcdApp_edit_temp_set(str);
	}
}

// type sensor
void tempLcdApp_type_sensor(char *str)
{
	uint8_t _posStart = 4;
	char _str[] =  "                ";
	
	_str[_posStart]   = 'D';
	_str[_posStart+1] = 'S';
	_str[_posStart+2] = '1';
	_str[_posStart+3] = '8';
	_str[_posStart+4] = 'B';
	_str[_posStart+5] = '2';
	_str[_posStart+6] = '0';
	
	strcpy(str, _str);
}

// number sensor
static void tempLcdApp_update_number_sensor(char *str)
{
	uint8_t _posStart = 7;
	char _str[] =  "       00       ";
	
	_str[_posStart]   = dsTemp->numSensor/10 + '0';
	_str[_posStart+1] = dsTemp->numSensor%10 + '0';
	
	strcpy(str, _str);
}

static void tempLcdApp_edit_number_sensor(char *str)
{
	uint8_t _posStart = 7;
	
	static uint8_t _state = 0;
	_state = 1-_state;
	
	if(_state == 1) return;
	
	str[_posStart]   = ' ';
	str[_posStart+1] = ' ';
}

void tempLcdApp_update_edit_number_sensor(char *str)
{
	tempLcdApp_update_number_sensor(str);
	
	if(dsTemp->changeNumSensor == 1)
	{
		tempLcdApp_edit_number_sensor(str);
	}
}














