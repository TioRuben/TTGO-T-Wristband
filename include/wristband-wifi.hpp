#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiManager.h>
#include "wristband-tft.hpp"

void setupWiFi();
void configModeCallback(WiFiManager *myWiFiManager);
void activateWifi();
void deactivateWifi();