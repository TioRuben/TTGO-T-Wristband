#include "wristband-wifi.hpp"

WiFiManager wifiManager;

void configModeCallback(WiFiManager *myWiFiManager)
{
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
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
  if (WiFi.status() != WL_CONNECTED)
  {
    setupWiFi();
  }
}

void deactivateWifi()
{
  WiFi.mode(WIFI_OFF);
}