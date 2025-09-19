# BMP390 Workshop - Complete Beginner's Guide

## 🤔 What Are We Actually Building?

You're building a **weather station** that can measure:
- **Temperature** (in Celsius)
- **Barometric Pressure** (in Pascals/hPa)
- **Altitude** (calculated from pressure)

Think of it like a digital barometer that also tells you the temperature!

---

## 🔧 Hardware Basics

### What is a BMP390?
- **BMP390** = Barometric Pressure sensor (Model 390)
- **Ultra-low power** pressure and temperature sensor
- **I2C Communication** = Digital communication protocol
- **3.3V operation** = Low voltage, safe for Raspberry Pi

### What is I2C?
- **I2C** = "Inter-Integrated Circuit" 
- **2-wire communication**: SDA (data) + SCL (clock)
- **Multiple devices** can share the same 2 wires
- **Like a digital conversation** between your Pi and sensor

### Raspberry Pi GPIO Pins
```
Raspberry Pi Pin Layout:
    3.3V  (1) (2)  5V
   GPIO2  (3) (4)  5V
   GPIO3  (5) (6)  GND
   GPIO4  (7) (8)  GPIO14
     GND  (9) (10) GPIO15
  GPIO17 (11) (12) GPIO18
  GPIO27 (13) (14) GND
  GPIO22 (15) (16) GPIO23
    3.3V (17) (18) GPIO24
  GPIO10 (19) (20) GND
   GPIO9 (21) (22) GPIO25
  GPIO11 (23) (24) GPIO8
     GND (25) (26) GPIO7
```

**Key Pins for I2C:**
- **Pin 1**: 3.3V (power)
- **Pin 3**: GPIO2/SDA (data)
- **Pin 5**: GPIO3/SCL (clock)
- **Pin 6**: GND (ground)

---

## 💻 Software Basics

### What is C++?
- **Programming language** for system-level programming
- **Faster than Python** for hardware control
- **More control** over memory and hardware
- **Industry standard** for embedded systems

### What is a Makefile?
- **Build instructions** for compiling code
- **Automates compilation** process
- **Handles dependencies** and linking
- **Like a recipe** for building your program

### What is wiringPi?
- **Library** for controlling Raspberry Pi GPIO pins
- **Provides functions** for I2C communication
- **Hardware abstraction** layer
- **Makes hardware programming easier**

---

## 🔄 How Everything Works Together

### 1. Hardware Flow
```
BMP390 Sensor → I2C Wires → Raspberry Pi GPIO → Software
```

### 2. Software Flow
```
Your Code → wiringPi Library → I2C Driver → Hardware
```

### 3. Data Flow
```
Sensor Reading → I2C Transfer → C++ Program → Display Output
```

---

## 📊 Understanding the Data

### Temperature
- **Units**: Celsius (°C)
- **Range**: -40°C to +85°C
- **Accuracy**: ±0.5°C
- **Example**: 23.45°C

### Pressure
- **Units**: Pascals (Pa) or hectopascals (hPa)
- **Range**: 300 to 1250 hPa
- **Accuracy**: ±0.08 hPa
- **Example**: 1013.25 hPa (sea level)

### Altitude
- **Units**: Meters (m)
- **Calculated** from pressure difference
- **Formula**: Uses barometric equation
- **Example**: 0.00 m (sea level)

---

## 🛠️ Workshop Day Workflow

### Step 1: Hardware Setup
1. **Power down** Raspberry Pi
2. **Connect wires** (VCC, GND, SDA, SCL)
3. **Power on** Raspberry Pi
4. **Verify connections** with `i2cdetect`

### Step 2: Software Setup
1. **Clone repository** from GitHub
2. **Install dependencies** (wiringPi, g++)
3. **Build program** with `make`
4. **Run program** with `sudo ./bmp3xx_reader`

### Step 3: Data Collection
1. **Start program** and see live data
2. **Record readings** for analysis
3. **Test different conditions** (indoor/outdoor)
4. **Compare with weather data**

---

## 🚨 Common Issues & Solutions

### "Could not find BMP3 sensor"
**Causes:**
- Wrong wiring
- Wrong I2C address
- Power issues
- I2C not enabled

**Solutions:**
- Check wire connections
- Try `sudo i2cdetect -y 1`
- Verify 3.3V power
- Enable I2C with `sudo raspi-config`

### "Permission denied"
**Cause:** Need root access for I2C
**Solution:** Use `sudo ./bmp3xx_reader`

### "Build failed"
**Causes:**
- Missing dependencies
- Wrong compiler
- File permissions

**Solutions:**
- Install: `sudo apt install wiringpi libwiringpi-dev g++`
- Check: `g++ --version`
- Fix permissions: `chmod +x bmp3xx_reader`

---

## 🎯 What You'll Learn

### Technical Skills
- **Hardware interfacing** with sensors
- **I2C communication** protocol
- **C++ programming** for embedded systems
- **Linux system administration**
- **Git version control**

### Practical Skills
- **Circuit assembly** and wiring
- **Debugging hardware** issues
- **Reading sensor data** sheets
- **Troubleshooting** software problems
- **Documentation** and setup guides

---

## 📚 Additional Resources

### Online References
- **BMP390 Datasheet**: Search "BMP390 datasheet"
- **Raspberry Pi GPIO**: Official documentation
- **I2C Protocol**: Wikipedia or technical guides
- **C++ Tutorials**: Learn basic syntax

### Tools You'll Use
- **Terminal/SSH**: Command line interface
- **Git**: Version control system
- **Make**: Build automation
- **I2C Tools**: Hardware debugging

---

## 🎉 Success Criteria

### You'll Know You're Successful When:
- ✅ **Hardware**: Sensor detected at I2C address
- ✅ **Software**: Program compiles without errors
- ✅ **Data**: Getting realistic temperature/pressure readings
- ✅ **Understanding**: Can explain what each component does

### Workshop Goals:
1. **Build** a working sensor system
2. **Understand** how hardware and software interact
3. **Debug** common issues independently
4. **Apply** knowledge to future projects

---

## 💡 Pro Tips

### Before Workshop:
- **Read the setup guide** completely
- **Test your Raspberry Pi** boots properly
- **Have backup wires** in case of connection issues
- **Bring a multimeter** to check voltages

### During Workshop:
- **Take notes** on any issues you encounter
- **Ask questions** - everyone starts somewhere!
- **Help others** - teaching reinforces learning
- **Experiment** with different sensor settings

### After Workshop:
- **Try modifications** to the code
- **Build additional projects** with the sensor
- **Share your experience** with others
- **Continue learning** embedded systems

---

## 🚀 Next Steps After Workshop

### Immediate Projects:
- **Weather station** with multiple sensors
- **Altitude logger** for hiking/climbing
- **Indoor climate** monitoring
- **Data logging** to files

### Advanced Projects:
- **Web dashboard** for remote monitoring
- **Alert system** for pressure changes
- **Integration** with other sensors
- **Mobile app** for data visualization

---

**Remember: Everyone starts as a beginner. The key is to ask questions, experiment, and learn from mistakes. You've got this!** 🎯
