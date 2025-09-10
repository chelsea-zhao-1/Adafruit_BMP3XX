#include <iostream>
#include <wiringPiI2C.h>
#include <unistd.h>
#include "Adafruit_BMP3XX.h"

#define SEALEVELPRESSURE_HPA (1013.25) // Adjust for your location
#define BMP3XX_DEFAULT_ADDRESS (0x77)  // Default I2C address (0x76 or 0x77, check i2cdetect)

Adafruit_BMP3XX bmp;

int main() {
    // Initialize WiringPi I2C
    int fd = wiringPiI2CSetup(BMP3XX_DEFAULT_ADDRESS);
    if (fd < 0) {
        std::cout << "Failed to initialize I2C!" << std::endl;
        return 1;
    }

    // Initialize BMP390
    if (!bmp.begin_I2C(fd)) {
        std::cout << "Could not find a valid BMP3 sensor, check wiring!" << std::endl;
        return 1;
    }

    // Set up oversampling and filter (same as your example)
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);

    std::cout << "Adafruit BMP390 test" << std::endl;

    while (true) {
        if (!bmp.performReading()) {
            std::cout << "Failed to perform reading :(" << std::endl;
            usleep(2000000); // 2 seconds
            continue;
        }

        std::cout << "Temperature = " << bmp.temperature << " *C" << std::endl;
        std::cout << "Pressure = " << (bmp.pressure / 100.0) << " hPa" << std::endl;
        std::cout << "Approx. Altitude = " << bmp.readAltitude(SEALEVELPRESSURE_HPA) << " m" << std::endl;
        std::cout << std::endl;

        usleep(2000000); // 2 seconds delay
    }

    return 0;
}
