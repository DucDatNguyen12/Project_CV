#ifndef BUZZER_LED_APP_H
#define BUZZER_LED_APP_H

#include "main.h"

#include "buzzer.h"
#include "led.h"
#include "button.h"

#define PRODUCT_HAVE_BUZZER

#define NUMBER_OF_CALL_PRESS_BUTTON 1
#define NUMBER_OF_CALL_KEEP_BUTTON  2

void buzzerLedApp_but_noti_inter( Button_TypDef_t *buttonX, 
																	Buzzer_TypDef_t *buzzerX, 
																	Led_TypDef_t *ledX );

#endif

