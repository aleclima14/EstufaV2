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
#include "app_temperature.h"

/* GLOBAL FUNCTIONS */
void fnvDisplayInit(void);
void fnvBacklightSetValue(int valuePWM);
void fnvDrawMainScreen(void);
void fnvDrawMenuList(void);
void fnvDrawMaterialList(void);
void fnvIncDecBrightness(void);
void fnvHeating(void);
void fnvNothingHere(); 


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

/* TABLE */

static const StSubMenuConfigList stSubMenuConfigTable[] = 
{
  /*MENU INDEX                            MENU NAME             FUNCTION                    */
   {SUBMENU_CONFIG_HEATING,               "Aquecimento",         &fnvDrawMaterialList        },
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

#endif /* __diplay_h__ */
