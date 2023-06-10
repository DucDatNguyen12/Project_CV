#include "alarm_app.h"

#include "buzzer.h"

#include "math.h"

static Ds1307_TypDef_t *ds1307;
static Buzzer_TypDef_t *buzzer; 

uint8_t flagAlarmNew = 0, flagAlarmOld = 0;

void alarmApp_init(Ds1307_TypDef_t *ds1307In, Buzzer_TypDef_t *buzzerIn)
{
	ds1307 = ds1307In;
	buzzer = buzzerIn;
}

static void alarmApp_find(Alarm_TypDef_t *alarm)
{
	if(alarm->flag == ALARM_TURN_OFF || alarm->change != ALARM_CHANGE_NOT)
	{
		return;
	}
		
	if( alarm->hour == ds1307->Time.hour )
	{
		if((ds1307->Time.min >= alarm->min) && ( (ds1307->Time.min - alarm->min) <= 2) ) 
		{
			if(flagAlarmOld == 0 && flagAlarmNew == 0)
			{
				flagAlarmOld = 1;
				flagAlarmNew = 1;
			}
			
			if(flagAlarmNew == 1)
			{
				buzzer_set_number_call(buzzer, 5, BUZZER_CALL_FAST);
			}
			return;
		}
			
		flagAlarmNew = 0;
		flagAlarmOld = 0;
	}
}

void alarmApp_handle_loop(void)
{
	alarmApp_find(&ds1307->MulAlarm.A1);
	alarmApp_find(&ds1307->MulAlarm.A2);
	alarmApp_find(&ds1307->MulAlarm.A3);
	alarmApp_find(&ds1307->MulAlarm.A4);
}

void AlarmApp_turn_off(void)
{
	if(flagAlarmNew == 0) return;
	
	buzzer->NumberOf = 0;
	buzzer_write(buzzer, BUZZER_TURN_OFF_STATE);	
	
	flagAlarmNew = 0;
}
