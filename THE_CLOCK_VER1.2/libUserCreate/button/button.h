#ifndef BTN_H_
#define BTN_H_

#include "main.h"

#define TIME_PRESS_FAST 100
#define TIME_PRESS_SLOW 1000
#define TIME_PRESS_LONG_SLOW 3000
#define TIME_PRESS_KEEP 5000

typedef enum{
	BUTTON_PRESS_STATE = 0,
	BUTTON_RELEASE_STATE
}Button_State_e;

typedef enum
{
	BUTTON_NOTHING = 0,
	BUTTON_PRESSED,
	BUTTON_FAST,
	BUTTON_SLOW,
	BUTTON_LONG_SLOW,
	BUTTON_KEEP,
	BUTTON_HANDLE_OK
}Button_Type_Press_e;

typedef enum
{
	BUTTON_NOTIFY_NOT = 0,
	BUTTON_NOTIFY,
	BUTTON_NOTIFY_KEEP
}Button_Notify_e;

typedef struct
{
	volatile uint32_t Count;
	volatile uint8_t Flag;
	volatile uint8_t Notify;
	
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
}Button_TypDef_t;

typedef void (*up_handle_fast_t)(void);
typedef void (*up_handle_slow_t)(void);
typedef void (*up_handle_long_slow_t)(void);
typedef void (*up_handle_keep_t)(void);
//
typedef void (*down_handle_fast_t)(void);
typedef void (*down_handle_slow_t)(void);
typedef void (*down_handle_long_slow_t)(void);
typedef void (*down_handle_keep_t)(void);
//
void up_button_set_handle_fast(void *functionIn);
void up_button_set_handle_slow(void *functionIn);
void up_button_set_handle_long_slow(void *functionIn);
void up_button_set_handle_keep(void *functionIn);
//
void down_button_set_handle_fast(void *functionIn);
void down_button_set_handle_slow(void *functionIn);
void down_button_set_handle_long_slow(void *functionIn);
void down_button_set_handle_keep(void *functionIn);

//====================================================================================
void button_init(Button_TypDef_t *buttonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void button_check_press_interrupt(Button_TypDef_t *buttonX);

void up_button_handle_loop(Button_TypDef_t *buttonX);
void down_button_handle_loop(Button_TypDef_t *buttonX);

#endif

