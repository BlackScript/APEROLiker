/**
 * Includes all encoder and button functions
 *
 * @author    Florian Staeblein
 * @date      2023/09/15
 * @copyright © 2023 Florian Staeblein
 */
 
#ifndef ENCODERBUTTONDRIVER_H
#define ENCODERBUTTONDRIVER_H

//===============================================================
// Includes
//===============================================================
#include "Config.h"
#include <Arduino.h>


//===============================================================
// Defines
//===============================================================
#define MINIMUMLONGTIMEPRESS_MS   500


//===============================================================
// Class for handling encoder and button functions
//===============================================================
class EncoderButtonDriver
{
  public:
    // Constructor
    EncoderButtonDriver(uint8_t pinEncoderOutA, uint8_t pinEncoderOutB, uint8_t pinEncoderButton, uint8_t pinBuzzer);

    // Initializes the encoder and button driver
    void Begin();
    
    // Return true, if cleaning mode is active. Otherwise false
    bool IsCleaningMode();

    // Return true, if a button press is pending. Otherwise false
    bool IsButtonPress();
    
    // Return true, if a long button press is pending. Otherwise false
    bool IsLongButtonPress();

    // Returns the counted encoder pulses since the last query and resets the counter
    int16_t GetEncoderIncrements();

    // Should be called if encoder edge A changed
    void IRAM_ATTR DoEncoderA();

    // Should be called if encoder edge B changed
    void IRAM_ATTR DoEncoderB();
    
    // Should be called if button was pressed or released
    void IRAM_ATTR ButtonEvent();

  private:
    uint8_t _pinEncoderOutA;
    uint8_t _pinEncoderOutB;
    uint8_t _pinEncoderButton;
    uint8_t _pinBuzzer;

    // Cleaning mode state
    bool _cleaningMode = false;

    // Interrupt service routine variables
    bool _A_set = false;
    bool _B_set = false;

    // Rotary encoder variables
    int16_t _encoderIncrements = 0;

    // Encoder state variables
    bool _isButtonPress = false;
    uint32_t _lastButtonPress_ms = 0;
};
#endif
    
