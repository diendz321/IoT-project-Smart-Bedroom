#include "config.h"
#include "mqtt_handler.h"
#include "blynk_handler.h"
#include <ESP8266WiFi.h>

// --- Ham Callback cho MQTT ---
void onMqttMessage(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // ESP2 chi nghe 2 topic nay tu ESP1
  if (strcmp(topic, TOPIC_PUB_TEMPERATURE) == 0) {
    updateBlynkTemperature(message.toFloat()); // Day len Blynk
  }

  if (strcmp(topic, TOPIC_PUB_DOOR_STATE) == 0) {
    updateBlynkDoorState(message); // Day len Blynk
  }
}

void setup() {
  Serial.begin(115200);
  
  // Ket noi WiFi (co the dat trong setupMQTT hoac de o day)
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  setupMQTT(onMqttMessage); // Bat dau MQTT
  setupBlynk(); // Bat dau Blynk
}

void loop() {
  mqttLoop(); // Luon goi
  blynkLoop(); // Luon goi
}