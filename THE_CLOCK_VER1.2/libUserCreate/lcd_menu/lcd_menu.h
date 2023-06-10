#ifndef LCD_MENU_H
#define LCD_MENU_H

#include "main.h"

typedef enum
{
	MENU_ROW_ONE = 1,
	MENU_ROW_TWO,
	MENU_ROW_THREE,
	MENU_ROW_FORE, 
	MENU_ROW_FIRE
}Lcd_Menu_Pos_TypDef_e;

typedef enum
{
	MENU_LEVEL_0 = 0,
	MENU_LEVEL_1,
	MENU_LEVEL_2,
	MENU_LEVEL_FINISH // MENU_LEVEL_3
}Lcd_Menu_Level_TypDef_e;

typedef struct
{
	int8_t up, down, choose, back;

	int8_t level;
	int8_t count_1, count_2, count_3, count_4;
	
	uint8_t update;
}Lcd_Menu_TypDef_t;

// content 0
typedef void (*content_0_t)(void);

// conten 1 
typedef void (*content_1_1_t)(void);
typedef void (*content_1_2_t)(void);
typedef void (*content_1_3_t)(void);
typedef void (*content_1_4_t)(void);
//
typedef void (*content_1_1_1_t)(void);
typedef void (*content_1_1_2_t)(void);
typedef void (*content_1_1_3_t)(void);
typedef void (*content_1_1_4_t)(void);

typedef void (*content_1_2_1_t)(void);
typedef void (*content_1_2_2_t)(void);
typedef void (*content_1_2_3_t)(void);
typedef void (*content_1_2_4_t)(void);

typedef void (*content_1_3_1_t)(void);
typedef void (*content_1_3_2_t)(void);
typedef void (*content_1_3_3_t)(void);
typedef void (*content_1_3_4_t)(void);

typedef void (*content_1_4_1_t)(void);
typedef void (*content_1_4_2_t)(void);
typedef void (*content_1_4_3_t)(void);
typedef void (*content_1_4_4_t)(void);
//
typedef void (*content_1_1_1_choose_t)(void);
typedef void (*content_1_1_2_choose_t)(void);
typedef void (*content_1_1_3_choose_t)(void);
typedef void (*content_1_1_4_choose_t)(void);

typedef void (*content_1_2_1_choose_t)(void);
typedef void (*content_1_2_2_choose_t)(void);
typedef void (*content_1_2_3_choose_t)(void);
typedef void (*content_1_2_4_choose_t)(void);

typedef void (*content_1_3_1_choose_t)(void);
typedef void (*content_1_3_2_choose_t)(void);
typedef void (*content_1_3_3_choose_t)(void);
typedef void (*content_1_3_4_choose_t)(void);

typedef void (*content_1_4_1_choose_t)(void);
typedef void (*content_1_4_2_choose_t)(void);
typedef void (*content_1_4_3_choose_t)(void);
typedef void (*content_1_4_4_choose_t)(void);

void lcdMenu_set_content_0(void *funcIn);
//
void lcdMenu_set_content_1_1(void *funcIn);
void lcdMenu_set_content_1_2(void *funcIn);
void lcdMenu_set_content_1_3(void *funcIn);
void lcdMenu_set_content_1_4(void *funcIn);
//
void ledMenu_set_content_1_1_1(void *funcIn);
void ledMenu_set_content_1_1_2(void *funcIn);
void ledMenu_set_content_1_1_3(void *funcIn);
void ledMenu_set_content_1_1_4(void *funcIn);

void ledMenu_set_content_1_2_1(void *funcIn);
void ledMenu_set_content_1_2_2(void *funcIn);
void ledMenu_set_content_1_2_3(void *funcIn);
void ledMenu_set_content_1_2_4(void *funcIn);

void ledMenu_set_content_1_3_1(void *funcIn);
void ledMenu_set_content_1_3_2(void *funcIn);
void ledMenu_set_content_1_3_3(void *funcIn);
void ledMenu_set_content_1_3_4(void *funcIn);

void ledMenu_set_content_1_4_1(void *funcIn);
void ledMenu_set_content_1_4_2(void *funcIn);
void ledMenu_set_content_1_4_3(void *funcIn);
void ledMenu_set_content_1_4_4(void *funcIn);
//
void ledMenu_set_content_1_1_1_choose(void *funcIn);
void ledMenu_set_content_1_1_2_choose(void *funcIn);
void ledMenu_set_content_1_1_3_choose(void *funcIn);
void ledMenu_set_content_1_1_4_choose(void *funcIn);

void ledMenu_set_content_1_2_1_choose(void *funcIn);
void ledMenu_set_content_1_2_2_choose(void *funcIn);
void ledMenu_set_content_1_2_3_choose(void *funcIn);
void ledMenu_set_content_1_2_4_choose(void *funcIn);

void ledMenu_set_content_1_3_1_choose(void *funcIn);
void ledMenu_set_content_1_3_2_choose(void *funcIn);
void ledMenu_set_content_1_3_3_choose(void *funcIn);
void ledMenu_set_content_1_3_4_choose(void *funcIn);

void ledMenu_set_content_1_4_1_choose(void *funcIn);
void ledMenu_set_content_1_4_2_choose(void *funcIn);
void ledMenu_set_content_1_4_3_choose(void *funcIn);
void ledMenu_set_content_1_4_4_choose(void *funcIn);
// ======================================================
void lcdMenu_init(Lcd_Menu_TypDef_t *lcdMenuIn);

void lcdMenu_back_main(void);

void lcdMenu_handle_loop(void);

void lcdMenu_set_choose(void);
void lcdMenu_set_back(void);
void lcdMenu_set_up(void);
void lcdMenu_set_down(void);

void lcdMenu_change_row_1(char *str);
void lcdMenu_change_row_2(char *str);
void lcdMenu_change_row_3(char *str);
void lcdMenu_change_row_4(char *str);

void lcdMenu_delete_row_1(void);
void lcdMenu_delete_row_2(void);
void lcdMenu_delete_row_3(void);
void lcdMenu_delete_row_4(void);

#endif


