#ifndef DS18B20_H
#define DS18B20_H

#include "main.h"

#ifndef DS18B20_Pin
	#define DS18B20_Pin GPIO_PIN_9
	#define DS18B20_GPIO_Port GPIOB
#endif

typedef enum
{
	DS18B20_START_ONE_TIME = 0,
	DS18B20_START_TWO_TIME,
	
	DS18B20_WRITE_ONE_TIME,
	DS18B20_WRITE_TWO_TIME,
	
	DS18B20_READ	
}Ds18b20_State_e;


typedef struct 
{
	float tempRead;
	
	uint8_t tempSet, changeTempSet, saveTempSet;
	uint8_t numSensor, changeNumSensor, saveNumSensor;
	char nameSensor[16];
	
	uint8_t state;
	uint32_t count;
	
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
}DS18B20_Name;


// Must start Tim into file main.c
// to run Timer
//HAL_TIM_Base_Start(&htim1);

void DS18B20_Init (DS18B20_Name *DSX, TIM_HandleTypeDef *htimX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
float DS18B20_ReadTemp(DS18B20_Name *DSX);

#endif


