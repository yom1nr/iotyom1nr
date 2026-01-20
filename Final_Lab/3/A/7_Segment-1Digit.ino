int SegmentPort[] = {16, 17, 5, 18, 19, 21, 22, 23}; // tgfe dcba

// ตารางเลข 0–9 (Common Cathode)
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
  0x6F  // 9
};

// ตัวอักษร b
#define CHAR_b 0x7C

// ลำดับที่ต้องการแสดง
int code[] = { CHAR_b, 6, 7, 1, 5, 3, 9, 7 };
int indexNum = 0;

void Display(int value, bool isChar) {
  int seg;

  if (isChar)
    seg = value;
  else
    seg = SegmentTable[value];

  seg = ~seg; // 🔁 กลับติด/ดับ

  for (int i = 0; i < 8; i++) {
    digitalWrite(SegmentPort[7 - i], seg & 1);
    seg >>= 1;
  }
}

// ดับทุกจุด
void ClearDisplay() {
  for (int i = 0; i < 8; i++)
    digitalWrite(SegmentPort[i], HIGH); // เพราะกลับบิตแล้ว
}

void setup() {
  for (int i = 0; i < 8; i++)
    pinMode(SegmentPort[i], OUTPUT);
}

void loop() {
  // แสดงค่า
  if (indexNum == 0)
    Display(code[indexNum], true);   // b
  else
    Display(code[indexNum], false);  // ตัวเลข

  delay(700);

  // ดับ
  ClearDisplay();
  delay(300);

  // ไปตัวถัดไป
  indexNum++;
  if (indexNum >= 8) indexNum = 0;
}
