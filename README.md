# 🚗 Driver Sleep Prevention System

A smart safety device designed to prevent drowsy driving accidents by detecting eye closure and alerting the driver using Arduino and IR sensors integrated into a wearable glasses form factor.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Arduino](https://img.shields.io/badge/Arduino-00979D?logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/status-active-success.svg)

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Circuit Diagram](#circuit-diagram)
- [Installation](#installation)
- [How It Works](#how-it-works)
- [Usage](#usage)
- [Code Explanation](#code-explanation)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## 🎯 Overview

Drowsy driving is a major cause of road accidents worldwide. This project implements a real-time driver drowsiness detection system using infrared (IR) sensors mounted on glasses to detect eye closure. When the driver's eyes remain closed for a predefined duration, a buzzer alerts them to prevent potential accidents.

**Key Innovation:** The system is integrated into a glasses form factor, making it comfortable, non-intrusive, and easy to wear during driving.

## ✨ Features

- ✅ **Real-time Eye Closure Detection** - Continuous monitoring using IR sensors
- ✅ **Immediate Alert System** - Buzzer activation upon detecting drowsiness
- ✅ **Wearable Design** - Integrated into glasses for comfort and convenience
- ✅ **Low Power Consumption** - Efficient power usage for extended operation
- ✅ **Adjustable Sensitivity** - Customizable threshold for eye closure detection
- ✅ **Affordable Solution** - Built with readily available components
- ✅ **Easy to Build** - Simple circuit and straightforward assembly

## 🔧 Hardware Requirements

| Component | Quantity | Specification | Purpose |
|-----------|----------|---------------|---------|
| Arduino Board | 1 | Arduino Uno/Nano | Microcontroller unit |
| IR Sensor Module | 2 | Digital IR obstacle sensor | Eye closure detection |
| Buzzer | 1 | Active buzzer (5V) | Audio alert |
| Glasses Frame | 1 | Any standard frame | Mounting platform |
| Resistors | 2 | 220Ω | LED current limiting |
| Connecting Wires | - | Jumper wires | Circuit connections |
| Battery | 1 | 9V or power bank | Power supply |
| Switch | 1 | SPST toggle switch | Power on/off |
| PCB (Optional) | 1 | Small prototype board | Compact assembly |

### Recommended Components
- **Arduino Nano** - For compact size and easy integration into glasses
- **IR Sensor**: FC-51 or similar digital IR obstacle detection module
- **Buzzer**: 5V active buzzer with built-in oscillator

## 📐 Circuit Diagram

```
Arduino Pins Configuration:
┌─────────────────────────────────┐
│  Component    │  Arduino Pin    │
├───────────────┼─────────────────┤
│  IR Sensor 1  │  Digital Pin 2  │
│  IR Sensor 2  │  Digital Pin 3  │
│  Buzzer       │  Digital Pin 8  │
│  Power (VCC)  │  5V             │
│  Ground (GND) │  GND            │
└─────────────────────────────────┘

Circuit Connection:
- IR Sensor 1 (Left Eye):
  * VCC → Arduino 5V
  * GND → Arduino GND
  * OUT → Arduino Digital Pin 2

- IR Sensor 2 (Right Eye):
  * VCC → Arduino 5V
  * GND → Arduino GND
  * OUT → Arduino Digital Pin 3

- Buzzer:
  * Positive (+) → Arduino Digital Pin 8
  * Negative (-) → Arduino GND
```

## 📥 Installation

### Step 1: Clone the Repository
```bash
git clone https://github.com/Vismay-dev1/driver-sleep-prevention-system.git
cd driver-sleep-prevention-system
```

### Step 2: Install Arduino IDE
- Download from [Arduino Official Website](https://www.arduino.cc/en/software)
- Install the IDE for your operating system

### Step 3: Upload the Code
1. Open `driver_sleep_prevention.ino` in Arduino IDE
2. Connect your Arduino board via USB
3. Select the correct board: `Tools > Board > Arduino Uno/Nano`
4. Select the correct port: `Tools > Port > [Your Arduino Port]`
5. Click the Upload button (→)

### Step 4: Hardware Assembly
1. Mount IR sensors on the inside of glasses frame (aligned with eyes)
2. Connect sensors to Arduino as per circuit diagram
3. Attach buzzer near the ear position on glasses frame
4. Secure Arduino board (use Arduino Nano for compactness)
5. Connect battery/power supply with switch
6. Test all connections before wearing

## 🔬 How It Works

### Detection Principle
The system uses **infrared reflection** to detect eye closure:

1. **IR Sensors Emit Infrared Light** - Positioned near each eye
2. **Reflection Detection** - When eyes are open, IR light is absorbed by the pupil (low reflection). When eyes close, the eyelid reflects more IR light back to the sensor
3. **Signal Processing** - Arduino continuously reads sensor outputs
4. **Alert Trigger** - If both sensors detect closure for more than the threshold time (e.g., 2 seconds), the buzzer activates

### Algorithm Flow
```
START
  ↓
Initialize Sensors & Buzzer
  ↓
[LOOP]
  ↓
Read IR Sensor 1 (Left Eye)
Read IR Sensor 2 (Right Eye)
  ↓
Both Eyes Closed? ──NO──→ Reset Timer, Continue Loop
  ↓ YES
Increment Closure Timer
  ↓
Timer > Threshold? ──NO──→ Continue Loop
  ↓ YES
ACTIVATE BUZZER (Alert!)
  ↓
Wait for Eyes to Open
  ↓
Reset Timer, Deactivate Buzzer
  ↓
[LOOP CONTINUES]
```

## 🚀 Usage

### Operating the Device
1. **Power On**: Flip the power switch
2. **Wear the Glasses**: Position sensors properly aligned with your eyes
3. **Drive Safely**: The system monitors you continuously
4. **Alert Response**: If buzzer sounds, take a break immediately

### Calibration
- Adjust IR sensor sensitivity using the onboard potentiometer
- Test by closing eyes for 2-3 seconds - buzzer should activate
- Fine-tune threshold time in code if needed

### Safety Tips
- This is an **assistive device**, not a replacement for adequate rest
- Take regular breaks during long drives
- Never rely solely on technology - listen to your body
- If you feel drowsy, pull over safely and rest

## 💻 Code Explanation

### Main Components

```cpp
// Pin Definitions
const int IR_LEFT = 2;     // Left eye IR sensor
const int IR_RIGHT = 3;    // Right eye IR sensor
const int BUZZER = 8;      // Buzzer pin

// Threshold for drowsiness detection (milliseconds)
const int CLOSURE_THRESHOLD = 2000; // 2 seconds
```

### Key Functions
- **setup()**: Initializes pins and serial communication
- **loop()**: Continuous monitoring and detection logic
- **checkEyeClosure()**: Reads sensor states and calculates closure duration
- **activateAlert()**: Triggers buzzer when drowsiness detected

### Customization
Modify these parameters in the code:
```cpp
const int CLOSURE_THRESHOLD = 2000;  // Alert delay (milliseconds)
const int BUZZER_DURATION = 1000;    // Buzzer active time
```

## 🔮 Future Enhancements

### Planned Features
- [ ] **Vibration Motor** - Additional tactile alert
- [ ] **Mobile App Integration** - Bluetooth connectivity for data logging
- [ ] **GPS Logging** - Track drowsiness patterns based on location
- [ ] **Machine Learning** - Adaptive threshold based on individual patterns
- [ ] **Emergency Contact Alert** - SMS/call to emergency contact
- [ ] **Sleep Stage Detection** - Differentiate between blink and sleep
- [ ] **Rechargeable Battery** - USB-C charging capability
- [ ] **LED Indicators** - Visual status feedback

### Advanced Versions
- Integration with vehicle systems (CAN bus)
- Cloud-based analytics dashboard
- Multi-sensor fusion (heart rate, head tilt)
- Voice-based alerts with customizable messages

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork the Repository**
2. **Create a Feature Branch**
   ```bash
   git checkout -b feature/amazing-feature
   ```
3. **Commit Your Changes**
   ```bash
   git commit -m "Add amazing feature"
   ```
4. **Push to Branch**
   ```bash
   git push origin feature/amazing-feature
   ```
5. **Open a Pull Request**

See [CONTRIBUTING.md](CONTRIBUTING.md) for more details.

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👤 Contact

**Vismay Vinod**
- GitHub: [@Vismay-dev1](https://github.com/Vismay-dev1)
- LinkedIn: [VismayVinod](https://linkedin.com/in/VismayVinod)
- Instagram: [@vis_may_v](https://instagram.com/vis_may_v/)

Project Link: [https://github.com/Vismay-dev1/driver-sleep-prevention-system](https://github.com/Vismay-dev1/driver-sleep-prevention-system)

---

## 🙏 Acknowledgments

- Arduino Community for extensive documentation
- Open-source hardware movement
- Road safety organizations worldwide
- Everyone working to prevent drowsy driving accidents

---

## ⚠️ Disclaimer

This device is designed as an **assistive safety tool** and should not be considered a complete solution for preventing drowsy driving. Always ensure you are well-rested before driving. If you feel tired, the safest option is to pull over and rest. The creators of this project are not liable for any accidents or injuries that may occur while using this device.

---

**⭐ If you found this project helpful, please consider giving it a star!**

**📢 Share this project to help make roads safer for everyone!**
