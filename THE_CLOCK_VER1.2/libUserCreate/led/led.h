#ifndef LED_H
#define LED_H

#include "main.h"

typedef enum
{
	LED_TURN_ON_STATE = 0,
	LED_TURN_OFF_STATE
}Led_State_e;

typedef struct
{
	uint32_t Old;
	uint32_t Blink;
}Led_Time_t;

typedef struct
{
	Led_Time_t Time;
	uint8_t Flag;
	
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
}Led_TypDef_t;


void led_init(Led_TypDef_t *ledX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void led_write(Led_TypDef_t *ledX, uint8_t state);

void led_toggle(Led_TypDef_t *ledX);

void led_blink(Led_TypDef_t *ledX, uint32_t time);


#endif


