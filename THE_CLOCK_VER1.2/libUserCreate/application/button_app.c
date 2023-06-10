#include "button_app.h"

#include "button.h"
#include "ds1307_button_app.h"
#include "temp_button_app.h"
#include "uart_button_app.h"
#include "alarm_app.h"

static Lcd_Menu_TypDef_t *lcdMenu;
static Ds1307_TypDef_t *ds1307;
static DS18B20_Name *ds18b20;
static Uart_TypDef_t *uart;

void buttonApp_init(Lcd_Menu_TypDef_t *lcdMenuIn, Ds1307_TypDef_t *ds1307In, DS18B20_Name *ds18b20In, Uart_TypDef_t *uartIn)
{
	lcdMenu = lcdMenuIn;
	ds1307 = ds1307In;
	ds18b20 = ds18b20In;
	uart = uartIn;
	//
	up_button_set_handle_fast(up_buttonApp_Fast);
	up_button_set_handle_slow(up_buttonApp_Slow);
	//
	up_button_set_handle_long_slow(up_buttonApp_Long_Slow);
	up_button_set_handle_keep(up_buttonApp_Keep);
	//
	down_button_set_handle_fast(down_buttonApp_Fast);
	down_button_set_handle_slow(down_buttonApp_Slow);
	down_button_set_handle_long_slow(down_buttonApp_Long_Slow);
	down_button_set_handle_keep(down_buttonApp_Keep);
}
//
void up_buttonApp_Fast(void)
{
	lcdMenu_set_up();
	
	rtc_button_incre_fast(lcdMenu, ds1307);	
	
	alarm_button_incre_fast(lcdMenu, ds1307);
	
	temp_button_incre_fast(lcdMenu, ds18b20);
	
	uart_button_incre_fast(lcdMenu, uart);
	
	AlarmApp_turn_off();
}
//
void down_buttonApp_Fast(void)
{
	lcdMenu_set_down();
	
	rtc_button_decre_fast(lcdMenu, ds1307);
	
	alarm_button_decre_fast(lcdMenu, ds1307);
	
	temp_button_decre_fast(lcdMenu, ds18b20);
	
	uart_button_decre_fast(lcdMenu, uart);
}
//
void up_buttonApp_Slow(void)
{
	lcdMenu_set_choose();
	
	rtc_button_slow(lcdMenu, ds1307);
	
	alarm_button_slow(lcdMenu, ds1307);
	
	temp_button_slow(lcdMenu, ds18b20);
	
	uart_button_slow(lcdMenu, uart);
}
//
void down_buttonApp_Slow(void)
{
	lcdMenu_set_back();
}
//
void up_buttonApp_Long_Slow(void)
{
	
}
//
void down_buttonApp_Long_Slow(void)
{
	
}
//
void up_buttonApp_Keep(void)
{
	
}
//
void down_buttonApp_Keep(void)
{
	lcdMenu_back_main();
}



