#include <Arduino.h>
#include <EasyButton.h>
#include "wristband-tft.hpp"
#include "pages/page-ota.hpp"
#include "pages/page-clock.hpp"
#include "pages/page-battery.hpp"
#include "pages/page-bearing.hpp"
#include "pages/page-temperature.hpp"

void handleUi();
void increasePage();
void showPage();
void handleSleep(bool showMsg = true);
void initButton();
void handleAction();