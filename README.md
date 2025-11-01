# ClimaGuard IoT Environmental Monitor

ClimaGuard is an IoT-based environmental monitoring system that currently tracks temperature, humidity, and air quality in real-time. It provides visual feedback through an LCD display, audible alerts, and cloud-based data logging via ThingSpeak.

## Features

- Real-time temperature and humidity monitoring using DHT22 sensor
- Air quality measurement with MQ-135 gas sensor
- Local display of environmental data on 16x2 LCD screen
- Audible alerts for critical conditions
- Cloud data logging and visualization with ThingSpeak
- Remote monitoring via WiFi connectivity
- Low-power design for continuous operation

## Hardware Requirements

- ESP32 development board
- DHT22 temperature and humidity sensor
- MQ-135 air quality sensor
- 16x2 I2C LCD display
- Buzzer for alerts
- Jumper wires and breadboard
- Micro-USB cable for power and programming

## Dependencies

- [Arduino Core for ESP32](https://github.com/espressif/arduino-esp32)
- [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)
- [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor)
- [LiquidCrystal I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
- [ThingSpeak](https://github.com/mathworks/thingspeak-arduino)

## Installation

1. Install the required libraries through Arduino IDE's Library Manager
2. Clone this repository
3. Open `sketch.ino` in Arduino IDE
4. Update the following in the code:
   - `WIFI_NAME`: Your WiFi SSID
   - `WIFI_PASSWORD`: Your WiFi password
   - `myChannelNumber`: Your ThingSpeak channel number
   - `myApiKey`: Your ThingSpeak API key
5. Select your ESP32 board from the board manager
6. Upload the sketch to your ESP32

## Pin Configuration

| Component | ESP32 Pin |
|-----------|-----------|
| DHT22 Data | GPIO 2    |
| MQ-135    | GPIO 4    |
| Buzzer    | GPIO 12   |
| I2C SDA   | Default I2C SDA |
| I2C SCL   | Default I2C SCL |

## ThingSpeak Integration

1. Create a free account on [ThingSpeak](https://thingspeak.com/)
2. Create a new channel
3. Add three fields:
   - Field 1: Temperature (°C)
   - Field 2: Humidity (%)
   - Field 3: Air Quality (PPM)
4. Update the `myChannelNumber` and `myApiKey` in the sketch with your channel details

## Data Visualization

ClimaGuard sends data to ThingSpeak where you can:
- View real-time graphs of environmental data
- Set up alerts and notifications
- Export data for analysis
- Create custom visualizations

## Troubleshooting

- **DHT22 not reading**: Check wiring and ensure the correct pin is specified
- **LCD not displaying**: Verify I2C address and connections
- **WiFi not connecting**: Double-check SSID and password
- **MQ-135 readings unstable**: Allow 24-48 hours for the sensor to stabilize

##  License

This project is open source.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Contact

For questions or support, please open an issue in the repository.
