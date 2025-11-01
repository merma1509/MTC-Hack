#include "ClimaGuard.h"
#include <Arduino.h>

// Constructor
ClimaGuard::ClimaGuard(int dhtPin, int mqPin, int buzzerPin, int lcdAddr, int lcdCols, int lcdRows)
  : dht(dhtPin, DHT22), mqPin(mqPin), buzzerPin(buzzerPin), lcd(lcdAddr, lcdCols, lcdRows) {
  // Initialize sensors and peripherals
}

// Initialize hardware
void ClimaGuard::begin() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  pinMode(buzzerPin, OUTPUT);
  Serial.println("ClimaGuard Hardware Initialized");
}

// Read all sensors
void ClimaGuard::readSensors(float &temp, float &hum, float &aqi) {
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  int raw = analogRead(mqPin);
  float voltage = raw * (5.0 / 1023.0);
  aqi = 116.6020682 * pow(voltage, -2.769034857);

  // Error handling
  if (isnan(temp) || isnan(hum)) {
    Serial.println("ERROR: DHT reading failed");
    temp = hum = -1;
  }
  if (raw < 0 || raw > 1023) {
    Serial.println("ERROR: MQ135 reading invalid");
    aqi = 0;
  }
}

// Display data on LCD
void ClimaGuard::displayData(float temp, float hum) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(hum);
  lcd.print("%");
}

// Trigger alert if thresholds exceeded
void ClimaGuard::checkAlerts(float hum, float aqi, float temp) {
  if (hum > 85 || aqi > 150 || temp > 40) {
    Serial.println("ALERT: Hazard detected!");
    tone(buzzerPin, 1000, 500);
    delay(1000);
  } else {
    noTone(buzzerPin);
  }
}
