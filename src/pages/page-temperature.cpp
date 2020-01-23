#include "pages/page-temperature.hpp"

uint32_t timeTemperature = millis();

void pageTemperature(bool initialLoading)
{

  if (initialLoading)
  {
    deactivateWifi();
    initDrawTemperature();
    initMPU();
  }
  if (millis() - timeTemperature > 300)
  {
    float temperature = getTemperature();
    refreshDrawTemperature(temperature);
    timeTemperature = millis();
  }
}