#ifndef ALARM_APP
#define ALARM_APP

#include "main.h"

#include "ds1307.h"
#include "buzzer.h"

void alarmApp_init(Ds1307_TypDef_t *ds1307In, Buzzer_TypDef_t *buzzerIn);

void AlarmApp_turn_off(void);

void alarmApp_handle_loop(void);

#endif


