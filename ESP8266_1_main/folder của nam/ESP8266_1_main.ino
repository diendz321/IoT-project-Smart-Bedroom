#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include "sensors.h"
#include "actuators.h"

// --- Biến toàn cục quản lý trạng thái ---
WiFiClient espClient;
PubSubClient client(espClient);

int blynkMode = 0;          // 0: Auto, 1-3: Manual levels
float tempThreshold = 30.0; // Ngưỡng nhiệt mặc định
float currentTemp = 0.0;
bool hasPerson = false;

unsigned long lastMsgTime = 0;

// --- Hàm kết nối Wifi ---
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

// --- Hàm nhận dữ liệu MQTT (Callback) ---
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Message received ["); Serial.print(topic); Serial.print("]: "); Serial.println(message);

  // 1. Nhận lệnh điều khiển quạt từ Blynk
  if (String(topic) == TOPIC_FAN_CONTROL) {
    blynkMode = message.toInt(); // 0, 1, 2, 3
    processFanLogic(); // Cập nhật quạt ngay lập tức
  }
  // 2. Nhận ngưỡng nhiệt độ mới
  else if (String(topic) == TOPIC_TEMP_THRESH) {
    tempThreshold = message.toFloat();
  }
}

// --- Hàm kết nối lại MQTT ---
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266_Node1_Sensor")) {
      Serial.println("connected");
      // Đăng ký nhận tin nhắn
      client.subscribe(TOPIC_FAN_CONTROL);
      client.subscribe(TOPIC_TEMP_THRESH);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// --- LOGIC TRUNG TÂM: Xử lý Tự động vs Thủ công ---
void processFanLogic() {
  // TH1: Chế độ THỦ CÔNG (Người dùng chọn 1, 2, 3)
  if (blynkMode > 0) {
    Serial.print("Manual Mode: Level "); Serial.println(blynkMode);
    setFanSpeed(blynkMode);
  }
  // TH2: Chế độ TỰ ĐỘNG (Người dùng chọn 0)
  else {
    Serial.print("Auto Mode: ");
    // Logic: Nhiệt > Ngưỡng VÀ Có người -> Bật mức trung bình (2)
    if (currentTemp > tempThreshold && hasPerson) {
      Serial.println("ON (Temp High & Person detected)");
      setFanSpeed(2); // Auto chạy mức Medium
    } else {
      Serial.println("OFF");
      setFanSpeed(0);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  // Khởi tạo các module con
  initSensors();
  initActuators();
  
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Đọc cảm biến định kỳ (2 giây / lần)
  unsigned long now = millis();
  if (now - lastMsgTime > 2000) {
    lastMsgTime = now;

    // 1. Đọc cảm biến
    float t = getTemperature();
    if (t != -1.0) currentTemp = t;
    hasPerson = isPersonDetected();

    // 2. Gửi dữ liệu lên MQTT (để Node 2 hiển thị)
    client.publish(TOPIC_PUB_TEMP, String(currentTemp).c_str());
    client.publish(TOPIC_PUB_MOTION, hasPerson ? "1" : "0");
    
    // 3. Chạy logic điều khiển quạt
    processFanLogic();
  }
}
