#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiManager.h>

void setupWiFi();
void configModeCallback(WiFiManager *myWiFiManager);
void activateWifi();
void deactivateWifi();