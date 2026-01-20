#define scanTimeMSec 5
#define segCommon 0   // 0 = Common Cathode (ขากลางลง GND)

int SegmentPosition[] = {12, 14, 27, 26}; // D1 D2 D3 D4
int SegmentPort[] = {16, 17, 5, 18, 19, 21, 22, 23}; // tgfe dcba

// 0–9 , A–F (เพิ่ม 0x40 สำหรับเครื่องหมาย - และ 0x00 สำหรับดับไฟ)
int SegmentTable[] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, // 0-9
  0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, // A-F
  0x40, // [16] เครื่องหมาย - (ขีดกลาง)
  0x00  // [17] ดับไฟ (ว่างเปล่า)
};

// รหัส b6729875 (ใส่ 17 เพื่อให้เริ่มจากว่างเปล่า)
// ลำดับ: ว่าง, ว่าง, ว่าง, ว่าง, b, 6, 7, 2, 9, 8, 7, 5, ว่าง, ว่าง, ว่าง, ว่าง
int myID[] = {17, 17, 17, 17, 11, 6, 7, 2, 9, 8, 7, 5, 17, 17, 17, 17};
int idLength = sizeof(myID) / sizeof(myID[0]);
int offset = 0;
unsigned long lastMoveTime = 0;
int moveDelay = 500; // ความเร็วในการเลื่อน (500ms)

void Display_1Digit(int data) {
  int seg = SegmentTable[data];
  seg = segCommon ? ~seg : seg;
  for (int i = 0; i < 8; i++) {
    digitalWrite(SegmentPort[7 - i], seg & 1);
    seg >>= 1;
  }
}

void setup() {
  for (int i = 0; i < 8; i++) pinMode(SegmentPort[i], OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(SegmentPosition[i], OUTPUT);
    digitalWrite(SegmentPosition[i], 1 - segCommon); // ปิดทุกหลักไว้ก่อน
  }
}

void loop() {
  // ควบคุมจังหวะการเลื่อนตำแหน่ง
  if (millis() - lastMoveTime > moveDelay) {
    offset++;
    if (offset > idLength - 4) offset = 0; 
    lastMoveTime = millis();
  }

  // การ Multiplexing แสดงผล 4 หลัก
  for (int i = 0; i < 4; i++) {
    // 1. ส่งข้อมูลตัวเลขไปยัง Segment
    Display_1Digit(myID[offset + i]);

    // 2. เปิดหลักที่ต้องการแสดง
    digitalWrite(SegmentPosition[i], segCommon);
    
    // 3. หน่วงเวลาสั้นๆ ให้ตาเห็นไฟสว่าง
    delay(scanTimeMSec);

    // 4. ปิดหลักนั้นก่อนเปลี่ยนไปหลักถัดไป (ป้องกันไฟซ้อน)
    digitalWrite(SegmentPosition[i], 1 - segCommon);
  }
}
