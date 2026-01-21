// กำหนดขาเชื่อมต่อ
#define STB 5
#define CLK 18
#define DIO 23

// ข้อมูล Segment สำหรับรหัส B 6 7 1 1 6 4 1 (รูปแบบ 8-bit)
// โครงสร้างบิต: 0b (DP)(G)(F)(E)(D)(C)(B)(A)
const uint8_t myID[] = {
  0x7C, // b  (0b01111100)
  0x7D, // 6  (0b01111101)
  0x07, // 7  (0b00000111)
  0x5B, // 1  (0b-0101-1011)
  0x7F, // 8  
  0x07, // 7  (0b00000111)
  0x7F, // 8  
  0x7D, // 6  (0b01111101)
  
};

void sendCommand(uint8_t value) {
  digitalWrite(STB, LOW);
  shiftOut(DIO, CLK, LSBFIRST, value);
  digitalWrite(STB, HIGH);
}

void sendData(uint8_t addr, uint8_t data) {
  sendCommand(0x44); // ตั้งค่าแบบ Fixed Address
  digitalWrite(STB, LOW);
  shiftOut(DIO, CLK, LSBFIRST, 0xC0 | addr); // ส่งตำแหน่ง Address (0xC0, 0xC2, ...)
  shiftOut(DIO, CLK, LSBFIRST, data);        // ส่งข้อมูล Segment
  digitalWrite(STB, HIGH);
}

void setup() {
  pinMode(STB, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DIO, OUTPUT);
  
  digitalWrite(STB, HIGH);
  
  sendCommand(0x8F); // เปิดหน้าจอ + ตั้งความสว่างสูงสุด (0x88 - 0x8F)
  
  // ล้างหน้าจอและไฟ LED ทั้งหมด
  for (int i = 0; i < 16; i++) {
    sendData(i, 0x00);
  }
}

void loop() {
  // แสดงผลตัวเลข 8 หลักตาม Array myID
  for (int i = 0; i < 8; i++) {
    // TM1638 ตำแหน่งตัวเลขจะอยู่ที่ Address คู่: 0, 2, 4, 6, 8, 10, 12, 14
    sendData(i * 2, myID[i]);
    
    // สั่งเปิดไฟ LED สีแดงด้านบน (Address คี่: 1, 3, 5, 7, 9, 11, 13, 15)
    sendData((i * 2) + 1, 0x01); 
  }
  
  delay(1000);
}