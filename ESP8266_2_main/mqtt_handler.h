#pragma once
#include <Arduino.h>
#include <PubSubClient.h> // Bao gom thu vien MQTT

// Dinh nghia ham callback se duoc goi o main.ino
typedef void (*MqttCallback)(char* topic, byte* payload, unsigned int length);

/**
 * @brief Khoi tao WiFi va MQTT Client.
 * @param callback Ham se duoc goi khi co tin nhan MQTT den (tu main.ino).
 */
void setupMQTT(MqttCallback callback);

/**
 * @brief Ham duy tri ket noi MQTT, phai duoc goi trong loop().
 */
void mqttLoop();

/**
 * @brief Kiem tra trang thai ket noi MQTT.
 * @return true neu dang ket noi, false neu mat ket noi.
 */
bool mqttIsConnected();

// --- Cac ham Publish du lieu (ma Blynk se goi) ---

/**
 * @brief Publish lenh dieu khien quat ("ON" hoac "OFF").
 */
void mqttPublishFanControl(String state);

/**
 * @brief Publish lenh dieu khien den ("ON" hoac "OFF").
 */
void mqttPublishLightControl(String state);

/**
 * @brief Publish nguong nhiet do moi.
 */
void mqttPublishTempThreshold(String threshold);

/**
 * @brief Publish thoi gian bao thuc moi.
 */
void mqttPublishAlarmTime(String time);