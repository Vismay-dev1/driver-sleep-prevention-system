/*
 * Driver Sleep Prevention System
 * 
 * Description:
 * This Arduino sketch detects driver drowsiness by monitoring eye closure
 * using IR sensors mounted on glasses. When both eyes are detected as closed
 * for more than the threshold duration, a buzzer alerts the driver.
 * 
 * Hardware:
 * - Arduino Uno/Nano
 * - 2x IR Sensor Modules (Digital Output)
 * - 1x Active Buzzer (5V)
 * - Power Supply (9V battery or USB)
 * 
 * Author: Your Name
 * Date: 2024
 * License: MIT
 */

// ==================== PIN DEFINITIONS ====================
const int IR_SENSOR_LEFT = 2;    // IR sensor for left eye (Digital Pin 2)
const int IR_SENSOR_RIGHT = 3;   // IR sensor for right eye (Digital Pin 3)
const int BUZZER_PIN = 8;        // Buzzer pin (Digital Pin 8)
const int LED_INDICATOR = 13;    // Built-in LED for status indication (optional)

// ==================== CONFIGURATION PARAMETERS ====================
const int CLOSURE_THRESHOLD = 2000;   // Time in milliseconds (2 seconds)
const int BUZZER_DURATION = 3000;     // Buzzer active time in milliseconds
const int DEBOUNCE_DELAY = 50;        // Debounce delay in milliseconds

// ==================== GLOBAL VARIABLES ====================
unsigned long eyesClosedStartTime = 0;  // Timestamp when eyes first closed
bool eyesWereClosed = false;            // Previous state of eyes
bool alertActive = false;               // Buzzer alert status
unsigned long alertStartTime = 0;       // Timestamp when alert started

// ==================== SETUP FUNCTION ====================
void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println("Driver Sleep Prevention System");
  Serial.println("Initializing...");
  
  // Configure pin modes
  pinMode(IR_SENSOR_LEFT, INPUT);
  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_INDICATOR, OUTPUT);
  
  // Initial state: buzzer off
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_INDICATOR, LOW);
  
  // Calibration period
  Serial.println("System Ready!");
  Serial.println("Starting monitoring...");
  delay(2000); // 2-second startup delay
}

// ==================== MAIN LOOP ====================
void loop() {
  // Read sensor states
  // IR sensors typically output LOW when object detected (eye closed)
  // and HIGH when no object detected (eye open)
  int leftEyeState = digitalRead(IR_SENSOR_LEFT);
  int rightEyeState = digitalRead(IR_SENSOR_RIGHT);
  
  // Check if both eyes are closed
  // Adjust this logic based on your IR sensor output:
  // Some sensors are LOW when detecting (obstacle present)
  // Some sensors are HIGH when detecting
  bool bothEyesClosed = (leftEyeState == LOW && rightEyeState == LOW);
  
  // Debugging output (optional - can be commented out)
  Serial.print("Left: ");
  Serial.print(leftEyeState);
  Serial.print(" | Right: ");
  Serial.print(rightEyeState);
  Serial.print(" | Eyes Closed: ");
  Serial.println(bothEyesClosed ? "YES" : "NO");
  
  // ==================== DROWSINESS DETECTION LOGIC ====================
  if (bothEyesClosed) {
    // Eyes are currently closed
    
    if (!eyesWereClosed) {
      // Eyes just closed - start the timer
      eyesClosedStartTime = millis();
      eyesWereClosed = true;
      Serial.println("⚠ Eyes closed - Timer started");
    } else {
      // Eyes were already closed - check duration
      unsigned long closureDuration = millis() - eyesClosedStartTime;
      
      if (closureDuration >= CLOSURE_THRESHOLD && !alertActive) {
        // Eyes closed for too long - activate alert
        activateAlert();
      }
    }
  } else {
    // Eyes are open
    
    if (eyesWereClosed) {
      // Eyes just opened
      Serial.println("✓ Eyes opened - Timer reset");
      eyesWereClosed = false;
      eyesClosedStartTime = 0;
    }
  }
  
  // ==================== ALERT MANAGEMENT ====================
  if (alertActive) {
    unsigned long alertDuration = millis() - alertStartTime;
    
    // Check if alert duration has passed
    if (alertDuration >= BUZZER_DURATION || !bothEyesClosed) {
      // Deactivate alert if duration exceeded or eyes opened
      deactivateAlert();
    }
  }
  
  // Small delay to prevent excessive serial output
  delay(100);
}

// ==================== ALERT ACTIVATION FUNCTION ====================
void activateAlert() {
  Serial.println("🚨 DROWSINESS DETECTED! ALERT ACTIVATED! 🚨");
  
  alertActive = true;
  alertStartTime = millis();
  
  // Turn on buzzer
  digitalWrite(BUZZER_PIN, HIGH);
  
  // Turn on LED indicator
  digitalWrite(LED_INDICATOR, HIGH);
  
  // Optional: Create pulsing buzzer effect
  // Uncomment below for pulsing alert
  /*
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
  digitalWrite(BUZZER_PIN, HIGH);
  */
}

// ==================== ALERT DEACTIVATION FUNCTION ====================
void deactivateAlert() {
  Serial.println("✓ Alert deactivated");
  
  alertActive = false;
  
  // Turn off buzzer
  digitalWrite(BUZZER_PIN, LOW);
  
  // Turn off LED indicator
  digitalWrite(LED_INDICATOR, LOW);
}

// ==================== ADDITIONAL HELPER FUNCTIONS ====================

/*
 * Function: testBuzzer
 * Description: Test function to verify buzzer is working
 * Call this from setup() to test
 */
void testBuzzer() {
  Serial.println("Testing buzzer...");
  digitalWrite(BUZZER_PIN, HIGH);
  delay(500);
  digitalWrite(BUZZER_PIN, LOW);
  delay(500);
  Serial.println("Buzzer test complete");
}

/*
 * Function: calibrateSensors
 * Description: Calibration routine for IR sensors
 * Helps determine the correct threshold values
 */
void calibrateSensors() {
  Serial.println("=== CALIBRATION MODE ===");
  Serial.println("Please keep eyes OPEN for 5 seconds...");
  delay(5000);
  
  int openSamples = 0;
  for (int i = 0; i < 50; i++) {
    if (digitalRead(IR_SENSOR_LEFT) == HIGH) openSamples++;
    delay(100);
  }
  
  Serial.println("Now CLOSE your eyes for 5 seconds...");
  delay(5000);
  
  int closedSamples = 0;
  for (int i = 0; i < 50; i++) {
    if (digitalRead(IR_SENSOR_LEFT) == LOW) closedSamples++;
    delay(100);
  }
  
  Serial.println("=== CALIBRATION RESULTS ===");
  Serial.print("Eyes Open samples (HIGH): ");
  Serial.println(openSamples);
  Serial.print("Eyes Closed samples (LOW): ");
  Serial.println(closedSamples);
  Serial.println("===========================");
}
