# Troubleshooting Guide

This guide helps you diagnose and fix common issues with the Driver Sleep Prevention System.

## 🔍 Diagnostic Checklist

Before troubleshooting specific issues, verify these basics:

- [ ] Arduino is powered and LED on board is lit
- [ ] All connections are secure and not loose
- [ ] Correct code is uploaded to Arduino
- [ ] Serial Monitor shows sensor readings (9600 baud)
- [ ] Sensors are positioned correctly near eyes
- [ ] Power supply has sufficient charge

## 🚨 Common Issues and Solutions

### Issue 1: Buzzer Constantly Active (False Positives)

**Symptoms:**
- Buzzer sounds immediately on power up
- Buzzer won't turn off even with eyes open
- Alert triggers randomly

**Possible Causes & Solutions:**

**1. Sensors Too Sensitive**
```
Solution:
- Turn sensor potentiometer clockwise (reduces sensitivity)
- Test after each adjustment
- Find the point where eyes open = HIGH, closed = LOW
```

**2. Inverted Sensor Logic**
```
Solution: Modify code to invert the logic
Change this line:
    bool bothEyesClosed = (leftEyeState == LOW && rightEyeState == LOW);
To:
    bool bothEyesClosed = (leftEyeState == HIGH && rightEyeState == HIGH);
```

**3. Sensors Too Close to Eyes**
```
Solution:
- Increase distance between sensor and eye to 10-15mm
- Reposition sensors slightly outward
- Test after adjustment
```

**4. Ambient IR Interference**
```
Solution:
- Test in different lighting conditions
- Shield sensors from direct sunlight
- Add IR filters to sensors
- Move away from IR sources (TV remotes, IR cameras)
```

**Debugging Steps:**
1. Open Serial Monitor (Tools > Serial Monitor, 9600 baud)
2. Observe sensor readings:
   ```
   Left: 1 | Right: 1  ← Eyes should be OPEN
   Left: 0 | Right: 0  ← Eyes should be CLOSED
   ```
3. If readings don't match eye state, adjust sensitivity or logic

---

### Issue 2: Buzzer Never Activates (False Negatives)

**Symptoms:**
- Buzzer never sounds, even with eyes closed for long time
- No alert despite keeping eyes closed
- System seems inactive

**Possible Causes & Solutions:**

**1. Buzzer Not Connected Properly**
```
Solution:
- Check buzzer polarity (+ to Pin 8, - to GND)
- Verify Pin 8 connection is secure
- Test buzzer separately with this code in setup():
  
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
```

**2. Buzzer Defective**
```
Solution:
- Test with multimeter: should show continuity
- Try different buzzer
- Ensure it's an ACTIVE buzzer (has built-in oscillator)
```

**3. Sensors Not Detecting Eye Closure**
```
Solution:
- Adjust sensor sensitivity (turn potentiometer counter-clockwise)
- Decrease sensor-to-eye distance to 5-8mm
- Ensure sensors face directly toward eyes
- Check if sensors are powered (VCC = 5V)
```

**4. Threshold Too Long**
```
Solution: Reduce detection threshold in code
Change:
    const int CLOSURE_THRESHOLD = 2000;
To:
    const int CLOSURE_THRESHOLD = 1000;  // 1 second
```

**Debugging Steps:**
1. Check Serial Monitor for sensor readings
2. Verify sensors change state when eyes close
3. Test each component individually
4. Verify power to all components

---

### Issue 3: Inconsistent or Erratic Detection

**Symptoms:**
- Sometimes works, sometimes doesn't
- Random triggering
- Detection varies with head position

**Possible Causes & Solutions:**

**1. Loose Connections**
```
Solution:
- Resolder all connections
- Use hot glue to secure wires
- Check for broken wires
- Ensure connectors are pushed in fully
```

**2. Unstable Sensor Mounting**
```
Solution:
- Use stronger adhesive (hot glue > tape)
- Add support structure to sensors
- Ensure sensors don't move when wearing glasses
- Use zip ties for additional security
```

**3. Electromagnetic Interference**
```
Solution:
- Move Arduino away from phone/other electronics
- Use shielded wires for sensor connections
- Add decoupling capacitors (0.1µF) near sensors
- Twist sensor wires together to reduce noise
```

**4. Power Supply Issues**
```
Solution:
- Check battery voltage (should be >7V for 9V battery)
- Replace battery if low
- Use regulated power supply or power bank
- Add capacitor (100µF) across power rails
```

---

### Issue 4: Doesn't Work with Eyes Open (Wrong Direction Detection)

**Symptoms:**
- Alert when eyes are open
- No alert when eyes are closed
- Inverted behavior

**Solution:**
Invert the detection logic in code:

```cpp
// Change from:
bool bothEyesClosed = (leftEyeState == LOW && rightEyeState == LOW);

// To:
bool bothEyesClosed = (leftEyeState == HIGH && rightEyeState == HIGH);
```

---

### Issue 5: One Sensor Not Working

**Symptoms:**
- Left or right sensor always shows same reading
- Uneven detection
- Only one eye detected

**Debugging:**
1. Open Serial Monitor
2. Check individual sensor outputs:
   ```
   Left: 1 | Right: 1  ← Both should match when eyes open
   Left: 0 | Right: 1  ← Problem: Right sensor stuck
   ```

**Solutions:**

**Sensor Not Powered:**
- Check VCC connection to 5V
- Verify GND connection
- Measure voltage at sensor (should be 5V)

**Sensor Defective:**
- Swap sensors to test
- Replace faulty sensor
- Check for physical damage

**Wrong Pin Connection:**
- Verify Left = Pin 2, Right = Pin 3
- Check pin definitions in code match wiring
- Re-upload code after changes

---

### Issue 6: Battery Drains Too Quickly

**Symptoms:**
- Device stops working after 30-60 minutes
- Battery gets warm
- Power LED dims

**Solutions:**

**1. Battery Capacity Too Low**
```
Solution:
- Use 500mAh+ 9V battery (not cheap 200mAh versions)
- Switch to USB power bank (5000mAh+ recommended)
- Add larger capacity battery pack
```

**2. Short Circuit**
```
Solution:
- Disconnect power and check all connections
- Look for exposed wires touching
- Use multimeter to check for shorts
- Insulate all connections properly
```

**3. Power-Hungry Components**
```
Solution:
- Use Arduino Nano instead of Uno (lower power)
- Add sleep mode when not detecting
- Reduce buzzer activation time
```

**Power Saving Code:**
```cpp
// Add this in setup:
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, LOW);  // Turn off onboard LED

// Reduce Serial output frequency or disable:
// Comment out Serial.print() statements for production use
```

---

### Issue 7: Discomfort When Wearing

**Symptoms:**
- Pressure on nose or ears
- Sensors press against eyes
- Weight causes headaches

**Solutions:**

**Weight Distribution:**
- Use Arduino Nano instead of Uno
- Mount Arduino on headband, not glasses
- Balance weight on both sides
- Use lighter battery (LiPo instead of 9V)

**Sensor Position:**
- Increase sensor distance from eyes
- Angle sensors slightly upward
- Use softer mounting material
- Add padding around sensors

**Glasses Fit:**
- Choose lightweight frame
- Adjust nose pads
- Use eyeglass straps to distribute weight
- Take breaks during long use

---

### Issue 8: Buzzer Too Loud/Quiet

**Too Loud:**
```
Solutions:
- Add resistor in series with buzzer (100-220Ω)
- Use PWM to reduce volume:
  
  analogWrite(BUZZER_PIN, 128);  // 50% volume instead of digitalWrite
  
- Cover buzzer with tape to muffle sound
- Use quieter buzzer model
```

**Too Quiet:**
```
Solutions:
- Remove any resistors in buzzer circuit
- Use higher current buzzer
- Position buzzer closer to ear
- Use acoustic chamber to amplify sound
```

---

### Issue 9: Normal Blinking Triggers Alert

**Symptoms:**
- Alert activates during normal blinking
- Threshold seems too sensitive
- Can't blink without triggering

**Solution:**
Increase the closure threshold:

```cpp
// Change from:
const int CLOSURE_THRESHOLD = 2000;  // 2 seconds

// To:
const int CLOSURE_THRESHOLD = 3000;  // 3 seconds

// Or add blink filtering:
const int DEBOUNCE_DELAY = 100;  // Ignore closures < 100ms
```

---

### Issue 10: Code Won't Upload to Arduino

**Symptoms:**
- "Upload failed" error
- COM port not found
- Board not recognized

**Solutions:**

**1. Driver Issues**
- Install CH340/FTDI drivers for clone boards
- Windows: Download from Arduino.cc
- Mac: Install drivers manually

**2. Wrong Board/Port Selected**
```
Solution:
- Tools > Board > Select your Arduino model
- Tools > Port > Select correct COM/Serial port
- Try different USB cable
- Try different USB port on computer
```

**3. Bootloader Issue**
```
Solution:
- Hold reset button, start upload, release when uploading starts
- Try burning bootloader (Tools > Burn Bootloader)
- Use ISP programmer if bootloader corrupted
```

---

## 🧪 Testing Procedures

### Complete System Test

**1. Power Test**
- Connect power, check Arduino LED
- Measure 5V at Arduino 5V pin
- Verify sensors receive power

**2. Sensor Test**
- Open Serial Monitor (9600 baud)
- Observe readings with eyes open/closed
- Verify both sensors respond correctly

**3. Buzzer Test**
- Close eyes for threshold duration
- Buzzer should activate
- Open eyes, buzzer should stop

**4. Endurance Test**
- Wear for 30 minutes
- Check for comfort issues
- Verify battery level
- Test in different lighting

### Individual Component Tests

**Arduino Test:**
```cpp
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
// LED should blink = Arduino working
```

**Sensor Test:**
```cpp
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
}

void loop() {
  Serial.println(digitalRead(2));
  delay(500);
}
// Should show 0 or 1 based on detection
```

**Buzzer Test:**
```cpp
void setup() {
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  delay(2000);
  digitalWrite(8, LOW);
}

void loop() {}
// Buzzer should sound for 2 seconds
```

---

## 📊 Advanced Diagnostics

### Serial Monitor Output Analysis

**Normal Operation:**
```
Left: 1 | Right: 1 | Eyes Closed: NO
Left: 1 | Right: 1 | Eyes Closed: NO
Left: 0 | Right: 0 | Eyes Closed: YES
⚠ Eyes closed - Timer started
Left: 0 | Right: 0 | Eyes Closed: YES
🚨 DROWSINESS DETECTED! ALERT ACTIVATED! 🚨
```

**Problem Indicators:**
```
Left: 0 | Right: 0 | Eyes Closed: YES  ← Constant even with eyes open
Left: 1 | Right: 0 | Eyes Closed: NO   ← Right sensor stuck
Left: -1 | Right: -1 | ...              ← Sensor not connected
```

### Multimeter Measurements

**Expected Values:**
- Arduino 5V pin: 4.8-5.2V
- Sensor VCC: 4.8-5.2V
- Sensor OUT (open): 3-5V (HIGH)
- Sensor OUT (closed): 0-0.5V (LOW)
- Battery: >7V for 9V battery

---

## 🆘 Still Having Issues?

If you've tried everything:

1. **Document the problem:**
   - Take photos/videos
   - Copy Serial Monitor output
   - Note your hardware setup

2. **Check existing issues:**
   - Search GitHub issues
   - Look for similar problems

3. **Open new issue:**
   - Use issue template
   - Provide all diagnostic info
   - Be specific and detailed

4. **Community help:**
   - Arduino forums
   - Reddit r/arduino
   - Electronics Stack Exchange

---

**Remember:** Most issues are caused by:
- Loose connections (50%)
- Incorrect sensor calibration (30%)
- Power supply problems (15%)
- Code configuration (5%)

Always start with the basics!
