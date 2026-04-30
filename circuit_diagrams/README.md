# Circuit Diagrams

This directory contains circuit diagrams and schematics for the Driver Sleep Prevention System.

## 📐 Circuit Diagram Overview

### Basic Circuit Schematic

```
                    DRIVER SLEEP PREVENTION SYSTEM
                         Circuit Schematic
                              
                                 Arduino
                          ┌─────────────────┐
                          │                 │
    IR Sensor 1 (Left)    │   Digital Pin 2 │────┐
         VCC ─────────────┤   5V            │    │
         GND ─────────────┤   GND           │    │
         OUT ─────────────┤                 │    │
                          │                 │    │
    IR Sensor 2 (Right)   │   Digital Pin 3 │────┤
         VCC ─────────────┤   5V            │    │
         GND ─────────────┤   GND           │    │
         OUT ─────────────┤                 │    │
                          │                 │    │
    Active Buzzer         │   Digital Pin 8 │────┘
         (+) ─────────────┤                 │
         (-) ─────────────┤   GND           │
                          │                 │
    Power Supply          │   VIN / 5V      │
      9V Battery ─────────┤   (via switch)  │
      GND        ─────────┤   GND           │
                          │                 │
                          └─────────────────┘
```

## 🔌 Component Connections

### IR Sensor 1 (Left Eye)
| IR Sensor Pin | Arduino Pin | Wire Color (Suggested) |
|---------------|-------------|------------------------|
| VCC           | 5V          | Red                    |
| GND           | GND         | Black                  |
| OUT           | Digital 2   | Yellow                 |

### IR Sensor 2 (Right Eye)
| IR Sensor Pin | Arduino Pin | Wire Color (Suggested) |
|---------------|-------------|------------------------|
| VCC           | 5V          | Red                    |
| GND           | GND         | Black                  |
| OUT           | Digital 3   | Green                  |

### Buzzer Connection
| Buzzer Pin | Arduino Pin | Wire Color (Suggested) |
|------------|-------------|------------------------|
| Positive   | Digital 8   | Orange                 |
| Negative   | GND         | Black                  |

### Power Supply
| Power Source | Arduino Pin | Notes                     |
|--------------|-------------|---------------------------|
| 9V Battery + | VIN         | Through toggle switch     |
| 9V Battery - | GND         | Common ground             |

## ⚡ Power Distribution

```
9V Battery
    │
    ├─── Toggle Switch ─── Arduino VIN
    │
    └─── Arduino GND
            │
            ├─── IR Sensor 1 GND
            ├─── IR Sensor 2 GND
            └─── Buzzer GND

Arduino 5V (Regulated)
    │
    ├─── IR Sensor 1 VCC
    └─── IR Sensor 2 VCC
```

## 🛠️ Optional Enhancements

### Adding LED Indicators
```
Digital Pin 13 (Built-in LED) - Status indicator
    or
External LED:
    Digital Pin 13 ─── 220Ω Resistor ─── LED (+)
    LED (-) ─── GND
```

### Adding Vibration Motor
```
Digital Pin 9 ─── NPN Transistor (Base)
    Collector ─── Vibration Motor (+)
    Emitter ─── GND
    Motor (-) ─── GND
    Motor (+) ─── 5V
```

### Adding Battery Voltage Monitor
```
Analog Pin A0 ─── Voltage Divider ─── Battery +
    (R1: 10kΩ to Battery+, R2: 10kΩ to GND)
```

## 📊 Electrical Specifications

| Component    | Voltage | Current | Power   |
|--------------|---------|---------|---------|
| Arduino Nano | 5V      | 19mA    | 95mW    |
| IR Sensor    | 5V      | 20mA ea | 100mW   |
| Buzzer       | 5V      | 30mA    | 150mW   |
| **Total**    | 5V      | ~90mA   | ~445mW  |

### Battery Life Estimation
- **9V Battery (500mAh)**: ~5-6 hours
- **USB Power Bank (5000mAh)**: ~50-55 hours

## 🔍 Testing Points

When troubleshooting, measure voltage at:
1. **Arduino 5V pin**: Should read 4.8-5.2V
2. **IR Sensor VCC**: Should read 4.8-5.2V
3. **IR Sensor OUT**: Should toggle between 0V (LOW) and 5V (HIGH)
4. **Buzzer Pin**: Should be 5V when active, 0V when inactive

## 📁 Files in This Directory

- `circuit_schematic.png` - Full circuit diagram (to be added)
- `breadboard_layout.png` - Breadboard prototyping layout (to be added)
- `pcb_design.png` - PCB layout for permanent installation (to be added)
- `wiring_photos/` - Photos of actual wiring (to be added)

## 🎨 Creating Circuit Diagrams

Recommended tools:
- [Fritzing](https://fritzing.org/) - Free circuit design software
- [EasyEDA](https://easyeda.com/) - Online PCB design
- [Tinkercad Circuits](https://www.tinkercad.com/circuits) - Online simulator

## ⚠️ Safety Notes

1. **Double-check polarity** before connecting power
2. **Verify all connections** before powering on
3. **Use appropriate wire gauge** (22-24 AWG recommended)
4. **Insulate all connections** to prevent shorts
5. **Test with multimeter** before final assembly

## 📸 Photo Contribution

Have better circuit diagrams or photos? Please contribute!
1. Take clear, well-lit photos
2. Annotate connections if helpful
3. Submit via pull request to this directory

---

**Note:** Actual circuit diagram images will be added as the project develops. Contributions welcome!
