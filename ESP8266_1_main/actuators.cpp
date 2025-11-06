#include "actuators.h"
#include "config.h"
// Them cac thu vien lien quan (vi du: Servo.h)

void setupActuators() {
  // Viet code de khoi tao (setup) tung co cau chap hanh
  // Vi du: pinMode(PIN_FAN, OUTPUT);
  // Khoi tao servo
}

void controlFan(bool isOn) {
  // Viet code de bat/tat quat
  // digitalWrite(PIN_FAN, isOn ? HIGH : LOW);
}

// ... Viet cac ham tuong tu cho controlLight(), controlNightLight(), controlBuzzer() ...

void controlServo(bool isOpen) {
  // Viet code de dieu khien servo mo cua (vi du: 90 do) hoac dong cua (0 do)
  // Neu isOpen == true -> servo.write(90);
  // else -> servo.write(0);
}