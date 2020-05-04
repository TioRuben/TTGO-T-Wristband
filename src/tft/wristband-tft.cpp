#include "wristband-tft.hpp"

TFT_eSPI tft = TFT_eSPI();

void tftInit()
{
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(TFT_BL, 0);
  ledcWrite(0, 185);
}

void wifiManagerAdvice(const char *ap_name)
{
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("Connect hotspot name ", 20, tft.height() / 2 - 20);
  tft.drawString("configure wrist", 35, tft.height() / 2 + 20);
  tft.setTextColor(TFT_GREEN);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(ap_name, tft.width() / 2, tft.height() / 2);
}

void drawProgressBar(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint8_t percentage, uint16_t frameColor, uint16_t barColor)
{
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(TC_DATUM);
  tft.setTextPadding(tft.textWidth(" 888% "));
  tft.drawString(String(percentage) + "%", 145, 35);
  if (percentage == 0)
  {
    tft.fillRoundRect(x0, y0, w, h, 3, TFT_BLACK);
  }
  uint8_t margin = 2;
  uint16_t barHeight = h - 2 * margin;
  uint16_t barWidth = w - 2 * margin;
  tft.drawRoundRect(x0, y0, w, h, 3, frameColor);
  tft.fillRect(x0 + margin, y0 + margin, barWidth * percentage / 100.0, barHeight, barColor);
}

void updatingText()
{
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("Updating...", tft.width() / 2 - 20, 55);
}

void msgBig(const char *message)
{
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_CYAN);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(message, tft.width() / 2, tft.height() / 2, 4);
}

void msgError(const char *message)
{
  msg(message, TFT_RED);
}

void msgError(const char *message1, const char *message2)
{
  msg(message1, message2, TFT_RED);
}

void msgWarning(const char *message)
{
  msg(message, TFT_ORANGE);
}

void msgWarning(const char *message1, const char *message2)
{
  msg(message1, message2, TFT_ORANGE);
}

void msgSuccess(const char *message)
{
  msg(message, TFT_GREEN);
}

void msgSuccess(const char *message1, const char *message2)
{
  msg(message1, message2, TFT_GREEN);
}

void msgInfo(const char *message)
{
  msg(message, TFT_CYAN);
}

void msgInfo(const char *message1, const char *message2)
{
  msg(message1, message2, TFT_CYAN);
}

void msg(const char *message, uint16_t color)
{
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(color);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(message, tft.width() / 2, tft.height() / 2, 2);
}

void msg(const char *message1, const char *message2, uint16_t color)
{
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(color);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(message1, tft.width() / 2, tft.height() / 2 - 15, 2);
  tft.drawString(message2, tft.width() / 2, tft.height() / 2 + 15, 2);
}

void tftSleep(bool showMsg)
{
  if (showMsg)
  {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("Press again to wake up", tft.width() / 2, tft.height() / 2);
    delay(2000);
  }
  tft.fillScreen(TFT_BLACK);
  tft.writecommand(ST7735_SWRESET);
  delay(100);
  tft.writecommand(ST7735_SLPIN);
  delay(150);
  tft.writecommand(ST7735_DISPOFF);
}

void clearScreen()
{
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
}

void displayDate(const uint8_t day, const uint8_t month, const uint16_t year, bool utc)
{
  char date[11] = " ";
  sprintf(date, "%02u/%02u/%u", day, month, year);
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setCursor(8, 65);
  tft.print(date);
  if (utc)
  {
    tft.print(" **UTC**");
  }
}

uint16_t displayHour(const uint8_t hour, const uint8_t minute, bool utc)
{
  uint8_t xpos = 6;
  uint8_t ypos = 6;
  uint16_t colonX = 0;
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(SEG7_BACKGROUND, TFT_BLACK);
  tft.drawString("88:88", xpos, ypos, 7);
  if (utc)
  {
    tft.setTextColor(TFT_GREENYELLOW);
  }
  else
  {
    tft.setTextColor(0xFBE0);
  }
  if (hour < 10)
  {
    xpos += tft.drawChar('0', xpos, ypos, 7);
  }
  xpos += tft.drawNumber(hour, xpos, ypos, 7);
  colonX = xpos;
  xpos += displayColon(xpos, true, utc);
  if (utc)
  {
    tft.setTextColor(TFT_GREENYELLOW);
  }
  else
  {
    tft.setTextColor(0xFBE0);
  }
  if (minute < 10)
  {
    xpos += tft.drawChar('0', xpos, ypos, 7);
  }
  tft.drawNumber(minute, xpos, ypos, 7);
  return colonX;
}

uint16_t displayColon(uint16_t x, bool color, bool utc)
{
  if (color)
  {
    tft.setTextColor(0x0821);
  }
  else
  {
    if (utc)
    {
      tft.setTextColor(TFT_GREENYELLOW);
    }
    else
    {
      tft.setTextColor(0xFBE0);
    }
  }
  return tft.drawChar(':', x, 6, 7);
}

void drawBattery(float voltage, uint8_t percentage, bool charging)
{
  char voltageString[5] = " ";
  uint16_t originx = 25;
  uint16_t originy = 15;
  uint16_t width = 120;
  uint16_t height = 40;
  uint16_t tabheight = 15;
  uint16_t tabwidth = 5;
  uint8_t margin = 2;
  uint16_t barHeight = height - 2 * margin;
  uint16_t barWidth = width - 2 * margin;
  sprintf(voltageString, "%2.2f", voltage);

  tft.fillScreen(TFT_BLACK);

  if (percentage == 0)
  {
    tft.fillRoundRect(originx, originy, width, height, 3, TFT_BLACK);
  }
  tft.fillRoundRect(originx - tabwidth + 1, (height - tabheight) / 2 + originy, tabwidth, tabheight, 1, TFT_WHITE);
  tft.drawRoundRect(originx, originy, width, height, 3, TFT_WHITE);
  tft.fillRect(originx + margin, originy + margin, barWidth * percentage / 100.0, barHeight, TFT_DARKGREEN);

  tft.setTextColor(TFT_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.setTextPadding(tft.textWidth(" 888% ", 2));
  tft.drawString(String(percentage) + "%", width / 2 + originx, height / 2 + originy, 2);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(BC_DATUM);
  String voltageInfo = String(voltageString) + "V";
  if (charging)
  {
    voltageInfo += " Charging";
  }
  tft.drawString(voltageInfo, tft.width() / 2, tft.height());
}

void initDrawBearing()
{
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.drawString("---", tft.width() / 2, tft.height() / 2, 7);
}

void refreshDrawBearing(int16_t bearing)
{
  char bearingText[5] = " ";
  if (bearing >= 0)
  {
    sprintf(bearingText, "%03d", bearing);
  }
  else
  {
    sprintf(bearingText, "---");
  }
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.drawString(bearingText, tft.width() / 2, tft.height() / 2, 7);
}

void initDrawTemperature()
{
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(BR_DATUM);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawString("Degrees Celsius", tft.width() - 5, tft.height(), 2);
}

void refreshDrawTemperature(float temperature)
{
  char temperatureText[8] = " ";
  sprintf(temperatureText, "%.1fC", temperature);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.drawString(temperatureText, tft.width() / 2, 5, 7);
}
