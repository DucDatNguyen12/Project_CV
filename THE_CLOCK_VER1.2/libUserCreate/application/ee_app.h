#ifndef EE_APP_H
#define EE_APP_H

#include "main.h"

#include "ds1307.h"
#include "ds18b20.h"
#include "uart.h"

#define ADD_RTC 2 // save 3 position

#define ADD_TEMP 5 // save 2 position

#define ADD_UART_BAUDRATE 7 // save 1 position

#define ADD_ALARM_1 8  // save 3 position
#define ADD_ALARM_2 11 // save 3 position
// address 16 errer
#define ADD_ALARM_3 17 // save 3 position
#define ADD_ALARM_4 20 // save 3 position

#define TIME_EE24 200

typedef enum
{
	SAVE_PULSE_OK = 0,
	S_RATE_PULSE,
	S_FLAG_PULSE,
}EeApp_TypDef_E;

typedef struct
{
	uint8_t createPulse;
	
}EeApp_Ds1307_TypDef_t;

typedef struct
{
	EeApp_Ds1307_TypDef_t ds1307;
}EeApp_TypDef_t;

typedef void (*eeApp_func_t)();

void eeApp_init(Ds1307_TypDef_t *ds1307In, DS18B20_Name *ds18b20In, Uart_TypDef_t *uartIn);

void eeApp_start(void);

void eeApp_handle_loop(void);

#endif


