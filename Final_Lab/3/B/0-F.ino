#define scanTimeMSec 5
#define segCommon 0   // 0 = Common Cathode

int SegmentPosition[] = {12, 14, 27, 26}; // D1 D2 D3 D4
int SegmentPort[] = {16, 17, 5, 18, 19, 21, 22, 23}; // tgfe dcba

// 0–9 , A–F
int SegmentTable[] = {
  0x3F, // 0
  0x06, // 1
  0x5B, // 2
  0x4F, // 3
  0x66, // 4
  0x6D, // 5
  0x7D, // 6
  0x07, // 7
  0x7F, // 8
  0x6F, // 9
  0x77, // A
  0x7C, // b
  0x39, // C
  0x5E, // d
  0x79, // E
  0x71  // F
};

int value = 0; // 0–15

void Display_1Digit(int data) {
  int seg = SegmentTable[data];
  seg = segCommon ? ~seg : seg;

  for (int i = 0; i < 8; i++) {
    digitalWrite(SegmentPort[7 - i], seg & 1);
    seg >>= 1;
  }
}

void setup() {
  for (int i = 0; i < 8; i++)
    pinMode(SegmentPort[i], OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(SegmentPosition[i], OUTPUT);
    digitalWrite(SegmentPosition[i], 1 - segCommon);
  }
}

void loop() {
  // แสดงเฉพาะหลักซ้ายสุด
  Display_1Digit(value);
  digitalWrite(SegmentPosition[0], segCommon);   // เปิดหลักซ้าย
  delay(500);
  digitalWrite(SegmentPosition[0], 1 - segCommon);

  value++;
  if (value > 15) value = 0;  // วน 0–F
}
