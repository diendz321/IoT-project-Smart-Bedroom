#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <Arduino.h>
#include "config.h"

// Khởi tạo chân điều khiển quạt
void initActuators();

// Hàm điều khiển tốc độ quạt dựa trên mức từ Blynk (0, 1, 2, 3)
// level: 0=Off, 1=Low, 2=Medium, 3=High
void setFanSpeed(int level);

#endif
