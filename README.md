# 🖱️ ESP32 Air Mouse using MPU6050 (Gesture Controlled Mouse)

## 📌 Overview
This project implements a **gesture-controlled wireless mouse** using an **ESP32** and **MPU6050 accelerometer**.  
The ESP32 acts as a **Bluetooth HID device**, allowing you to control a cursor by simply tilting your hand.

---

## 🚀 Features
- 📡 Bluetooth-based wireless mouse (no receiver required)
- 🎯 Smooth cursor control using **Kalman filter**
- ✋ Gesture-based movement (tilt to move)
- 🖱️ Physical button for left click
- 🔇 Noise reduction with dead-zone filtering
- ⚡ Low-latency response

---

## 🧰 Hardware Required
- ESP32 Development Board  
- MPU6050 Accelerometer & Gyroscope Module  
- Push Button (or use ESP32 BOOT button)  
- Jumper Wires  

---

## 🔌 Circuit Connections

| MPU6050 | ESP32 |
|--------|------|
| VCC    | 3.3V |
| GND    | GND  |
| SDA    | GPIO 21 |
| SCL    | GPIO 22 |

| Button | ESP32 |
|--------|------|
| One side | GPIO 0 |
| Other side | GND |

---

## 💻 Software Requirements
- Arduino IDE  
- ESP32 Board Package  

### 📚 Required Libraries
- Wire (comes with Arduino)
- BleMouse  

🔗 BleMouse Library GitHub:  
https://github.com/T-vK/ESP32-BLE-Mouse

---

## ⚙️ Installation Steps

1. Install Arduino IDE  
2. Add ESP32 board:
   - Go to **Preferences → Additional Board URLs**
   - Add:
     https://dl.espressif.com/dl/package_esp32_index.json
3. Install ESP32 from Board Manager  
4. Install BleMouse library:
   - Download ZIP from GitHub link above  
   - Go to **Sketch → Include Library → Add .ZIP Library**  
5. Connect ESP32 and select correct COM port  
6. Upload the code  

---

## 🔗 How It Works

1. MPU6050 detects hand tilt (X and Y axis)
2. Raw data is mapped to cursor movement
3. Kalman filter smooths noisy sensor data
4. Small jitters are removed using a dead zone
5. ESP32 sends movement via Bluetooth as a mouse
6. Button press triggers left-click

---

## ⚠️ Problems Faced & Solutions

### ❌ 1. Cursor Too Jumpy
**Cause:** Noisy accelerometer data  
**Solution:**  
- Implemented **Kalman filter**
- Added dead-zone filtering  
- Tuned parameters (`q`, `r`)

---

### ❌ 2. Bluetooth Not Connecting
**Cause:** ESP32 BLE issues or wrong board selection  
**Solution:**  
- Ensure correct ESP32 board is selected  
- Restart Bluetooth on device  
- Re-upload code  

---

### ❌ 3. MPU6050 Not Detected
**Cause:** Wrong wiring or I2C issue  
**Solution:**  
- Check SDA (21) and SCL (22)  
- Verify power (3.3V)  
- Use I2C scanner sketch  

---

### ❌ 4. Movement Too Fast / Too Slow
**Cause:** Improper sensitivity mapping  
**Solution:**  
- Adjust mapping range:
  map(value, -17000, 17000, -35, 35);
- Lower range → slower movement  
- Higher range → faster movement  

---

### ❌ 5. Small Unwanted Movements
**Cause:** Sensor noise  
**Solution:**  
- Added dead zone:
  if (abs(value) < 1.5) value = 0;

---

### ❌ 6. Button Multiple Click Issue
**Cause:** Button bouncing  
**Solution:**  
- Added delay debounce:
  delay(200);

---

## 🔧 Tuning Parameters

| Parameter | Purpose |
|----------|--------|
| `q` | Responsiveness (higher = faster) |
| `r` | Smoothness (higher = smoother) |
| Dead zone | Reduces jitter |
| Mapping range | Controls sensitivity |

---

## 📈 Future Improvements
- 🖱️ Right-click gesture  
- 🔄 Scroll using tilt  
- 🎮 Gesture recognition (swipe, tap)  
- 📊 Adaptive sensitivity  
- 🔋 Battery optimization  

---

## 📸 Demo
(Add your project images/videos here)

---

## 🤝 Contributing
Feel free to fork this repo and improve the project!

---

## 📜 License
This project is open-source and free to use.

---

## ⭐ Acknowledgment
Inspired by gesture-based human-computer interaction systems and DIY embedded projects.
