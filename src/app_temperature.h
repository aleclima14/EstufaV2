/**
 * @file app_temperature.h
 * @author Alecsander Lima (aleclima14@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-23 (yyyy-mm-dd)
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __app_temperature_h__
#define __app_temperature_h__

/* INCLUDES */
#include "configuration.h"
#include "temperature.h"

/* DEFINES */

/* ENUMS */
typedef enum
{
   FILAMENT_ABS,
   FILAMENT_PLA,
   FILAMENT_PETG,
   FILAMENT_TPU,
   FILAMENT_NYLON,
   RETURN,
}EnMaterialList;

/* STRUCTS */
typedef struct 
{
   EnMaterialList enMaterial;
   const char *pucMaterialName;
   uint8_t SetTemperature;
}StMaterialList;

/* TABLE */
static const StMaterialList stMaterialListTable[] = 
{
   /* MATERIAL INDEX     MATERIAL NAME     MATERIAL TEMPERATURE  */
   {FILAMENT_ABS,       "ABS",             60,                    },
   {FILAMENT_PLA,       "PLA",             40,                    },
   {FILAMENT_PETG,      "PETG",            50,                    },
   {FILAMENT_TPU,       "TPU",             45,                    },
   {FILAMENT_NYLON,     "NYLON",           65,                    },
   {RETURN,             "Voltar",          NULL,                  },
};
#define MATERIAL_LIST_SIZE (int)(sizeof(stMaterialListTable)/sizeof(StMaterialList))

/* FUNCTIONS */


#endif // end __app_temperature_h__