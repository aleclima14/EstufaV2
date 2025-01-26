/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
*/

#ifndef __diplay_h__
#define __diplay_h__

/* INCLUDES */
#include "Arduino.h"
#include <U8g2lib.h>
#include "configuration.h"
#include "peripherals.h"
#include "eeprom_app.h"
#include "display_screen.h"
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#include "temperature.h"

/* GLOBAL FUNCTIONS */
void fnvDisplayInit(void);
void fnvBacklightSetValue(int valuePWM);
void fnvDrawMainScreen(void);
void fnvDrawMenuList(void);
void fnvIncDecBrightness(void);
void fnvHeating(void);

/* ENUM */
typedef enum
{
  SUBMENU_CONFIG_HEATING,
  SUBMENU_CONFIG_BRIGHTNESS,
  SUBMENU_CONFIG_SOUND,
  SUBMENU_CONFIG_RETURN
}EnSubMenuConfigurationItems;

typedef enum
{
  BRIGHTNESS_1,
  BRIGHTNESS_2,
  BRIGHTNESS_3,
  BRIGHTNESS_4,
  BRIGHTNESS_5,
}EnBrightnessLevel;

typedef enum
{
   TEMPERATURE_1,
   TEMPERATURE_2,
   TEMPERATURE_3,
   TEMPERATURE_4,
   TEMPERATURE_5,
   TEMPERATURE_6,
   TEMPERATURE_7,
   TEMPERATURE_8,
}EnTemperatureLevel;

/* STRUCT */
typedef struct
{
  EnSubMenuConfigurationItems enMenuItem;
  const char *pucMenuName;
  void (*pvFunction)();
}StSubMenuConfigList;

typedef struct
{
  EnBrightnessLevel level;
  const char *levelName;
  const int integerValue;
}StBrightnessLevel;

typedef struct
{
  EnTemperatureLevel level;
  const char *levelName;
  const int integerValue;
}StTemperatureLevel;

/* TABLE */

static const StSubMenuConfigList stSubMenuConfigTable[] = 
{
  /*MENU INDEX                            MENU NAME             FUNCTION                    */
   {SUBMENU_CONFIG_HEATING,               "Aquecimento",         &fnvHeating                 },
   {SUBMENU_CONFIG_BRIGHTNESS,            "Brilho tela",         &fnvIncDecBrightness        },
   {SUBMENU_CONFIG_SOUND,                 "Som",                 &fnvBuzzerToggleStatus      },
   {SUBMENU_CONFIG_RETURN,                "Voltar",              &fnvDrawMainScreen          },
};
#define CONFIG_MENU_TABLE_SIZE (int)(sizeof(stSubMenuConfigTable)/sizeof(StSubMenuConfigList))

static const StBrightnessLevel stBrightnessList[] =
{
   {BRIGHTNESS_1,      "O",        0   },
   {BRIGHTNESS_2,      "25",       25  },
   {BRIGHTNESS_3,      "5O",       50  },
   {BRIGHTNESS_4,      "75",       75  },
   {BRIGHTNESS_5,      "1OO",      100 },
};
#define BRIGHTNESS_LEVELS_SIZE (int)(sizeof(stBrightnessList)/sizeof(StBrightnessLevel))

static const StTemperatureLevel stTemperatureList[] =
{
   {TEMPERATURE_1,      "O",       0  },
   {TEMPERATURE_2,      "4O",      40 },
   {TEMPERATURE_3,      "45",      45 },
   {TEMPERATURE_4,      "5O",      50 },
   {TEMPERATURE_5,      "55",      55 },
   {TEMPERATURE_6,      "6O",      60 },
   {TEMPERATURE_7,      "65",      65 },
   {TEMPERATURE_8,      "7O",      70 },
};
#define TEMPERATURE_LEVELS_SIZE (int)(sizeof(stTemperatureList)/sizeof(StTemperatureLevel))

#endif /* __diplay_h__ */
