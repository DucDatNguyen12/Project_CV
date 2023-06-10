/* An STM32 HAL library written for the DS1307 real-time clock IC. */
#ifndef DS1307_H
#define DS1307_H

#include "main.h"

/*----------------------------------------------------------------------------*/
#define DS1307_I2C_ADDR 	  0x68

#define DS1307_REG_SECOND 	0x00
#define DS1307_REG_MINUTE 	0x01
#define DS1307_REG_HOUR  	  0x02
#define DS1307_REG_DOW    	0x03
#define DS1307_REG_DATE   	0x04
#define DS1307_REG_MONTH  	0x05
#define DS1307_REG_YEAR   	0x06
#define DS1307_REG_CONTROL 	0x07
#define DS1307_REG_UTC_HR	  0x08
#define DS1307_REG_UTC_MIN	0x09
#define DS1307_REG_CENT    	0x10
#define DS1307_REG_RAM   	  0x11

#define DS1307_TIMEOUT		  1000
/*----------------------------------------------------------------------------*/
typedef enum 
{
	DS1307_1HZ, 
	DS1307_4096HZ, 
	DS1307_8192HZ, 
	DS1307_32768HZ
} DS1307_Rate;

typedef enum 
{
	DS1307_DISABLED, 
	DS1307_ENABLED
} DS1307_SquareWaveEnable;

typedef enum
{
	PULSE_1HZ = 0,
	PULSE_4096HZ,
	PULSE_8192HZ,
	PULSE_32768HZ
}Create_Pulse_Rate_e;

typedef enum
{
	PULSE_CHANGE_NOT = 0,
	PULSE_CHANGE_RATE,
	PULSE_CHANGE_FLAG
}Create_Pulse_Change_e;

typedef enum
{
	PULSE_TURN_OFF = 0,
	PULSE_TURN_ON
}Create_Pulse_Flag_e;

typedef enum
{
	RTC_TIME_CHANGE_NOT = 0,
	RTC_TIME_CHANGE_HOUR,
	RTC_TIME_CHANGE_MIN
}TIME_Change_e;

typedef enum
{
	RTC_DATE_CHANGE_NOT = 0,
	RTC_DATE_CHANGE_DOW,
	RTC_DATE_CHANGE_DAY,
	RTC_DATE_CHANGE_MONTH,
	RTC_DATE_CHANGE_YEAR
}DATE_Change_e;

typedef enum
{
	ALARM_CHANGE_NOT = 0,
	ALARM_CHANGE_HOUR,
	ALARM_CHANGE_MIN,
	ALARM_CHANGE_FLAG // TURN ON / TURN OFF
}Alarm_Change_e;

typedef enum
{
	ALARM_TURN_OFF = 0,
	ALARM_TURN_ON
}Alarm_Flag_e;

typedef enum
{
	H24MODE_CHANGE_NOT = 0,
	H24MODE_CHANGE
}Hour24Mode_Change_e;

typedef enum
{
	H24MODE_TURN_OFF = 0,
	H24MODE_TURN_ON
}Hour24Mode_Flag_e;

typedef struct
{
	uint8_t sec, min, hour;
	uint8_t change;
	uint8_t save;
}Time_TypDef_t;

typedef struct
{
	uint8_t dow, // day of week: mon, tus, web, thus...
					date, // day of month 1, 2, 3... 31
					month,
					year;
	uint8_t change;
	uint8_t	save;
}Date_TypDef_t;


typedef struct
{
	uint8_t hour, min;
	
	uint8_t flag;
	uint8_t change;
	uint8_t save;
}Alarm_TypDef_t;

typedef struct
{
	Alarm_TypDef_t A1, A2, A3, A4;
}Multiple_Alarms_TypDef_t;

typedef struct
{
	uint8_t rate;
	uint8_t flag;
	uint8_t change;
	uint8_t save;
}Create_Pulse_TypDef_t;

typedef struct
{
	uint8_t flag;
	uint8_t change;
  uint8_t	save;
}H24Mode_TypDef_t;

typedef struct
{
	uint8_t save;
	
	Time_TypDef_t Time;
	
	Date_TypDef_t Date;
	
	Create_Pulse_TypDef_t CreatePulse;
	
	H24Mode_TypDef_t H24Mode;
					
	Multiple_Alarms_TypDef_t MulAlarm;
	
}Ds1307_TypDef_t;


void ds1307_init(I2C_HandleTypeDef *hi2c) ;

// Root
void DS1307_SetClockHalt(uint8_t halt);
uint8_t DS1307_GetClockHalt(void);

void DS1307_SetRegByte(uint8_t regAddr, uint8_t val);
uint8_t DS1307_GetRegByte(uint8_t regAddr);

void DS1307_SetEnableSquareWave(DS1307_SquareWaveEnable mode);
void DS1307_SetInterruptRate(DS1307_Rate rate);

// Get
int8_t ds1307_get_time_zone_hour(void) ;
uint8_t ds1307_get_time_zone_min(void) ;


uint8_t ds1307_get_day_of_week(void) ;

char *ds1307_get_dow(int num);
uint8_t ds1307_get_day(void) ;
uint8_t ds1307_get_month(void) ;
uint16_t ds1307_get_year(void) ;

uint8_t ds1307_get_hour(void) ;
uint8_t ds1307_get_minute(void) ;
uint8_t ds1307_get_second(void) ;

void ds1307_get_all(Ds1307_TypDef_t *ds1307_X);

// Set
void ds1307_set_time_zone(int8_t hr, uint8_t min);

void ds1307_set_day_of_week(uint8_t dayOfWeek);
void ds1307_set_day(uint8_t date);
void ds1307_set_month(uint8_t month);
void ds1307_set_year(uint16_t year);

void ds1307_set_hour(uint8_t hour_24mode);
void ds1307_set_minute(uint8_t minute);
void ds1307_set_second(uint8_t second);

void ds1307_set_all(Ds1307_TypDef_t *ds1307In);



#endif



