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