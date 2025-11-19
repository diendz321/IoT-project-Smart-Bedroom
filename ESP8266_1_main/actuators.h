#pragma once
// Khai bao cac ham de dieu khien co cau chap hanh
void setupActuators();
void controlFan(bool isOn);
void controlLight(bool isOn);
void controlNightLight(bool isOn);
void controlServo(bool isOpen);
void controlBuzzer(bool isOn);

// --- THÊM VÀO actuators.h ---
void initNightLight();          // Cài đặt mode cho chân đèn
void controlNightLight(bool state); // Hàm bật tắt (true=Bật, false=Tắt)