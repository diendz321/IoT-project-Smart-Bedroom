#pragma once
// Khai bao cac ham de doc du lieu tu cam bien
void setupSensors();
float readTemperature();
bool detectPresence(); // Tra ve true neu co nguoi
int readLightLevel();   // Tra ve muc do sang

// --- THÊM VÀO sensors.h ---
int getLightLevel(); // Hàm đọc giá trị analog
bool isRoomDark();   // Hàm kiểm tra xem phòng có tối không