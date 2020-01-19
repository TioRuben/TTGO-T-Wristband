#include <Arduino.h>
#include "clock.hpp"
#include "ntp.hpp"
#include "wristband-tft.hpp"
#include "wristband-wifi.hpp"

void pageClock(bool initialLoad);
void pageRtc(bool initialLoad);
void actionClock();