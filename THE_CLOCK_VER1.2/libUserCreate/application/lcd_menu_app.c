#include "lcd_menu_app.h"

#include "stdio.h"
#include "lcd_menu.h"
#include "ds1307_lcd_app.h"
#include "temp_lcd_app.h"
#include "uart_lcd_app.h"

void lcdMenuApp_content_0()
{
	char _time[16];
	char _date[16];
	char _alarmTemp[16];
	
	ds1307App_lcd_update_time(_time);
	ds1307App_lcd_update_date(_date);
	
	lcdMenu_change_row_1(_time);
	lcdMenu_change_row_2(_date);
	
	lcdMenu_delete_row_3();
	
	// Move up will error
	ds1307LcdApp_alarm_basic(_alarmTemp);
	tempLcdApp_update_basic_tempCur(_alarmTemp);
	
	lcdMenu_change_row_4(_alarmTemp);
}

//
void lcdMenuApp_content_1_1()
{
	lcdMenu_change_row_1(">Time And Date  ");
	lcdMenu_change_row_2(" Alarm          ");
	lcdMenu_change_row_3(" Temp           ");
	lcdMenu_change_row_4(" Uart           ");
}

void lcdMenuApp_content_1_2()
{
	lcdMenu_change_row_1(" Time And Date  ");
	lcdMenu_change_row_2(">Alarm          ");
	lcdMenu_change_row_3(" Temp           ");
	lcdMenu_change_row_4(" Uart           ");
}

void lcdMenuApp_content_1_3()
{
	lcdMenu_change_row_1(" Time And Date  ");
	lcdMenu_change_row_2(" Alarm          ");
	lcdMenu_change_row_3(">Temp           ");
	lcdMenu_change_row_4(" Uart           ");
}

void lcdMenuApp_content_1_4()
{
	lcdMenu_change_row_1(" Time And Date  ");
	lcdMenu_change_row_2(" Alarm          ");
	lcdMenu_change_row_3(" Temp           ");
	lcdMenu_change_row_4(">Uart           ");
}

//
void lcdMenuApp_content_1_1_1()
{
	lcdMenu_change_row_1(">Time           ");
	lcdMenu_change_row_2(" Date           ");
	lcdMenu_change_row_3(" Hour 24 Mode   ");
	lcdMenu_change_row_4(" Create Pulse   ");
}

void lcdMenuApp_content_1_1_2()
{
	lcdMenu_change_row_1(" Time           ");
	lcdMenu_change_row_2(">Date           ");
	lcdMenu_change_row_3(" Hour 24 Mode   ");
	lcdMenu_change_row_4(" Create Pulse   ");
}

void lcdMenuApp_content_1_1_3()
{
	lcdMenu_change_row_1(" Time           ");
	lcdMenu_change_row_2(" Date           ");
	lcdMenu_change_row_3(">Hour 24 Mode   ");
	lcdMenu_change_row_4(" Create Pulse   ");
}

void lcdMenuApp_content_1_1_4()
{
	lcdMenu_change_row_1(" Time           ");
	lcdMenu_change_row_2(" Date           ");
	lcdMenu_change_row_3(" Hour 24 Mode   ");
	lcdMenu_change_row_4(">Create Pulse   ");
}

//
void lcdMenuApp_content_1_2_1()
{
	lcdMenu_change_row_1(">Alarm 1        ");
	lcdMenu_change_row_2(" Alarm 2        ");
	lcdMenu_change_row_3(" Alarm 3        ");
	lcdMenu_change_row_4(" Alarm 4        ");
}

void lcdMenuApp_content_1_2_2()
{
	lcdMenu_change_row_1(" Alarm 1        ");
	lcdMenu_change_row_2(">Alarm 2        ");
	lcdMenu_change_row_3(" Alarm 3        ");
	lcdMenu_change_row_4(" Alarm 4        ");
}

void lcdMenuApp_content_1_2_3()
{
	lcdMenu_change_row_1(" Alarm 1        ");
	lcdMenu_change_row_2(" Alarm 2        ");
	lcdMenu_change_row_3(">Alarm 3        ");
	lcdMenu_change_row_4(" Alarm 4        ");
}

void lcdMenuApp_content_1_2_4()
{
	lcdMenu_change_row_1(" Alarm 1        ");
	lcdMenu_change_row_2(" Alarm 2        ");
	lcdMenu_change_row_3(" Alarm 3        ");
	lcdMenu_change_row_4(">Alarm 4        ");
}

//
void lcdMenuApp_content_1_3_1()
{
	lcdMenu_change_row_1(">Temp Current   ");
	lcdMenu_change_row_2(" Temp Set       ");
	lcdMenu_change_row_3(" Type Sensor    ");
	lcdMenu_change_row_4(" Number Sensor  ");
}

void lcdMenuApp_content_1_3_2()
{
	lcdMenu_change_row_1(" Temp Current   ");
	lcdMenu_change_row_2(">Temp Set       ");
	lcdMenu_change_row_3(" Type Sensor    ");
	lcdMenu_change_row_4(" Number Sensor  ");
}

void lcdMenuApp_content_1_3_3()
{
	lcdMenu_change_row_1(" Temp Current   ");
	lcdMenu_change_row_2(" Temp Set       ");
	lcdMenu_change_row_3(">Type Sensor    ");
	lcdMenu_change_row_4(" Number Sensor  ");
}

void lcdMenuApp_content_1_3_4()
{
	lcdMenu_change_row_1(" Temp Current   ");
	lcdMenu_change_row_2(" Temp Set       ");
	lcdMenu_change_row_3(" Type Sensor    ");
	lcdMenu_change_row_4(">Number Sensor  ");
}

//
void lcdMenuApp_content_1_4_1()
{
	lcdMenu_change_row_1(">Data Receive   ");
	lcdMenu_change_row_2(" Data Send      ");
	lcdMenu_change_row_3(" State Connect  ");
	lcdMenu_change_row_4(" Baudrate       ");
}

void lcdMenuApp_content_1_4_2()
{
	lcdMenu_change_row_1(" Data Receive   ");
	lcdMenu_change_row_2(">Data Send      ");
	lcdMenu_change_row_3(" State Connect  ");
	lcdMenu_change_row_4(" Baudrate       ");
}

void lcdMenuApp_content_1_4_3()
{
	lcdMenu_change_row_1(" Data Receive   ");
	lcdMenu_change_row_2(" Data Send      ");
	lcdMenu_change_row_3(">State Connect  ");
	lcdMenu_change_row_4(" Baudrate       ");
}

void lcdMenuApp_content_1_4_4()
{
	lcdMenu_change_row_1(" Data Receive   ");
	lcdMenu_change_row_2(" Data Send      ");
	lcdMenu_change_row_3(" State Connect  ");
	lcdMenu_change_row_4(">Baudrate       ");
}

//
void lcdMenuApp_content_1_1_1_choose()
{
	char _time[16];
	ds1307App_lcd_update_edit_time(_time);
	
	lcdMenu_change_row_1("      Time      ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(_time);
	
	lcdMenu_delete_row_4();
}

void lcdMenuApp_content_1_1_2_choose()
{
	char _date[16];
	ds1307App_lcd_update_edit_date(_date);
	
	lcdMenu_change_row_1("      Date      ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(_date);
	
	lcdMenu_delete_row_4();
}

void lcdMenuApp_content_1_1_3_choose()
{
	char _hour24Mode[16];
	ds1307App_lcd_update_edit_24Mode(_hour24Mode);
	
	lcdMenu_change_row_1("  Hour 24 Mode  ");
	lcdMenu_delete_row_2();
	lcdMenu_change_row_3(_hour24Mode);
	lcdMenu_delete_row_4();
}

void lcdMenuApp_content_1_1_4_choose()
{
	char _pulse[16];
	ds1307App_lcd_update_edit_pulse(_pulse);
	
	lcdMenu_change_row_1("  Create Pulse  ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(_pulse);
	
	lcdMenu_delete_row_4();
}

//
void lcdMenuApp_content_1_2_1_choose()
{
	char alarm1[16];
	ds1307App_lcd_update_edit_alarm_1(alarm1);
	
	lcdMenu_change_row_1("    Alarm 1     ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(alarm1);
	
	lcdMenu_delete_row_4();
}

void lcdMenuApp_content_1_2_2_choose()
{
	char alarm2[16];
	ds1307App_lcd_update_edit_alarm_2(alarm2);
	
	lcdMenu_change_row_1("    Alarm 2     ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(alarm2);
	
	lcdMenu_delete_row_4();
}

void lcdMenuApp_content_1_2_3_choose()
{
	char alarm3[16];
	ds1307App_lcd_update_edit_alarm_3(alarm3);
	
	lcdMenu_change_row_1("    Alarm 3     ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(alarm3);
	
	lcdMenu_delete_row_4();
}

void lcdMenuApp_content_1_2_4_choose()
{
	char alarm4[16];
	ds1307App_lcd_update_edit_alarm_4(alarm4);
	
	lcdMenu_change_row_1("    Alarm 4     ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(alarm4);
	
	lcdMenu_delete_row_4();
}

//
void lcdMenuApp_content_1_3_1_choose()
{
	char _temp[16];
	tempLcdApp_update_tempCur(_temp);
	
	lcdMenu_change_row_1("  Temp Current  ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(_temp);
	
	lcdMenu_delete_row_4();
}

void lcdMenuApp_content_1_3_2_choose()
{
	char _tempSet[16];
	tempLcdApp_update_edit_temp_set(_tempSet);
	
	lcdMenu_change_row_1("    Temp Set    ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(_tempSet);
	
	lcdMenu_delete_row_4();
}

void lcdMenuApp_content_1_3_3_choose()
{
	char _typeSensor[16];
	tempLcdApp_type_sensor(_typeSensor);
	
	lcdMenu_change_row_1("   Type Sensor  ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(_typeSensor);
	
	lcdMenu_delete_row_4();
}

void lcdMenuApp_content_1_3_4_choose()
{
	char _numSensor[16];
	tempLcdApp_update_edit_number_sensor(_numSensor);
	
	lcdMenu_change_row_1("  Number Sensor ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(_numSensor);
	
	lcdMenu_delete_row_4();
}

//
void lcdMenuApp_content_1_4_1_choose()
{
	char _data[16];
	uartLcdApp_update_data_receive(_data);
	
	lcdMenu_change_row_1("   Data Receive ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(_data);
	
	lcdMenu_delete_row_4();
}

void lcdMenuApp_content_1_4_2_choose()
{
	char _data[16];
	uartLcdApp_update_data_send(_data);
	
	lcdMenu_change_row_1("    Data Send   ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(_data);
	
	lcdMenu_delete_row_4();
}

void lcdMenuApp_content_1_4_3_choose()
{
	char _flag[16];
	uartLcdApp_update_state_conncet(_flag);
	
	lcdMenu_change_row_1("  State Connect ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(_flag);
	
	lcdMenu_delete_row_4();
}

void lcdMenuApp_content_1_4_4_choose()
{
	char _baudrate[16];
	uartLcdApp_edit_update_baudrate(_baudrate);
	
	lcdMenu_change_row_1("    Baudrate    ");
	lcdMenu_delete_row_2();
	
	lcdMenu_change_row_3(_baudrate);
	
	lcdMenu_delete_row_4();
}

void lcdMenuApp_init(void)
{
	lcdMenu_set_content_0( lcdMenuApp_content_0 );
	
	//
	lcdMenu_set_content_1_1( lcdMenuApp_content_1_1 );
	lcdMenu_set_content_1_2( lcdMenuApp_content_1_2 );
	lcdMenu_set_content_1_3( lcdMenuApp_content_1_3 );
	lcdMenu_set_content_1_4( lcdMenuApp_content_1_4 );
	
	//
	ledMenu_set_content_1_1_1( lcdMenuApp_content_1_1_1 );
	ledMenu_set_content_1_1_2( lcdMenuApp_content_1_1_2 );
	ledMenu_set_content_1_1_3( lcdMenuApp_content_1_1_3 );
	ledMenu_set_content_1_1_4( lcdMenuApp_content_1_1_4 );
	
	ledMenu_set_content_1_2_1( lcdMenuApp_content_1_2_1 );
	ledMenu_set_content_1_2_2( lcdMenuApp_content_1_2_2 );
	ledMenu_set_content_1_2_3( lcdMenuApp_content_1_2_3 );
	ledMenu_set_content_1_2_4( lcdMenuApp_content_1_2_4 );
	
	ledMenu_set_content_1_3_1( lcdMenuApp_content_1_3_1 );
	ledMenu_set_content_1_3_2( lcdMenuApp_content_1_3_2 );
	ledMenu_set_content_1_3_3( lcdMenuApp_content_1_3_3 );
	ledMenu_set_content_1_3_4( lcdMenuApp_content_1_3_4 );
	
	ledMenu_set_content_1_4_1( lcdMenuApp_content_1_4_1 );
	ledMenu_set_content_1_4_2( lcdMenuApp_content_1_4_2 );
	ledMenu_set_content_1_4_3( lcdMenuApp_content_1_4_3 );
	ledMenu_set_content_1_4_4( lcdMenuApp_content_1_4_4 );
	
	//
	ledMenu_set_content_1_1_1_choose( lcdMenuApp_content_1_1_1_choose );
	ledMenu_set_content_1_1_2_choose( lcdMenuApp_content_1_1_2_choose );
	ledMenu_set_content_1_1_3_choose( lcdMenuApp_content_1_1_3_choose );
	ledMenu_set_content_1_1_4_choose( lcdMenuApp_content_1_1_4_choose );
	
	ledMenu_set_content_1_2_1_choose( lcdMenuApp_content_1_2_1_choose );
	ledMenu_set_content_1_2_2_choose( lcdMenuApp_content_1_2_2_choose );
	ledMenu_set_content_1_2_3_choose( lcdMenuApp_content_1_2_3_choose );
	ledMenu_set_content_1_2_4_choose( lcdMenuApp_content_1_2_4_choose );
	
	ledMenu_set_content_1_3_1_choose( lcdMenuApp_content_1_3_1_choose );
	ledMenu_set_content_1_3_2_choose( lcdMenuApp_content_1_3_2_choose );
	ledMenu_set_content_1_3_3_choose( lcdMenuApp_content_1_3_3_choose );
	ledMenu_set_content_1_3_4_choose( lcdMenuApp_content_1_3_4_choose );
	
	ledMenu_set_content_1_4_1_choose( lcdMenuApp_content_1_4_1_choose );
	ledMenu_set_content_1_4_2_choose( lcdMenuApp_content_1_4_2_choose );
	ledMenu_set_content_1_4_3_choose( lcdMenuApp_content_1_4_3_choose );
	ledMenu_set_content_1_4_4_choose( lcdMenuApp_content_1_4_4_choose );
}




