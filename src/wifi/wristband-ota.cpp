#include "wristband-ota.hpp"

bool otaStart = false;

void setupOTA()
{
  ArduinoOTA.setHostname("T-Wristband");
  ArduinoOTA.setPassword("wristbandpass");

  ArduinoOTA.onStart([]() {
              String type;
              if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
              else // U_SPIFFS
                type = "filesystem";
              Serial.println("Start updating " + type);
              otaStart = true;
              updatingText();
            })
      .onEnd([]() {
        Serial.println("\nEnd");
        delay(500);
        esp_restart();
      })
      .onProgress([](unsigned int progress, unsigned int total) {
        int percentage = (progress / (total / 100));
        drawProgressBar(10, 30, 120, 15, percentage, TFT_WHITE, TFT_BLUE);
      })
      .onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR)
          Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR)
          Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR)
          Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR)
          Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR)
          Serial.println("End Failed");
        msgWarning("UPDATE FAILED!");
        delay(3000);
        otaStart = false;
      });

  ArduinoOTA.begin();
}

bool otaRunning()
{
  ArduinoOTA.handle();
  return otaStart;
}