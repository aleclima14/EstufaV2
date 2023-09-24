/**
 * @file temperature.h
 * @author Alecsander Lima (aleclima14@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-11 (yyyy-mm-dd)
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __temperature_h__
#define __temperature_h__

/* INCLUDES */
#include "configuration.h"

/* DEFINES */
#define DHT_TYPE DHT22

/* ENUMS */

/* FUNCTIONS */
void fnvStartDHT22(void);
float fvfReadTemperatureDHT22(void);
float fvfReadHumidityDHT22(void);

void fnvInitHeater(void);
void fnvHeaterControl(uint8_t channel, uint8_t power);
void fnvCtrlHeating(void);
void fnvSetTemperature(bool isHeating, int temperature);

#endif // end __temperature_h__