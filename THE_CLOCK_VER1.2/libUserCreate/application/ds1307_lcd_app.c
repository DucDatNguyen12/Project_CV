#include "ds1307_lcd_app.h"

#include "string.h"

static Ds1307_TypDef_t *ds1307_app;
#define rtcX ds1307_app

extern char codeDayOfWeek[7][4];

void ds1307App_init(Ds1307_TypDef_t *ds1307In)
{
	ds1307_app = ds1307In;
}

// ds1307 date
void ds1307App_lcd_update_date(char *str)
{
	char _str[] =  "000, 00/00/2000 ";
	
	if(rtcX->Date.dow > 0)
	{
		_str[0] = codeDayOfWeek[rtcX->Date.dow-1][0];
		_str[1] = codeDayOfWeek[rtcX->Date.dow-1][1];
		_str[2] = codeDayOfWeek[rtcX->Date.dow-1][2];
	}
	
	_str[5] = (int)rtcX->Date.date/10 + '0';
	_str[6] = (int)rtcX->Date.date%10 + '0';

	_str[8] = rtcX->Date.month/10 + '0';
	_str[9] = rtcX->Date.month%10 + '0';
	
	_str[13] = rtcX->Date.year/10 + '0';
	_str[14] = rtcX->Date.year%10 + '0';
	
	strcpy(str, _str);
}

void ds1307App_lcd_edit_date(char *_str)
{
	static uint8_t _state = 0;
	_state = 1-_state;
	
	if(_state == 1) return;
	
	switch(rtcX->Date.change)
	{
		case RTC_DATE_CHANGE_DOW:
			_str[0] = ' ';
			_str[1] = ' ';
			_str[2] = ' ';
			break;
		case RTC_DATE_CHANGE_DAY: 
			_str[5] = ' ';
			_str[6] = ' ';
			break;
		
		case RTC_DATE_CHANGE_MONTH: 
			_str[8] = ' ';
			_str[9] = ' ';
			break;
		
		case RTC_DATE_CHANGE_YEAR: 
			_str[13] = ' ';
			_str[14] = ' ';
			break;
	}
}

void ds1307App_lcd_update_edit_date(char *str)
{
	ds1307App_lcd_update_date(str);
	
	if(rtcX->Date.change != RTC_DATE_CHANGE_NOT)
	{
		ds1307App_lcd_edit_date(str);
	}
}

// ds1307 time
void ds1307App_lcd_update_time(char *str)
{
	uint8_t _posStart = 4; 
	char _str[] = "    00:00:00    ";
	                              
	_str[_posStart]   = rtcX->Time.hour/10 + '0';
	_str[_posStart+1] = rtcX->Time.hour%10 + '0';
	
	_str[_posStart+3] = rtcX->Time.min/10 + '0';
	_str[_posStart+4] = rtcX->Time.min%10 + '0';
	
	_str[_posStart+6] = rtcX->Time.sec/10 + '0';
	_str[_posStart+7] = rtcX->Time.sec%10 + '0';
	
	strcpy(str, _str);
}

void ds1307App_lcd_edit_time(char *_str)
{
	uint8_t _posStart = 4;                             
	
	static uint8_t _state = 0;
	_state = 1 - _state;
	
	if(_state == 1) return;
	
	switch(rtcX->Time.change)
	{
		case RTC_TIME_CHANGE_HOUR:
			_str[_posStart]   = ' ';
			_str[_posStart+1] = ' ';
			break;
			
		case RTC_TIME_CHANGE_MIN:
			_str[_posStart+3] = ' ';
			_str[_posStart+4] = ' ';
			break;
	}
}

void ds1307App_lcd_update_edit_time(char *str)
{
	ds1307App_lcd_update_time(str);
	
	if(rtcX->Time.change != RTC_TIME_CHANGE_NOT)
	{
		ds1307App_lcd_edit_time(str);
	}
}

// ds1307 hour 24 mode
void ds1307App_lcd_update_24Mode(char *str)
{
	uint8_t _posStart = 6; 
	char _str[] = "      ON        ";
	 
	if(rtcX->H24Mode.flag == H24MODE_TURN_ON)
	{
		_str[_posStart]   = 'O';
		_str[_posStart+1] = 'N';
		_str[_posStart+2] = ' ';
	}
	else
	{
		_str[_posStart]   = 'O';
		_str[_posStart+1] = 'F';
		_str[_posStart+2] = 'F';
	}
	
	strcpy(str, _str);
}

void ds1307App_lcd_edit_24Mode(char *_str)
{
	uint8_t _posStart = 6;                             
	
	static uint8_t _state = 0;
	_state = 1 - _state;
	
	if(_state == 1) return;
	
	_str[_posStart]   = ' ';
	_str[_posStart+1] = ' ';
	_str[_posStart+2] = ' ';
}

void ds1307App_lcd_update_edit_24Mode(char *str)
{
	ds1307App_lcd_update_24Mode(str);
	
	if(rtcX->H24Mode.change == H24MODE_CHANGE)
	{
		ds1307App_lcd_edit_24Mode(str);
	}
}

// Pulse
void ds1307App_lcd_update_pulse(char *str)
{
	uint8_t _posStart1 = 2, _posStart2 = 12; 

	char _str[] = "  32768HZ - ON  ";
	 
	// pulse
	switch(rtcX->CreatePulse.rate)
	{
		case PULSE_1HZ:
			_str[_posStart1]   = ' ';
			_str[_posStart1+1] = ' ';
			_str[_posStart1+2] = ' ';
			_str[_posStart1+3] = ' ';
			_str[_posStart1+4] = '1';
			_str[_posStart1+5] = 'H';
			_str[_posStart1+6] = 'Z';
			
			break;
		
		case PULSE_4096HZ:
			_str[_posStart1]   = ' ';
			_str[_posStart1+1] = '4';
			_str[_posStart1+2] = '0';
			_str[_posStart1+3] = '9';
			_str[_posStart1+4] = '6';
			_str[_posStart1+5] = 'H';
			_str[_posStart1+6] = 'Z';
			break;
		
		case PULSE_8192HZ:
			_str[_posStart1]   = ' ';
			_str[_posStart1+1] = '8';
			_str[_posStart1+2] = '1';
			_str[_posStart1+3] = '9';
			_str[_posStart1+4] = '2';
			_str[_posStart1+5] = 'H';
			_str[_posStart1+6] = 'Z';
			break;
		
		case PULSE_32768HZ:
			_str[_posStart1]   = '3';
			_str[_posStart1+1] = '2';
			_str[_posStart1+2] = '7';
			_str[_posStart1+3] = '6';
			_str[_posStart1+4] = '8';
			_str[_posStart1+5] = 'H';
			_str[_posStart1+6] = 'Z';
			break;
	}
	// flag
	switch(rtcX->CreatePulse.flag)
	{
		case PULSE_TURN_OFF:
			_str[_posStart2]   = 'O';
			_str[_posStart2+1] = 'F';
			_str[_posStart2+2] = 'F';
			break;
		
		case PULSE_TURN_ON:
			_str[_posStart2]   = 'O';
			_str[_posStart2+1] = 'N';
			_str[_posStart2+2] = ' ';
			break;
	}
	
	
	strcpy(str, _str);
}

void ds1307App_lcd_edit_pulse(char *_str)
{
	uint8_t _posStart1 = 2, _posStart2 = 12;                             
	
	static uint8_t _state = 0;
	_state = 1 - _state;
	
	if(_state == 1) return;
	
	switch(rtcX->CreatePulse.change)
	{
		case PULSE_CHANGE_RATE:
			_str[_posStart1]   = ' ';
			_str[_posStart1+1] = ' ';
			_str[_posStart1+2] = ' ';
			_str[_posStart1+3] = ' ';
			_str[_posStart1+4] = ' ';
			_str[_posStart1+5] = ' ';
			_str[_posStart1+6] = ' ';
			break;
		
		case PULSE_CHANGE_FLAG:
			_str[_posStart2]   = ' ';
			_str[_posStart2+1] = ' ';
			_str[_posStart2+2] = ' ';
			break;
	}
}

void ds1307App_lcd_update_edit_pulse(char *str)
{
	ds1307App_lcd_update_pulse(str);
	
	if(rtcX->CreatePulse.change != PULSE_CHANGE_NOT)
	{
		ds1307App_lcd_edit_pulse(str);
	}
}

// alarm
void ds1307LcdApp_alarm_basic(char *str)
{
	uint8_t _posStart = 0;
	char _str[] = "00000    00.00*C"; 
	
	if( (rtcX->MulAlarm.A1.flag == ALARM_TURN_OFF)
			&& (rtcX->MulAlarm.A2.flag ==  ALARM_TURN_OFF)
			&& (rtcX->MulAlarm.A3.flag ==  ALARM_TURN_OFF)
			&& (rtcX->MulAlarm.A4.flag ==  ALARM_TURN_OFF) )
	{
		_str[_posStart]   = 'O';
		_str[_posStart+1] = 'F';
		_str[_posStart+2] = 'F';
		_str[_posStart+3] = ' ';
		_str[_posStart+4] = ' ';
	}
	else
	{
		_str[_posStart]   = 'O';
		_str[_posStart+1] = 'N';
		_str[_posStart+2] = ' ';
		_str[_posStart+3] = ' ';
		_str[_posStart+4] = ' ';
	}
	
	strcpy(str, _str);
}

static void ds1307App_lcd_update_alarm(char *str, uint8_t hour, uint8_t min, uint8_t flag)
{
	uint8_t _posStart1 = 1, _posStart2 = 12; 
	char _str[] = " 00:00:00   OFF ";
	
	_str[_posStart1]   = hour/10 + '0';
	_str[_posStart1+1] = hour%10 + '0';
	
	_str[_posStart1+3] = min/10 + '0';
	_str[_posStart1+4] = min%10 + '0';
	
	switch(flag)
	{
		case ALARM_TURN_OFF:
			_str[_posStart2]   = 'O';
			_str[_posStart2+1] = 'F';
			_str[_posStart2+2] = 'F';
			break;
		
		case ALARM_TURN_ON:
			_str[_posStart2]   = 'O';
			_str[_posStart2+1] = 'N';
			_str[_posStart2+2] = ' ';
			break;
	}
	
	strcpy(str, _str);
}

static void ds1307App_lcd_edit_alarm(char *_str, uint8_t change)
{
	uint8_t _posStart1 = 1, _posStart2 = 12;                 
	
	static uint8_t _state = 0;
	_state = 1 - _state;
	
	if(_state == 1) return;
	
	switch(change)
	{
		case ALARM_CHANGE_NOT:
			
			break;
		
		case ALARM_CHANGE_HOUR:
			_str[_posStart1]   = ' ';
			_str[_posStart1+1] = ' ';
			break;
			
		case ALARM_CHANGE_MIN:
			_str[_posStart1+3] = ' ';
			_str[_posStart1+4] = ' ';
			break;
		
		case ALARM_CHANGE_FLAG:
			_str[_posStart2]   = ' ';
			_str[_posStart2+1] = ' ';
			_str[_posStart2+2] = ' ';
			break;
	}
}

void ds1307App_lcd_update_edit_alarm_1(char *str)
{
	ds1307App_lcd_update_alarm(str, rtcX->MulAlarm.A1.hour, rtcX->MulAlarm.A1.min, rtcX->MulAlarm.A1.flag);
	
	if( rtcX->MulAlarm.A1.change != ALARM_CHANGE_NOT)
	{
		ds1307App_lcd_edit_alarm(str, rtcX->MulAlarm.A1.change);
	}
}

void ds1307App_lcd_update_edit_alarm_2(char *str)
{
	ds1307App_lcd_update_alarm(str, rtcX->MulAlarm.A2.hour, rtcX->MulAlarm.A2.min, rtcX->MulAlarm.A2.flag);
	
	if( rtcX->MulAlarm.A2.change != ALARM_CHANGE_NOT)
	{
		ds1307App_lcd_edit_alarm(str, rtcX->MulAlarm.A2.change);
	}
}

void ds1307App_lcd_update_edit_alarm_3(char *str)
{
	ds1307App_lcd_update_alarm(str, rtcX->MulAlarm.A3.hour, rtcX->MulAlarm.A3.min, rtcX->MulAlarm.A3.flag);
	
	if( rtcX->MulAlarm.A3.change != ALARM_CHANGE_NOT)
	{
		ds1307App_lcd_edit_alarm(str, rtcX->MulAlarm.A3.change);
	}
}

void ds1307App_lcd_update_edit_alarm_4(char *str)
{
	ds1307App_lcd_update_alarm(str, rtcX->MulAlarm.A4.hour, rtcX->MulAlarm.A4.min, rtcX->MulAlarm.A4.flag);
	
	if( rtcX->MulAlarm.A4.change != ALARM_CHANGE_NOT)
	{
		ds1307App_lcd_edit_alarm(str, rtcX->MulAlarm.A4.change);
	}
}










