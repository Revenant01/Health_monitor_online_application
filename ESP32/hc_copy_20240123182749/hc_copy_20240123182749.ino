// Libraries
#include "BluetoothSerial.h"
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/RTDBHelper.h"
#include "addons/tokenhelper.h"

// Defined variables
FirebaseData fbdo;            // Firebase data object
FirebaseAuth auth;             // Firebase authentication object
FirebaseConfig config;         // Firebase configuration object
BluetoothSerial SerialBT;      // Bluetooth serial object
uint8_t  MAC[] = {0x00, 0x22, 0x04, 0x00, 0x5e, 0x0d};  // MAC address for Bluetooth device

// Bluetooth Configurations
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

// Firebase Configurations
#define WIFI_SSID "Khalid"
#define WIFI_PASSWORD "135791113"
#define DATABASE_SECRET "AIzaSyB33bbm94wGqyZaVjF0FYcxOS_otsXuCuA"
#define API_KEY "AIzaSyB33bbm94wGqyZaVjF0FYcxOS_otsXuCuA"
#define DATABASE_URL "https://embedded-daafd-default-rtdb.europe-west1.firebasedatabase.app/" 

// Setup function
void setup() {
  // Bluetooth initializations
  Serial.begin(9600);
  SerialBT.begin(9600);
  SerialBT.begin("ESP32"); // Set Bluetooth device name

  // WiFi Initializations
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Firebase initializations
  config.database_url = DATABASE_URL;
  config.api_key = API_KEY;
  config.signer.tokens.legacy_token=DATABASE_SECRET;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

// Loop function
void loop() {
  // Check if data is available on Bluetooth
  if (SerialBT.available()) {
    // Check if there is enough data (assuming each value is one byte)
    if (SerialBT.available() >= 2) {
      // Read HeartRate and Temperature from Bluetooth
      int heartRate = SerialBT.read();
      float temperature = SerialBT.read();

      // Firebase paths for HeartRate and Temperature
      String heartRatePath = "/INFO/HeartRate";
      String temperaturePath = "/INFO/Temperature";

      // Print data to serial monitor
      Serial.println("HeartRate:" + String(heartRate));
      Serial.println("Temperature:" + String(temperature));

      // Upload data to Firebase Realtime Database
      Firebase.RTDB.setString(&fbdo, heartRatePath.c_str(), String(heartRate));
      Firebase.RTDB.setString(&fbdo, temperaturePath.c_str(), String(temperature)); 
    }
  }
  delay(500);  // Delay for stability
}
