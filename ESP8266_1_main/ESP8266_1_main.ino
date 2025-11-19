#include "config.h"
#include "sensors.h"
#include "actuators.h"
#include "rfid.h"
#include "oled_display.h"
#include "mqtt_handler.h"
// #include <NTPClient.h> // Bỏ comment nếu đã cài thư viện và cấu hình

// --- CẤU HÌNH NGƯỠNG (THRESHOLDS) ---
const int LIGHT_THRESHOLD = 400; // Dưới mức này là TỐI (Quang trở)

// --- BIẾN TOÀN CỤC (GLOBAL VARIABLES) ---
float currentTemperature = 0;
bool isPresence = false;
int currentLightLevel = 0;
String currentTime = "00:00"; // Định dạng giờ phút

// Các biến cấu hình từ MQTT/App
float tempThreshold = 28.0; 
String alarmTime = "07:00"; 
bool manualFanOff = false;   
bool manualLightOff = false;

// --- HÀM CALLBACK MQTT ---
void onMqttMessage(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Điều khiển Quạt
  if (strcmp(topic, TOPIC_SUB_FAN_CONTROL) == 0) {
    if (message == "OFF") {
      controlFan(false);
      manualFanOff = true;
    } else if (message == "ON") {
      controlFan(true);
      manualFanOff = false;
    }
  }
  
  // Điều khiển Đèn Chính (Của Nam/Hoàng)
  if (strcmp(topic, TOPIC_SUB_LIGHT_CONTROL) == 0) {
    if (message == "OFF") {
      controlLight(false);
      manualLightOff = true;
    } else if (message == "ON") {
      controlLight(true);
      manualLightOff = false;
    }
  }

  // Cập nhật ngưỡng nhiệt độ
  if (strcmp(topic, TOPIC_SUB_TEMP_THRESHOLD) == 0) {
    tempThreshold = message.toFloat();
  }

  // Cập nhật giờ báo thức
  if (strcmp(topic, TOPIC_SUB_ALARM_TIME) == 0) {
    alarmTime = message;
  }
}

// --- SETUP ---
void setup() {
  Serial.begin(115200);
  
  // Khởi tạo các module
  setupSensors();   // Bao gồm cả LDR của Huy
  setupActuators(); // Bao gồm cả Đèn ngủ của Huy (initNightLight)
  setupRFID();
  setupOLED();
  
  // Khởi tạo đèn ngủ (Hàm riêng của Huy trong actuators.cpp)
  initNightLight(); 

  setupMQTT(onMqttMessage);
  
  // setupNTP(); // Nếu có dùng NTP
}

// --- LOOP ---
void loop() {
  // 1. Duy trì kết nối
  mqttLoop();
  
  // 2. Đọc cảm biến
  currentTemperature = readTemperature();
  isPresence = detectPresence();
  currentLightLevel = readLightLevel(); // Hàm đọc LDR của Huy
  
  // Giả lập lấy giờ (hoặc dùng NTP thực tế)
  // currentTime = getNTPTime(); 

  // 3. Xử lý RFID (Mở cửa)
  if (checkAndProcessRFID()) {
    controlServo(true); // Mở cửa
    mqttPublish(TOPIC_PUB_DOOR_STATE, "OPEN");
    delay(5000); 
    controlServo(false); // Đóng cửa
    mqttPublish(TOPIC_PUB_DOOR_STATE, "CLOSED");
  }

  // 4. LOGIC TỰ ĐỘNG HÓA (AUTOMATION)

  // --- A. Logic Quạt (Nam) ---
  // Có người + Nóng + Không bị ép tắt -> Bật
  if (isPresence && currentTemperature > tempThreshold && !manualFanOff) {
    controlFan(true);
  } else if (!isPresence || manualFanOff) {
    controlFan(false);
    if (!isPresence) manualFanOff = false; // Reset trạng thái khi người đi vắng
  }

  // --- B. Logic Đèn Chính (Hoàng) ---
  // Xác định trời tối hay sáng
  bool isDark = (currentLightLevel < LIGHT_THRESHOLD); 

  // Có người + Trời tối + Không bị ép tắt -> Bật đèn chính
  // Lưu ý: Khi đèn chính bật, phòng sẽ sáng lên -> isDark sẽ thành false ở vòng lặp sau.
  // Để tránh đèn nhấp nháy, ta thường chỉ bật đèn chính khi ánh sáng tự nhiên thấp.
  // Tuy nhiên, với logic đơn giản, ta ưu tiên biến manualLightOff.
  if (isPresence && isDark && !manualLightOff) {
     controlLight(true);
  } else if (!isPresence || manualLightOff) {
     controlLight(false);
     if (!isPresence) manualLightOff = false;
  }
  
  // --- C. Logic Đèn Ngủ (Của Huy) ---
  // Yêu cầu: Bật khi phòng tắt đèn (tối) VÀ có người bên trong.
  // Logic thực tế: Khi Đèn Chính Tắt (do người dùng tắt đi ngủ hoặc không bật) 
  // thì LDR sẽ thấy TỐI. Lúc đó nếu vẫn có người -> Bật đèn ngủ.
  
  // Cập nhật lại isDark sau khi logic đèn chính chạy (vì đèn chính có thể vừa bật/tắt)
  // Nhưng tốt nhất cứ dựa vào cảm biến thực tế:
  
  if (isPresence && (currentLightLevel < LIGHT_THRESHOLD)) {
    // Có người VÀ Cảm biến thấy tối (nghĩa là đèn chính đang tắt)
    controlNightLight(true);
  } else {
    // Không có người HOẶC Phòng đang sáng (đèn chính đang bật hoặc trời sáng)
    controlNightLight(false);
  }

  // --- D. Logic Báo Thức ---
  /*
  if (currentTime == alarmTime) {
     controlBuzzer(true);
  } else {
     controlBuzzer(false);
  }
  */

  // 5. Cập nhật hiển thị & Gửi dữ liệu (mỗi 2 giây)
  static unsigned long lastUpdateTime = 0;
  if (millis() - lastUpdateTime > 2000) {
    lastUpdateTime = millis();
    
    // Update OLED
    updateOLED(currentTemperature, currentTime);
    
    // Gửi nhiệt độ lên MQTT
    char tempPayload[10];
    dtostrf(currentTemperature, 4, 2, tempPayload);
    mqttPublish(TOPIC_PUB_TEMPERATURE, tempPayload);

    // Gửi trạng thái ánh sáng (để debug xem ngưỡng bao nhiêu là vừa)
    char lightPayload[10];
    itoa(currentLightLevel, lightPayload, 10);
    mqttPublish("home/sensors/light", lightPayload);
  }
}