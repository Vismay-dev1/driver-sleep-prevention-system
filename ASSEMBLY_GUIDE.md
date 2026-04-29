# Hardware Assembly Guide

This guide provides step-by-step instructions for assembling the Driver Sleep Prevention System.

## 📦 Required Components Checklist

Before starting, ensure you have:
- [ ] Arduino Uno or Nano
- [ ] 2× IR Sensor Modules (FC-51 or similar)
- [ ] 1× Active Buzzer (5V)
- [ ] 1× Glasses frame
- [ ] Jumper wires (Male-to-Male and Male-to-Female)
- [ ] 9V Battery or USB power bank
- [ ] Toggle switch
- [ ] Soldering iron and solder (optional but recommended)
- [ ] Hot glue gun or double-sided tape
- [ ] Wire strippers
- [ ] Multimeter (for testing)

## 🔧 Assembly Steps

### Step 1: Prepare the Glasses Frame
1. Choose a lightweight glasses frame (can be non-prescription safety glasses)
2. Clean the inside of the frame where sensors will be mounted
3. Mark positions for IR sensors:
   - Left sensor: Inside left frame, aligned with left eye
   - Right sensor: Inside right frame, aligned with right eye
   - Position: ~5-10mm from where your eye would be when wearing

### Step 2: Mount IR Sensors

**Positioning:**
- Sensors should face inward toward the eyes
- Optimal distance: 5-15mm from the eye when glasses are worn
- Angle: Slightly tilted downward toward the eyelid

**Mounting Method 1: Hot Glue (Recommended)**
1. Apply small amount of hot glue to sensor back
2. Press firmly onto the inside of glasses frame
3. Hold for 30 seconds until glue sets
4. Ensure sensor is stable and properly aligned

**Mounting Method 2: Double-Sided Tape**
1. Cut small piece of strong double-sided tape
2. Attach to back of sensor
3. Press firmly onto glasses frame
4. Add a drop of super glue around edges for extra security

### Step 3: Wire the IR Sensors

**For Each Sensor:**
```
IR Sensor Pin Layout:
┌─────────────┐
│   VCC  →  5V     (Red wire)
│   GND  →  GND    (Black wire)
│   OUT  →  Digital Pin (Yellow/Green wire)
└─────────────┘
```

**Wiring:**
1. Cut wires to appropriate length (measure from sensor to Arduino location)
2. Strip ~5mm of insulation from each end
3. Solder wires to sensor pins (or use connector if available):
   - Left sensor OUT → Arduino Pin 2
   - Right sensor OUT → Arduino Pin 3
   - Both sensors VCC → Arduino 5V (can share common 5V rail)
   - Both sensors GND → Arduino GND (can share common ground)

**Wire Management:**
- Run wires along the glasses frame arms
- Use small cable ties or tape to secure wires
- Leave some slack for head movement
- Route wires to where Arduino will be positioned (back of head/ear)

### Step 4: Mount the Buzzer

**Position Options:**
- **Option A:** Near temple (inside glasses arm)
- **Option B:** Behind ear (attached to glasses arm tip)
- **Option C:** On headband/strap (if adding external support)

**Wiring:**
1. Connect buzzer positive (+) to Arduino Pin 8
2. Connect buzzer negative (-) to Arduino GND
3. Secure buzzer with hot glue or tape
4. Ensure it's positioned close to ear for effective alert

### Step 5: Mount Arduino Board

**Recommended Locations:**
- Behind head (using elastic headband)
- On glasses arm (if using Arduino Nano)
- In a small project box attached to glasses

**Mounting Arduino Nano on Glasses:**
1. Use a small plastic project box or 3D-printed enclosure
2. Attach to glasses arm using zip ties or adhesive
3. Ensure box has openings for wires and USB port (for programming)

**Mounting Arduino Uno Separately:**
1. Place Arduino in a small belt pouch or pocket
2. Use longer wires from sensors to Arduino
3. More comfortable but requires more wire management

### Step 6: Power Supply Setup

**Option 1: 9V Battery**
```
9V Battery → Toggle Switch → Arduino VIN pin
Battery GND → Arduino GND
```

**Option 2: USB Power Bank**
```
Power Bank → USB Cable → Arduino USB Port
Add toggle switch to USB cable (cut and splice)
```

**Mounting Power:**
- Attach battery/power bank to glasses arm or headband
- Ensure weight is balanced
- Switch should be easily accessible

### Step 7: Final Assembly

1. **Connect all components** according to circuit diagram
2. **Secure all connections** with solder or electrical tape
3. **Test before wearing:**
   - Upload code to Arduino
   - Open Serial Monitor
   - Observe sensor readings
   - Close eyes manually over sensors - buzzer should activate
4. **Insulate connections** with heat shrink tubing or electrical tape
5. **Cable management:**
   - Bundle wires neatly
   - Use small zip ties
   - Ensure no loose wires that could catch or pull

## 🧪 Testing and Calibration

### Initial Testing
1. Power on the system
2. Open Arduino IDE Serial Monitor (9600 baud)
3. Observe sensor readings:
   ```
   Left: 1 | Right: 1 | Eyes Closed: NO    (eyes open)
   Left: 0 | Right: 0 | Eyes Closed: YES   (eyes closed)
   ```

### Sensor Calibration

**If sensors are too sensitive (false positives):**
- Adjust the sensitivity potentiometer on IR sensor (turn clockwise)
- Increase distance between sensor and eye slightly
- Check for ambient IR interference

**If sensors are not sensitive enough (not detecting):**
- Decrease distance between sensor and eye
- Adjust potentiometer (turn counterclockwise)
- Ensure sensors are powered properly (check voltage)

**Calibration Process:**
1. Wear the glasses
2. Adjust potentiometer on each sensor while checking Serial Monitor
3. Find the point where:
   - Eyes open = HIGH (1)
   - Eyes closed = LOW (0)
4. Test by blinking rapidly - should not trigger alert
5. Close eyes for 2+ seconds - should trigger buzzer

### Fine-Tuning

**Adjust Threshold Time:**
Edit in code:
```cpp
const int CLOSURE_THRESHOLD = 2000;  // Change value (milliseconds)
```
- Shorter time (1000ms) = more sensitive, quicker alerts
- Longer time (3000ms) = less sensitive, allows for normal long blinks

**Adjust Buzzer Duration:**
```cpp
const int BUZZER_DURATION = 3000;  // Change value (milliseconds)
```

## 🔍 Troubleshooting

### Problem: Buzzer constantly active
**Solution:**
- Check sensor orientation (should face eyes)
- Adjust sensor sensitivity (potentiometer)
- Verify wiring connections
- Check if sensors are inverted (swap HIGH/LOW logic in code)

### Problem: Buzzer never activates
**Solution:**
- Test buzzer separately: `digitalWrite(BUZZER_PIN, HIGH);` in setup()
- Check buzzer polarity (+ and - terminals)
- Verify Pin 8 connection
- Check 5V power to buzzer

### Problem: Inconsistent detection
**Solution:**
- Stabilize sensor mounting (may be loose)
- Check wire connections for loose contacts
- Add debounce delay in code
- Shield sensors from external IR sources

### Problem: Battery drains quickly
**Solution:**
- Use USB power bank instead of 9V battery
- Add a sleep mode when not detecting closure
- Use Arduino Nano/Pro Mini (lower power)
- Check for short circuits

## 📏 Optimal Measurements

| Parameter | Recommended Value |
|-----------|------------------|
| Sensor-to-eye distance | 8-12mm |
| Sensor angle | 10-15° downward |
| Wire gauge | 22-24 AWG |
| Closure threshold | 1500-2500ms |
| Buzzer volume | 85-95 dB |

## 🛡️ Safety Considerations

1. **Electrical Safety:**
   - Use proper insulation on all connections
   - Avoid short circuits near face
   - Test thoroughly before wearing while driving

2. **Comfort:**
   - Ensure glasses are comfortable for extended wear
   - Balance weight distribution
   - Avoid pressure points

3. **Visibility:**
   - Sensors should not obstruct vision
   - Wires should not dangle in front of eyes
   - Keep design minimal and non-distracting

## 📸 Assembly Photos

*(Add your assembly photos here)*

- [ ] Sensor mounting on glasses
- [ ] Wiring closeup
- [ ] Arduino placement
- [ ] Complete assembled unit
- [ ] Wearing demonstration

## ✅ Final Checklist

Before using the device:
- [ ] All components securely mounted
- [ ] All electrical connections insulated
- [ ] Sensors properly aligned with eyes
- [ ] Buzzer audible when worn
- [ ] Code uploaded and tested
- [ ] Power switch accessible
- [ ] Comfortable to wear for extended periods
- [ ] No loose wires or components
- [ ] Serial monitoring shows correct readings
- [ ] Alert triggers correctly when eyes close

---

**Need help?** Open an issue on GitHub or contact the project maintainer.

**Safety First:** This is an assistive device. Always prioritize proper rest before driving.
