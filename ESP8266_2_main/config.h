#pragma once

// --- Cau hinh WiFi & MQTT ---
#define WIFI_SSID "TEN_WIFI_CUA_BAN"
#define WIFI_PASS "MAT_KHAU_WIFI"
#define MQTT_BROKER "DIA_CHI_IP_CUA_BROKER" // Phai giong ESP1
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "ESP8266_2_Bridge"

// --- Cau hinh Blynk ---
#define BLYNK_AUTH_TOKEN "TOKEN_BLYNK_CUA_BAN"
#define BLYNK_TEMPLATE_ID "..."
#define BLYNK_TEMPLATE_NAME "..."

// --- Dinh nghia MQTT Topics (PHAI GIONG HET ESP1) ---
#define TOPIC_PUB_TEMPERATURE "smartroom/temperature"
#define TOPIC_PUB_DOOR_STATE "smartroom/door/state"
#define TOPIC_SUB_FAN_CONTROL "smartroom/control/fan"
#define TOPIC_SUB_LIGHT_CONTROL "smartroom/control/light"
#define TOPIC_SUB_TEMP_THRESHOLD "smartroom/config/temp_threshold"
#define TOPIC_SUB_ALARM_TIME "smartroom/config/alarm_time"

// --- Dinh nghia cac Virtual Pin (V-Pin) cua Blynk ---
#define VPIN_TEMP_DISPLAY ...     // Widget hien thi nhiet do
#define VPIN_DOOR_STATUS ...    // Widget hien thi trang thai cua
#define VPIN_FAN_BUTTON ...     // Button tat/bat quat
#define VPIN_LIGHT_BUTTON ...   // Button tat/bat den
#define VPIN_TEMP_SLIDER ...    // Slider chinh nguong nhiet
#define VPIN_ALARM_INPUT ...    // Time Input de hen gio
#define VPIN_EMAIL_NOTIFY ...   // Widget Email