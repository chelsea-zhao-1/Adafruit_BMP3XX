#!/usr/bin/env python3
"""
BMP3XX Sensor Data Reader for Raspberry Pi
Reads temperature, pressure, and altitude from BMP388/BMP390 sensor
"""

import time
import board
import busio
import adafruit_bmp3xx

# Create I2C bus
i2c = busio.I2C(board.SCL, board.SDA)

# Create sensor object
bmp = adafruit_bmp3xx.BMP3XX_I2C(i2c)

# Optional: Configure sensor settings
bmp.pressure_oversampling = 8
bmp.temperature_oversampling = 2
bmp.sea_level_pressure = 1013.25

print("BMP3XX Sensor Data Reader")
print("Press Ctrl+C to exit")
print("-" * 40)

try:
    while True:
        # Read sensor data
        temperature = bmp.temperature
        pressure = bmp.pressure
        altitude = bmp.altitude
        
        # Print readings
        print(f"Temperature: {temperature:.2f} °C")
        print(f"Pressure: {pressure/100:.2f} hPa")
        print(f"Altitude: {altitude:.2f} m")
        print("-" * 40)
        
        time.sleep(2)  # Wait 2 seconds between readings
        
except KeyboardInterrupt:
    print("\nExiting...")
