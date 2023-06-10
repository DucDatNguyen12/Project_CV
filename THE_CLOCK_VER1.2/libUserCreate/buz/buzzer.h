#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "main.h"

typedef enum 
{
	BUZZER_TURN_OFF_STATE = 0,
	BUZZER_TURN_ON_STATE
}Buzzer_State_e;

typedef enum
{
	BUZZER_CALL_FAST = 10, //100
	BUZZER_CALL_SLOW = 300,
	BUZZER_CALL_LONG_SLOW = 500
}Buzzer_Time_Call_e;

typedef struct
{
	uint32_t Count;
	uint32_t Old;
}Buzzer_Time_t;

typedef struct
{
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
	
	Buzzer_Time_t Time;
	
	uint8_t Flag; // flag activity: turn on/ turn off
	uint8_t NumberOf; // number of call: 1,2,3,4....
	
	uint16_t Mode; // mode call: fast, slow, long_slow
}Buzzer_TypDef_t;

void buzzer_init(Buzzer_TypDef_t *buzzerX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void buzzer_write(Buzzer_TypDef_t *buzzerX, uint8_t state);

void buzzer_set_number_call(Buzzer_TypDef_t *buzzerX, uint32_t number, uint16_t timeCall);

void buzzer_call_blink_interrupt(Buzzer_TypDef_t *buzzerX);

#endif



