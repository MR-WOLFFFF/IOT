#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

// Create BME680 object
Adafruit_BME680 bme;

// I2C pins for Heltec LoRa V3
#define SDA_PIN 41
#define SCL_PIN 42

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Initializing BME680 Sensor...");

  // Initialize I2C communication
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize BME680 sensor
  if (!bme.begin(0x77)) { // Using the detected I2C address 0x77
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Configure BME680 sensor settings
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320°C for 150 ms
}

void loop() {
  if (!bme.performReading()) {
    Serial.println("Failed to perform reading!");
    return;
  }

  // Print sensor readings
  Serial.println("BME680 Sensor Readings:");
  Serial.print("Temperature: ");
  Serial.print(bme.temperature);
  Serial.println(" °C");

  Serial.print("Pressure: ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Humidity: ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  Serial.print("Gas Resistance: ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" kOhms");

  Serial.println();
  delay(2000); // Delay for 2 seconds before the next reading
}
