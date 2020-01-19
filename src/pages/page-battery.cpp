#include "pages/page-battery.hpp"

void pageBattery(bool initialLoad)
{
  if (initialLoad)
  {
    deactivateWifi();
    float voltage = getVoltage();
    drawBattery(voltage, calcPercentage(voltage), isCharging());
  }
}
