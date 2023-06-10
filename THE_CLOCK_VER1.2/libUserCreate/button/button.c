#include "button.h"

#include "gpio_stm32.h"

up_handle_fast_t up_handle_fast = NULL;
up_handle_slow_t up_handle_slow = NULL;
up_handle_long_slow_t up_handle_long_slow = NULL;
up_handle_keep_t up_handle_keep = NULL;
//
down_handle_fast_t down_handle_fast = NULL;
down_handle_slow_t down_handle_slow = NULL;
down_handle_long_slow_t down_handle_long_slow = NULL;
down_handle_keep_t down_handle_keep = NULL;
//
void up_button_set_handle_fast(void *functionIn)
{
	up_handle_fast = functionIn;
}

void up_button_set_handle_slow(void *functionIn)
{
	up_handle_slow = functionIn;
}

void up_button_set_handle_long_slow(void *functionIn)
{
	up_handle_long_slow = functionIn;
}

void up_button_set_handle_keep(void *functionIn)
{
	up_handle_keep = functionIn;
}
//
void down_button_set_handle_fast(void *functionIn)
{
	down_handle_fast = functionIn;
}

void down_button_set_handle_slow(void *functionIn)
{
	down_handle_slow = functionIn;
}

void down_button_set_handle_long_slow(void *functionIn)
{
	down_handle_long_slow = functionIn;
}

void down_button_set_handle_keep(void *functionIn)
{
	down_handle_keep = functionIn;
}
//
void button_init(Button_TypDef_t *buttonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	buttonX->Count = 0;
	
	buttonX->Flag = BUTTON_NOTHING;
	
	buttonX->Notify = 0;
	
	buttonX->GPIOx = GPIOx;
	buttonX->GPIO_Pin = GPIO_Pin;
}

void button_press(Button_TypDef_t *buttonX)
{	
	if( gpio_read(buttonX->GPIOx, buttonX->GPIO_Pin) == BUTTON_PRESS_STATE )
	{
		buttonX->Count++;
		
		if (buttonX->Count == 50) 
		{
			buttonX->Count = 0;
			buttonX->Flag = BUTTON_PRESSED;
		}
	}
}

void button_clean_press(Button_TypDef_t *buttonX)
{
	buttonX->Count = 0;
	buttonX->Flag = BUTTON_NOTHING;
}

// time <1s
void button_release_fast(Button_TypDef_t *buttonX)
{
	if ( (buttonX->Count < TIME_PRESS_SLOW) && (buttonX->Count != 0))
	{
		buttonX->Flag = BUTTON_FAST;
	}
}

// time 1-3s
void button_release_slow(Button_TypDef_t *buttonX)
{	
	if( (buttonX->Count >= TIME_PRESS_SLOW) && (buttonX->Count < TIME_PRESS_LONG_SLOW ) )
	{
		buttonX->Flag = BUTTON_SLOW;
	}
}

// time 3-5s
void button_release_long_slow(Button_TypDef_t *buttonX)
{
	if( (buttonX->Count>=TIME_PRESS_LONG_SLOW) && (buttonX->Count < TIME_PRESS_KEEP ) )
	{
		buttonX->Flag = BUTTON_LONG_SLOW;
	}
}

// time >5s
void button_keep(Button_TypDef_t *buttonX)
{
	if( buttonX->Count >= TIME_PRESS_KEEP )
	{
		buttonX->Flag = BUTTON_KEEP;
	}
}

void button_notify(Button_TypDef_t *buttonX)
{
	if( (buttonX->Count == TIME_PRESS_FAST)
			|| (buttonX->Count == TIME_PRESS_SLOW)
			|| (buttonX->Count == TIME_PRESS_LONG_SLOW) )
	{
		buttonX->Notify = BUTTON_NOTIFY;
	}
	else if(buttonX->Count == TIME_PRESS_KEEP)
	{
		buttonX->Notify = BUTTON_NOTIFY_KEEP;
	}
}

/* 
	 Call in interrupt function timer with T = 1ms 
*/
void button_check_press_interrupt(Button_TypDef_t *buttonX)
{
	if( buttonX->Flag == BUTTON_NOTHING )
	{
		button_press(buttonX);
	}
	else if( buttonX->Flag == BUTTON_PRESSED )
	{
		buttonX->Count++;
		
		if( gpio_read(buttonX->GPIOx, buttonX->GPIO_Pin) == BUTTON_RELEASE_STATE )
		{
			button_release_fast(buttonX);
			button_release_slow(buttonX);
			button_release_long_slow(buttonX);
		}
		
		button_keep(buttonX);
		
		button_notify(buttonX);			
	}
	else if( buttonX->Flag == BUTTON_HANDLE_OK )
	{
		if( gpio_read(buttonX->GPIOx, buttonX->GPIO_Pin) == BUTTON_RELEASE_STATE )
		{
			button_clean_press(buttonX);
		}
	}
}

void up_button_handle_loop(Button_TypDef_t *buttonX)
{
	if(buttonX->Flag == BUTTON_NOTHING)
	{
		return;
	}
	
	if(buttonX->Flag == BUTTON_FAST)
	{
		up_handle_fast();
		
		buttonX->Flag = BUTTON_HANDLE_OK;
	}
	else if(buttonX->Flag == BUTTON_SLOW)
	{
		up_handle_slow();
		
		buttonX->Flag = BUTTON_HANDLE_OK;
	}
	else if(buttonX->Flag == BUTTON_LONG_SLOW)
	{
		up_handle_long_slow();
		
		buttonX->Flag = BUTTON_HANDLE_OK;
	}
	else if(buttonX->Flag == BUTTON_KEEP)
	{
		up_handle_keep();
		
		buttonX->Flag = BUTTON_HANDLE_OK;
	}	
}

void down_button_handle_loop(Button_TypDef_t *buttonX)
{
	if(buttonX->Flag == BUTTON_NOTHING)
	{
		return;
	}
	
	if(buttonX->Flag == BUTTON_FAST)
	{
		down_handle_fast();
		
		buttonX->Flag = BUTTON_HANDLE_OK;
	}
	else if(buttonX->Flag == BUTTON_SLOW)
	{
		down_handle_slow();
		
		buttonX->Flag = BUTTON_HANDLE_OK;
	}
	else if(buttonX->Flag == BUTTON_LONG_SLOW)
	{
		down_handle_long_slow();
		
		buttonX->Flag = BUTTON_HANDLE_OK;
	}
	else if(buttonX->Flag == BUTTON_KEEP)
	{
		down_handle_keep();
		
		buttonX->Flag = BUTTON_HANDLE_OK;
	}	
}






