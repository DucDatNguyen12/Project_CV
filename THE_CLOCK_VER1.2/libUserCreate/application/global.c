#include "global.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "led.h"

#include "buzzer.h"

#include "button.h"
#include "button_app.h"
#include "buzzer_led_app.h"

#include "lcd.h"
#include "lcd_menu.h"
#include "lcd_menu_app.h"
#include "temp_lcd_app.h" 

#include "ee.h"
#include "ee_app.h"

#include "ds1307.h"
#include "ds1307_lcd_app.h"
#include "alarm_app.h"

#include "DS18B20.h"

#include "uart.h"
#include "uart_lcd_app.h"

// system
static I2C_HandleTypeDef *hi2c1; 
static TIM_HandleTypeDef *htim1; 
static TIM_HandleTypeDef *htim2; 
static UART_HandleTypeDef *huart3;

#define timSys htim1
#define timTemp htim2
#define i2c hi2c1
#define uart huart3

// global
static Global_Count_Time_t count1;
static Global_Flag_t flag1;

static Led_TypDef_t led0, led1;

static Button_TypDef_t buttonUp, buttonDown;

static Buzzer_TypDef_t buzzer1; 

static Lcd_Menu_TypDef_t lcdMenu1;

Ee_TypDef_t ee1;

Ds1307_TypDef_t ds1;

DS18B20_Name dsTemp1;

char dataReceive;
Uart_TypDef_t uart1;

// ======================================== setup ===================================
void global_start(void)
{
	// count time
	count1.system = 0;
	count1.ds1307 = 0;
	count1.lcd = 0;
	count1.led0 = 0;
	count1.temp = 0;
	
	// flag
	flag1.system = 0;
	flag1.ds1307 = 0;
	flag1.lcd = 0;
	flag1.led0 = 0;
	flag1.temp = 0;
	flag1.buzzer = 0;
}

uint8_t global_init(  TIM_HandleTypeDef *htim1In, 
											TIM_HandleTypeDef *htim2In,
											I2C_HandleTypeDef *hi2cIn,
                      UART_HandleTypeDef *huartIn )
{
	// system
	timSys = htim1In;
	timTemp = htim2In;
	i2c = hi2cIn;
	uart = huartIn;
	
	// global
	global_start();
	// ds18b20
	DS18B20_Init(&dsTemp1, timTemp, DS18B20_GPIO_Port, DS18B20_Pin);
	tempLcdApp_init(&dsTemp1);
	// led 
	led_init(&led0, LED0_GPIO_Port, LED0_Pin); 
	led_init(&led1, LED1_GPIO_Port, LED1_Pin); 
	// button
	button_init(&buttonUp, BUTTON2_GPIO_Port, BUTTON2_Pin);
	button_init(&buttonDown, BUTTON4_GPIO_Port, BUTTON4_Pin);
	buttonApp_init(&lcdMenu1, &ds1, &dsTemp1, &uart1);
	// uart
	uart_init(&uart1);
	uartLcdApp_init(&uart1);
	
	HAL_UART_Receive_IT(uart, (uint8_t*)&dataReceive, 1);
	// lcd
	lcd_init(i2c);
	HAL_Delay(1000);
	lcd_send_string_goto_xy(1,3,"THE CLOCK");
	lcd_send_string_goto_xy(3,3, "20/02/2023");
	HAL_Delay(1000);
	
	lcdMenu_init(&lcdMenu1);
	lcdMenuApp_init();
	// ds1307
	ds1307_init(i2c);
	ds1307App_init(&ds1);
	alarmApp_init(&ds1, &buzzer1);
	// buzzer
	buzzer_init(&buzzer1, BUZZER_GPIO_Port, BUZZER_Pin);
	// ee24xx
	ee24_init(i2c);
	HAL_Delay(1000);
	eeApp_init(&ds1, &dsTemp1, &uart1);
	

	if(ee24_available() == 1 )
	{
		HAL_UART_Transmit(uart, (uint8_t*)"Ee24c02 connected.\n", sizeof("Ee24c02 connected.\n"), 100);
	}
	
	eeApp_start();
	// timer
	HAL_TIM_Base_Start_IT(timSys);
	HAL_TIM_Base_Start(timTemp);
	
	return 0;
}
// ====================================== loop =============================
void global_button(void)
{
	up_button_handle_loop(&buttonUp);
	down_button_handle_loop(&buttonDown);
}

void global_lcd(void)
{
	if(flag1.lcd == 1)
	{
		lcdMenu_handle_loop();
		
		flag1.lcd = 0;
	}
}

void global_ee(void)
{
	if(flag1.ee == 1)
	{
		flag1.ee = 0;
		
		// save data into eeprom
		eeApp_handle_loop();
	}
}

void global_ds1307(void)
{
	if(flag1.ds1307 == 1)
	{
		flag1.ds1307 = 0;
		
		if( ds1.Date.change == RTC_TIME_CHANGE_NOT
				&& ds1.Time.change == RTC_DATE_CHANGE_NOT 
				&& ds1.Time.save == 0 
				&& ds1.Date.save == 0 )
		{
			ds1307_get_all( &ds1 );
		}
	}
	
	if(flag1.alarm == 1)
	{
		flag1.alarm = 0;
		
		alarmApp_handle_loop();
	}
}

void global_dsTemp()
{
	float _temp = DS18B20_ReadTemp(&dsTemp1);
	
	if( _temp!= -1)
	{
		dsTemp1.tempRead = _temp;
	}
}

uint8_t global_loop(void)
{
	global_button();
	global_lcd();
	global_ee();
	global_dsTemp();
	global_ds1307();
	return 0;
}

// ======================================================== interrupt =============================
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Transmit(uart, (uint8_t*)&dataReceive, 1, 100);
	HAL_UART_Receive_IT(uart, (uint8_t*)&dataReceive, 1);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// global
	count1.system++;
	if(count1.system >= 100)
	{
		count1.system = 0;
		led_toggle(&led0);
	}
	
	// lcd
	count1.lcd++;
	if(count1.lcd > 500)
	{
		count1.lcd = 0;
		flag1.lcd = 1;
	}
	
	// ds1307
	count1.ds1307++;
	if(count1.ds1307 >= 900)
	{
		flag1.ds1307 = 1;
		
		count1.ds1307 = 0;
	}
	
	count1.alarm++;
	if(count1.alarm == 2000)
	{
		count1.alarm  = 0;
		
		flag1.alarm = 1;
	}
		
	// ee
	count1.ee++;
	if(count1.ee >= 500)
	{
		count1.ee = 0;
		
		flag1.ee = 1;
	}
	
	// button
	button_check_press_interrupt(&buttonUp);
	button_check_press_interrupt(&buttonDown);
	
	buzzerLedApp_but_noti_inter(&buttonUp, &buzzer1, &led1);
	buzzerLedApp_but_noti_inter(&buttonDown, &buzzer1, &led1);
	
	// buzzer
	buzzer_call_blink_interrupt(&buzzer1);
}

