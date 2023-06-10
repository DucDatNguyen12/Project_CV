#include "ds1307.h"

#ifdef __cplusplus
extern "C"{
#endif

static I2C_HandleTypeDef *hi2c;
#define i2c_ds1307  hi2c

const uint8_t codeDayOfWeek[7][4] = {"Sun", "Mon", "Tue", "Web", "Thu", "Fri", "Sat"};
	
/**
 * @brief Initializes the DS1307 module. Sets clock halt bit to 0 to start timing.
 * @param hi2c User I2C handle pointer.
 */
void ds1307_init(I2C_HandleTypeDef *hi2cIn) 
{
	i2c_ds1307 = hi2cIn;
	
	DS1307_SetClockHalt(0);
}

/**
 * @brief Sets clock halt bit.
 * @param halt Clock halt bit to set, 0 or 1. 0 to start timing, 0 to stop.
 */
void DS1307_SetClockHalt(uint8_t halt) 
{
	uint8_t ch = (halt ? 1 << 7 : 0);
	
	DS1307_SetRegByte(DS1307_REG_SECOND, ch | (DS1307_GetRegByte(DS1307_REG_SECOND) & 0x7f));
}

/**
 * @brief Gets clock halt bit.
 * @return Clock halt bit, 0 or 1.
 */
uint8_t DS1307_GetClockHalt(void) 
{
	return (DS1307_GetRegByte(DS1307_REG_SECOND) & 0x80) >> 7;
}

/**
 * @brief Sets the byte in the designated DS1307 register to value.
 * @param regAddr Register address to write.
 * @param val Value to set, 0 to 255.
 */
void DS1307_SetRegByte(uint8_t regAddr, uint8_t val) 
{
	uint8_t bytes[2] = { regAddr, val };
	
	HAL_I2C_Master_Transmit(i2c_ds1307, DS1307_I2C_ADDR << 1, bytes, 2, DS1307_TIMEOUT);
}

/**
 * @brief Gets the byte in the designated DS1307 register.
 * @param regAddr Register address to read.
 * @return Value stored in the register, 0 to 255.
 */
uint8_t DS1307_GetRegByte(uint8_t regAddr) 
{
	uint8_t val;
	
	HAL_I2C_Master_Transmit(i2c_ds1307, DS1307_I2C_ADDR << 1, &regAddr, 1, DS1307_TIMEOUT);
	HAL_I2C_Master_Receive(i2c_ds1307, DS1307_I2C_ADDR << 1, &val, 1, DS1307_TIMEOUT);
	return val;
}

/**
 * @brief Toggle square wave output on pin 7.
 * @param mode DS1307_ENABLED (1) or DS1307_DISABLED (0);
 */
void DS1307_SetEnableSquareWave(DS1307_SquareWaveEnable mode)
{
	uint8_t controlReg = DS1307_GetRegByte(DS1307_REG_CONTROL);
	uint8_t newControlReg = (controlReg & ~(1 << 4)) | ((mode & 1) << 4);
	DS1307_SetRegByte(DS1307_REG_CONTROL, newControlReg);
}

/**
 * @brief Set square wave output frequency.
 * @param rate DS1307_1HZ (0b00), DS1307_4096HZ (0b01), DS1307_8192HZ (0b10) or DS1307_32768HZ (0b11).
 */
void DS1307_SetInterruptRate(DS1307_Rate rate)
{
	uint8_t controlReg = DS1307_GetRegByte(DS1307_REG_CONTROL);
	uint8_t newControlReg = (controlReg & ~0x03) | rate;
	DS1307_SetRegByte(DS1307_REG_CONTROL, newControlReg);
}

/**
 * @brief Decodes the raw binary value stored in registers to decimal format.
 * @param bin Binary-coded decimal value retrieved from register, 0 to 255.
 * @return Decoded decimal value.
 */
static uint8_t DS1307_DecodeBCD(uint8_t bin) 
{
	return (((bin & 0xf0) >> 4) * 10) + (bin & 0x0f);
}

/**
 * @brief Encodes a decimal number to binaty-coded decimal for storage in registers.
 * @param dec Decimal number to encode.
 * @return Encoded binary-coded decimal value.
 */
static uint8_t DS1307_EncodeBCD(uint8_t dec) 
{
	return (dec % 10 + ((dec / 10) << 4));
}

/**
 * @brief Gets the current day of week.
 * @return Days from last Sunday, 0 to 6.
 */
uint8_t ds1307_get_day_of_week(void) 
{
	return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_DOW));
}

/**
 * @brief Gets the current day of month.
 * @return Day of month, 1 to 31.
 */
uint8_t ds1307_get_date(void) 
{
	return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_DATE));
}

/**
 * @brief Gets the current month.
 * @return Month, 1 to 12.
 */
uint8_t ds1307_get_month(void) 
{
	return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_MONTH));
}

/**
 * @brief Gets the current year.
 * @return Year, 2000 to 2099.
 */
uint16_t ds1307_get_year(void) 
{
	uint16_t cen = DS1307_GetRegByte(DS1307_REG_CENT) * 100;
	
	return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_YEAR)) + cen;
}

/**
 * @brief Gets the current hour in 24h format.
 * @return Hour in 24h format, 0 to 23.
 */
uint8_t ds1307_get_hour(void) 
{
	return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_HOUR) & 0x3f);
}

/**
 * @brief Gets the current minute.
 * @return Minute, 0 to 59.
 */
uint8_t ds1307_get_minute(void) 
{
	return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_MINUTE));
}

/**
 * @brief Gets the current second. Clock halt bit not included.
 * @return Second, 0 to 59.
 */
uint8_t ds1307_get_second(void) 
{
	return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_SECOND) & 0x7f);
}

/**
 * @brief Gets the stored UTC hour offset.
 * @note  UTC offset is not updated automatically.
 * @return UTC hour offset, -12 to 12.
 */
int8_t ds1307_get_time_zone_hour(void) 
{
	return DS1307_GetRegByte(DS1307_REG_UTC_HR);
}

/**
 * @brief Gets the stored UTC minute offset.
 * @note  UTC offset is not updated automatically.
 * @return UTC time zone, 0 to 59.
 */
uint8_t ds1307_get_time_zone_min(void) 
{
	return DS1307_GetRegByte(DS1307_REG_UTC_MIN);
}

char *ds1307_get_dow(int num)
{
	return  (char*)codeDayOfWeek[num];
}

void ds1307_get_all(Ds1307_TypDef_t *ds1307_X)
{
	ds1307_X->Time.sec = ds1307_get_second();
	ds1307_X->Time.min = ds1307_get_minute();
	ds1307_X->Time.hour = ds1307_get_hour();
	
	ds1307_X->Date.dow = ds1307_get_day_of_week();
	
	ds1307_X->Date.date = ds1307_get_date();
	ds1307_X->Date.month = ds1307_get_month();
	ds1307_X->Date.year = ds1307_get_year();
}

/**
 * @brief Sets the current day of week.
 * @param dayOfWeek Days since last Sunday, 0 to 6.
 */
void ds1307_set_day_of_week(uint8_t dayOfWeek) 
{
	DS1307_SetRegByte(DS1307_REG_DOW, DS1307_EncodeBCD(dayOfWeek));
}

/**
 * @brief Sets the current day of month.
 * @param date Day of month, 1 to 31.
 */
void ds1307_set_day(uint8_t date) 
{
	DS1307_SetRegByte(DS1307_REG_DATE, DS1307_EncodeBCD(date));
}

/**
 * @brief Sets the current month.
 * @param month Month, 1 to 12.
 */
void ds1307_set_month(uint8_t month) 
{
	DS1307_SetRegByte(DS1307_REG_MONTH, DS1307_EncodeBCD(month));
}

/**
 * @brief Sets the current year.
 * @param year Year, 2000 to 2099.
 */
void ds1307_set_year(uint16_t year) 
{
	DS1307_SetRegByte(DS1307_REG_CENT, year / 100);
	DS1307_SetRegByte(DS1307_REG_YEAR, DS1307_EncodeBCD(year % 100));
}

/**
 * @brief Sets the current hour, in 24h format.
 * @param hour_24mode Hour in 24h format, 0 to 23.
 */
void ds1307_set_hour(uint8_t hour_24mode) 
{
	DS1307_SetRegByte(DS1307_REG_HOUR, DS1307_EncodeBCD(hour_24mode & 0x3f));
}

/**
 * @brief Sets the current minute.
 * @param minute Minute, 0 to 59.
 */
void ds1307_set_minute(uint8_t minute) 
{
	DS1307_SetRegByte(DS1307_REG_MINUTE, DS1307_EncodeBCD(minute));
}

/**
 * @brief Sets the current second.
 * @param second Second, 0 to 59.
 */
void ds1307_set_second(uint8_t second) 
{
	uint8_t ch = DS1307_GetClockHalt();
	DS1307_SetRegByte(DS1307_REG_SECOND, DS1307_EncodeBCD(second | ch));
}

/**
 * @brief Sets UTC offset.
 * @note  UTC offset is not updated automatically.
 * @param hr UTC hour offset, -12 to 12.
 * @param min UTC minute offset, 0 to 59.
 */
void ds1307_set_time_zone(int8_t hr, uint8_t min) 
{
	DS1307_SetRegByte(DS1307_REG_UTC_HR, hr);
	DS1307_SetRegByte(DS1307_REG_UTC_MIN, min);
}

void ds1307_set_all(Ds1307_TypDef_t *ds1307In)
{
	ds1307_set_second(ds1307In->Time.sec);
	ds1307_set_minute(ds1307In->Time.min);
	ds1307_set_hour(ds1307In->Time.hour);
	
	ds1307_set_day_of_week(ds1307In->Date.dow);
	ds1307_set_day(ds1307In->Date.date);
	ds1307_set_month(ds1307In->Date.month);
	ds1307_set_year(ds1307In->Date.month);	
}


#ifdef __cplusplus
}

#endif


