#include "mqtt_handler.h"
#include "config.h"
#include <ESP8266WiFi.h>

// Khai bao WiFiClient va PubSubClient
// Khai bao ham callback
MqttCallback globalCallback;

void setupMQTT(MqttCallback callback) {
  globalCallback = callback;
  // Viet code ket noi WiFi
  // Thiet lap MQTT server, port va ham callback cho PubSubClient
  // client.setServer(MQTT_BROKER, MQTT_PORT);
  // client.setCallback(globalCallback);
}

void reconnect() {
  // Viet code de ket noi lai MQTT neu bi mat ket noi
  // Khi ket noi lai, dang ky (subscribe) cac topic
  // client.subscribe(TOPIC_SUB_FAN_CONTROL);
  // client.subscribe(TOPIC_SUB_LIGHT_CONTROL);
  // client.subscribe(TOPIC_SUB_TEMP_THRESHOLD);
  // client.subscribe(TOPIC_SUB_ALARM_TIME);
}

void mqttLoop() {
  // Kiem tra ket noi, neu mat thi goi reconnect()
  // Goi client.loop() de duy tri
}

bool mqttIsConnected() {
  // return client.connected();
  return false; // placeholder
}

void mqttPublish(const char* topic, const char* payload) {
  // if (mqttIsConnected()) {
  //   client.publish(topic, payload);
  // }
}