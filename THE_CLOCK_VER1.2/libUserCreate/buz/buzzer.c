#include "buzzer.h"

#include "gpio_stm32.h"

void buzzer_init(Buzzer_TypDef_t *buzzerX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	buzzerX->GPIOx = GPIOx;
	buzzerX->GPIO_Pin = GPIO_Pin;
	
	buzzerX->Flag = BUZZER_TURN_OFF_STATE;
	buzzerX->Mode = BUZZER_CALL_LONG_SLOW;
	
	buzzerX->Time.Count = 0;
	buzzerX->Time.Old = 0;
	
	buzzerX->NumberOf = 0;
	
	buzzer_write(buzzerX, buzzerX->Flag);
}

void buzzer_write(Buzzer_TypDef_t *buzzerX, uint8_t state)
{
	buzzerX->Flag = state;
	gpio_write(buzzerX->GPIOx, buzzerX->GPIO_Pin, buzzerX->Flag);
}

void buzzer_set_number_call(Buzzer_TypDef_t *buzzerX, uint32_t number, uint16_t timeCall)
{
	number *= 2;
	
	buzzerX->NumberOf = number;
	
	buzzerX->Mode = timeCall;
}
/*
 numCall: number of call
 time: time stop betwen call
*/
void buzzer_call_blink_interrupt(Buzzer_TypDef_t *buzzerX)
{
	if(buzzerX->NumberOf != 0)
	{
		buzzerX->Time.Count++;
		if(buzzerX->Time.Count - buzzerX->Time.Old > buzzerX->Mode)
		{
			buzzerX->Time.Old = buzzerX->Time.Count;
			
			buzzerX->NumberOf--;
			if(buzzerX->NumberOf %2 == 0)	
			{
				buzzer_write(buzzerX, BUZZER_TURN_OFF_STATE);
			}
			else 
			{	
				buzzer_write(buzzerX, BUZZER_TURN_ON_STATE);
			}
		}
	}
}

