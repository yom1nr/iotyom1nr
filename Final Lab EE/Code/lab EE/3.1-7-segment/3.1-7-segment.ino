#define minData 0
#define maxData 7  //จำนวนตัวอักษร

// ขาที่ต่อ (เหมือนเดิม)
int SegmentPort[] = { 16, 17, 5, 18, 19, 21, 22, 23 };
int myID[] = { 0x7C, 0x7D, 0x07, 0x5B, 0x7F, 0x07, 0x7F, 0x7D }; // b6728786

int nCounter = 0;

void Display_1Digit_7Segment(int SegDecode) {
  // สำหรับ Common Anode ต้องใส่ ~ เพื่อกลับลอจิก
  int decoded = ~SegDecode;

  for (int i = 0; i < 8; i++) {
    digitalWrite(SegmentPort[7 - i], decoded & 1);
    decoded = decoded >> 1;
  }
}

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(SegmentPort[i], OUTPUT);
    digitalWrite(SegmentPort[i], HIGH);  // ปิดไฟเริ่มต้น
  }
  Serial.begin(115200);
}

void loop() {
  // ดึงค่ารหัสจากอาเรย์ myID ตามลำดับตัวนับ
  Display_1Digit_7Segment(myID[nCounter]);

  // แสดงผลทาง Serial เพื่อเช็คว่าถึงตัวไหนแล้ว
  char labels[] = { 'B', '6', '7', '2', '8', '7', '8', '6' };
  Serial.print("Displaying: ");
  Serial.println(labels[nCounter]);

  nCounter++;
  if (nCounter > maxData) {
    nCounter = minData;
  }

  delay(1000);  // แสดงตัวละ 1 วินาที
}