#include <Arduino.h>
#include "hal.hpp"

#define BATTERY_MIN_V 2.9
#define BATTERY_MAX_V 4.0

float getVoltage();
uint8_t calcPercentage(float volts);
void addBatteryChargeInterrupt();
bool isCharging();