#include "led.h"

#include "gpio_stm32.h"

// init led single 3mm->5mm
void led_init(Led_TypDef_t *ledX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	ledX->Time.Blink = 0;
	ledX->Time.Old = 0;
	ledX->Flag = 0;
	
	ledX->GPIOx = GPIOx;
	ledX->GPIO_Pin = GPIO_Pin;
}

// write level logic 0 or 1
void led_write(Led_TypDef_t *ledX, uint8_t state)
{	
	if(state == LED_TURN_ON_STATE)
	{
		gpio_write(ledX->GPIOx, ledX->GPIO_Pin, state);
	}
	else if(state == LED_TURN_OFF_STATE)
	{
		gpio_write(ledX->GPIOx, ledX->GPIO_Pin, state);
	}
}	

void led_toggle(Led_TypDef_t *ledX)
{
	gpio_toggle(ledX->GPIOx, ledX->GPIO_Pin);
}

// time: after time ms led will change state
void led_blink(Led_TypDef_t *ledX, uint32_t time)
{
	if(ledX->Time.Blink != time)
	{
		ledX->Time.Blink = time;
	}
	
	if(HAL_GetTick() - ledX->Time.Old > ledX->Time.Blink)
	{
		ledX->Time.Old = HAL_GetTick();
		
		ledX->Flag = 1 - ledX->Flag;
		
		led_write(ledX, ledX->Flag);
	}
}


