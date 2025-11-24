#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <DHT.h>
#include "config.h"

// Khởi tạo cảm biến
void initSensors();

// Đọc nhiệt độ (trả về độ C)
float getTemperature();

// Kiểm tra có người không (trả về true/false)
bool isPersonDetected();

#endif
