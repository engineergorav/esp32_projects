# ESP32 Projects

This repository contains two ESP32-based projects developed for learning and demonstration purposes.

## Projects Included

### 1. Gesture Controlled Car (Two Motors)

A car that can be controlled using hand gestures via sensors or motion detection.

#### Features:
- Two-motor drive system
- Gesture-based directional control (e.g., forward, backward, left, right)
- Suitable for hobby robotics and DIY automation

#### Components Used:
- ESP32
- L298N Motor Driver
- Gear Motors with Wheels
- Gesture Sensor (e.g., MPU6050 or Accelerometer module)
- Power Supply (Li-ion batteries)

#### Folder: `gesture_controlled_car_2_motors`

---

### 2. Power Monitoring System

A real-time system to monitor and log electrical power consumption.

#### Features:
- Measures voltage, current, and power
- Can display data on a mobile app or web dashboard
- Useful for home automation and energy-saving applications

#### Components Used:
- ESP32
- ACS712 Current Sensor or CT Sensor (e.g., SCT-013)
- Voltage Divider Circuit
- Blynk App or custom dashboard for visualization

#### Folder: `power_monitoring_system`

---

## Getting Started

### Prerequisites
- Arduino IDE or PlatformIO
- ESP32 Board Drivers
- Required libraries (specified in individual project folders)

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/engineergorav/esp32_projects.git
