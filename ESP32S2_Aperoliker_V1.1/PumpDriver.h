/**
 * Includes all pump functions
 *
 * @author    Florian Staeblein
 * @date      2024/01/28
 * @copyright © 2024 Florian Staeblein
 */
 
#ifndef PUMPDRIVER_H
#define PUMPDRIVER_H

//===============================================================
// Includes
//===============================================================
#include "Config.h"
#include <Arduino.h>


//===============================================================
// Defines
//===============================================================
#define CYCLETIME_MS    (uint32_t)1000

//===============================================================
// Class for handling pump driver functions
//===============================================================
class PumpDriver
{
  public:
    // Constructor
    PumpDriver(uint8_t pinPump1, uint8_t pinPump2, uint8_t pinPump3);

    // Initializes the pump driver
    void Begin();

    // Enables pump output
    void IRAM_ATTR Enable();
    
    // Disables pump output
    void IRAM_ATTR Disable();

    // Return true, if the pumps are enabled. Otherwise false
    bool IsEnabled();

    // Sets pumps from percentage (0-100%)
    void UpdatePercentages(double pump1_percentage, double pump2_percentage, double pump3_percentage, bool maximizeHighest);
    
    // Should be called every < 50 ms
    void IRAM_ATTR UpdateOutputs();

  private:
    uint8_t _pinPump1;
    uint8_t _pinPump2;
    uint8_t _pinPump3;
    
    bool _isPumpEnabled = false;
    
    uint32_t _pwmPump1_ms;
    uint32_t _pwmPump2_ms;
    uint32_t _pwmPump3_ms;
    uint32_t lastPumpCycle_ms = 0;
    
    // Set pump channel values
    void SetPWM(uint32_t pwm1, uint32_t pwm2, uint32_t pwm3);
};

#endif
