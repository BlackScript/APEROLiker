/**
 * Includes all config defines
 *
 * @author    Florian Staeblein
 * @date      2024/01/28
 * @copyright © 2024 Florian Staeblein
 */

#ifndef CONFIG_H
#define CONFIG_H

//===============================================================
// Includes
//===============================================================
#include <Arduino.h>
#include <Adafruit_ST77xx.h>


//===============================================================
// Defines
//===============================================================
#define APP_VERSION                       "V1.2"
#define SETTINGS_NAME                     "Settings"

// Define one of these or none for generic colors
#define APEROLIKER
//#define HUGOLIKER

// This means that the ESP will wait 2 seconds each time it is started
// because the start of the serial debug output on ESP32S2 takes this time
// Uncomment for debug build
#define DEBUG_MIXER

// Using the mixer without wifi makes the firmware more stable
// Uncomment for wifi usage
//#define WIFI_MIXER

//===============================================================
// Enums
//===============================================================
enum MixtureLiquid : uint16_t
{
  eLiquid1 = 0,
  eLiquid2 = 1,
  eLiquid3 = 2,
  eLiquidAll = 3,
  eLiquidNone = 0xFFFF
};
const int MixtureLiquidDashboardMax = 3;
const int MixtureLiquidCleaningMax = 4;

enum MixerState : uint16_t
{
  eMenu = 0,
  eDashboard = 1,
  eCleaning = 2,
  eReset = 3,
  eSettings = 4,
  eScreenSaver = 5,
};

enum MixerEvent : uint16_t
{
  eEntry = 0,
  eMain = 1,
  eExit = 2
};


//===============================================================
// Variant specific settings:
//===============================================================
#if defined(APEROLIKER)

// Draw setting
#define MIXER_NAME                        "APEROLiker"    // Should not exceed 15 characters and be a single word -> will be the dns name in lower case and without white spaces for example "http://aperoliker.local/"
#define LIQUID1_NAME                      "Aperol"        // Should not exceed 8 characters
#define LIQUID2_NAME                      "Soda"          // Should not exceed 8 characters
#define LIQUID3_NAME                      "Prosecco"      // Should not exceed 8 characters

// Color defines
#define TFT_COLOR_STARTPAGE               ST77XX_ORANGE
#define TFT_COLOR_STARTPAGE_FOREGROUND    0xDF9E
#define TFT_COLOR_STARTPAGE_BACKGROUND    0xA6DC
#define TFT_COLOR_TEXT_HEADER             ST77XX_ORANGE
#define TFT_COLOR_TEXT_BODY               ST77XX_WHITE
#define TFT_COLOR_INFOBOX_BORDER          ST77XX_ORANGE
#define TFT_COLOR_INFOBOX_FOREGROUND      ST77XX_ORANGE
#define TFT_COLOR_INFOBOX_BACKGROUND      ST77XX_WHITE
#define TFT_COLOR_MENU_SELECTOR           ST77XX_ORANGE
#define TFT_COLOR_LIQUID_1                ST77XX_ORANGE
#define TFT_COLOR_LIQUID_2                0x0F1F
#define TFT_COLOR_LIQUID_3                0x0390
#define TFT_COLOR_FOREGROUND              ST77XX_WHITE
#define TFT_COLOR_BACKGROUND              ST77XX_BLACK

#define WIFI_COLOR_LIQUID_1               0xFE5000
#define WIFI_COLOR_LIQUID_2               0x01FFFF
#define WIFI_COLOR_LIQUID_3               0x00E784

// Startup image
const String startupImageBottle = "/BottleAperoliker.bmp";
const String startupImageGlass = "/GlassAperoliker.bmp";
const String startupImageLogo = "/LogoAperoliker.bmp";

#define TFT_TRANSPARENCY_COLOR            0x07E0
#define TFT_LOGO_POS_X                    0
#define TFT_LOGO_POS_Y                    25
#define TFT_GLASS_POS_X                   140
#define TFT_GLASS_POS_Y                   85
#define TFT_BOTTLE_POS_X                  40
#define TFT_BOTTLE_POS_Y                  5

#elif defined(HUGOLIKER)

// Draw setting
#define MIXER_NAME                        "HUGOliker"     // Should not exceed 15 characters and be a single word -> will be the dns name in lower case and without white spaces for example "http://hugoliker.local/"
#define LIQUID1_NAME                      "Syrup"         // Should not exceed 8 characters
#define LIQUID2_NAME                      "Soda"          // Should not exceed 8 characters
#define LIQUID3_NAME                      "Prosecco"      // Should not exceed 8 characters

// Color defines
#define TFT_COLOR_STARTPAGE               ST77XX_YELLOW
#define TFT_COLOR_STARTPAGE_FOREGROUND    0xDF9E
#define TFT_COLOR_STARTPAGE_BACKGROUND    0xA6DC
#define TFT_COLOR_TEXT_HEADER             ST77XX_YELLOW
#define TFT_COLOR_TEXT_BODY               ST77XX_WHITE
#define TFT_COLOR_INFOBOX_BORDER          ST77XX_YELLOW
#define TFT_COLOR_INFOBOX_FOREGROUND      ST77XX_BLACK
#define TFT_COLOR_INFOBOX_BACKGROUND      ST77XX_WHITE
#define TFT_COLOR_MENU_SELECTOR           ST77XX_YELLOW
#define TFT_COLOR_LIQUID_1                ST77XX_YELLOW
#define TFT_COLOR_LIQUID_2                ST77XX_CYAN
#define TFT_COLOR_LIQUID_3                0x0390
#define TFT_COLOR_FOREGROUND              ST77XX_WHITE
#define TFT_COLOR_BACKGROUND              ST77XX_BLACK

#define WIFI_COLOR_LIQUID_1               0xD6FF00
#define WIFI_COLOR_LIQUID_2               0x01FFFF
#define WIFI_COLOR_LIQUID_3               0x00E784

// Startup image
const String startupImageBottle = "/BottleHugoliker.bmp";
const String startupImageGlass = "/GlassHugoliker.bmp";
const String startupImageLogo = "/LogoHugoliker.bmp";

#define TFT_TRANSPARENCY_COLOR            0x07E0
#define TFT_LOGO_POS_X                    0
#define TFT_LOGO_POS_Y                    25
#define TFT_GLASS_POS_X                   140
#define TFT_GLASS_POS_Y                   85
#define TFT_BOTTLE_POS_X                  40
#define TFT_BOTTLE_POS_Y                  5

#else

// Draw setting
#define MIXER_NAME                        "Cocktailmixer"   // Should not exceed 15 characters and be a single word -> will be the dns name in lower case and without white spaces for example "http://mixer.local/"
#define LIQUID1_NAME                      "Liquid 1"        // Should not exceed 8 characters
#define LIQUID2_NAME                      "Liquid 2"        // Should not exceed 8 characters
#define LIQUID3_NAME                      "Liquid 3"        // Should not exceed 8 characters

// Color defines
#define TFT_COLOR_STARTPAGE               ST77XX_RED
#define TFT_COLOR_STARTPAGE_FOREGROUND    ST77XX_BLACK
#define TFT_COLOR_STARTPAGE_BACKGROUND    ST77XX_WHITE
#define TFT_COLOR_TEXT_HEADER             ST77XX_RED
#define TFT_COLOR_TEXT_BODY               ST77XX_WHITE
#define TFT_COLOR_INFOBOX_BORDER          ST77XX_RED
#define TFT_COLOR_INFOBOX_FOREGROUND      ST77XX_RED
#define TFT_COLOR_INFOBOX_BACKGROUND      ST77XX_WHITE
#define TFT_COLOR_MENU_SELECTOR           ST77XX_RED
#define TFT_COLOR_LIQUID_1                ST77XX_RED
#define TFT_COLOR_LIQUID_2                ST77XX_GREEN
#define TFT_COLOR_LIQUID_3                ST77XX_BLUE
#define TFT_COLOR_FOREGROUND              ST77XX_WHITE
#define TFT_COLOR_BACKGROUND              ST77XX_BLACK

#define WIFI_COLOR_LIQUID_1               0xCC3D21
#define WIFI_COLOR_LIQUID_2               0x779937
#define WIFI_COLOR_LIQUID_3               0x547ACC

// Startup image
const String startupImageBottle = "/Bottle.bmp";
const String startupImageGlass = "/Glass.bmp";
const String startupImageLogo = "/Logo.bmp";

#define TFT_TRANSPARENCY_COLOR            0x07E0
#define TFT_LOGO_POS_X                    0
#define TFT_LOGO_POS_Y                    25
#define TFT_GLASS_POS_X                   140
#define TFT_GLASS_POS_Y                   85
#define TFT_BOTTLE_POS_X                  40
#define TFT_BOTTLE_POS_Y                  5

#endif

#endif
