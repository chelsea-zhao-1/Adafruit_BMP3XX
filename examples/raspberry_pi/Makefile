# Makefile for BMP3XX Raspberry Pi C++ example
# Requires wiringPi library and the BMP3XX library files

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
INCLUDES = -I../../ -I../../bmp3_defs.h
LIBS = -lwiringPi -lm

# Source files
BMP3XX_SOURCES = ../../Adafruit_BMP3XX.cpp ../../bmp3.c
MAIN_SOURCE = bmp3xx_reader.cpp
TARGET = bmp3xx_reader

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(MAIN_SOURCE) $(BMP3XX_SOURCES)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(MAIN_SOURCE) $(BMP3XX_SOURCES) $(LIBS)

# Clean build files
clean:
	rm -f $(TARGET)

# Install dependencies (run with sudo)
install-deps:
	sudo apt update
	sudo apt install -y wiringpi libwiringpi-dev g++ make

# Enable I2C (requires reboot)
enable-i2c:
	sudo raspi-config nonint do_i2c 0
	@echo "I2C enabled. Please reboot your Raspberry Pi."

# Check I2C devices
check-i2c:
	sudo i2cdetect -y 1

# Run the program
run: $(TARGET)
	sudo ./$(TARGET)

# Help
help:
	@echo "Available targets:"
	@echo "  all          - Build the program"
	@echo "  clean        - Remove build files"
	@echo "  install-deps - Install required dependencies"
	@echo "  enable-i2c   - Enable I2C interface"
	@echo "  check-i2c    - Check for I2C devices"
	@echo "  run          - Build and run the program"
	@echo "  help         - Show this help"

.PHONY: all clean install-deps enable-i2c check-i2c run help
