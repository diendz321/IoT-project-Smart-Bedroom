#include "actuators.h"

void initActuators() {
  pinMode(PIN_FAN, OUTPUT);
  // Đảm bảo quạt tắt khi khởi động
  analogWrite(PIN_FAN, 0);
}

void setFanSpeed(int level) {
  int pwmValue = 0;
  
  switch (level) {
    case 0: // OFF
      pwmValue = 0;
      break;
    case 1: // LOW
      pwmValue = 400; // Cần test thực tế để quạt quay được
      break;
    case 2: // MEDIUM
      pwmValue = 700;
      break;
    case 3: // HIGH
      pwmValue = 1023; // Max tốc độ (10bit)
      break;
    default:
      pwmValue = 0;
      break;
  }
  
  // Xuất xung PWM ra chân quạt
  analogWrite(PIN_FAN, pwmValue);
}
