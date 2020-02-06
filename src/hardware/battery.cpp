#include "battery.hpp"

int vref = 1100;

void setupADC()
{
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize((adc_unit_t)ADC_UNIT_1, (adc_atten_t)ADC1_CHANNEL_6, (adc_bits_width_t)ADC_WIDTH_BIT_12, 1100, &adc_chars);
  if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF)
  {
    vref = adc_chars.vref;
  }
}

void setupBattery()
{
  pinMode(CHARGE_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

float getVoltage()
{
  uint16_t v = analogRead(BATT_ADC_PIN);
  float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
  return battery_voltage;
}

uint8_t calcPercentage(float volts)
{
  float percentage = (volts - BATTERY_MIN_V) * 100 / (BATTERY_MAX_V - BATTERY_MIN_V);
  if (percentage > 100)
  {
    percentage = 100;
  }
  if (percentage < 0)
  {
    percentage = 0;
  }
  return (uint8_t)percentage;
}

void updateBatteryChargeStatus()
{
  digitalWrite(LED_PIN, isCharging());
}

bool isCharging()
{
  return !digitalRead(CHARGE_PIN);
}