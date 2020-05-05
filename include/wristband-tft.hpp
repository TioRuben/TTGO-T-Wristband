#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <hal.hpp>

#define SEG7_BACKGROUND 0x0821

void tftInit();
void wifiManagerAdvice(const char *ap_name);
void drawProgressBar(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint8_t percentage, uint16_t frameColor, uint16_t barColor);
void updatingText();
void msgError(const char *message);
void msgError(const char *message1, const char *message2);
void msgWarning(const char *message);
void msgWarning(const char *message1, const char *message2);
void msgSuccess(const char *message);
void msgSuccess(const char *message1, const char *message2);
void msgInfo(const char *message);
void msgInfo(const char *message1, const char *message2);
void tftSleep(bool showMsg);
void msgBig(const char *message);
void msg(const char *message, uint16_t color);
void msg(const char *message1, const char *message2, uint16_t color);
void displayDate(const uint8_t day, const uint8_t month, const uint16_t year, bool utc);
uint16_t displayHour(const uint8_t hour, const uint8_t minute, bool utc);
uint16_t displayColon(uint16_t x, bool color, bool utc);
void clearScreen();
void drawBattery(float voltage, uint8_t percentage, bool charging);
void initDrawBearing();
void refreshDrawBearing(int16_t bearing);
void initDrawTemperature();
void refreshDrawTemperature(float temperature);