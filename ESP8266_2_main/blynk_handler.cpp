#include "blynk_handler.h"
#include "config.h"
#include <BlynkSimpleEsp8266.h>
#include "mqtt_handler.h" // Goi ham publish cua MQTT

void setupBlynk() {
  // Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
  // Co the them Blynk.config(...) de ket noi non-blocking
}

void blynkLoop() {
  Blynk.run();
}

// --- Ham GUI DU LIEU LEN BLYNK (goi tu main.ino) ---
void updateBlynkTemperature(float temp) {
  Blynk.virtualWrite(VPIN_TEMP_DISPLAY, temp);
}

void updateBlynkDoorState(String state) {
  Blynk.virtualWrite(VPIN_DOOR_STATUS, state);
  if (state == "OPEN") {
    // Gui email thong bao
    Blynk.email("your_email@gmail.com", "CANH BAO", "Cua nha da mo!");
    Blynk.virtualWrite(VPIN_EMAIL_NOTIFY); // Kich hoat widget thong bao
  }
}

// --- Ham NHAN DU LIEU TU BLYNK (xu ly qua MQTT) ---

// Button dieu khien quat
BLYNK_WRITE(VPIN_FAN_BUTTON) {
  int state = param.asInt(); // 1 = ON, 0 = OFF
  if (state == 1) {
    mqttPublishFanControl("ON");
  } else {
    mqttPublishFanControl("OFF");
  }
}

// Button dieu khien den
BLYNK_WRITE(VPIN_LIGHT_BUTTON) {
  int state = param.asInt();
  if (state == 1) {
    mqttPublishLightControl("ON");
  } else {
    mqttPublishLightControl("OFF");
  }
}

// Slider chinh nguong nhiet
BLYNK_WRITE(VPIN_TEMP_SLIDER) {
  String threshold = param.asString();
  mqttPublishTempThreshold(threshold);
}

// Chinh gio bao thuc
BLYNK_WRITE(VPIN_ALARM_INPUT) {
  // Xu ly thoi gian tu Blynk (co the can format lai)
  // ...
  String formattedTime = "..."; // Vi du: "07:30"
  mqttPublishAlarmTime(formattedTime);
}