#include "buzzer_led_app.h"

// but_noti_inter: button notify interrupt
void buzzerLedApp_but_noti_inter( Button_TypDef_t *buttonX, 
																	Buzzer_TypDef_t *buzzerX, 
																	Led_TypDef_t *ledX )
{
	if(buttonX->Notify == BUTTON_NOTIFY_NOT)
	{
		return;
	}
	
	if(buttonX->Notify == BUTTON_NOTIFY)
	{
		buttonX->Notify = BUTTON_NOTIFY_NOT;
		
		#ifdef PRODUCT_HAVE_BUZZER
			buzzer_set_number_call(buzzerX, NUMBER_OF_CALL_PRESS_BUTTON, BUZZER_CALL_FAST);
		#endif
		
		#ifndef PRODUCT_HAVE_BUZZER
			led_toggle(ledX);
		#endif
	}
	else if(buttonX->Notify == BUTTON_NOTIFY_KEEP)
	{
		buttonX->Notify = BUTTON_NOTIFY_NOT;
		
		#ifdef PRODUCT_HAVE_BUZZER
			buzzer_set_number_call(buzzerX, NUMBER_OF_CALL_KEEP_BUTTON, BUZZER_CALL_FAST);
		#endif
		
		#ifndef PRODUCT_HAVE_BUZZER
			led_toggle(ledX);
		#endif
	}
}


