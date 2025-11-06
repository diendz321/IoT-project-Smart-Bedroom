#pragma once
#include <PubSubClient.h>

// Dinh nghia ham callback se duoc goi o main.ino
// Day la cach de file .ino xu ly logic khi co tin nhan MQTT den
typedef void (*MqttCallback)(char* topic, byte* payload, unsigned int length);

void setupMQTT(MqttCallback callback); // Truyen ham callback tu main.ino vao day
void mqttLoop();
bool mqttIsConnected();
void mqttPublish(const char* topic, const char* payload);