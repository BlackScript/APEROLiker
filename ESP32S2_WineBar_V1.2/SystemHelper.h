/**
 * Includes all system helper functions
 *
 * @author    Florian Staeblein
 * @date      2024/01/28
 * @copyright © 2024 Florian Staeblein
 */
 
#ifndef SYSTEMHELPER_H
#define SYSTEMHELPER_H

//===============================================================
// Inlcudes
//===============================================================
#include <Arduino.h>
#include <ESP.h>
#include <WiFi.h>

//===============================================================
// Returns the complete system info as string
//===============================================================
String GetSystemInfoString();

//===============================================================
// Returns a string for a wifi power
//===============================================================
String WifiPowerToString(wifi_power_t power);

#endif