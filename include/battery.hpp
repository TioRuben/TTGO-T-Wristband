#include <Arduino.h>
#include "hal.hpp"

#define BATTERY_MIN_V 3.8
#define BATTERY_MAX_V 4.1

float getVoltage();
uint8_t calcPercentage(float volts);
void addBatteryChargeInterrupt();
bool isCharging();