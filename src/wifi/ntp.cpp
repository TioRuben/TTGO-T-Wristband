#include "ntp.hpp"
#include <WiFiUdp.h>
#include <NTP.h>

WiFiUDP wifiUdp;
NTP ntp(wifiUdp);

void initNTP()
{
  ntp.ruleDST("CEST", Last, Sun, Mar, 2, 120);
  ntp.ruleSTD("CET", Last, Sun, Oct, 3, 60);
  ntp.begin();
  ntp.update();
}

RTC_Date syncTime()
{
  initNTP();
  RTC_Date datetime = RTC_Date(ntp.year(), ntp.month(), ntp.day(), ntp.hours(), ntp.minutes(), ntp.seconds());
  ntp.stop();
  return datetime;
}
