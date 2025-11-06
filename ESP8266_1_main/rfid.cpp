#include "rfid.h"
#include "config.h"
// Them thu vien MFRC522.h

// Dinh nghia UID hop le
byte validUID[4] = {0xDE, 0xAD, 0xBE, 0xEF}; // Thay bang UID cua ban

void setupRFID() {
  // Viet code setup module MFRC522
}

bool checkAndProcessRFID() {
  // Kiem tra xem co the moi khong?
  // Neu co:
  //   Doc UID cua the
  //   So sanh voi 'validUID'
  //   Neu trung khop (hop le) -> return true
  // Luon tra ve false neu khong co the hoac the khong hop le
  return false;
}