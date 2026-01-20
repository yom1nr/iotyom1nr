#define minData 0
#define maxData 15 // นับถึง 15 (F)
#define scanTimeMSec 10
#define segCommon 0
// 0 = CK 7-Segment – GND Common
// 1 = CA 7-Segment – Vcc Common

int SegmentPosition[] = {12, 14, 27, 26}; // Dig.1 Dig.2 Dig.3 Dig.4
int SegmentPort[] = {16, 17, 5, 18, 19, 21, 22, 23}; // tgfe dcba

// เพิ่มรหัส 0-F ลงในตาราง
int SegmentTable[] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, // 0-4
  0x6D, 0x7D, 0x07, 0x7F, 0x6F, // 5-9
  0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 // A, b, C, d, E, F
}; 

int nCounter = 0;

void Display_1Digit_7Segment(int iData) {
  int SegDecode = SegmentTable[iData]; 
  SegDecode = segCommon == 0 ? SegDecode : ~SegDecode;
  for (int i = 0; i < 8; i++) {
    digitalWrite(SegmentPort[7 - i], SegDecode & 1);
    SegDecode = SegDecode >> 1;
  }
}

// ฟังก์ชันใหม่: แสดงผลเฉพาะหลักซ้ายสุด (Digit 1)
void Display_LeftDigit_Hex(int iData) {
    // ส่งข้อมูล Segments (a-g)
    Display_1Digit_7Segment(iData); 
    
    // เปิดเฉพาะหลักซ้ายสุด (SegmentPosition[0])
    digitalWrite(SegmentPosition[0], segCommon); 
    
    delay(scanTimeMSec);
    
    // ปิดหลักซ้ายสุด (เพื่อป้องกันเงาซ้อน ถ้ามีการขยายในอนาคต)
    digitalWrite(SegmentPosition[0], 1 - segCommon); 
}

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 8; i++)
    pinMode(SegmentPort[i], OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(SegmentPosition[i], OUTPUT);
    // ปิดทุกหลักไว้ก่อน
    digitalWrite(SegmentPosition[i], 1 - segCommon); 
  }
}

void loop() {
  Serial.println(nCounter);
  
  // วนลูปเพื่อหน่วงเวลาและคงสถานะไฟ (Refresh rate)
  for (int nloop = 0; nloop < 50; nloop++) {
    Display_LeftDigit_Hex(nCounter);
  }

  nCounter++;
  // ตรวจสอบเงื่อนไข 0-15
  if (nCounter > maxData) {
    nCounter = minData;
  }
}