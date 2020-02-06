#include <Arduino.h>
#include <esp_adc_cal.h>
#include "hal.hpp"

#define BATTERY_MIN_V 3.2
#define BATTERY_MAX_V 4.1

void setupADC();
void setupBattery();
float getVoltage();
uint8_t calcPercentage(float volts);
void updateBatteryChargeStatus();
bool isCharging();
