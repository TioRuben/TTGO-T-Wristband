#include <Arduino.h>
#include <Wire.h>
#include <pcf8563.h>
#include "hal.hpp"
#include "translations.hpp"

void initClock();
RTC_Date getClockTime();
RTC_Date getUTCTime();
void setTime(RTC_Date datetime);
bool isDST(RTC_Date now);