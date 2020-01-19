#include <Arduino.h>
#include <ArduinoOTA.h>
#include "wristband-tft.hpp"

void setupOTA();
bool otaRunning();
String getOtaHostname();