#include "ee.h" 

#include "stdio.h"
#include "string.h"

#if (EEPROM_SIZE_KBIT == 1) || (EEPROM_SIZE_KBIT == 2)
#define EEPROM_PSIZE     8
#elif (EEPROM_SIZE_KBIT == 4) || (EEPROM_SIZE_KBIT == 8) || (EEPROM_SIZE_KBIT == 16)
#define EEPROM_PSIZE     16
#else
#define EEPROM_PSIZE     32
#endif

static I2C_HandleTypeDef *hi2c2;
#define ee_i2c hi2c2

uint8_t ee24Lock = 0;


void ee24_init(I2C_HandleTypeDef *i2cX)
{
	ee_i2c = i2cX;
}

// Device Ready
uint8_t ee24_available(void)
{
	if (HAL_I2C_IsDeviceReady(ee_i2c, EEPROM_ADDR, 2, 100) == HAL_OK)
	{
    return 1;
	}
  else
	{
    return 0;	
	}
}

uint8_t ee24_write(uint16_t address, uint8_t *data, size_t len, uint32_t timeout)
{
	if(ee24Lock == 1)
	{
		return 0;
	}
	ee24Lock = 1;	
	
	uint16_t w = 0;
	uint8_t startTime = HAL_GetTick();
	
	while(1)
	{
		w = EEPROM_PSIZE - (address % EEPROM_PSIZE);
		if(w > len)
		{
			w = len;
		}
		
		#if ((EEPROM_SIZE_KBIT == 1) || (EEPROM_SIZE_KBIT == 2))
			if(HAL_I2C_Mem_Write(ee_i2c, EEPROM_ADDR,address, I2C_MEMADD_SIZE_8BIT, data, w, 100))
		#elif (EEPROM_SIZE_KBIT == 4)
			if(HAL_I2C_Mem_Write(ee_i2c, EEPROM_ADDR | ((address & 0x0100) >> 7), (address & oxff), I2C_MEMADD_SIZE_8BIT, data, w, 100))
		#elif (EEPROM_SIZE_KBIT == 8)
			if(HAL_I2C_Mem_Write(ee_i2c, EEPROM_ADDR | ((address & 0x0300) >> 7), (address & oxff), I2C_MEMADD_SIZE_8BIT, data, w, 100))
		#elif (EEPROM_SIZE_KBIT == 16)
			if(HAL_I2C_Mem_Write(ee_i2c, EEPROM_ADDR | ((address & 0x0700) >> 7), (address & oxff), I2C_MEMADD_SIZE_8BIT, data, w, 100))
		#elif 
			if(HAL_I2C_Mem_Write(ee_i2c, EEPROM_ADDR , address, I2C_MEMADD_SIZE_16BIT, data, w, 100))
		#endif
		
		{
			len -= w;
			data += w;
			address += w;
			
			if(len==0)
			{
				ee24Lock = 0;
				return 1;
			}
			
			if(HAL_GetTick() - startTime >=timeout)
			{
				ee24Lock = 0;
				return 0;
			}
		}
		else
		{
			ee24Lock = 0;
			return 0;
		}
	}
}

uint8_t ee24_read(uint16_t address, uint8_t *data, size_t len, uint32_t timeout)
{
	if(ee24Lock == 1)
	{
		return 0;
	}
	ee24Lock = 1;
	
	#if ((EEPROM_SIZE_KBIT == 1) || (EEPROM_SIZE_KBIT == 2))
		if(HAL_I2C_Mem_Read(ee_i2c, EEPROM_ADDR,address, I2C_MEMADD_SIZE_8BIT, data, len, 100) == HAL_OK)
	#elif (EEPROM_SIZE_KBIT == 4)
		if(HAL_I2C_Mem_Read(ee_i2c, EEPROM_ADDR | ((address & 0x0100) >> 7), (address & oxff), I2C_MEMADD_SIZE_8BIT, data, len, 100))
	#elif (EEPROM_SIZE_KBIT == 8)
		if(HAL_I2C_Mem_Read(ee_i2c, EEPROM_ADDR | ((address & 0x0300) >> 7), (address & oxff), I2C_MEMADD_SIZE_8BIT, data, len, 100))
	#elif (EEPROM_SIZE_KBIT == 16)
		if(HAL_I2C_Mem_Read(ee_i2c, EEPROM_ADDR | ((address & 0x0700) >> 7), (address & oxff), I2C_MEMADD_SIZE_8BIT, data, len, 100))
	#elif 
		if(HAL_I2C_Mem_Read(ee_i2c, EEPROM_ADDR , address, I2C_MEMADD_SIZE_16BIT, data, w, 100))
	#endif
	
	{
		ee24Lock = 0;
		return 1;
	}
	else
	{
		ee24Lock = 0;
		return 0;
	}
}

// Delete all data save on chip eeprom
uint8_t ee24_erase_data(void)
{
		const uint8_t eraseData[32] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF\
    , 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	
		uint32_t _bytes = 0;
		
		while( _bytes < (EEPROM_SIZE_KBIT*256) )
		{ 
			if( ee24_write(_bytes, (uint8_t*)eraseData, sizeof(eraseData), 100) == 0)
			{
				return 0;
			}
			
			_bytes += sizeof(eraseData);
		}
		
		return 1;
}

// Run once, in part setup of program
void ee24_check_read_write_data(void)
{
	char _dataRead[20], _dataWrite[20];
	int _value = 0;
	
	if(ee24_available() == 1 )
	{
		ee24_read(0, (uint8_t*)_dataRead, sizeof(_dataRead), 100);
		ee_ci_charArray_to_int((char*)_dataRead, &_value);
		
		// Display _value
		// HAL_UART_Transmit(uart, (uint8_t*)dataRead, strlen(dataRead), 100);
		
		_value++;
		ee_ci_int_to_charArray((char*)_dataWrite, _value);
		ee24_write(0, (uint8_t*)_dataWrite, sizeof(_dataWrite), 100);
		
		// Display _value
		// HAL_UART_Transmit(uart, (uint8_t*)dataWrite, strlen(dataWrite), 100);
	}
}

//void ee_ci_charArray_to_int(char *str, int *num)
//{
//	int i;
//	
//	for (i = 0; str[i] != '\0'; i++) 
//	{
//        (*num) = (*num) * 10 + (str[i] - '0');
//	}
//}

//void ee_ci_int_to_charArray(char *str, int num)
//{
//	uint16_t len = strlen(str);
//	
//	memset(str, '\0', len);
//	sprintf((char*)str, "%d", num);
//}

void ee_ci_charArray_to_int(char *str, int *num)
{
	int i;
	
	for (i = 0; str[i] != '\0'; i++) 
	{
        (*num) = (*num) * 10 + (str[i] - '0');
	}
}

void ee_ci_int_to_charArray(char *str, int num)
{
	uint16_t len = sizeof(str);
	
	memset(str, '\0', len);
	sprintf((char*)str, "%d", num);
}


uint8_t i2c_ready(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout)
{
	if (HAL_I2C_IsDeviceReady(hi2c, DevAddress, Trials, Timeout) == HAL_OK)
	{
    return 1;
	}
  else
	{
    return 0;	
	}
}

uint8_t i2c_write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	if(HAL_I2C_Mem_Write(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout) == HAL_OK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t i2c_read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	if (HAL_I2C_Mem_Read(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout) == HAL_OK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}






