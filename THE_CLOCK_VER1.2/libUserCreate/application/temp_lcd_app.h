#ifndef TEMP_LCD_APP_H
#define TEMP_LCD_APP_H

#include "main.h"

#include "ds18b20.h"

void tempLcdApp_init(DS18B20_Name *dsTempIn);

void tempLcdApp_update_basic_tempCur(char *str);

void tempLcdApp_update_tempCur(char *str);

void tempLcdApp_update_edit_temp_set(char *str);

void tempLcdApp_type_sensor(char *str);

void tempLcdApp_update_edit_number_sensor(char *str);

#endif



