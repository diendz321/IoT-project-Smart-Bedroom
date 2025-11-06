// Import tat ca cac file .h
#include "config.h"
#include "sensors.h"
#include "actuators.h"
#include "rfid.h"
#include "oled_display.h"
#include "mqtt_handler.h"
// Them thu vien thoi gian (NTPClient.h) de lay gio

// --- Bien toan cuc (Global Variables) ---
float currentTemperature = 0;
bool isPresence = false;
int currentLightLevel = 0;
String currentTime = "00:00:00";

// Cac bien cau hinh tu MQTT
float tempThreshold = 28.0; // Gia tri mac dinh
String alarmTime = "07:00"; // Gia tri mac dinh
bool manualFanOff = false;  // Bien co de Blynk co the tat
bool manualLightOff = false;

// --- Ham Callback cho MQTT ---
void onMqttMessage(char* topic, byte* payload, unsigned int length) {
  // Chuyen payload thanh String
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Kiem tra topic den
  if (strcmp(topic, TOPIC_SUB_FAN_CONTROL) == 0) {
    if (message == "OFF") {
      controlFan(false);
      manualFanOff = true; // Nguoi dung da ep tat
    } else if (message == "ON") {
      controlFan(true);
      manualFanOff = false; // Huy ep tat
    }
  }
  
  if (strcmp(topic, TOPIC_SUB_LIGHT_CONTROL) == 0) {
    if (message == "OFF") {
      controlLight(false);
      manualLightOff = true;
    } else if (message == "ON") {
      controlLight(true);
      manualLightOff = false;
    }
  }

  if (strcmp(topic, TOPIC_SUB_TEMP_THRESHOLD) == 0) {
    tempThreshold = message.toFloat(); // Cap nhat nguong nhiet
  }

  if (strcmp(topic, TOPIC_SUB_ALARM_TIME) == 0) {
    alarmTime = message; // Cap nhat gio bao thuc
  }
}

// --- Setup ---
void setup() {
  Serial.begin(115200);
  setupSensors();
  setupActuators();
  setupRFID();
  setupOLED();
  setupMQTT(onMqttMessage); // Truyen ham callback vao
  
  // Khoi tao NTP de lay thoi gian
}

// --- Loop ---
void loop() {
  // 1. Duy tri ket noi
  mqttLoop();
  
  // 2. Doc cam bien (dinh ky ngan)
  currentTemperature = readTemperature();
  isPresence = detectPresence();
  currentLightLevel = readLightLevel();
  // Lay thoi gian hien tai tu NTP
  // currentTime = ...
  
  // 3. Kiem tra RFID (logic doc lap)
  if (checkAndProcessRFID()) {
    // Neu RFID hop le
    controlServo(true);
    mqttPublish(TOPIC_PUB_DOOR_STATE, "OPEN");
    delay(5000); // Giu cua mo 5 giay
    controlServo(false);
    mqttPublish(TOPIC_PUB_DOOR_STATE, "CLOSED");
  }

  // 4. Logic tu dong hoa (Automation Logic)
  
  // Logic Quat:
  if (isPresence && currentTemperature > tempThreshold && !manualFanOff) {
    controlFan(true);
  } else if (!isPresence || manualFanOff) {
    controlFan(false);
    if (!isPresence) manualFanOff = false; // Reset co neu khong co nguoi
  }

  // Logic Den:
  bool isDark = currentLightLevel < 400; // Gia su nguong toi la 400
  if (isPresence && isDark && !manualLightOff) {
    controlLight(true);
    controlNightLight(false); // Tat den ngu khi den chinh bat
  } else if (isPresence && !isDark && !manualLightOff) {
    // Co nguoi nhung troi sang -> tat den
    controlLight(false);
  } else if (!isPresence || manualLightOff) {
    controlLight(false);
    if (!isPresence) manualLightOff = false; // Reset co
  }
  
  // Logic Den ngu:
  if (isPresence && !controlLight.isOn() && manualLightOff) { // Neu co nguoi VA den chinh bi 'ep tat'
     controlNightLight(true);
  } else {
     controlNightLight(false); 
  }

  // Logic Bao thuc:
  // So sanh 'currentTime' voi 'alarmTime'
  // if (currentTime.startsWith(alarmTime)) {
  //   controlBuzzer(true);
  // } else {
  //   controlBuzzer(false);
  // }

  // 5. Cap nhat (dinh ky dai hon, vi du 5 giay 1 lan)
  static unsigned long lastUpdateTime = 0;
  if (millis() - lastUpdateTime > 5000) {
    lastUpdateTime = millis();
    
    // Cap nhat OLED
    updateOLED(currentTemperature, currentTime);
    
    // Publish len MQTT
    char tempPayload[10];
    dtostrf(currentTemperature, 4, 2, tempPayload); // Chuyen float thanh string
    mqttPublish(TOPIC_PUB_TEMPERATURE, tempPayload);
  }
}