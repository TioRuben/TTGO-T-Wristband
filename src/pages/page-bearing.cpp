#include "pages/page-bearing.hpp"

uint32_t timeBearing = millis();

void pageBearing(bool initialLoading)
{
  if (initialLoading)
  {
    deactivateWifi();
    initDrawBearing();
    initMPU();
  }
  if (millis() - timeBearing > 300)
  {
    int16_t bearing = getBearing();
    if (bearing > -1)
    {
      refreshDrawBearing(bearing);
    }
    timeBearing = millis();
  }
}

void actionBearing()
{
  msgInfo("Move wristband\nin 8 figure");
  int result = calibrateBearing();
  if (result < 0)
  {
    msgError("Calibration failed");
  }
  else
  {
    msgSuccess("Calibration Successful");
  }
  sleep(5);
}