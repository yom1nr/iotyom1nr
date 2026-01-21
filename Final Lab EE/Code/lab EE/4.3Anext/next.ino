#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES 1

#define DATA_PIN 23   // MOSI
#define CLK_PIN  18   // SCK
#define CS_PIN   5    // SS

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// ================= Arrow Bitmap =================
// ลูกศรชี้ขึ้น 8x8 (นิ่ง)
const uint8_t arrowUp[8] = {
  0x18, //   ██
  0x3C, //  ████
  0x7E, // ██████
  0xFF, // ████████
  0x18, //   ██
  0x18, //   ██
  0x18, //   ██
  0x18  //   ██
};

void setup()
{
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 5);   // ความสว่าง 0–15
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();

  // แสดงลูกศรนิ่ง
  for (uint8_t col = 0; col < 8; col++)
  {
    mx.setColumn(col, arrowUp[col]);
  }
}

void loop()
{
  // ไม่ต้องทำอะไร → รูปค้างนิ่ง
}