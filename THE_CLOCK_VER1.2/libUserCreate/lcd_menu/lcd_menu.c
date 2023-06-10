#include "lcd_menu.h"

#include "string.h"

#include "lcd.h"

/*
content_0 ---> content_1_1 ---> content_1_1_1 --> content_1_1_1_choose
																content_1_1_2 --> content_1_1_2_choose
																content_1_1_3 --> content_1_1_3_choose
																content_1_1_4 --> content_1_1_4_choose
																
				  ---> content_1_2 ---> content_1_2_1 --> content_1_2_1_choose
																content_1_2_2 --> content_1_2_2_choose
																content_1_2_3 --> content_1_2_3_choose
																content_1_2_4 --> content_1_2_4_choose
							 
					---> content_1_3 ---> content_1_3_1 --> content_1_3_1_choose
																content_1_3_2 --> content_1_3_2_choose
																content_1_3_3 --> content_1_3_3_choose
																content_1_3_4 --> content_1_3_4_choose
																
					---> content_1_4 ---> content_1_4_1 --> content_1_4_1_choose
																content_1_4_2 --> content_1_4_2_choose
																content_1_4_3 --> content_1_4_3_choose
																content_1_4_4 --> content_1_4_4_choose

---------       ----------      -------------      -------------------
level 0          level 1            level 2               level 3

*/

static Lcd_Menu_TypDef_t *lcdMenuX;

char contentRow_1[] = "                ";
char contentRow_2[] = "                ";
char contentRow_3[] = "                ";
char contentRow_4[] = "                ";

content_0_t content_0 = NULL;
//
content_1_1_t content_1_1 = NULL;
content_1_2_t content_1_2 = NULL;
content_1_3_t content_1_3 = NULL;
content_1_4_t content_1_4 = NULL;
//
content_1_1_1_t content_1_1_1 = NULL;
content_1_1_2_t content_1_1_2 = NULL;
content_1_1_3_t content_1_1_3 = NULL;
content_1_1_4_t content_1_1_4 = NULL;

content_1_2_1_t content_1_2_1 = NULL;
content_1_2_2_t content_1_2_2 = NULL;
content_1_2_3_t content_1_2_3 = NULL;
content_1_2_4_t content_1_2_4 = NULL;

content_1_3_1_t content_1_3_1 = NULL;
content_1_3_2_t content_1_3_2 = NULL;
content_1_3_3_t content_1_3_3 = NULL;
content_1_3_4_t content_1_3_4 = NULL;

content_1_4_1_t content_1_4_1 = NULL;
content_1_4_2_t content_1_4_2 = NULL;
content_1_4_3_t content_1_4_3 = NULL;
content_1_4_4_t content_1_4_4 = NULL;
//
content_1_1_1_choose_t content_1_1_1_choose = NULL;
content_1_1_2_choose_t content_1_1_2_choose = NULL;
content_1_1_3_choose_t content_1_1_3_choose = NULL;
content_1_1_4_choose_t content_1_1_4_choose = NULL;

content_1_2_1_choose_t content_1_2_1_choose = NULL;
content_1_2_2_choose_t content_1_2_2_choose = NULL;
content_1_2_3_choose_t content_1_2_3_choose = NULL;
content_1_2_4_choose_t content_1_2_4_choose = NULL;

content_1_3_1_choose_t content_1_3_1_choose = NULL;
content_1_3_2_choose_t content_1_3_2_choose = NULL;
content_1_3_3_choose_t content_1_3_3_choose = NULL;
content_1_3_4_choose_t content_1_3_4_choose = NULL;

content_1_4_1_choose_t content_1_4_1_choose = NULL;
content_1_4_2_choose_t content_1_4_2_choose = NULL;
content_1_4_3_choose_t content_1_4_3_choose = NULL;
content_1_4_4_choose_t content_1_4_4_choose = NULL;

void lcdMenu_set_content_0(void *funcIn)
{
	content_0 = funcIn;
}

void lcdMenu_set_content_1_1(void *funcIn)
{
	content_1_1 = funcIn;
}

void lcdMenu_set_content_1_2(void *funcIn)
{
	content_1_2 = funcIn;
}

void lcdMenu_set_content_1_3(void *funcIn)
{
	content_1_3 = funcIn;
}

void lcdMenu_set_content_1_4(void *funcIn)
{
	content_1_4 = funcIn;
}

void ledMenu_set_content_1_1_1(void *funcIn)
{
	content_1_1_1 = funcIn;
}

void ledMenu_set_content_1_1_2(void *funcIn)
{
	content_1_1_2 = funcIn;
}

void ledMenu_set_content_1_1_3(void *funcIn)
{
	content_1_1_3 = funcIn;
}

void ledMenu_set_content_1_1_4(void *funcIn)
{
	content_1_1_4 = funcIn;
}

void ledMenu_set_content_1_2_1(void *funcIn)
{
	content_1_2_1 = funcIn;
}

void ledMenu_set_content_1_2_2(void *funcIn)
{
	content_1_2_2 = funcIn;
}

void ledMenu_set_content_1_2_3(void *funcIn)
{
	content_1_2_3 = funcIn;
}

void ledMenu_set_content_1_2_4(void *funcIn)
{
	content_1_2_4 = funcIn;
}

void ledMenu_set_content_1_3_1(void *funcIn)
{
	content_1_3_1 = funcIn;
}

void ledMenu_set_content_1_3_2(void *funcIn)
{
	content_1_3_2 = funcIn;
}

void ledMenu_set_content_1_3_3(void *funcIn)
{
	content_1_3_3 = funcIn;
}

void ledMenu_set_content_1_3_4(void *funcIn)
{
	content_1_3_4 = funcIn;
}

void ledMenu_set_content_1_4_1(void *funcIn)
{
	content_1_4_1 = funcIn;
}

void ledMenu_set_content_1_4_2(void *funcIn)
{
	content_1_4_2 = funcIn;
}

void ledMenu_set_content_1_4_3(void *funcIn)
{
	content_1_4_3 = funcIn;
}

void ledMenu_set_content_1_4_4(void *funcIn)
{
	content_1_4_4 = funcIn;
}

void ledMenu_set_content_1_1_1_choose(void *funcIn)
{
	content_1_1_1_choose = funcIn;
}

void ledMenu_set_content_1_1_2_choose(void *funcIn)
{
	content_1_1_2_choose = funcIn;
}

void ledMenu_set_content_1_1_3_choose(void *funcIn)
{
	content_1_1_3_choose = funcIn;
}

void ledMenu_set_content_1_1_4_choose(void *funcIn)
{
	content_1_1_4_choose = funcIn;
}

void ledMenu_set_content_1_2_1_choose(void *funcIn)
{
	content_1_2_1_choose = funcIn;
}

void ledMenu_set_content_1_2_2_choose(void *funcIn)
{
	content_1_2_2_choose = funcIn;
}

void ledMenu_set_content_1_2_3_choose(void *funcIn)
{
	content_1_2_3_choose = funcIn;
}

void ledMenu_set_content_1_2_4_choose(void *funcIn)
{
	content_1_2_4_choose = funcIn;
}

void ledMenu_set_content_1_3_1_choose(void *funcIn)
{
	content_1_3_1_choose = funcIn;
}

void ledMenu_set_content_1_3_2_choose(void *funcIn)
{
	content_1_3_2_choose = funcIn;
}

void ledMenu_set_content_1_3_3_choose(void *funcIn)
{
	content_1_3_3_choose = funcIn;
}

void ledMenu_set_content_1_3_4_choose(void *funcIn)
{
	content_1_3_4_choose = funcIn;
}

void ledMenu_set_content_1_4_1_choose(void *funcIn)
{
	content_1_4_1_choose = funcIn;
}

void ledMenu_set_content_1_4_2_choose(void *funcIn)
{
	content_1_4_2_choose = funcIn;
}

void ledMenu_set_content_1_4_3_choose(void *funcIn)
{
	content_1_4_3_choose = funcIn;
}

void ledMenu_set_content_1_4_4_choose(void *funcIn)
{
	content_1_4_4_choose = funcIn;
}


void content_1_1_choose()
{
	if(lcdMenuX->count_1 != MENU_ROW_ONE) return;
	
	switch(lcdMenuX->count_2)
	{
		case MENU_ROW_ONE:
			content_1_1_1();
			break;
		case MENU_ROW_TWO:
			content_1_1_2();
			break;
		case MENU_ROW_THREE:
			content_1_1_3();
			break;
		case MENU_ROW_FORE:
			content_1_1_4();
			break;
	}
}

void content_1_2_choose()
{
	if(lcdMenuX->count_1 != MENU_ROW_TWO) return;
	
	switch(lcdMenuX->count_2)
	{
		case MENU_ROW_ONE:
			content_1_2_1();
			break;
		case MENU_ROW_TWO:
			content_1_2_2();
			break;
		case MENU_ROW_THREE:
			content_1_2_3();
			break;
		case MENU_ROW_FORE:
			content_1_2_4();
			break;
	}
}

void content_1_3_choose()
{
	if(lcdMenuX->count_1 != MENU_ROW_THREE) return;
	
	switch(lcdMenuX->count_2)
	{
		case MENU_ROW_ONE:
			content_1_3_1();
			break;
		case MENU_ROW_TWO:
			content_1_3_2();
			break;
		case MENU_ROW_THREE:
			content_1_3_3();
			break;
		case MENU_ROW_FORE:
			content_1_3_4();
			break;
	}
}

void content_1_4_choose()
{
	if(lcdMenuX->count_1 != MENU_ROW_FORE) return;
	
	switch(lcdMenuX->count_2)
	{
		case MENU_ROW_ONE:
			content_1_4_1();
			break;
		case MENU_ROW_TWO:
			content_1_4_2();
			break;
		case MENU_ROW_THREE:
			content_1_4_3();
			break;
		case MENU_ROW_FORE:
			content_1_4_4();
			break;
	}
}

void content_1_1_display(void)
{
	if(lcdMenuX->count_1 != MENU_ROW_ONE) return;
	
	switch(lcdMenuX->count_2)
	{
		case MENU_ROW_ONE:
			content_1_1_1_choose();
			break;
		case MENU_ROW_TWO:
			content_1_1_2_choose();
			break;
		case MENU_ROW_THREE:
			content_1_1_3_choose();
			break;
		case MENU_ROW_FORE:
			content_1_1_4_choose();
			break;
	}
}

void content_1_2_display(void)
{
	if(lcdMenuX->count_1 != MENU_ROW_TWO) return;
	
	switch(lcdMenuX->count_2)
	{
		case MENU_ROW_ONE:
			content_1_2_1_choose();
			break;
		case MENU_ROW_TWO:
			content_1_2_2_choose();
			break;
		case MENU_ROW_THREE:
			content_1_2_3_choose();
			break;
		case MENU_ROW_FORE:
			content_1_2_4_choose();
			break;
	}
}

void content_1_3_display(void)
{
	if(lcdMenuX->count_1 != MENU_ROW_THREE) return;
	
	switch(lcdMenuX->count_2)
	{
		case MENU_ROW_ONE:
			content_1_3_1_choose();
			break;
		case MENU_ROW_TWO:
			content_1_3_2_choose();
			break;
		case MENU_ROW_THREE:
			content_1_3_3_choose();
			break;
		case MENU_ROW_FORE:
			content_1_3_4_choose();
			break;
	}
}

void content_1_4_display(void)
{
	if(lcdMenuX->count_1 != MENU_ROW_FORE) return;
	
	switch(lcdMenuX->count_2)
	{
		case MENU_ROW_ONE:
			content_1_4_1_choose();
			break;
		case MENU_ROW_TWO:
			content_1_4_2_choose();
			break;
		case MENU_ROW_THREE:
			content_1_4_3_choose();
			break;
		case MENU_ROW_FORE:
			content_1_4_4_choose();
			break;
	}
}

void lcdMenu_level_0()
{
	if(lcdMenuX->level != MENU_LEVEL_0)	return;
	
	content_0();
}

void lcdMenu_level_1(void)
{
	if(lcdMenuX->level != MENU_LEVEL_1)	return;
	
	switch(lcdMenuX->count_1)
	{
		case MENU_ROW_ONE:
			content_1_1();
			break;
		
		case MENU_ROW_TWO:
			content_1_2();
			break;
		
		case MENU_ROW_THREE:
			content_1_3();
			break;
		
		case MENU_ROW_FORE:
			content_1_4();
			break;
	}
}

void lcdMenu_level_2()
{
	if(lcdMenuX->level != MENU_LEVEL_2)	return;
	
	content_1_1_choose();
	content_1_2_choose();
	content_1_3_choose();
	content_1_4_choose();
}


void lcdMenu_level_3()
{
	if(lcdMenuX->level != MENU_LEVEL_FINISH)	return;
	
	content_1_1_display();
	content_1_2_display();
	content_1_3_display();
	content_1_4_display();
}
//
void lcdMenu_set_choose()
{
	lcdMenuX->choose = 1;
}

void lcdMenu_set_back()
{
	lcdMenuX->back = 1;
}

void lcdMenu_set_up()
{
	lcdMenuX->up = 1;
}

void lcdMenu_set_down()
{
	lcdMenuX->down = 1;
}
//
void lcdMenu_check_choose()
{
	if(lcdMenuX->choose == 1)
	{
		lcdMenuX->choose = 0;
		
		if(lcdMenuX->level < MENU_LEVEL_FINISH)	lcdMenuX->level++;
	}
}

void lcdMenu_check_back()
{
	if(lcdMenuX->back == 1)
	{
		lcdMenuX->back = 0;
		
		if(lcdMenuX->level > MENU_LEVEL_0) lcdMenuX->level--;
		
		// Clear number khen back
		if(lcdMenuX->level == MENU_LEVEL_0)
		{
			lcdMenuX->count_1 = MENU_ROW_ONE;
		}
		else if(lcdMenuX->level == MENU_LEVEL_1)
		{
			lcdMenuX->count_2 = MENU_ROW_ONE;
		}
	}
}

void lcdMenu_check_up(void)
{
	if(lcdMenuX->up == 1)
	{
		lcdMenuX->up = 0;
		switch( lcdMenuX->level)
		{
			case MENU_LEVEL_1:
				lcdMenuX->count_1++;
				if(lcdMenuX->count_1 > MENU_ROW_FORE)	lcdMenuX->count_1 = MENU_ROW_ONE;
				break;
			
			case MENU_LEVEL_2:
				lcdMenuX->count_2++;
				if(lcdMenuX->count_2 > MENU_ROW_FORE)	lcdMenuX->count_2 = MENU_ROW_ONE;
				break;
		}
	}
}

void lcdMenu_check_down()
{
	if(lcdMenuX->down == 1)
	{
		lcdMenuX->down = 0;
		
		switch(lcdMenuX->level)
		{
			case MENU_LEVEL_1:
				if(lcdMenuX->count_1 > MENU_ROW_ONE) lcdMenuX->count_1--;
				break;
			case MENU_LEVEL_2:
				if(lcdMenuX->count_2 > MENU_ROW_ONE) lcdMenuX->count_2--;
				break;
		}
	}
}
//
void lcdMenu_move(void)
{
	lcdMenu_check_choose();
	lcdMenu_check_back();
	
	lcdMenu_check_up();
	lcdMenu_check_down();
}
//
void lcdMenu_display()
{
	lcd_send_string_goto_xy(0, 0, contentRow_1);

	lcd_send_string_goto_xy(1, 0, contentRow_2);

	lcd_send_string_goto_xy(2, 0, contentRow_3);

	lcd_send_string_goto_xy(3, 0, contentRow_4);
}

void lcdMenu_handle_loop(void)
{
	lcdMenu_move();
	
	lcdMenu_level_0();
	lcdMenu_level_1();
	lcdMenu_level_2();
	lcdMenu_level_3();
	
	lcdMenu_display();
}

void lcdMenu_change_row_1(char *str)
{
	strcpy(contentRow_1, str);
}

void lcdMenu_change_row_2(char *str)
{
	strcpy(contentRow_2, str);
}

void lcdMenu_change_row_3(char *str)
{
	strcpy(contentRow_3, str);
}

void lcdMenu_change_row_4(char *str)
{
	strcpy(contentRow_4, str);
}

void lcdMenu_delete_row_1(void)
{
	lcdMenu_change_row_1("                ");
}

void lcdMenu_delete_row_2(void)
{
	lcdMenu_change_row_2("                ");
}

void lcdMenu_delete_row_3(void)
{
	lcdMenu_change_row_3("                ");
}

void lcdMenu_delete_row_4(void)
{
	lcdMenu_change_row_4("                ");
}


void lcdMenu_start(void)
{
	lcdMenuX->up = lcdMenuX->down 
							 = lcdMenuX->choose 
							 = lcdMenuX->back    = 0;
	
	lcdMenuX->level = MENU_LEVEL_0;

	lcdMenuX->count_1 = lcdMenuX->count_2
									  = lcdMenuX->count_3
									  = lcdMenuX->count_4  = MENU_ROW_ONE;
}

void lcdMenu_back_main(void)
{
	lcdMenuX->level = MENU_LEVEL_0;

	lcdMenuX->count_1 = lcdMenuX->count_2
									  = lcdMenuX->count_3
									  = lcdMenuX->count_4  = MENU_ROW_ONE;
}

void lcdMenu_init(Lcd_Menu_TypDef_t *lcdMenuIn)
{
	lcdMenuX = lcdMenuIn;
	
	lcdMenu_start();
}









