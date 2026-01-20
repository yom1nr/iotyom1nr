#include <TM1638plus.h>

// กำหนดขาพินตามที่คุณต่อ
#define STB_PIN 21
#define CLK_PIN 19
#define DIO_PIN 18

// แก้ไขจุดนี้: เพิ่มพารามิเตอร์ตัวที่ 4 เป็น true เพื่อรองรับความเร็วของ ESP32
TM1638plus tm(STB_PIN, CLK_PIN, DIO_PIN, true);

void setup() {
  // เริ่มต้นการทำงาน
  tm.displayBegin();

  // ล้างหน้าจอให้ว่าง
  tm.reset();

  // ตัว b จะแสดงเป็นตัวเล็กโดยอัตโนมัติ
  tm.displayText("b6708429");
}

void loop() {
  // แสดงผลค้างไว้ตลอด
}