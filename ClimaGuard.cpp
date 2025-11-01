#ifndef CLIMAGUARD_H
#define CLIMAGUARD_H

#include <DHT.h>
#include <LiquidCrystal_I2C.h>

class ClimaGuard {
public:
  ClimaGuard(int dhtPin, int mqPin, int buzzerPin, int lcdAddr = 0x27, int lcdCols = 16, int lcdRows = 2);
  void begin();
  void readSensors(float &temp, float &hum, float &aqi);
  void displayData(float temp, float hum);
  void checkAlerts(float hum, float aqi, float temp);

private:
  DHT dht;
  int mqPin;
  int buzzerPin;
  LiquidCrystal_I2C lcd;
};

#endif
