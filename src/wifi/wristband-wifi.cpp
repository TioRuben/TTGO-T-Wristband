#include "wristband-wifi.hpp"

WiFiManager wifiManager;

void configModeCallback(WiFiManager *myWiFiManager)
{
  char apName[50] = " ";
  wifiManager.getConfigPortalSSID().toCharArray(apName, 50);
  wifiManagerAdvice(apName);
}

void setupWiFi()
{
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setBreakAfterConfig(true);
  wifiManager.autoConnect("T-Wristband");
}

void activateWifi()
{
  WiFi.mode(WIFI_STA);
  sleep(1);
  if (WiFi.status() != WL_CONNECTED)
  {
    setupWiFi();
  }
}

void deactivateWifi()
{
  WiFi.mode(WIFI_OFF);
}