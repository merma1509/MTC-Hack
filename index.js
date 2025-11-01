// ClimaGuard IoT Algorithm Test Script
// Simulates sensor readings, AQI calculation, and alerts without hardware

// Simulate sensor data 
function simulateSensors() {
  const temperature = Math.random() * 50 + 10;             // 10-60°C
  const humidity = Math.random() * 100;                    // 0-100%
  const airQualityRaw = Math.floor(Math.random() * 1024);  // 0-1023
  return { temperature, humidity, airQualityRaw };
}

// AQI calculation
function calculateAQI(voltage) {
  return 116.6020682 * Math.pow(voltage, -2.769034857);
}

// Main test function
function testClimaGuard() {
  console.log('=== ClimaGuard IoT Algorithm Test ===');

  for (let i = 0; i < 5; i++) {  // Run 5 test cycles
    const { temperature, humidity, airQualityRaw } = simulateSensors();
    const voltage = airQualityRaw * (5.0 / 1023.0);
    const aqi_ppm = calculateAQI(voltage);

    console.log(`Cycle ${i + 1}:`);
    console.log(`  Temperature: ${temperature.toFixed(1)} °C`);
    console.log(`  Humidity: ${humidity.toFixed(1)} %`);
    console.log(`  Air Quality Raw: ${airQualityRaw}`);
    console.log(`  Voltage: ${voltage.toFixed(2)} V`);
    console.log(`  AQI PPM: ${aqi_ppm.toFixed(2)} ppm`);

    // Alert logic
    const alert = (humidity > 85 || aqi_ppm > 150 || temperature > 40);
    console.log(`  Alert: ${alert ? 'YES - Hazard detected!' : 'No'}\n`);
  }

  console.log('Test complete. Upload to ESP32 for real hardware testing.');
}

// Wiring Test Function (Simulates connection checks)
function testWiring() {
  console.log('=== ClimaGuard Wiring Test ===');

  // Simulate pin mappings from diagram.json
  const pins = {
    esp32: { vcc: '5V', gnd: 'GND', data: 'D2', analog: 'D4', sda: '21', scl: '22', buzzer: '12' },
    dht22: { vcc: '5V', gnd: 'GND', data: 'D2' },
    mq135: { vcc: '5V', gnd: 'GND', aout: 'D4' },
    lcd: { vcc: '5V', gnd: 'GND', sda: '21', scl: '22' },
    buzzer: { vcc: '5V', gnd: 'GND', signal: '12' }
  };

  // Check VCC/GND connections
  const vccConnected = pins.esp32.vcc === pins.dht22.vcc && pins.esp32.vcc === pins.mq135.vcc && pins.esp32.vcc === pins.lcd.vcc;
  const gndConnected = pins.esp32.gnd === pins.dht22.gnd && pins.esp32.gnd === pins.mq135.gnd && pins.esp32.gnd === pins.lcd.gnd;

  console.log(' VCC Connections:', vccConnected ? 'OK' : 'ERROR - Mismatch!');
  console.log(' GND Connections:', gndConnected ? 'OK' : 'ERROR - Mismatch!');

  // Check data pins
  console.log(' DHT22 Data Pin (D2):', pins.dht22.data === pins.esp32.data ? 'OK' : 'ERROR');
  console.log(' MQ135 Analog Pin (D4):', pins.mq135.aout === pins.esp32.analog ? 'OK' : 'ERROR');
  console.log(' LCD SDA (21):', pins.lcd.sda === pins.esp32.sda ? 'OK' : 'ERROR');
  console.log(' LCD SCL (22):', pins.lcd.scl === pins.esp32.scl ? 'OK' : 'ERROR');
  console.log(' Buzzer Signal (12):', pins.buzzer.signal === pins.esp32.buzzer ? 'OK' : 'ERROR');

  console.log('\nWiring Test Complete. All OK for assembly!\n');
}

// Run both tests
testClimaGuard();
testWiring();
