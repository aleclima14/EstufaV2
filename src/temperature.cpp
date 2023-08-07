/**
 * @file peripherals.cpp
 * @author Alecsander Lima (aleclima14@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-11 (yyyy-mm-dd)
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* INCLUDES */
#include "temperature.h"
#include <DHT.h>

extern bool flagToggleHeating;
/**
 * @brief DHT Constructor
 * 
 * @return DHT 
 */
DHT dht(TEMP_SENSOR_PIN, DHT_TYPE);   

/**
 * @brief Init the DHT22 sensor
 * 
 */
void fnvStartDHT22(void)
{
   dht.begin();
}

/**
 * @brief Read Ambient Temperature
 * 
 * @return Temperature 
 */
float fvfReadTemperatureDHT22(void)
{
   return dht.readTemperature();
}

/**
 * @brief Read Ambient Humidity
 * 
 * @return Temperature 
 */
float fvfReadHumidityDHT22(void)
{
   float humidity = dht.readHumidity();
   if(humidity > 99)
   {
      humidity = 99;
   }
   return humidity;
}

/**
 * @brief Init Heater 
 * 
 */
void fnvInitHeater(void)
{
   pinMode(POWER_CH_1_PIN, OUTPUT);
}

void fnvHeaterControl(uint8_t channel, uint8_t power)
{
   analogWrite(channel, power);
}

void fnvCtrlHeating(void)
{
   if((flagToggleHeating == true) && (fvfReadTemperatureDHT22() < 65))
   {
      fnvHeaterControl(POWER_CH_1_PIN, 255);
      fnvHeaterControl(POWER_CH_2_PIN, 170);
   }
   else
   {
      fnvHeaterControl(POWER_CH_1_PIN, 0);
      fnvHeaterControl(POWER_CH_2_PIN, 0);
   }
}