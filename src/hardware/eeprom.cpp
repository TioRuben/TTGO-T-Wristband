#include "eeprom.hpp"

void storeMagBiasEEPROM(float *magbias)
{
  int i = 0;
  for (i = 0; i < 3; i++)
  {
    EEPROM.put(MAG_CALIBRATION_ADDRESS + (i * sizeof(float)), magbias[i]);
  }
}

void getMagBiasEEPROM(float *magbias)
{
  int i = 0;
  for (i = 0; i < 3; i++)
  {
    magbias[i] = EEPROM.read(MAG_CALIBRATION_ADDRESS + (i * sizeof(float)));
  }
}