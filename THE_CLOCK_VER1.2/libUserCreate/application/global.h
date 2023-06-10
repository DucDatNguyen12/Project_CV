#ifndef GLOBAL_H
#define GLOBAL_H

#include "main.h"

typedef struct
{
	uint32_t system,			
					 ds1307,
					 led0,
					 temp,
					 ee,
					 lcd, 
					 buzzer, alarm;
}Global_Count_Time_t;
 
typedef struct
{
	uint8_t system,
					ds1307,
					led0,
					temp,
					ee,
					lcd,
					buzzer, alarm;
}Global_Flag_t;

uint8_t global_init(  TIM_HandleTypeDef *htim1In, 
											TIM_HandleTypeDef *htim2In,
											I2C_HandleTypeDef *hi2cIn,
                      UART_HandleTypeDef *huartIn );

uint8_t global_loop(void);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif



