#define scanTimeMSec 5
#define segCommon 0    // 0 = CK (GND Common), 1 = CA (Vcc Common)

int SegmentPosition[] = {12, 14, 27, 26}; // Dig.1(ซ้าย) -> Dig.4(ขวา)
int SegmentPort[] = {16, 17, 5, 18, 19, 21, 22, 23}; // tgfe dcba

// เพิ่มรหัส 0x00 (ดับไฟหมด) ไว้ที่ตำแหน่งสุดท้าย (Index 16) เพื่อใช้เป็น "ช่องว่าง"
int SegmentTable[] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, // 0-4
  0x6D, 0x7D, 0x07, 0x7F, 0x6F, // 5-9
  0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, // A-F
  0x00 // Index 16 = Space (ดับทุกดวง)
};

// ข้อมูล: b 6 7 0 8 9 6 2
int MyData[] = {11, 6, 7, 0, 8, 9, 6, 2}; 
int DataLength = 8; 
int SpaceChar = 16; // Index ของช่องว่างใน SegmentTable

int scrollStep = 0; // ตัวนับจังหวะการเลื่อน

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 8; i++) pinMode(SegmentPort[i], OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(SegmentPosition[i], OUTPUT);
    digitalWrite(SegmentPosition[i], 1 - segCommon);
  }
}

void Display_1Digit_7Segment(int iData) {
  int SegDecode = SegmentTable[iData];
  SegDecode = segCommon == 0 ? SegDecode : ~SegDecode;
  for (int i = 0; i < 8; i++) {
    digitalWrite(SegmentPort[7 - i], SegDecode & 1);
    SegDecode = SegDecode >> 1;
  }
}

// ฟังก์ชันคำนวณตำแหน่งและแสดงผล
void Display_Marquee(int step) {
  for (int j = 0; j < 4; j++) { // วนลูป 4 หลัก (ซ้ายไปขวา 0-3)
    
    // สูตรคำนวณตำแหน่งข้อมูล
    // เราลบ 3 ออก เพื่อให้ step แรกๆ ดึงค่าติดลบ (ซึ่งจะเป็นช่องว่าง)
    // ทำให้เกิด effect ตัวหนังสือโผล่มาจากทางขวา
    int charIndex = step + j - 3; 

    int valueToShow;
    
    // ถ้า Index หลุดขอบซ้าย หรือ หลุดขอบขวา ให้แสดงช่องว่าง
    if (charIndex < 0 || charIndex >= DataLength) {
      valueToShow = SpaceChar; 
    } else {
      valueToShow = MyData[charIndex];
    }
    
    Display_1Digit_7Segment(valueToShow);
    digitalWrite(SegmentPosition[j], segCommon);
    delay(scanTimeMSec);
    digitalWrite(SegmentPosition[j], 1 - segCommon);
  }
}

void loop() {
  // Loop หน่วงเวลา: ปรับเลข 30 เพื่อให้วิ่งช้าลงหรือเร็วขึ้น
  for (int frame = 0; frame < 30; frame++) {
    Display_Marquee(scrollStep);
  }

  scrollStep++;
  
  // คำนวณจุดจบ: DataLength + 4 เพื่อให้เลื่อนจนตัวสุดท้ายหายไปจากจอ
  if (scrollStep > DataLength + 3) {
    scrollStep = 0; // เริ่มต้นใหม่
  }
}