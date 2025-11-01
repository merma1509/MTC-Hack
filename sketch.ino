#include "ClimaGuard.h"
#include "ThingSpeak.h"
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <Wire.h>

#define DHTPIN 2
#define MQ_PIN 4
#define BUZZER_PIN 12

const char *WIFI_NAME = "Wokwi-GUEST"; // Update to your WiFi SSID
const char *WIFI_PASSWORD = "";        // Update to your WiFi password
const int myChannelNumber = 2319977;
const char *myApiKey = "HD66D1WA9P9FW64C";

ClimaGuard climaGuard(DHTPIN, MQ_PIN,
                      BUZZER_PIN); // Create instance of the class
WiFiClient client;

unsigned long lastWiFiCheck = 0;
const unsigned long wifiCheckInterval = 30000;

void setup() {
  climaGuard.begin(); // Initialize hardware via class

  connectWiFi(); // Initial connection
  ThingSpeak.begin(client);
  Serial.println("ClimaGuard IoT Node Initialized");
}

void loop() {
  // Check WiFi periodically and reconnect if needed
  if (millis() - lastWiFiCheck > wifiCheckInterval) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi lost, reconnecting...");
      connectWiFi();
    }
    lastWiFiCheck = millis();
  }

  // Use ClimaGuard class for sensors, display, and alerts
  float temperature, humidity, aqi_ppm;
  climaGuard.readSensors(temperature, humidity, aqi_ppm);
  climaGuard.displayData(temperature, humidity);
  climaGuard.checkAlerts(humidity, aqi_ppm, temperature);

  // Log readings
  Serial.println("--- Sensor Readings ---");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("AQI PPM: ");
  Serial.print(aqi_ppm, 2);
  Serial.println(" ppm");

  // Update ThingSpeak only if WiFi is connected and data is valid
  if (WiFi.status() == WL_CONNECTED && !isnan(aqi_ppm)) {
    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, humidity);
    ThingSpeak.setField(3, aqi_ppm);
    int response = ThingSpeak.writeFields(myChannelNumber, myApiKey);
    if (response == 200) {
      Serial.println("SUCCESS: Data uploaded to ThingSpeak");
    } else {
      Serial.println("ERROR: ThingSpeak upload failed - Code: " +
                     String(response));
    }
  } else {
    Serial.println("WARNING: WiFi disconnected or invalid data - Skipping "
                   "ThingSpeak upload");
  }

  delay(5000); // Stability delay
}

void connectWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(1000);
    Serial.print(".");
    attempts++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.println("Local IP: " + String(WiFi.localIP()));
  } else {
    Serial.println("\nFailed to connect to WiFi");
  }
}
