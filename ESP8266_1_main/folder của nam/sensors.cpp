#include "sensors.h"

// Khởi tạo đối tượng DHT
DHT dht(PIN_DHT, DHT_TYPE);

void initSensors() {
  pinMode(PIN_PIR, INPUT);
  dht.begin();
}

float getTemperature() {
  float t = dht.readTemperature();
  // Kiểm tra nếu đọc lỗi thì trả về giá trị cũ hoặc -1
  if (isnan(t)) {
    return -1.0; 
  }
  return t;
}

bool isPersonDetected() {
  // Giả sử cảm biến PIR/Sonar trả về HIGH khi có người
  return digitalRead(PIN_PIR) == HIGH;
}
