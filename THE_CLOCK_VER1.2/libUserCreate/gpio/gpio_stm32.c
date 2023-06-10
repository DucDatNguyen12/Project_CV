#include "gpio_stm32.h"

uint8_t gpio_read(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

void gpio_write(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t state)
{
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, (GPIO_PinState)state);
}

void gpio_toggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
}


