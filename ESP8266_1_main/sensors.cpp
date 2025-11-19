#include "sensors.h"
#include "config.h"
// Them cac thu vien lien quan (vi du: DHT.h, NewPing.h)

void setupSensors() {
  // Viet code de khoi tao (setup) tung cam bien
  // Vi du: pinMode(PIN_PHOTORESISTOR, INPUT);
}

float readTemperature() {
  // Viet code de doc tu cam bien nhiet do (vi du: DHT22)
  // return ...;
}

bool detectPresence() {
  // Viet code de doc tu cam bien sonar (vi du: NewPing)
  // Neu khoang cach < mot nguong nao do -> return true;
  // return false;
}

int readLightLevel() {
  // Viet code de doc tu quang tro
  // return analogRead(PIN_PHOTORESISTOR);
}

// --- THÊM VÀO CUỐI sensors.cpp ---

// Đọc giá trị thô từ quang trở (0 - 1023)
int getLightLevel() {
  return analogRead(LDR_PIN); 
}

// Trả về true nếu trời tối, false nếu trời sáng
bool isRoomDark() {
  int lightVal = getLightLevel();
  // Nếu giá trị đọc được nhỏ hơn ngưỡng -> Tối (Tùy mạch phân áp của bạn)
  return (lightVal < LDR_THRESHOLD); 
}