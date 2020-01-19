#include "pages/page-clock.hpp"

unsigned long clockRefresh = 0;
bool colon = true;
uint16_t colonX = 0;
uint8_t oldMinute = 99;
uint8_t oldDay = 99;
bool colonUTC = true;
uint16_t colonXUTC = 0;
uint8_t oldMinuteUTC = 99;
uint8_t oldDayUTC = 99;

void pageClock(bool initialLoad)
{
  RTC_Date current;
  if (initialLoad)
  {
    deactivateWifi();
    clearScreen();
    current = getClockTime();
    displayDate(current.day, current.month, current.year, false);
    colonX = displayHour(current.hour, current.minute, false);
    oldMinute = current.minute;
    oldDay = current.day;
    clockRefresh = millis();
  }
  else if (millis() - clockRefresh > 1000)
  {
    clockRefresh = millis();
    current = getClockTime();
    colon = !colon;
    displayColon(colonX, colon, false);
    if (oldMinute != current.minute)
    {
      colonX = displayHour(current.hour, current.minute, false);
    }
    if (oldDay != current.day)
    {
      displayDate(current.day, current.month, current.year, false);
    }
    oldMinute = current.minute;
    oldDay = current.day;
  }
}

void pageRtc(bool initialLoad)
{
  RTC_Date current;
  if (initialLoad)
  {
    deactivateWifi();
    clearScreen();
    current = getUTCTime();
    displayDate(current.day, current.month, current.year, true);
    colonXUTC = displayHour(current.hour, current.minute, true);
    oldMinuteUTC = current.minute;
    oldDayUTC = current.day;
    clockRefresh = millis();
  }
  else if (millis() - clockRefresh > 1000)
  {
    clockRefresh = millis();
    current = getUTCTime();
    colonUTC = !colonUTC;
    displayColon(colonXUTC, colonUTC, true);
    if (oldMinuteUTC != current.minute)
    {
      colonXUTC = displayHour(current.hour, current.minute, true);
    }
    if (oldDayUTC != current.day)
    {
      displayDate(current.day, current.month, current.year, true);
    }
    oldMinuteUTC = current.minute;
    oldDayUTC = current.day;
  }
}

void actionClock()
{
  activateWifi();
  msgInfo("UPDATING TIME...");
  setTime(syncTime());
  deactivateWifi();
  msgSuccess("TIME UPDATED");
  sleep(3);
}