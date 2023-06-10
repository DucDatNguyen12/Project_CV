#ifndef GPIO_STM32_H
#define GPIO_STM32_H

#include "main.h"

uint8_t gpio_read(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void gpio_write(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t state);

void gpio_toggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);


#endif



