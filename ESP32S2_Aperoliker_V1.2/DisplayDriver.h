/**
 * Includes all display functions
 *
 * @author    Florian Staeblein
 * @date      2024/01/28
 * @copyright © 2024 Florian Staeblein
 */
 
#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H

//===============================================================
// Includes
//===============================================================
#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Fonts/FreeSans9pt7b.h>
#include "Config.h"
#include "StateMachine.h"
#include "SPIFFSImageReader.h"
#include "AngleHelper.h"
#include "FlowMeterDriver.h"


//===============================================================
// Defines
//===============================================================
#define TFT_DEG2RAD                 0.017453292519943295769236907684886F
#define TFT_WIDTH                   240
#define TFT_HEIGHT                  240

#define HEADEROFFSET_Y              30
#define HEADER_MARGIN               10
#define X0_DOUGHNUTCHART            65
#define Y0_DOUGHNUTCHART            130
#define R_INNER_DOUGHNUTCHART       30
#define R_OUTER_DOUGHNUTCHART       60
#define X_LEGEND                    (X0_DOUGHNUTCHART + R_OUTER_DOUGHNUTCHART + 10)
#define Y_LEGEND                    (Y0_DOUGHNUTCHART - R_OUTER_DOUGHNUTCHART)
#define WIDTH_LEGEND                (TFT_WIDTH - X_LEGEND - 10)
#define HEIGHT_LEGEND               (TFT_HEIGHT - Y_LEGEND - 10)

#define INFOBOX_MARGIN_VERT         60
#define INFOBOX_MARGIN_HORI         25
#define INFOBOX_CORNERRADIUS        8

#define MENU_MARGIN_HORI            18
#define MENU_MARGIN_ICON            8
#define MENU_MARGIN_TEXT            47
#define MENU_SELECTOR_HEIGHT        38
#define MENU_SELECTOR_CORNERRADIUS  8
#define MENU_LINEOFFSET             43

#define SHORTLINEOFFSET             20
#define LONGLINEOFFSET              30
#define LOONGLINEOFFSET             50
#define SPACERANGLE_DEGREES         1  // Angle which will be displayed as spacer between pie elements (will be multiplied by 2, left and right of the setting angle)

#define SCREENSAVER_STARCOUNT       30

//===============================================================
// Icons
//===============================================================
// 'cleaning', 32x32px
const unsigned char icon_cleaning [] PROGMEM =
{
	0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x88, 0x24, 0xc2, 0x01, 
	0x90, 0x35, 0xc0, 0x21, 0x20, 0x84, 0xc0, 0x71, 0x40, 0x44, 0x00, 0x20, 0x88, 0x20, 0x03, 0x00, 
	0x10, 0x04, 0x01, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x7f, 0xdb, 0x1f, 0x03, 0x00, 0x0e, 0x00, 0x61, 
	0x00, 0x0a, 0x01, 0xf0, 0x98, 0x20, 0x03, 0x60, 0x40, 0x44, 0x00, 0x20, 0x20, 0x84, 0x00, 0x00, 
	0x10, 0x35, 0x11, 0x04, 0x88, 0x24, 0xa2, 0x04, 0x00, 0x04, 0xa0, 0x06, 0x00, 0x04, 0x68, 0x1a, 
	0x00, 0x04, 0x51, 0xca, 0x18, 0x00, 0x0e, 0x70, 0x7c, 0x00, 0x98, 0x08, 0x38, 0x10, 0xc6, 0x73, 
	0x38, 0x38, 0xc0, 0x01, 0x00, 0x10, 0x9c, 0x19, 0x00, 0x00, 0x05, 0xe0, 0x80, 0x01, 0x58, 0x0a, 
	0xc0, 0x03, 0x28, 0x12, 0x80, 0x01, 0xa0, 0x04, 0x00, 0x00, 0x30, 0x04, 0x00, 0x00, 0x10, 0x04
};
// 'dashboard', 32x32px
const unsigned char icon_dashboard [] PROGMEM =
{
	0x00, 0xf0, 0x0f, 0x00, 0x00, 0x1e, 0x78, 0x00, 0x80, 0xe3, 0xcf, 0x01, 0xc0, 0x3c, 0x3c, 0x03, 
	0x60, 0xe7, 0xe7, 0x06, 0xb0, 0xf9, 0x9f, 0x0d, 0xd8, 0x8e, 0x71, 0x1b, 0x6c, 0x0f, 0xf0, 0x36, 
	0xb4, 0x09, 0x90, 0x2d, 0xd6, 0x00, 0x00, 0x6b, 0xda, 0x00, 0x10, 0x5b, 0xea, 0x01, 0x88, 0x57, 
	0x2b, 0x00, 0x0c, 0xd4, 0x3d, 0x00, 0x06, 0xbc, 0x35, 0x80, 0x03, 0xac, 0x75, 0xc0, 0x03, 0xae, 
	0x65, 0xc0, 0x03, 0xa6, 0x05, 0x80, 0x01, 0xa0, 0x0d, 0x00, 0x00, 0xb0, 0xfb, 0xff, 0xff, 0xdf, 
	0x02, 0x00, 0x00, 0x40, 0x02, 0xfe, 0x7f, 0x40, 0x06, 0x03, 0xc0, 0x60, 0x84, 0xf1, 0x8f, 0x21, 
	0x8c, 0xf1, 0x8f, 0x31, 0x18, 0x03, 0xc0, 0x18, 0x30, 0xfe, 0x7f, 0x0c, 0x60, 0x00, 0x00, 0x06, 
	0xc0, 0x00, 0x00, 0x03, 0x80, 0x03, 0xc0, 0x01, 0x00, 0x1e, 0x78, 0x00, 0x00, 0xf0, 0x0f, 0x00
};
// 'eraser', 32x32px
const unsigned char icon_eraser [] PROGMEM =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0xe3, 0x00, 
	0x00, 0x80, 0xc1, 0x01, 0x00, 0xc0, 0x80, 0x03, 0x00, 0x60, 0x00, 0x07, 0x00, 0x30, 0x00, 0x0e, 
	0x00, 0x18, 0x00, 0x1c, 0x00, 0x0c, 0x00, 0x38, 0x00, 0x06, 0x00, 0x70, 0x00, 0x03, 0x00, 0x60, 
	0x80, 0x01, 0x00, 0x40, 0xc0, 0x00, 0x00, 0x60, 0xe0, 0x00, 0x00, 0x30, 0xf0, 0x01, 0x00, 0x18, 
	0x98, 0x03, 0x00, 0x0c, 0x0c, 0x07, 0x00, 0x06, 0x06, 0x0e, 0x00, 0x03, 0x06, 0x1c, 0x80, 0x01, 
	0x06, 0x38, 0xc0, 0x00, 0x02, 0x70, 0x60, 0x00, 0x06, 0xe0, 0x30, 0x00, 0x06, 0xc0, 0x19, 0x00, 
	0x06, 0x80, 0x0f, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x18, 0x00, 0x03, 0x00, 0x30, 0x80, 0x01, 0x00, 
	0x60, 0xc0, 0x00, 0x00, 0xc0, 0xfb, 0x00, 0x00, 0x80, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00
};
// 'reset', 32x32px
const unsigned char icon_reset [] PROGMEM =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xc0, 0x07, 0x00, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0x78, 0x0c, 0x00, 0x00, 0x3c, 0x1c, 
	0x00, 0x00, 0x0f, 0x38, 0x00, 0x80, 0x47, 0x30, 0x00, 0xe0, 0x61, 0x70, 0x00, 0x70, 0xe0, 0x60, 
	0x00, 0x3c, 0xe4, 0x60, 0x00, 0x0e, 0xee, 0x70, 0x80, 0x0f, 0x4e, 0x3c, 0xc0, 0x1f, 0x0e, 0x1e, 
	0xf0, 0x18, 0x8e, 0x07, 0x38, 0x38, 0xc0, 0x01, 0x1e, 0x30, 0xf0, 0x00, 0x06, 0x60, 0x38, 0x00, 
	0x06, 0xe0, 0x1e, 0x00, 0x06, 0xc0, 0x07, 0x00, 0x0e, 0xc0, 0x03, 0x00, 0x1c, 0xe0, 0x00, 0x00, 
	0x18, 0x78, 0x00, 0x00, 0x38, 0x1c, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfe, 0x3f, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'settings', 32x32px
const unsigned char icon_settings [] PROGMEM =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x80, 0x01, 0x0c, 0x30, 0x80, 0x01, 0x0c, 
	0x30, 0x80, 0x01, 0x0c, 0x30, 0xe0, 0x07, 0x0c, 0x30, 0xe0, 0x07, 0x0c, 0x30, 0x60, 0x06, 0x0c, 
	0x30, 0xe0, 0x07, 0x0c, 0x30, 0xe0, 0x07, 0x0c, 0xfc, 0x80, 0x01, 0x3f, 0xfc, 0x80, 0x01, 0x3f, 
	0xcc, 0x80, 0x01, 0x33, 0xfc, 0x80, 0x01, 0x3f, 0xfc, 0xbc, 0x3d, 0x3f, 0x30, 0xbe, 0x7d, 0x0c, 
	0x30, 0x36, 0x6c, 0x0c, 0x30, 0xce, 0x73, 0x0c, 0x30, 0xee, 0x77, 0x0c, 0xb0, 0x77, 0xee, 0x0d, 
	0xb0, 0x33, 0xcc, 0x0d, 0xb0, 0x33, 0xcc, 0x0d, 0xb0, 0x77, 0xee, 0x0d, 0x30, 0xee, 0x77, 0x0c, 
	0x30, 0xce, 0x73, 0x0c, 0x30, 0x36, 0x6c, 0x0c, 0x30, 0x7e, 0x7e, 0x0c, 0x30, 0xfc, 0x3f, 0x0c, 
	0x30, 0xc0, 0x03, 0x0c, 0x30, 0xc0, 0x03, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'noWifi', 24x24px
const unsigned char icon_noWifi [] PROGMEM =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x70, 0xfe, 0x00, 0xe0, 
	0xff, 0x03, 0xd0, 0x81, 0x0f, 0x98, 0x03, 0x1c, 0x1c, 0x1f, 0x38, 0x00, 0xfe, 0x01, 0xc0, 0xfc, 
	0x03, 0xe0, 0x18, 0x07, 0x70, 0x30, 0x0c, 0x00, 0x76, 0x00, 0x00, 0xe7, 0x00, 0x80, 0xc3, 0x01, 
	0x00, 0x80, 0x03, 0x00, 0x00, 0x07, 0x00, 0x18, 0x0e, 0x00, 0x18, 0x0c, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'wifi', 24x24px
const unsigned char icon_wifi [] PROGMEM =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xc0, 
	0xff, 0x03, 0xf0, 0x01, 0x0f, 0x38, 0x00, 0x1c, 0x1c, 0x00, 0x38, 0x00, 0x7e, 0x00, 0x80, 0xff, 
	0x01, 0xc0, 0xc3, 0x03, 0xe0, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0xff, 0x00, 
	0x00, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'device', 24x24px
const unsigned char icon_device [] PROGMEM =
{
	0x00, 0x00, 0x00, 0xc0, 0xff, 0x03, 0x20, 0x18, 0x04, 0xa0, 0xff, 0x05, 0x60, 0x00, 0x06, 0x60, 
	0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 
	0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x06, 
	0x60, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x06, 0xe0, 0xff, 0x07, 0x20, 0x00, 0x04, 0x20, 
	0x00, 0x04, 0xc0, 0xff, 0x03, 0x00, 0x00, 0x00
};

// 'copyright', 20x20px
const unsigned char icon_copyright [] PROGMEM = {
	0x80, 0x1f, 0x00, 0xe0, 0x7f, 0x00, 0x70, 0xe0, 0x00, 0x18, 0x80, 0x01, 0x0c, 0x00, 0x03, 0x06, 
	0x06, 0x06, 0x86, 0x1f, 0x06, 0xc3, 0x19, 0x0c, 0xc3, 0x00, 0x0c, 0x63, 0x00, 0x0c, 0x63, 0x00, 
	0x0c, 0xc3, 0x00, 0x0c, 0xc3, 0x19, 0x0c, 0x86, 0x1f, 0x06, 0x06, 0x06, 0x06, 0x0c, 0x00, 0x03, 
	0x18, 0x80, 0x01, 0x70, 0xe0, 0x00, 0xe0, 0x7f, 0x00, 0x80, 0x1f, 0x00
};

//===============================================================
// Class for screen saver stars
//===============================================================
class Star
{
  public:
    int16_t X = 0;
    int16_t Y = 0;
    int16_t Size = 5;
    int16_t MaxSize = 0;
    bool FullStars = false;
};

//===============================================================
// Class for handling display functions
//===============================================================
class DisplayDriver
{
  public:
    // Constructor
    DisplayDriver();

    // Initializes the display driver
    void Begin(Adafruit_ST7789* tft, bool spiffsAvailable);

    // Sets the menu state
    void SetMenuState(MixerState state);

    // Sets the dashboard liquid value
    void SetDashboardLiquid(MixtureLiquid liquid);

    // Sets the cleaning liquid value
    void SetCleaningLiquid(MixtureLiquid liquid);

    // Sets the angles values
    void SetAngles(int16_t liquid1Angle_Degrees, int16_t liquid2Angle_Degrees, int16_t liquid3Angle_Degrees);

    // Sets the percentage values
    void SetPercentages(double liquid1_Percentage, double liquid2_Percentage, double liquid3_Percentage);

    // Shows intro page
    void ShowIntroPage();
    
    // Shows help page
    void ShowHelpPage();

    // Shows menu page
    void ShowMenuPage();

    // Shows dashboard page
    void ShowDashboardPage();
    
    // Shows cleaning page
    void ShowCleaningPage();

    // Shows settings page
    void ShowSettingsPage();

    // Shows screen saver page
    void ShowScreenSaverPage();
    
    // Draws the Wifi icon
    void DrawWifiIcons();
    
    // Draws the info box
    void DrawInfoBox(const String &line1, const String &line2);

    // Draws the menu partially
    void DrawMenu(bool isfullUpdate = false);

    // Draw checkboxes
    void DrawCheckBoxes();
    
    // Draws the legend
    void DrawLegend();
    
    // Draws current values partially
    void DrawCurrentValues(bool isfullUpdate = false);

    // Draws full doughnut chart
    void DrawDoughnutChart3();
    
    // Draws doughnut chart partially
    void DrawDoughnutChart3(bool clockwise, bool isfullUpdate = false);

    // Draws settings partially
    void DrawSettings(bool isfullUpdate = false);

    // Draws screen saver
    void DrawScreenSaver();

  private:
    // Display variable
    Adafruit_ST7789* _tft;
    char _output[30];

    // Image pointer
    SPIFFSImage* _imageBottle;
    SPIFFSImage* _imageGlass;
    SPIFFSImage* _imageLogo;
    SPIFFSImageReader reader;
    ImageReturnCode _imagesAvailable = IMAGE_ERR_FILE_NOT_FOUND;

    // Current mixture settings
    MixerState _menuState = eDashboard;
    MixtureLiquid _dashboardLiquid = eLiquid1;
    MixtureLiquid _cleaningLiquid = eLiquidAll;
    int16_t _liquid1Angle_Degrees = 0;
    int16_t _liquid2Angle_Degrees = 0;
    int16_t _liquid3Angle_Degrees = 0;
    double _liquid1_Percentage = 0.0;
    double _liquid2_Percentage = 0.0;
    double _liquid3_Percentage = 0.0;
        
    // Last draw values
    MixerState _lastDraw_MenuState = eDashboard;
    int16_t _lastDraw_liquid1Angle_Degrees = 0;
    int16_t _lastDraw_liquid2Angle_Degrees = 0;
    int16_t _lastDraw_liquid3Angle_Degrees = 0;
    double _lastDraw_liquid1_Percentage = 0.0;
    double _lastDraw_liquid2_Percentage = 0.0;
    double _lastDraw_liquid3_Percentage = 0.0;
    String _lastDraw_Liquid1String = "";
    String _lastDraw_Liquid2String = "";
    String _lastDraw_Liquid3String = "";
    uint32_t _lastDraw_cycleTimespan_ms = 0;
    wifi_mode_t _lastDraw_wifiMode = WIFI_MODE_NULL;

    // Screen saver variables
    Star _stars[SCREENSAVER_STARCOUNT];
    int16_t _lastLogo_x = 10;
    int16_t _lastLogo_y = TFT_HEIGHT / 2;
    int16_t _xDir = 1;
    int16_t _yDir = 1;

    // Draws default header Text
    void DrawHeader();
    
    // Draws header Text
    void DrawHeader(const String &text, bool withIcons = true);
    
    // Draws only partial update of arcs
    void DrawPartial(int16_t angle, int16_t lastAngle,  uint16_t colorAfter, uint16_t colorBefore, bool clockwise);
    
    // Draws an arc with a defined thickness
    void FillArc(int16_t start_angle, int16_t distance_Degrees, uint16_t color);
    
    // Draws a string centered
    void DrawCenteredString(const String &text, int16_t x, int16_t y, bool underlined, uint16_t lineColor);
    
    // Formats double value
    String FormatValue(double value, int mainPlaces, int decimalPlaces);

    // Draws a star
    void DrawStar(int16_t x0, int16_t y0, bool fullStars, uint16_t color, int16_t size = 0);
    
    // Draws a star tail
    void DrawStarTail(int16_t x0, int16_t y0, int16_t start, int16_t end, bool fullStars, uint16_t color);
};


//===============================================================
// Global variables
//===============================================================
extern DisplayDriver Display;


#endif
