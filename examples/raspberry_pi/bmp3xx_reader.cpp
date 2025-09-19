#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "Adafruit_BMP3XX.h"

// Raspberry Pi I2C implementation
class RaspberryPiI2C {
private:
    int fd;
    
public:
    RaspberryPiI2C(uint8_t addr) {
        fd = wiringPiI2CSetup(addr);
        if (fd == -1) {
            std::cerr << "Failed to initialize I2C device at address 0x" 
                      << std::hex << (int)addr << std::dec << std::endl;
        }
    }
    
    bool begin() {
        return fd != -1;
    }
    
    bool write_then_read(uint8_t *write_buffer, size_t write_len, 
                        uint8_t *read_buffer, size_t read_len) {
        // Write register address
        if (wiringPiI2CWrite(fd, write_buffer[0]) == -1) {
            return false;
        }
        
        // Read data
        for (size_t i = 0; i < read_len; i++) {
            read_buffer[i] = wiringPiI2CRead(fd);
            if (read_buffer[i] == -1) {
                return false;
            }
        }
        return true;
    }
    
    bool write(uint8_t *data, size_t len, bool stop, uint8_t *prefix, size_t prefix_len) {
        // Write prefix (register address)
        for (size_t i = 0; i < prefix_len; i++) {
            if (wiringPiI2CWrite(fd, prefix[i]) == -1) {
                return false;
            }
        }
        
        // Write data
        for (size_t i = 0; i < len; i++) {
            if (wiringPiI2CWrite(fd, data[i]) == -1) {
                return false;
            }
        }
        return true;
    }
};

// Global I2C device for the library
RaspberryPiI2C* g_i2c_device = nullptr;

// I2C read function for the Bosch library
int8_t i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    if (!g_i2c_device) return 1;
    
    uint8_t reg = reg_addr;
    if (!g_i2c_device->write_then_read(&reg, 1, reg_data, len)) {
        return 1;
    }
    return 0;
}

// I2C write function for the Bosch library
int8_t i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    if (!g_i2c_device) return 1;
    
    uint8_t reg = reg_addr;
    if (!g_i2c_device->write((uint8_t*)reg_data, len, true, &reg, 1)) {
        return 1;
    }
    return 0;
}

// Delay function for the Bosch library
void delay_usec(uint32_t us, void *intf_ptr) {
    usleep(us);
}

// Custom BMP3XX class for Raspberry Pi
class BMP3XX_Pi {
private:
    struct bmp3_dev the_sensor;
    RaspberryPiI2C* i2c_dev;
    
public:
    BMP3XX_Pi() : i2c_dev(nullptr) {}
    
    ~BMP3XX_Pi() {
        if (i2c_dev) delete i2c_dev;
    }
    
    bool begin_I2C(uint8_t addr = 0x77) {
        // Initialize wiringPi
        if (wiringPiSetup() == -1) {
            std::cerr << "Failed to initialize wiringPi" << std::endl;
            return false;
        }
        
        // Create I2C device
        i2c_dev = new RaspberryPiI2C(addr);
        if (!i2c_dev->begin()) {
            return false;
        }
        
        // Set global pointer for library callbacks
        g_i2c_device = i2c_dev;
        
        // Configure sensor structure
        the_sensor.chip_id = addr;
        the_sensor.intf = BMP3_I2C_INTF;
        the_sensor.read = &i2c_read;
        the_sensor.write = &i2c_write;
        the_sensor.intf_ptr = i2c_dev;
        the_sensor.delay_us = &delay_usec;
        the_sensor.dummy_byte = 0;
        
        // Initialize sensor
        int8_t rslt = bmp3_soft_reset(&the_sensor);
        if (rslt != BMP3_OK) {
            std::cerr << "Sensor reset failed" << std::endl;
            return false;
        }
        
        rslt = bmp3_init(&the_sensor);
        if (rslt != BMP3_OK) {
            std::cerr << "Sensor initialization failed" << std::endl;
            return false;
        }
        
        // Set default settings
        the_sensor.settings.temp_en = BMP3_ENABLE;
        the_sensor.settings.press_en = BMP3_ENABLE;
        the_sensor.settings.op_mode = BMP3_MODE_FORCED;
        
        return true;
    }
    
    bool performReading() {
        if (!i2c_dev) return false;
        
        // Set sensor settings
        uint16_t settings_sel = BMP3_SEL_TEMP_EN | BMP3_SEL_PRESS_EN;
        int8_t rslt = bmp3_set_sensor_settings(settings_sel, &the_sensor);
        if (rslt != BMP3_OK) return false;
        
        // Set power mode
        the_sensor.settings.op_mode = BMP3_MODE_FORCED;
        rslt = bmp3_set_op_mode(&the_sensor);
        if (rslt != BMP3_OK) return false;
        
        // Read sensor data
        struct bmp3_data data;
        uint8_t sensor_comp = BMP3_TEMP | BMP3_PRESS;
        rslt = bmp3_get_sensor_data(sensor_comp, &data, &the_sensor);
        if (rslt != BMP3_OK) return false;
        
        // Store results
        temperature = data.temperature;
        pressure = data.pressure;
        
        return true;
    }
    
    float readTemperature() {
        performReading();
        return temperature;
    }
    
    float readPressure() {
        performReading();
        return pressure;
    }
    
    float readAltitude(float seaLevel = 1013.25) {
        float atmospheric = readPressure() / 100.0F;
        return 44330.0 * (1.0 - pow(atmospheric / seaLevel, 0.1903));
    }
    
    // Public data members
    double temperature = 0.0;
    double pressure = 0.0;
};

int main() {
    std::cout << "BMP3XX Sensor Data Reader (Raspberry Pi C++)" << std::endl;
    std::cout << "Press Ctrl+C to exit" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    BMP3XX_Pi bmp;
    
    if (!bmp.begin_I2C()) {
        std::cerr << "Could not find BMP3 sensor, check wiring!" << std::endl;
        return 1;
    }
    
    std::cout << "BMP3 sensor found!" << std::endl;
    
    try {
        while (true) {
            if (bmp.performReading()) {
                std::cout << "Temperature: " << bmp.temperature << " °C" << std::endl;
                std::cout << "Pressure: " << (bmp.pressure / 100.0) << " hPa" << std::endl;
                std::cout << "Altitude: " << bmp.readAltitude() << " m" << std::endl;
                std::cout << "----------------------------------------" << std::endl;
            } else {
                std::cout << "Failed to read sensor!" << std::endl;
            }
            
            sleep(2); // Wait 2 seconds between readings
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
