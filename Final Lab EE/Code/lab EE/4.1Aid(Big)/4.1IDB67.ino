#include <SPI.h>

// กำหนดขาเชื่อมต่อ
#define CS_PIN 5  
// DIN 23, CS 5 CLK 18

// คำสั่งสำหรับ MAX7219
#define REG_DECODE_MODE  0x09
#define REG_INTENSITY    0x0A
#define REG_SCAN_LIMIT   0x0B
#define REG_SHUTDOWN     0x0C
#define REG_DISPLAY_TEST 0x0F

void sendData(byte reg, byte data) {
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(reg);
  SPI.transfer(data);
  digitalWrite(CS_PIN, HIGH);
}

void setup() {
  pinMode(CS_PIN, OUTPUT);
  SPI.begin(); // เริ่มต้น SPI (Default: CLK=18, DIN=23)

  // เริ่มต้นตั้งค่า MAX7219
  sendData(REG_DISPLAY_TEST, 0x00); // ปิดโหมด Test
  sendData(REG_SHUTDOWN, 0x01);     // เปิดหน้าจอ (Normal Operation)
  sendData(REG_SCAN_LIMIT, 0x07);   // ใช้งานครบ 8 หลัก
  sendData(REG_INTENSITY, 0x08);    // ตั้งความสว่าง (0-15)
  sendData(REG_DECODE_MODE, 0x00);  // **สำคัญ** ตั้งเป็น No Decode เพื่อคุมแบบ 8-bit
  
  for(int i=1; i<=8; i++) sendData(i, 0x00); // ล้างหน้าจอ
}

void loop() {
  // การส่งข้อมูลแบบ 8-bit เพื่อแสดงรหัส B 6 7 1 1 6 4 1
  // รูปแบบ: sendData(ตำแหน่งหลัก 1-8, ข้อมูล Segment แบบ Byte)
  // 0b0 abcd efg แบ่งตาม segment แต่ละตัว 
  sendData(8, 0b00011111); // b 
  sendData(7, 0b01011111); // 6
  sendData(6, 0b01110000); // 7
  sendData(5, 0b01101101); // 2
  sendData(4, 0b01111111); // 8
  sendData(3, 0b01110000); // 7
  sendData(2, 0b01111111); // 8
  sendData(1, 0b01011111); // 6
  
  delay(5000);
}