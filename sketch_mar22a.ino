#include <Wire.h>
#include <BleMouse.h>

BleMouse bleMouse("ESP32 Air Mouse", "ESP32", 100);

const int MPU = 0x68;
int16_t AcX, AcY;

// BOOT button (GPIO 0)
#define BUTTON_PIN 0

// Kalman variables
float estimateX = 0, estimateY = 0;
float errorX = 1, errorY = 1;
float q = 0.1;   // responsiveness
float r = 4;     // smoothness
float k;

// Kalman filter function
float kalman(float measurement, float &estimate, float &error) {
  error = error + q;
  k = error / (error + r);
  estimate = estimate + k * (measurement - estimate);
  error = (1 - k) * error;
  return estimate;
}

void setup() {
  Serial.begin(115200);

  Wire.begin();

  // Wake MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  bleMouse.begin();
}

void loop() {

  if (bleMouse.isConnected()) {

    // Read sensor
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);

    Wire.requestFrom(MPU, 4);

    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();

    // 🎯 Slightly increased sensitivity
    float rawX = map(AcY, -17000, 17000, -35, 35);
    float rawY = map(AcX, -17000, 17000, -35, 35);

    // Apply Kalman filter
    float smoothX = kalman(rawX, estimateX, errorX);
    float smoothY = kalman(rawY, estimateY, errorY);

    // Remove tiny noise
    if (abs(smoothX) < 1.5) smoothX = 0;
    if (abs(smoothY) < 1.5) smoothY = 0;

    // Move cursor
    bleMouse.move((int)smoothX, (int)smoothY);

    // BOOT button click
    if (digitalRead(BUTTON_PIN) == LOW) {
      bleMouse.click(MOUSE_LEFT);
      delay(200); // debounce
    }

    delay(10);
  }
}