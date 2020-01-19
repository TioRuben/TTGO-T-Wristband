#include "battery.hpp"

float getVoltage()
{
  uint16_t v = analogRead(BATT_ADC_PIN);
  return ((float)v / 4095.0) * 2.0 * 3.3 * (1100 / 1000.0);
}

uint8_t calcPercentage(float volts)
{
  uint8_t percentage = (volts - BATTERY_MIN_V) * 100 / (BATTERY_MAX_V - BATTERY_MIN_V);
  if (percentage > 100)
  {
    percentage = 100;
  }
  if (percentage < 0)
  {
    percentage = 0;
  }
  return percentage;
}

void addBatteryChargeInterrupt()
{
  pinMode(CHARGE_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, !digitalRead(CHARGE_PIN));
  attachInterrupt(CHARGE_PIN, [] {
    digitalWrite(LED_PIN, !digitalRead(CHARGE_PIN));
  },
                  CHANGE);
}

bool isCharging()
{
  return !digitalRead(CHARGE_PIN);
}