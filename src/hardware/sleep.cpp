#include "sleep.hpp"

void handleSleep(bool showMsg)
{
  //tftSleep(showMsg);
  tftSleep(false);
  mpuSleep();
  deactivateWifi();
  esp_sleep_enable_ext1_wakeup(GPIO_SEL_33 | GPIO_SEL_38, ESP_EXT1_WAKEUP_ANY_HIGH);
  esp_deep_sleep_start();
}