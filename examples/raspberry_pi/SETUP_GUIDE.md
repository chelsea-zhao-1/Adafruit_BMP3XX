# BMP390 Raspberry Pi Setup Guide

## Pre-Workshop Checklist

### Hardware Needed:
- [ ] Raspberry Pi (any model with GPIO pins)
- [ ] BMP390 sensor board
- [ ] 4x jumper wires (male-to-female or male-to-male)
- [ ] MicroSD card with Raspberry Pi OS
- [ ] Power supply for Raspberry Pi
- [ ] Monitor/keyboard or SSH access

### Software Prerequisites:
- [ ] Raspberry Pi OS installed and updated
- [ ] Internet connection for package installation
- [ ] Terminal/SSH access

---

## Step 1: Initial Raspberry Pi Setup

### 1.1 Boot and Update System
```bash
# Update package lists
sudo apt update

# Upgrade existing packages
sudo apt upgrade -y

# Reboot if kernel was updated
sudo reboot
```

### 1.2 Enable I2C Interface
```bash
# Enable I2C using raspi-config
sudo raspi-config

# Navigate to: Interfacing Options → I2C → Yes → Finish
# OR use command line:
sudo raspi-config nonint do_i2c 0

# Reboot to apply changes
sudo reboot
```

### 1.3 Verify I2C is Enabled
```bash
# Check if I2C modules are loaded
lsmod | grep i2c

# Should show: i2c_bcm2835 and i2c_dev
```

---

## Step 2: Install Required Software

### 2.1 Install Development Tools
```bash
# Install essential build tools
sudo apt install -y build-essential g++ make

# Install wiringPi library
sudo apt install -y wiringpi libwiringpi-dev

# Install I2C tools (for debugging)
sudo apt install -y i2c-tools
```

### 2.2 Verify WiringPi Installation
```bash
# Check wiringPi version
gpio -v

# Should show version information
```

---

## Step 3: Hardware Wiring

### 3.1 Power Down Raspberry Pi
```bash
sudo shutdown -h now
```

### 3.2 Connect BMP390 to Raspberry Pi

**Wiring Diagram:**
```
BMP390 Board          Raspberry Pi
┌─────────────┐       ┌─────────────┐
│ VCC  ───────┼───────┤ 3.3V (Pin 1)│
│ GND  ───────┼───────┤ GND (Pin 6) │
│ SCL  ───────┼───────┤ SCL (Pin 5) │
│ SDA  ───────┼───────┤ SDA (Pin 3) │
└─────────────┘       └─────────────┘
```

**Pin Reference:**
- **BMP390 VCC** → **Raspberry Pi Pin 1** (3.3V)
- **BMP390 GND** → **Raspberry Pi Pin 6** (Ground)
- **BMP390 SCL** → **Raspberry Pi Pin 5** (GPIO 3, SCL)
- **BMP390 SDA** → **Raspberry Pi Pin 3** (GPIO 2, SDA)

### 3.3 Power On Raspberry Pi
```bash
# Boot up and log in
```

---

## Step 4: Test Hardware Connection

### 4.1 Check I2C Bus
```bash
# Scan for I2C devices
sudo i2cdetect -y 1

# Expected output:
#      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
# 00:          -- -- -- -- -- -- -- -- -- -- -- -- -- 
# 10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
# 20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
# 30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
# 40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
# 50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
# 60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
# 70: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 77
```

**If you see "77" in the output, your BMP390 is connected correctly!**

### 4.2 Troubleshoot Connection Issues
```bash
# If no device found, check wiring:
# 1. Verify power connections (VCC to 3.3V, GND to GND)
# 2. Check SDA/SCL connections
# 3. Try different I2C address (0x76):
sudo i2cdetect -y 1

# Check I2C bus status
sudo i2cdetect -l
```

---

## Step 5: Download and Build the Code

### 5.1 Navigate to Project Directory
```bash
# Go to the BMP3XX library directory
cd /Users/chelseazhao/Desktop/coding/repo/Adafruit_BMP3XX/examples/raspberry_pi/

# Verify files are present
ls -la
# Should show: bmp3xx_reader.cpp, Makefile, SETUP_GUIDE.md
```

### 5.2 Build the Program
```bash
# Build using Makefile
make

# Expected output:
# g++ -std=c++11 -Wall -Wextra -O2 -I../../ -o bmp3xx_reader bmp3xx_reader.cpp ../../Adafruit_BMP3XX.cpp ../../bmp3.c -lwiringPi -lm
```

### 5.3 Verify Build Success
```bash
# Check if executable was created
ls -la bmp3xx_reader

# Should show executable file with execute permissions
```

---

## Step 6: Run the Program

### 6.1 Execute the Program
```bash
# Run with sudo (required for I2C access)
sudo ./bmp3xx_reader
```

### 6.2 Expected Output
```
BMP3XX Sensor Data Reader (Raspberry Pi C++)
Press Ctrl+C to exit
----------------------------------------
BMP3 sensor found!
Temperature: 23.45 °C
Pressure: 1013.25 hPa
Altitude: 0.00 m
----------------------------------------
Temperature: 23.47 °C
Pressure: 1013.23 hPa
Altitude: 1.23 m
----------------------------------------
```

### 6.3 Stop the Program
```bash
# Press Ctrl+C to stop the program
```

---

## Step 7: Workshop Verification Checklist

### 7.1 Quick Health Check
```bash
# 1. Verify I2C is working
sudo i2cdetect -y 1 | grep 77

# 2. Check wiringPi
gpio -v

# 3. Test build
make clean && make

# 4. Quick sensor test
sudo ./bmp3xx_reader &
sleep 5
sudo pkill bmp3xx_reader
```

### 7.2 Common Issues and Solutions

**Issue: "Could not find BMP3 sensor"**
```bash
# Solution: Check wiring and I2C address
sudo i2cdetect -y 1
# Make sure you see "77" or "76"
```

**Issue: "Failed to initialize wiringPi"**
```bash
# Solution: Run with sudo
sudo ./bmp3xx_reader
```

**Issue: "Permission denied"**
```bash
# Solution: Make executable
chmod +x bmp3xx_reader
```

**Issue: "No such file or directory"**
```bash
# Solution: Check you're in the right directory
pwd
ls -la bmp3xx_reader
```

---

## Step 8: Workshop Day Commands

### 8.1 Quick Start (Copy-Paste Ready)
```bash
# Navigate to project
cd /Users/chelseazhao/Desktop/coding/repo/Adafruit_BMP3XX/examples/raspberry_pi/

# Build and run
make && sudo ./bmp3xx_reader
```

### 8.2 Debug Commands
```bash
# Check I2C devices
sudo i2cdetect -y 1

# Check system status
gpio -v
lsmod | grep i2c

# Rebuild if needed
make clean && make
```

---

## Troubleshooting Quick Reference

| Problem | Solution |
|---------|----------|
| No I2C device found | Check wiring, try address 0x76 |
| Permission denied | Use `sudo` |
| Build fails | Install dependencies: `sudo apt install wiringpi libwiringpi-dev g++` |
| I2C not enabled | Run `sudo raspi-config nonint do_i2c 0` and reboot |
| Sensor not responding | Check power (3.3V), verify connections |

---

## Success Indicators

✅ **Hardware**: BMP390 detected at I2C address 0x77 or 0x76  
✅ **Software**: Program compiles without errors  
✅ **Execution**: Program runs and displays sensor data  
✅ **Data**: Temperature, pressure, and altitude readings are reasonable  

**You're ready for the workshop!** 🎉
