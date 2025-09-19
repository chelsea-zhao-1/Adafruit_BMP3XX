#include <Wire.h>
#include "Adafruit_BMP3XX.h"

// Create sensor object
Adafruit_BMP3XX bmp;

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect
  
  Serial.println("BMP3XX Sensor Data Reader");
  
  // Initialize sensor with I2C
  if (!bmp.begin_I2C()) {
    Serial.println("Could not find BMP3 sensor, check wiring!");
    while (1); // Stop if sensor not found
  }
  
  Serial.println("BMP3 sensor found!");
}

void loop() {
  // Read sensor data
  if (bmp.performReading()) {
    // Print temperature
    Serial.print("Temperature: ");
    Serial.print(bmp.temperature);
    Serial.println(" *C");
    
    // Print pressure
    Serial.print("Pressure: ");
    Serial.print(bmp.pressure / 100.0); // Convert Pa to hPa
    Serial.println(" hPa");
    
    // Print altitude (using standard sea level pressure)
    Serial.print("Altitude: ");
    Serial.print(bmp.readAltitude(1013.25));
    Serial.println(" m");
    
    Serial.println("---");
  } else {
    Serial.println("Failed to read sensor!");
  }
  
  delay(2000); // Wait 2 seconds between readings
}
