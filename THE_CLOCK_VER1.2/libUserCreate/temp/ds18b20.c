#include "ds18b20.h"

static TIM_HandleTypeDef *htim;

// Prescaler = 72-1;
// Period = 65535;
void delay (uint16_t time)
{
	/* change your code here for the delay in microseconds */
	__HAL_TIM_SET_COUNTER(htim, 0);
	while ((__HAL_TIM_GET_COUNTER(htim)) < time);
}

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void DS18B20_Init (DS18B20_Name *DSX, TIM_HandleTypeDef *htimX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) 
{	
	htim = htimX;
	
	DSX->GPIOx = GPIOx;
	DSX->GPIO_Pin = GPIO_Pin;
}

uint8_t DS18B20_Start (DS18B20_Name *DSX)
{
	uint8_t Response = 0;
	Set_Pin_Output(DSX->GPIOx, DSX->GPIO_Pin);   // set the pin as output
	HAL_GPIO_WritePin (DSX->GPIOx, DSX->GPIO_Pin, 0);  // pull the pin low
	delay (480);   // delay according to datasheet

	Set_Pin_Input(DSX->GPIOx, DSX->GPIO_Pin);    // set the pin as input
	delay (80);    // delay according to datasheet

	if (!(HAL_GPIO_ReadPin (DSX->GPIOx, DSX->GPIO_Pin))) Response = 1;    // if the pin is low i.e the presence pulse is detected
	else Response = -1;

	delay (400); // 480 us delay totally.

	return Response;
}

void DS18B20_Write (DS18B20_Name *DSX, uint8_t data)
{
	Set_Pin_Output(DSX->GPIOx, DSX->GPIO_Pin);  // set as output

	for (int i=0; i<8; i++)
	{
		if ((data & (1<<i))!=0)  // if the bit is high
		{
			// write 1

			Set_Pin_Output(DSX->GPIOx, DSX->GPIO_Pin);  // set as output
			HAL_GPIO_WritePin (DSX->GPIOx, DSX->GPIO_Pin, GPIO_PIN_RESET);  // pull the pin LOW
			delay (1);  // wait for 1 us

			Set_Pin_Input(DSX->GPIOx, DSX->GPIO_Pin);  // set as input
			delay (50);  // wait for 60 us
		}

		else  // if the bit is low
		{
			// write 0

			Set_Pin_Output(DSX->GPIOx, DSX->GPIO_Pin);
			HAL_GPIO_WritePin (DSX->GPIOx, DSX->GPIO_Pin, GPIO_PIN_RESET);  // pull the pin LOW
			delay (50);  // wait for 60 us

			Set_Pin_Input(DSX->GPIOx, DSX->GPIO_Pin);
		}
	}
}

uint8_t DS18B20_Read (DS18B20_Name *DSX)
{
	uint8_t value=0;

	Set_Pin_Input(DSX->GPIOx, DSX->GPIO_Pin);

	for (int i=0;i<8;i++)
	{
		Set_Pin_Output(DSX->GPIOx, DSX->GPIO_Pin);   // set as output

		HAL_GPIO_WritePin (DSX->GPIOx, DSX->GPIO_Pin, GPIO_PIN_RESET);  // pull the data pin LOW
		delay (1);  // wait for > 1us

		Set_Pin_Input(DSX->GPIOx, DSX->GPIO_Pin);  // set as input
		if (HAL_GPIO_ReadPin (DSX->GPIOx, DSX->GPIO_Pin))  // if the pin is HIGH
		{
			value |= 1<<i;  // read = 1
		}
		delay (50);  // wait for 60 us
	}
	return value;
}

// Every 1ms call once
float DS18B20_ReadTemp(DS18B20_Name *DSX) 
{
	static  uint8_t Rh_byte1 = 0, 
					Rh_byte2 = 0, 
					Temp_byte1 = 0, 
					Temp_byte2 = 0;
	
	static uint16_t SUM = 0, 
					 RH = 0, 
					 TEMP = 0;
	
	static uint8_t Presence = 0;
	float Temperature = -1;
	
	DSX->count++;
	if(DSX->state == DS18B20_START_ONE_TIME)
	{
		Presence = DS18B20_Start (DSX);
		
		DSX->count = 0;
		DSX->state = DS18B20_WRITE_ONE_TIME;
	}
	else if(DSX->count >= 1 && DSX->state == DS18B20_WRITE_ONE_TIME)
	{
		DS18B20_Write (DSX, 0xCC);  // skip ROM
		DS18B20_Write (DSX, 0x44);  // convert t
		
		DSX->count = 0;
		DSX->state = DS18B20_START_TWO_TIME;
	}
	else if(DSX->count >= 800 && DSX->state == DS18B20_START_TWO_TIME)
	{
		Presence = DS18B20_Start (DSX);
		
		DSX->count = 0;
		DSX->state = DS18B20_WRITE_TWO_TIME;
	}
	else if(DSX->count >= 1 && DSX->state == DS18B20_WRITE_TWO_TIME)
	{
		DS18B20_Write (DSX, 0xCC);  // skip ROM
		DS18B20_Write (DSX, 0xBE);  // Read Scratch-pad

		Temp_byte1 = DS18B20_Read(DSX);
		Temp_byte2 = DS18B20_Read(DSX);
		TEMP = (Temp_byte2<<8)|Temp_byte1;
		Temperature = (float)TEMP/16;
		
		DSX->count = 0;
		DSX->state = DS18B20_START_ONE_TIME;
	
		return Temperature;
	}
	
	return -1;
}



