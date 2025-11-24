
#ifndef CONFIG_H
#define CONFIG_H

// --- 1. Cấu hình Wifi & MQTT ---
#define WIFI_SSID       "TEN_WIFI_CUA_BAN"
#define WIFI_PASS       "MAT_KHAU_WIFI"
#define MQTT_SERVER     "192.168.1.xxx"  // IP của Broker
#define MQTT_PORT       1883

// --- 2. Định nghĩa Chân (Pin Mapping) ---
// Lưu ý: D1, D2 dành cho OLED (I2C) nên tránh dùng
#define PIN_DHT         D4      // Cảm biến nhiệt độ
#define PIN_FAN         D5      // Chân PWM điều khiển quạt (L298N/Mosfet)
#define PIN_PIR         D6      // Cảm biến người (PIR/Sonar)

// --- 3. Loại cảm biến ---
#define DHT_TYPE        DHT11   // Đổi thành DHT22 nếu dùng loại màu trắng

// --- 4. MQTT Topics (Các chủ đề để giao tiếp) ---
#define TOPIC_FAN_CONTROL   "home/fan/control"    // Nhận lệnh 0-3 từ Blynk
#define TOPIC_TEMP_THRESH   "home/temp/threshold" // Nhận ngưỡng nhiệt độ
#define TOPIC_PUB_TEMP      "home/sensor/temp"    // Gửi nhiệt độ lên
#define TOPIC_PUB_MOTION    "home/sensor/motion"  // Gửi trạng thái người lên

#endif
