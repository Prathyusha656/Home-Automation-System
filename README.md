# Home Automation System

## Overview

This project allows you to automate home devices like lights, fans, air conditioners, and other appliances using an Arduino-based system. By utilizing sensors (motion, temperature, humidity) and relay modules, you can control these devices remotely via Wi-Fi or Bluetooth from your smartphone. The system makes your home smarter, more convenient, and energy-efficient by automating the control of household devices based on real-time sensor data.

## Components

- **Arduino Uno** - Microcontroller to control the system.
- **Relay Modules** (4x) - Used to control high-voltage devices.
- **PIR Motion Sensor** (1x) - Detects motion for automatic lighting.
- **DHT11/DHT22 Sensor** (1x) - Measures temperature and humidity.
- **ESP8266/ESP32** (1x) - For Wi-Fi connectivity.
- **HC-05 Bluetooth Module** (1x, optional) - For Bluetooth control.
- **Smartphone** - For remote control via Blynk app.
- **Wires and Breadboard** - For connections.
- **AC-powered devices** - Lights, fans, ACs, etc. for control.

## Features

- Control devices like lights, fans, and AC remotely using a smartphone app.
- Automate devices based on motion detection (turn on lights when motion is detected).
- Monitor and control the environment by reading temperature and humidity.
- Compatible with Wi-Fi or Bluetooth communication for flexibility.
- User-friendly control interface via the Blynk app.

## Installation

### 1. Install Arduino IDE

Download and install the [Arduino IDE](https://www.arduino.cc/en/software) if you don't have it yet.

### 2. Install Necessary Libraries

Install the following libraries using the Arduino IDE's Library Manager:

- **DHT sensor library** (for temperature and humidity sensor).
- **ESP8266WiFi library** (for Wi-Fi communication).
- **Blynk library** (for smartphone control).

You can install these by going to **Sketch > Include Library > Manage Libraries...**, searching for the library names, and clicking "Install".

### 3. Setup Blynk App

1. Download and install the **Blynk App** from [Google Play](https://play.google.com/store/apps/details?id=cc.blynk) or [App Store](https://apps.apple.com/us/app/blynk-iot/id1527496025).
2. Create a **New Project** in the app:
   - Select **ESP8266** as the device type.
   - Note down the **Auth Token** sent to your email (you'll use this in the Arduino code).
3. Add **Widgets** in the Blynk app:
   - **Temperature Widget** (Virtual Pin V1).
   - **Humidity Widget** (Virtual Pin V2).
   - **Button Widgets** for controlling devices (like light, fan, etc.) mapped to virtual pins for relay control.

### 4. Hardware Setup

- Connect the **Relay Modules** to the Arduino pins (8, 9, 10, 11).
- Connect the **PIR Motion Sensor** to pin 7 of the Arduino.
- Connect the **DHT11/DHT22** sensor to pin 6 of the Arduino.
- Connect the **ESP8266/ESP32** to the Arduino for Wi-Fi communication, or alternatively, use the **HC-05** for Bluetooth control.

## Code

Here is the Arduino code for controlling devices with motion detection and sensor input:

```cpp
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Wi-Fi credentials
char auth[] = "YourBlynkAuthToken";  // Blynk Auth Token
char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

// Pin definitions
#define RELAY_PIN_1 8
#define RELAY_PIN_2 9
#define RELAY_PIN_3 10
#define RELAY_PIN_4 11
#define PIR_SENSOR_PIN 7
#define DHT_PIN 6

DHT dht(DHT_PIN, DHT11);  // DHT11 sensor
BlynkTimer timer;

void setup() {
  // Serial monitor setup
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass);

  // Pin setup
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(RELAY_PIN_3, OUTPUT);
  pinMode(RELAY_PIN_4, OUTPUT);
  pinMode(PIR_SENSOR_PIN, INPUT);
  
  // Initialize DHT sensor
  dht.begin();

  // Set up a timer to send sensor data to the Blynk app
  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
  controlDevicesBasedOnMotion();
}

// Function to send temperature and humidity data to the app
void sendSensorData() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Send data to the Blynk app
  Blynk.virtualWrite(V1, temp);     // Virtual pin V1 for temperature
  Blynk.virtualWrite(V2, humidity); // Virtual pin V2 for humidity
}

// Function to control devices based on motion
void controlDevicesBasedOnMotion() {
  int motionDetected = digitalRead(PIR_SENSOR_PIN);
  if (motionDetected == HIGH) {
    // Turn on devices
    digitalWrite(RELAY_PIN_1, HIGH);  // Turn on light
    digitalWrite(RELAY_PIN_2, HIGH);  // Turn on fan
  } else {
    // Turn off devices
    digitalWrite(RELAY_PIN_1, LOW);   // Turn off light
    digitalWrite(RELAY_PIN_2, LOW);   // Turn off fan
  }
}

## Image 
![Image](/Images/image.png)
