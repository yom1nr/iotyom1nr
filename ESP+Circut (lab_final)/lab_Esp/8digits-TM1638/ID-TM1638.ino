#include <LedController.hpp>


// กำหนดขาตามที่คุณต่อ: D5 -> CLK, D18 -> CS, D19 -> DIN
const int DIN_PIN = 19; 
const int CS_PIN  = 18;
const int CLK_PIN = 5;

// ฟังก์ชันส่งข้อมูลไปยัง MAX7219
void sendData(byte address, byte data) {
  digitalWrite(CS_PIN, LOW);
  shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, address);
  shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, data);
  digitalWrite(CS_PIN, HIGH);
}


// เรียงจากหลักซ้ายไปขวา (ตำแหน่ง 8 ถึง 1)
byte msg[] = {
  0x1F, // b
  0x5F, // 6
  0x70, // 7
  0x7E, // 0
  0x7F, // 8
  0x33, // 4
  0x6D, // 2
  0x7B  // 9
};

void setup() {
  // ตั้งค่าพินเป็น Output
  pinMode(DIN_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);

  // เริ่มต้นการทำงานของ MAX7219
  sendData(0x0C, 0x01); // Normal operation (Wake up)
  sendData(0x0B, 0x07); // Scan limit (ใช้ 8 หลัก)
  sendData(0x0A, 0x08); // ความสว่าง (0-15)
  sendData(0x09, 0x00); // ไม่ใช้การถอดรหัส (เรากำหนด segment เอง)
  sendData(0x0F, 0x00); // ปิด Display Test
  
  // ล้างหน้าจอก่อนแสดงผล
  for(int i=1; i<=8; i++) sendData(i, 0x00);


  for(int i=0; i<8; i++) {
    // MAX7219 ใช้ Address 1-8 (1 คือหลักขวาสุด, 8 คือหลักซ้ายสุด)
    sendData(8-i, msg[i]); 
  }
}

void loop() {
  // วนลูปว่างไว้เพื่อให้แสดงผลค้างไว้
}
