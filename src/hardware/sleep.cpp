#include "sleep.hpp"

void handleSleep(bool showMsg)
{
  //tftSleep(showMsg);
#ifndef IMU_SKIP
  mpuSleep();
#endif
  tftSleep(false);
  deactivateWifi();
  rtcSleep();
  pinMode(39, GPIO_MODE_INPUT);
#ifndef IMU_SKIP
  esp_sleep_enable_ext1_wakeup(GPIO_SEL_33 | GPIO_SEL_39, ESP_EXT1_WAKEUP_ANY_HIGH);
#else
  esp_sleep_enable_ext1_wakeup(GPIO_SEL_33, ESP_EXT1_WAKEUP_ANY_HIGH);
#endif
  esp_deep_sleep_disable_rom_logging();
  esp_deep_sleep_start();
}
