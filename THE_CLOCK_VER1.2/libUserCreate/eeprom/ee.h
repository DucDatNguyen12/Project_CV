#ifndef EEPROM_24CXX_H
#define EEPROM_24CXX_H

#include "main.h"

// Just Choose One Line Follow
#define	EEPROM_SIZE_KBIT				2
//#define	EEPROM_SIZE_KBIT			16
//#define	EEPROM_SIZE_KBIT			256
//#define	EEPROM_SIZE_KBIT			512

#define EEPROM_ADDR 						0xA0

#define		EEPROM_USE_FREERTOS   0


typedef struct
{
	int Count;
}Ee_TypDef_t;

void ee24_init(I2C_HandleTypeDef *i2cX);

uint8_t ee24_available(void);

uint8_t ee24_write(uint16_t address, uint8_t *data, size_t len, uint32_t timeout);
uint8_t ee24_read(uint16_t address, uint8_t *data, size_t len, uint32_t timeout);

uint8_t ee24_erase_data(void);

void ee24_check_read_write_data(void);


void ee_ci_charArray_to_int(char *str, int *num);
void ee_ci_int_to_charArray(char *str, int num);

#endif




