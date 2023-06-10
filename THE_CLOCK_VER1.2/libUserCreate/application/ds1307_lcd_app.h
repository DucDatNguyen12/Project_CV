#ifndef DS1307_APP_H
#define DS1307_APP_H	

#include "main.h"

#include "ds1307.h"
#include "button.h"

void ds1307App_init(Ds1307_TypDef_t *ds1307In);

//rtc-date
void ds1307App_lcd_update_date(char *str);
void ds1307App_lcd_update_edit_date(char *str);

//rtc-time
void ds1307App_lcd_update_time(char *str);
void ds1307App_lcd_update_edit_time(char *str);

//hour 24 mode
void ds1307App_lcd_update_edit_24Mode(char *str);

//pulse
void ds1307App_lcd_update_edit_pulse(char *str);

//alarm
void ds1307LcdApp_alarm_basic(char *str);
void ds1307App_lcd_update_edit_alarm_1(char *str);
void ds1307App_lcd_update_edit_alarm_2(char *str);
void ds1307App_lcd_update_edit_alarm_3(char *str);
void ds1307App_lcd_update_edit_alarm_4(char *str);


#endif


