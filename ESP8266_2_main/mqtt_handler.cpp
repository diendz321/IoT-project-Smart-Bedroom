#include "mqtt_handler.h"
#include "config.h" // Chua thong tin WiFi, MQTT Broker, va Topics
#include <ESP8266WiFi.h>

// --- Khai bao bien toan cuc ---
// Khai bao mot bien WiFiClient
// Khai bao mot bien PubSubClient ten la 'client'
// Khai bao mot bien de luu tru ham callback tu main (globalCallback)


/**
 * @brief Ham callback noi bo, duoc goi boi thu vien PubSubClient.
 */
void internalCallback(char* topic, byte* payload, unsigned int length) {
  // Kiem tra xem 'globalCallback' co ton tai (khac NULL) khong
  // Neu co, goi 'globalCallback' va truyen cac tham so vao
}

/**
 * @brief Ket noi lai MQTT neu bi mat ket noi.
 */
void reconnect() {
  // Viet vong lap while (!client.connected()) de lien tuc thu lai
  // Ben trong vong lap:
    // In ra thong bao dang co gang ket noi MQTT...
    
    // Thu ket noi: if (client.connect(MQTT_CLIENT_ID))
    // Neu ket noi thanh cong:
      // In ra thong bao "da ket noi!"
      // (Quan trong) SUBSCRIBE (dang ky) cac topic du lieu tu ESP1:
      // client.subscribe(TOPIC_PUB_TEMPERATURE);
      // client.subscribe(TOPIC_PUB_DOOR_STATE);
      
    // Neu ket noi that bai (else):
      // In ra trang thai loi (client.state())
      // Doi 5 giay (delay(5000)) truoc khi thu lai
}

/**
 * @brief Khoi tao WiFi va MQTT Client.
 */
void setupMQTT(MqttCallback callback) {
  // Luu ham 'callback' vao bien 'globalCallback'
  
  // Viet code ket noi WiFi
  // In ra thong bao "Dang ket noi toi [TEN_WIFI]"
  // Goi WiFi.begin(WIFI_SSID, WIFI_PASS);
  // Viet vong lap while (WiFi.status() != WL_CONNECTED) de cho
    // delay(500);
    // In ra dau "."
  
  // In ra thong bao WiFi da ket noi va dia chi IP (WiFi.localIP())

  // Thiet lap MQTT
  // client.setServer(MQTT_BROKER, MQTT_PORT);
  // client.setCallback(internalCallback); // Su dung ham callback noi bo
}

/**
 * @brief Ham duy tri ket noi MQTT.
 */
void mqttLoop() {
  // Kiem tra neu client chua ket noi (!client.connected())
  // Neu dung, goi ham reconnect()
  
  // Luon luon goi client.loop() de duy tri ket noi va xu ly tin nhan
}

/**
 * @brief Kiem tra trang thai ket noi MQTT.
 */
bool mqttIsConnected() {
  // return client.connected();
  return false; // placeholder
}

// --- Dinh nghia cac ham Publish (ma Blynk se goi) ---

void mqttPublishFanControl(String state) {
  // Kiem tra if (mqttIsConnected())
  // Neu co, publish: client.publish(TOPIC_SUB_FAN_CONTROL, state.c_str());
}

void mqttPublishLightControl(String state) {
  // Kiem tra if (mqttIsConnected())
  // Neu co, publish: client.publish(TOPIC_SUB_LIGHT_CONTROL, state.c_str());
}

void mqttPublishTempThreshold(String threshold) {
  // Kiem tra if (mqttIsConnected())
  // Neu co, publish: client.publish(TOPIC_SUB_TEMP_THRESHOLD, threshold.c_str());
}

void mqttPublishAlarmTime(String time) {
  // Kiem tra if (mqttIsConnected())
  // Neu co, publish: client.publish(TOPIC_SUB_ALARM_TIME, time.c_str());
}