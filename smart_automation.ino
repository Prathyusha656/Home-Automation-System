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
