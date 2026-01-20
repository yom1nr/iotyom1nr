#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 5
#define DATA_PIN 23
#define CLK_PIN 18

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// รูปลูกศรชี้ขึ้น
uint8_t arrowUp[8] = {
  0b00001000,
  0b00011100,
  0b00111110,
  0b01111111,
  0b00011100,
  0b00011100,
  0b00011100,
  0b00011100
};

int offset = 8;  // เริ่มจากด้านล่าง

void setup() {
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 5);
  mx.clear();
}

void loop() {
  mx.clear();

  // วาดลูกศรโดยเลื่อนขึ้น
  for (int i = 0; i < 8; i++) {
    int row = i + offset;
    if (row >= 0 && row < 8) {
      mx.setRow(0, row, arrowUp[i]);
    }
  }

  offset--;           // เลื่อนขึ้น
  if (offset < -8) {  // หลุดจอแล้ว เริ่มใหม่
    offset = 8;
  }

  delay(150);  // ความเร็วลูกศร
}
