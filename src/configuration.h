/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
*/

#ifndef __configuration_h__
#define __configuration_h__

/* INCLUDES */
#include "Arduino.h"
#include "gpio.h"

/* DEFINES */
#define DISPLAY_ST7920_128X64
// #define DISPLAY_SSD1306_128X64

/* Peripherals */
#define BUZZER_PIN         GPIO_PIN_6
#define BUTTON_UP_PIN      GPIO_PIN_7  
#define BUTTON_DOWN_PIN    GPIO_PIN_4
#define BUTTON_SELECT_PIN  GPIO_PIN_2

/* Display ST7920 128x64 pixels */
#define SCK_PIN            GPIO_PIN_13
#define MOSI_PIN           GPIO_PIN_11
#define CS_PIN             GPIO_PIN_10
#define ENABLE_BACKLIGHT   GPIO_PIN_9
#define RESET_PIN          GPIO_PIN_8 

/* Sensor */
#define TEMP_SENSOR_PIN    GPIO_PIN_12

/* Power Channel */
#define POWER_CH_1_PIN     GPIO_PIN_5
#define POWER_CH_2_PIN     GPIO_PIN_3

/* EEPROM ADDRESS */
#define BACKLIGHT_ADDRESS  0
#define BUZZER_ADDRESS     1

/* FONT */
#define FONT_TEXT_SMALL u8g2_font_t0_11_mr
#define FONT_TEXT_BIG   u8g2_font_helvB18_tf

#endif /* __configuration_h__ */
