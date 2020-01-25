#include <Arduino.h>
#include <EEPROM.h>

#define MAG_CALIBRATION_ADDRESS 0x00

void storeMagBiasEEPROM(float *magbias);
void getMagBiasEEPROM(float *magbias);