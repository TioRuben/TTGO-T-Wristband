#include "pages/page-ota.hpp"

void pageOta(bool initialLoad)
{
  if (initialLoad)
  {
    deactivateWifi();
    msgBig("OTA");
  }
}

void waitOta()
{
  unsigned long oldmilis = millis();
  activateWifi();
  setupOTA();
  msgInfo("Waiting for OTA on", WiFi.localIP().toString().c_str());
  while (millis() - oldmilis < 60000)
  {
    while (otaRunning())
    {
    }
    usleep(10);
  }
  deactivateWifi();
  msgWarning("OTA Timeout");
}