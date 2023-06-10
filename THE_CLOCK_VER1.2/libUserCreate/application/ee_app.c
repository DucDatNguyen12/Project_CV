#include "ee_app.h"

#include "string.h"

#include "ee.h"

eeApp_func_t eeApp_func = NULL;

static Ds1307_TypDef_t *ds1307;
static DS18B20_Name *ds18b20;
static Uart_TypDef_t *uart;

EeApp_TypDef_t eeApp1;

void eeApp_ds1307_write(void)
{
	if(ds1307->save == 1)
	{
		ds1307->save = 0;
	}
	else
	{
		return;
	}
	
	uint8_t _dataTemp[3];
	
	if(ds1307->Time.save == 1)
	{
		ds1307->Time.save = 0;
		
		ds1307_set_hour(ds1307->Time.hour);
		ds1307_set_minute(ds1307->Time.min);
		ds1307_set_second(0); 
		
		return;
	}
	
	if(ds1307->Date.save == 1)
	{
		ds1307->Date.save = 0;
		
		ds1307_set_day_of_week(ds1307->Date.dow);
		ds1307_set_day(ds1307->Date.date);
		ds1307_set_month(ds1307->Date.month);
		ds1307_set_year(ds1307->Date.year);
		
		return;
	}
	
	if(	ds1307->H24Mode.save == 1 
			|| (ds1307->CreatePulse.save == 1) )
	{
		ds1307->H24Mode.save = 0;
		ds1307->CreatePulse.save = 0;
		
		_dataTemp[0] = ds1307->H24Mode.flag;
		_dataTemp[1] = ds1307->CreatePulse.rate;
		_dataTemp[2] = ds1307->CreatePulse.flag;
		
		ee24_write(ADD_RTC, _dataTemp, 3, 1000);
		
		return;
	}
		
	if(ds1307->MulAlarm.A1.save == 1)
	{
		ds1307->MulAlarm.A1.save = 0;
		
		_dataTemp[0] = ds1307->MulAlarm.A1.hour;
		_dataTemp[1] = ds1307->MulAlarm.A1.min;
		_dataTemp[2] = ds1307->MulAlarm.A1.flag;
		
		ee24_write(ADD_ALARM_1, _dataTemp, 3, 1000);
		
		return;
	}
	
	if(ds1307->MulAlarm.A2.save == 1)
	{
		ds1307->MulAlarm.A2.save = 0;
		
		_dataTemp[0] = ds1307->MulAlarm.A2.hour;
		_dataTemp[1] = ds1307->MulAlarm.A2.min;
		_dataTemp[2] = ds1307->MulAlarm.A2.flag;
		
		ee24_write(ADD_ALARM_2, _dataTemp, 3, 1000);
		
		return;
	}
	
	if(ds1307->MulAlarm.A3.save == 1)
	{
		ds1307->MulAlarm.A3.save = 0;
		
		_dataTemp[0] = ds1307->MulAlarm.A3.hour;
		_dataTemp[1] = ds1307->MulAlarm.A3.min;
		_dataTemp[2] = ds1307->MulAlarm.A3.flag;
		
		ee24_write(ADD_ALARM_3, _dataTemp, 3, 1000);
		
		return;
	}
	
	if(ds1307->MulAlarm.A4.save == 1)
	{
		ds1307->MulAlarm.A4.save = 0;
		
		_dataTemp[0] = ds1307->MulAlarm.A4.hour;
		_dataTemp[1] = ds1307->MulAlarm.A4.min;
		_dataTemp[2] = ds1307->MulAlarm.A4.flag;
		
		ee24_write(ADD_ALARM_4, _dataTemp, 3, 1000);
		
		return;
	}
}

void eeApp_ds18b20_write(void)
{
	uint8_t _dataTemp[2];
	
	_dataTemp[0] = ds18b20->tempSet;
	_dataTemp[1] = ds18b20->numSensor;
	
	if(ds18b20->saveTempSet == 1 || ds18b20->saveNumSensor == 1)
	{
		ds18b20->saveTempSet = 0;
		ds18b20->saveNumSensor = 0;
		
		ee24_write(ADD_TEMP, _dataTemp, 2, 1000);
	}
}

void eeApp_uart_write(void)
{
	uint8_t _dataTemp[1];
	
	 _dataTemp[0] = uart->baudrate;
	if(uart->saveBaudrate == 1)
	{
		uart->saveBaudrate = 0;
		
		ee24_write(ADD_UART_BAUDRATE,  _dataTemp, 1, 1000);
	}
}

void eeApp_ds1307_read(void)
{
	uint8_t _dataTemp[3];
	
	ee24_read(ADD_RTC, _dataTemp, 3, 1000);
	//
	HAL_Delay(TIME_EE24);
	
	ds1307->H24Mode.flag = _dataTemp[0];
	ds1307->CreatePulse.rate  = _dataTemp[1];
	ds1307->CreatePulse.flag  = _dataTemp[2];
}

static void alarm_read(uint16_t add, uint8_t *hour, uint8_t *min, uint8_t *flag)
{
	uint8_t _dataTemp[3];
	
	ee24_read(add, _dataTemp, 3, 1000);
	HAL_Delay(TIME_EE24);
	
	(*hour) = _dataTemp[0];
	(*min)  = _dataTemp[1];
	(*flag) = _dataTemp[2];
	
	return;
}

void eeApp_alarm_read(void)
{	
	alarm_read(ADD_ALARM_1, &ds1307->MulAlarm.A1.hour, &ds1307->MulAlarm.A1.min, &ds1307->MulAlarm.A1.flag);
	
	alarm_read(ADD_ALARM_2, &ds1307->MulAlarm.A2.hour, &ds1307->MulAlarm.A2.min, &ds1307->MulAlarm.A2.flag);
	
	alarm_read(ADD_ALARM_3, &ds1307->MulAlarm.A3.hour, &ds1307->MulAlarm.A3.min, &ds1307->MulAlarm.A3.flag);
	
	alarm_read(ADD_ALARM_4, &ds1307->MulAlarm.A4.hour, &ds1307->MulAlarm.A4.min, &ds1307->MulAlarm.A4.flag);
}

void eeApp_ds18b20_read(void)
{
	uint8_t _dataTemp[2];
	
	HAL_Delay(TIME_EE24);
	//
	ee24_read(ADD_TEMP, _dataTemp, 2, 1000);
	//
	HAL_Delay(TIME_EE24);
	
	ds18b20->tempSet = _dataTemp[0];
	ds18b20->numSensor = _dataTemp[1];
}

void eeApp_uart_read(void)
{
	HAL_Delay(TIME_EE24);
	//
	ee24_read(ADD_UART_BAUDRATE, &uart->baudrate, 1, 1000);
	//
	HAL_Delay(TIME_EE24);
}

void eeApp_init(Ds1307_TypDef_t *ds1307In, DS18B20_Name *ds18b20In, Uart_TypDef_t *uartIn)
{
	ds1307 = ds1307In;
	ds18b20 = ds18b20In;
	uart = uartIn;
}

void eeApp_start(void)
{
	eeApp_ds1307_read();
	
	eeApp_alarm_read();
	
	eeApp_ds18b20_read();
	
	eeApp_uart_read();
}

void eeApp_handle_loop(void)
{
	eeApp_ds1307_write();

	eeApp_ds18b20_write();

	eeApp_uart_write();
}




