#define minData 0
#define maxData 7  // *** แก้จุดนี้: เปลี่ยนเป็น 7 (เพราะข้อมูลมีลำดับ 0-7) ***

int SegmentPort[] = {2, 4, 5, 18, 19, 21, 22, 23}; // tgfe dcba

// ตารางรหัส B6729875
int SegmentTable[] = {
  0x7C, // ลำดับที่ 0: B
  0x7D, // ลำดับที่ 1: 6
  0x07, // ลำดับที่ 2: 7
  0x5B, // ลำดับที่ 3: 2
  0x6F, // ลำดับที่ 4: 9
  0x7F, // ลำดับที่ 5: 8
  0x07, // ลำดับที่ 6: 7
  0x6D  // ลำดับที่ 7: 5
}; 

int nCounter = 0;

void Display_1Digit_7Segment(int iData) {
  // เครื่องหมาย ~ (Not) ใช้สำหรับจอ Common Anode
  // ถ้าใช้ Common Cathode ให้ลบ ~ ออกนะครับ
  int SegDecode = ~SegmentTable[iData]; 

  for (int i = 0; i < 8; i++) {
    // ใช้ 7-i หรือ i ขึ้นอยู่กับการเรียงสายของคุณ
    digitalWrite(SegmentPort[7-i], SegDecode & 1);
    SegDecode = SegDecode >> 1;
  }
}

void setup() {
  for (int i = 0; i < 8; i++)
    pinMode(SegmentPort[i], OUTPUT);
  Serial.begin(115200);
}

void loop() {
  Display_1Digit_7Segment(nCounter);
  Serial.println(nCounter);
  
  nCounter++;
  
  // เช็คเงื่อนไขการวนลูป
  // ถ้า nCounter มากกว่า 7 (เกินตัวสุดท้าย) -> ให้กลับไปเริ่มที่ 0 (ตัว B)
  nCounter = nCounter > maxData ? minData : nCounter;
  
  delay(1000); // รอ 1 วินาที
}