#include "ds1307_button_app.h"

// loc: location
// incre: increment
static uint8_t date_edit_incre(uint8_t loc, uint8_t value)
{
	value++;
	switch(loc)
	{
		case RTC_DATE_CHANGE_DOW:
			if(value>7) value = 1;
			break;
		case RTC_DATE_CHANGE_DAY:
			if(value>31)	value = 1;
			break;
		case RTC_DATE_CHANGE_MONTH:
			if(value>12)	value = 1;
			break;
		case RTC_DATE_CHANGE_YEAR:
			if(value>99) value = 0;
			break;
	}
	
	return value;
}

static uint8_t time_edit_incre(uint8_t loc, uint8_t value)
{
	value++;
	switch(loc)
	{
		case RTC_TIME_CHANGE_HOUR:
			if(value>23) value = 0;
			break;
		case RTC_TIME_CHANGE_MIN:
			if(value>59) value = 0;
			break;
	}
	
	return value;
}

static uint8_t date_edit_decre(uint8_t loc, uint8_t value)
{
	switch(loc)
	{
		case RTC_DATE_CHANGE_DOW:
			if(value>1) value--;
			break;
		case RTC_DATE_CHANGE_DAY:
			if(value>1)	value--;
			break;
		case RTC_DATE_CHANGE_MONTH:
			if(value>1)	value--;
			break;
		case RTC_DATE_CHANGE_YEAR:
			if(value>0) value--;
			break;
	}
	
	return value;
}

static uint8_t time_edit_decre(uint8_t loc, uint8_t value)
{
	switch(loc)
	{
		case RTC_TIME_CHANGE_HOUR:
			if(value>0) value--;
			break;
		case RTC_TIME_CHANGE_MIN:
			if(value>0) value--;
			break;
	}
	
	return value;
}

static void date_update_incre(Ds1307_TypDef_t* ds1307X)
{
	switch(ds1307X->Date.change)
	{
		case RTC_DATE_CHANGE_DOW:
			ds1307X->Date.dow = date_edit_incre(ds1307X->Date.change, ds1307X->Date.dow);
			break;
		
		case RTC_DATE_CHANGE_DAY:
			ds1307X->Date.date = date_edit_incre(ds1307X->Date.change, ds1307X->Date.date);
			break;
		
		case RTC_DATE_CHANGE_MONTH:
			ds1307X->Date.month = date_edit_incre(ds1307X->Date.change, ds1307X->Date.month);
			break;
		
		case RTC_DATE_CHANGE_YEAR:
			ds1307X->Date.year = date_edit_incre(ds1307X->Date.change, ds1307X->Date.year);
			break;
	}
}

static void time_update_incre(Ds1307_TypDef_t* ds1307X)
{
	switch(ds1307X->Time.change)
	{
		case RTC_TIME_CHANGE_HOUR:
			ds1307X->Time.hour = time_edit_incre(ds1307X->Time.change, ds1307X->Time.hour);
			break;
		case RTC_TIME_CHANGE_MIN:
			ds1307X->Time.min = time_edit_incre(ds1307X->Time.change, ds1307X->Time.min);
			break;
	}
}

static void date_update_decre(Ds1307_TypDef_t* ds1307X)
{
	switch(ds1307X->Date.change)
	{
		case RTC_DATE_CHANGE_DOW:
			ds1307X->Date.dow = date_edit_decre(ds1307X->Date.change, ds1307X->Date.dow);
			break;
		
		case RTC_DATE_CHANGE_DAY:
			ds1307X->Date.date = date_edit_decre(ds1307X->Date.change, ds1307X->Date.date);
			break;
		
		case RTC_DATE_CHANGE_MONTH:
			ds1307X->Date.month = date_edit_decre(ds1307X->Date.change, ds1307X->Date.month);
			break;
		
		case RTC_DATE_CHANGE_YEAR:
			ds1307X->Date.year = date_edit_decre(ds1307X->Date.change, ds1307X->Date.year);
			break;
	}
}

static void time_update_decre(Ds1307_TypDef_t* ds1307X)
{
	switch(ds1307X->Time.change)
	{
		case RTC_TIME_CHANGE_HOUR:
			ds1307X->Time.hour = time_edit_decre(ds1307X->Time.change, ds1307X->Time.hour);
			break;
		case RTC_TIME_CHANGE_MIN:
			ds1307X->Time.min = time_edit_decre(ds1307X->Time.change, ds1307X->Time.min);
			break;
	}
}

static void hour24Mode_incre(Ds1307_TypDef_t* ds1307X)
{
	if(ds1307X->H24Mode.change != H24MODE_CHANGE) return;
	
	ds1307X->H24Mode.flag++;
	if(ds1307X->H24Mode.flag > H24MODE_TURN_ON)
	{
		ds1307X->H24Mode.flag = H24MODE_TURN_OFF;
	}
}

static void createPulse_incre(Ds1307_TypDef_t* ds1307X)
{
	switch(ds1307X->CreatePulse.change)
	{
		case PULSE_CHANGE_NOT:
			
			break;
		
		case PULSE_CHANGE_RATE: 
			switch(ds1307X->CreatePulse.rate)
			{
				case PULSE_1HZ:
					ds1307X->CreatePulse.rate = PULSE_4096HZ;
					break;
				
				case PULSE_4096HZ:
					ds1307X->CreatePulse.rate = PULSE_8192HZ;
					break;
				
				case PULSE_8192HZ:
					ds1307X->CreatePulse.rate = PULSE_32768HZ;
					break;
				
				case PULSE_32768HZ:
					ds1307X->CreatePulse.rate = PULSE_1HZ;
					break;
				
				default:
					ds1307X->CreatePulse.rate = PULSE_1HZ;
					break;
			}
			break;
		
		case PULSE_CHANGE_FLAG: 
			ds1307X->CreatePulse.flag++;
			if(ds1307X->CreatePulse.flag > PULSE_TURN_ON)
			{
				ds1307X->CreatePulse.flag = PULSE_TURN_OFF;
			}
			break;
	}
}

void rtc_button_incre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t* ds1307In)
{
	if(lcdMenuIn->level != MENU_LEVEL_FINISH)	return;
	if(lcdMenuIn->count_1 != MENU_ROW_ONE) return;
	
	switch(lcdMenuIn->count_2)
	{
		case MENU_ROW_ONE:
			time_update_incre(ds1307In);
			break;
		
		case MENU_ROW_TWO:
			date_update_incre(ds1307In);
			break;
		
		case MENU_ROW_THREE:
			hour24Mode_incre(ds1307In);
			break;
		
		case MENU_ROW_FORE:
			createPulse_incre(ds1307In);
			break;
	}
}

void rtc_button_decre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t* ds1307In)
{
	if(lcdMenuIn->level != MENU_LEVEL_FINISH)	return;
	if(lcdMenuIn->count_1 !=  MENU_ROW_ONE) return;
	
	switch(lcdMenuIn->count_2)
	{
		case  MENU_ROW_ONE:
			time_update_decre(ds1307In);
			break;
		
		case  MENU_ROW_TWO:
			date_update_decre(ds1307In);
			break;
		
		case  MENU_ROW_THREE:
			
			break;
		
		case  MENU_ROW_FORE:
			
			break;
	}
}

void rtc_button_slow(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t* ds1307In)
{
	if(lcdMenuIn->level !=  MENU_LEVEL_FINISH)	return;
	if(lcdMenuIn->count_1 !=  MENU_ROW_ONE) return;
	
	switch(lcdMenuIn->count_2)
	{
		case  MENU_ROW_ONE:
			ds1307In->Time.change++;
			if(ds1307In->Time.change > RTC_TIME_CHANGE_MIN) 
			{
				ds1307In->Time.save = 1;
				ds1307In->save = 1;
				ds1307In->Time.change = RTC_TIME_CHANGE_NOT;
			}
			break;
		
		case  MENU_ROW_TWO:
			ds1307In->Date.change++;
			if(ds1307In->Date.change > RTC_DATE_CHANGE_YEAR)
			{
				ds1307In->Date.save = 1;
				ds1307In->save = 1;
				ds1307In->Date.change = RTC_DATE_CHANGE_NOT;
			}
			break;
		
		case  MENU_ROW_THREE:
			ds1307In->H24Mode.change++;
			if(ds1307In->H24Mode.change > H24MODE_CHANGE)
			{
				ds1307In->H24Mode.save = 1;
				ds1307In->save = 1;
				ds1307In->H24Mode.change = H24MODE_CHANGE_NOT;
			}
			break;
		
		case  MENU_ROW_FORE:
			ds1307In->CreatePulse.change++;
			if(ds1307In->CreatePulse.change > PULSE_CHANGE_FLAG)
			{
				ds1307In->CreatePulse.save = 1;
				ds1307In->save = 1;
				ds1307In->CreatePulse.change = PULSE_CHANGE_NOT;
			}
			break;
	}
}

// alarm
static void alarm_edit_incre(uint8_t change, uint8_t *value)
{
	(*value)++;
	switch(change)
	{
		case ALARM_CHANGE_HOUR:
			if( (*value) > 23 ) (*value) = 0;
			break;
		
		case ALARM_CHANGE_MIN:
			if( (*value) > 59 ) (*value) = 0;
			break;
		
		case ALARM_CHANGE_FLAG:
			if( (*value) > ALARM_TURN_ON ) (*value) = ALARM_TURN_OFF;
			break;
	}
}

static void alarm_edit_decre(uint8_t change, uint8_t *value)
{
	switch(change)
	{
		case ALARM_CHANGE_HOUR:
			if( (*value) > 0 ) (*value)--;
			break;
		
		case ALARM_CHANGE_MIN:
			if( (*value) > 0 ) (*value)--;
			break;
		
		case ALARM_CHANGE_FLAG:
			(*value)++;
			if( (*value) > ALARM_TURN_ON ) (*value) = ALARM_TURN_OFF;
			break;
	}
}

static void alarm_update_incre(uint8_t change, uint8_t *hour, uint8_t *min, uint8_t *flag)
{
	switch(change)
	{
		case ALARM_CHANGE_HOUR:
			alarm_edit_incre(ALARM_CHANGE_HOUR, hour);
			break;
		
		case ALARM_CHANGE_MIN:
			alarm_edit_incre(ALARM_CHANGE_MIN, min);
			break;
		
		case ALARM_CHANGE_FLAG:
			alarm_edit_incre(ALARM_CHANGE_FLAG, flag);
			break;
	}
}

static void alarm_update_decre(uint8_t change, uint8_t *hour, uint8_t *min, uint8_t *flag)
{
	switch(change)
	{
		case ALARM_CHANGE_HOUR:
			alarm_edit_decre(ALARM_CHANGE_HOUR, hour);
			break;
		
		case ALARM_CHANGE_MIN:
			alarm_edit_decre(ALARM_CHANGE_MIN, min);
			break;
		
		case ALARM_CHANGE_FLAG:
			alarm_edit_decre(ALARM_CHANGE_FLAG, flag);
			break;
	}
}

void alarm_button_incre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t* ds1307In)
{
	if(lcdMenuIn->level != MENU_LEVEL_FINISH)	return;
	if(lcdMenuIn->count_1 != MENU_ROW_TWO) return;
	
	switch(lcdMenuIn->count_2)
	{
		case MENU_ROW_ONE:
			alarm_update_incre(ds1307In->MulAlarm.A1.change, &ds1307In->MulAlarm.A1.hour,  &ds1307In->MulAlarm.A1.min,  &ds1307In->MulAlarm.A1.flag);
			break;
		
		case MENU_ROW_TWO:
			alarm_update_incre(ds1307In->MulAlarm.A2.change, &ds1307In->MulAlarm.A2.hour,  &ds1307In->MulAlarm.A2.min,  &ds1307In->MulAlarm.A2.flag);
			break;
		
		case MENU_ROW_THREE:
			alarm_update_incre(ds1307In->MulAlarm.A3.change, &ds1307In->MulAlarm.A3.hour,  &ds1307In->MulAlarm.A3.min,  &ds1307In->MulAlarm.A3.flag);
			break;
		
		case MENU_ROW_FORE:
			alarm_update_incre(ds1307In->MulAlarm.A4.change, &ds1307In->MulAlarm.A4.hour,  &ds1307In->MulAlarm.A4.min,  &ds1307In->MulAlarm.A4.flag);
			break;
	}
}

void alarm_button_decre_fast(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t* ds1307In)
{
	if(lcdMenuIn->level != MENU_LEVEL_FINISH)	return;
	if(lcdMenuIn->count_1 !=  MENU_ROW_TWO) return;
	
	switch(lcdMenuIn->count_2)
	{
		case MENU_ROW_ONE:
			alarm_update_decre(ds1307In->MulAlarm.A1.change, &ds1307In->MulAlarm.A1.hour,  &ds1307In->MulAlarm.A1.min,  &ds1307In->MulAlarm.A1.flag);
			break;
		
		case MENU_ROW_TWO:
			alarm_update_decre(ds1307In->MulAlarm.A2.change, &ds1307In->MulAlarm.A2.hour,  &ds1307In->MulAlarm.A2.min,  &ds1307In->MulAlarm.A2.flag);
			break;
		
		case MENU_ROW_THREE:
			alarm_update_decre(ds1307In->MulAlarm.A3.change, &ds1307In->MulAlarm.A3.hour,  &ds1307In->MulAlarm.A3.min,  &ds1307In->MulAlarm.A3.flag);
			break;
		
		case MENU_ROW_FORE:
			alarm_update_decre(ds1307In->MulAlarm.A4.change, &ds1307In->MulAlarm.A4.hour,  &ds1307In->MulAlarm.A4.min,  &ds1307In->MulAlarm.A4.flag);
			break;
	}
}

void alarm_button_slow(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t* ds1307In)
{
	if(lcdMenuIn->level !=  MENU_LEVEL_FINISH)	return;
	if(lcdMenuIn->count_1 !=  MENU_ROW_TWO) return;
	
	switch(lcdMenuIn->count_2)
	{
		case  MENU_ROW_ONE:
			ds1307In->MulAlarm.A1.change++;
			if(ds1307In->MulAlarm.A1.change > ALARM_CHANGE_FLAG)
			{
				ds1307In->MulAlarm.A1.save = 1;
				ds1307In->save = 1;
				ds1307In->MulAlarm.A1.change = ALARM_CHANGE_NOT;
			}
			break;
		
		case  MENU_ROW_TWO:
			ds1307In->MulAlarm.A2.change++;
			if(ds1307In->MulAlarm.A2.change > ALARM_CHANGE_FLAG)
			{
				ds1307In->MulAlarm.A2.save = 1;
				ds1307In->save = 1;
				ds1307In->MulAlarm.A2.change = ALARM_CHANGE_NOT;
			}
			break;
		
		case  MENU_ROW_THREE:
			ds1307In->MulAlarm.A3.change++;
			if(ds1307In->MulAlarm.A3.change > ALARM_CHANGE_FLAG)
			{
				ds1307In->MulAlarm.A3.save = 1;
				ds1307In->save = 1;
				ds1307In->MulAlarm.A3.change = ALARM_CHANGE_NOT;
			}
			break;
		
		case  MENU_ROW_FORE:
			ds1307In->MulAlarm.A4.change++;
			if(ds1307In->MulAlarm.A4.change > ALARM_CHANGE_FLAG)
			{
				ds1307In->MulAlarm.A4.save = 1;
				ds1307In->save = 1;
				ds1307In->MulAlarm.A4.change = ALARM_CHANGE_NOT;
			}
			break;
	}
}


