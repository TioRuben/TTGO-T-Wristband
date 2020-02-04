#include "eeprom.hpp"

void storeMagBiasEEPROM(float *magbias)
{
  EEPROM.begin(3 * sizeof(float));
  for (uint8_t i = 0; i < 3; i++)
  {
    EEPROM.put(MAG_CALIBRATION_ADDRESS + (i * sizeof(float)), magbias[i]);
  }
  EEPROM.commit();
  EEPROM.end();
}

void getMagBiasEEPROM(float *magbias)
{
  EEPROM.begin(3 * sizeof(float));
  for (uint8_t i = 0; i < 3; i++)
  {
    magbias[i] = EEPROM.read(MAG_CALIBRATION_ADDRESS + (i * sizeof(float)));
  }
  EEPROM.end();
}