/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
*/

#include "display.h"

#ifdef DISPLAY_ST7920_128X64 
   U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, SCK_PIN, MOSI_PIN, CS_PIN, RESET_PIN);
#else //DISPLAY_SSD1306_128X64
   U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#endif

/* PRIVATE FUNCTIONS */
void fnvIncDecSelectedSubMenuItem(void);
void fnvWriteBacklightValue(int value);
void fnvSetBrightness(void);
void fnvDrawString(const uint8_t *font, uint8_t x, uint8_t y, const char *string);
void fnvDrawValue(const uint8_t *font, uint8_t x, uint8_t y, double value, uint8_t decimal);

void (*pfvChangeScreen)();

/* GLOBAL VARIABLES */
int brightnessValue = EERead(BACKLIGHT_ADDRESS);
int iSelectedSubMenuItem = 0;
// Adjusts the initial value to be between 0 and 4
int brightnessSelect = brightnessValue / 55;
int subMenu0 = 0;
int subMenu1 = 1;
int subMenu2 = 2;
int subMenu3 = 3;
int selectBarPosition = 1;

bool flagToggleHeating = false;

/**
 * @brief Init u8g2 lib and backlight display
 * 
 */
void fnvDisplayInit(void)
{
   u8g2.begin();
   pinMode(ENABLE_BACKLIGHT, OUTPUT);
   analogWrite(ENABLE_BACKLIGHT, EERead(BACKLIGHT_ADDRESS));
   pfvChangeScreen = fnvDrawMainScreen;
}

/**
 * @brief Set value of brightness
 * 
 * @param valuePWM
 */
void fnvBacklightSetValue(int valuePWM)
{
   if (valuePWM > 250) valuePWM = 250;
   if (valuePWM < 0) valuePWM = 0;

   analogWrite(ENABLE_BACKLIGHT, valuePWM);
}

/**
 * @brief Set font and draw string
 * 
 * @param font family
 * @param x position
 * @param y  position
 * @param string 
 */
void fnvDrawString(const uint8_t *font, uint8_t x, uint8_t y, const char *string)
{
   u8g2.setFont(font);
   u8g2.drawStr(x, y, string);
}

/**
 * @brief Set font and draw value
 * 
 * @param font 
 * @param x 
 * @param y 
 * @param value 
 * @param decimal 
 */
void fnvDrawValue(const uint8_t *font, uint8_t x, uint8_t y, double value, uint8_t decimal)
{
   u8g2.setFont(font);
   u8g2.setCursor(x, y);
   u8g2.print(value, decimal);
}

/**
 * @brief Draw main menu
 * 
 */
void fnvDrawMainScreen(void)
{
   float readTemperature = fvfReadTemperatureDHT22();
   float readHumidity = fvfReadHumidityDHT22();

   u8g2.setDrawColor(1);

   u8g2.firstPage();
   do
   {  
      u8g2.drawXBMP(0, 0, 128, 64, backgroundMainScreen);
      fnvDrawString(FONT_TEXT_SMALL, 17, 13, "ABS");
      fnvDrawString(FONT_TEXT_SMALL, 81, 13, "65 C");

      fnvDrawValue(FONT_TEXT_BIG, 14, 38, readHumidity, 0);
      u8g2.drawXBMP(44, 29, 8, 8, percentage_icon);

      fnvDrawValue(FONT_TEXT_BIG, 78, 38, readTemperature, 0);
      u8g2.drawXBMP(108, 29, 8, 8, celsius_icon);

      // fnvDrawString(FONT_TEXT_BIG, 23, 56, "--:--:--");
      // u8g2.drawXBMP(4, 39, 16, 16, hourglass_icon);
      
   } while (u8g2.nextPage());

   if(ButtonPressed() == BUTTON_SELECT)
   {
      pfvChangeScreen = fnvDrawMenuList;
   }
}

/**
 * @brief Draw Menu List
 * 
 */
void fnvDrawMenuList(void)
{
   u8g2.firstPage();
   do
   {
      fnvIncDecSelectedSubMenuItem();
      u8g2.setDrawColor(1);
      u8g2.drawLine(125, 1, 125, 63);
      u8g2.drawBox(124, 64 / CONFIG_MENU_TABLE_SIZE * iSelectedSubMenuItem, 3, 64 / CONFIG_MENU_TABLE_SIZE);
      u8g2.drawXBMP(2, selectBarPosition, 116, 16, submenuSelectBar);
      u8g2.setFontMode(1);
      u8g2.setDrawColor(2);

      /* Draw line 0 */
      fnvDrawString(FONT_TEXT_SMALL, 6, 13, stSubMenuConfigTable[subMenu0].pucMenuName);
      /* Draw line 1 */
      fnvDrawString(FONT_TEXT_SMALL, 6, 28, stSubMenuConfigTable[subMenu1].pucMenuName);
      /* Draw line 2 */
      fnvDrawString(FONT_TEXT_SMALL, 6, 43, stSubMenuConfigTable[subMenu2].pucMenuName);
      /* Draw line 3 */
      fnvDrawString(FONT_TEXT_SMALL, 6, 58, stSubMenuConfigTable[subMenu3].pucMenuName);
   }while (u8g2.nextPage());
}

/**
 * @brief Config submenu navigation logic
 * 
 */
void fnvIncDecSelectedSubMenuItem(void)
{
   switch (ButtonPressed())
   {
      case BUTTON_UP:
      {
         if (iSelectedSubMenuItem == 0) iSelectedSubMenuItem = 0;
         else iSelectedSubMenuItem--;
         fnvWriteBacklightValue(brightnessValue);
         selectBarPosition = selectBarPosition - 15;
         if(selectBarPosition < 0) selectBarPosition = 1;
         if((iSelectedSubMenuItem+3 < subMenu3) && (subMenu0 > 0) && (selectBarPosition == 1))
         {
            subMenu0--;
            subMenu1--;
            subMenu2--;
            subMenu3--;
         }         
      }
      break;

      case BUTTON_DOWN:
      {
         if (iSelectedSubMenuItem >= CONFIG_MENU_TABLE_SIZE-1) iSelectedSubMenuItem = CONFIG_MENU_TABLE_SIZE-1;
         else iSelectedSubMenuItem++;
         fnvWriteBacklightValue(brightnessValue);
         selectBarPosition = selectBarPosition + 15;
         if(selectBarPosition > 46) selectBarPosition = 46;
         if(iSelectedSubMenuItem > subMenu3)
         {
            subMenu0++;
            subMenu1++;
            subMenu2++;
            subMenu3++;
         }
      }
      break;

      case BUTTON_SELECT:
      {
         switch (stSubMenuConfigTable[iSelectedSubMenuItem].enMenuItem)
         {
            case SUBMENU_CONFIG_RETURN:
            {
               subMenu0 = 0;
               subMenu1 = 1;
               subMenu2 = 2;
               subMenu3 = 3;
               selectBarPosition = 1;
               pfvChangeScreen = stSubMenuConfigTable[iSelectedSubMenuItem].pvFunction;
               iSelectedSubMenuItem = 0;
            }
            break;

            default:
            {
               stSubMenuConfigTable[iSelectedSubMenuItem].pvFunction();
            }
            break;
         }
      }
      break;

      default:
      break;
   }
}

/**
 * @brief Check buttons and set brightness
 * 
 */
void fnvIncDecBrightness(void)
{
   brightnessSelect--;
   if(brightnessSelect < BRIGHTNESS_1) brightnessSelect = BRIGHTNESS_5;
   brightnessValue = stBrightnessList[brightnessSelect].integerValue * 250/100;
   fnvBacklightSetValue(brightnessValue);
}

/**
 * @brief Set the value according to the brightness table 
 * 
 */
void fnvSetBrightness(void)
{
   if(stBrightnessList[brightnessSelect].integerValue > 99)
   {
      u8g2.drawStr(91, 13, stBrightnessList[brightnessSelect].levelName);
   }
   else if(stBrightnessList[brightnessSelect].integerValue < 10)
   {
      u8g2.drawStr(97, 13, stBrightnessList[brightnessSelect].levelName);
   }
   else
   {
      u8g2.drawStr(94, 13, stBrightnessList[brightnessSelect].levelName);
   }
} 

/**
 * @brief Write bightness into "BACKLIGHT_ADDRESS" EEPROM Address
 * 
 * @param brightnessWriteValue 
 */
void fnvWriteBacklightValue(int brightnessWriteValue)
{
   if(brightnessValue != EERead(BACKLIGHT_ADDRESS))
   {
      EEWrite(BACKLIGHT_ADDRESS, brightnessWriteValue);
      fnvBuzzerPlay(1000, 50);
      fnvBuzzerPlay(4000, 50);
      fnvBuzzerPlay(1000, 50);
   }
}

void fnvHeating(void)
{
   flagToggleHeating = !flagToggleHeating;
}


void fnvNothingHere()
{
  //Nothing here
}