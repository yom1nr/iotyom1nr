int SegmentPort[] = { 16, 17, 5, 18, 19, 21, 22, 23 };  // tgfe dcba
int SegmentPosition[] = { 12, 14, 27, 26 };             // Dig1 Dig2 Dig3 Dig4

int SegmentTable[] = {
  0x3F,  // 0
  0x06,  // 1
  0x5B,  // 2
  0x4F,  // 3
  0x66,  // 4
  0x6D,  // 5
  0x7D,  // 6
  0x07,  // 7
  0x7F,  // 8
  0x6F   // 9
};

#define scanTimeMSec 1
#define segCommon 0  // 0 = Common Cathode
#define SEG_DASH 0x40
#define SEG_BLANK 0x00
#define SEG_b 0x7C  // b (c d e f g)

char text[] = "b6708429";
int textLen = 8;
int scrollPos = -4;  // เริ่มจาก ----

/* ========================== */

int getSegCode(char c) {
  if (c >= '0' && c <= '9')
    return SegmentTable[c - '0'];
  if (c == 'b')
    return SEG_b;
  if (c == '-')
    return SEG_DASH;
  if (c == ' ')
    return SEG_BLANK;
  return SEG_BLANK;
}


/* ========================== */

void Display_4Digit_Buffer(char buf[4]) {
  for (int j = 0; j < 4; j++) {
    int seg = getSegCode(buf[j]);
    seg = segCommon == 0 ? seg : ~seg;

    for (int i = 0; i < 8; i++) {
      digitalWrite(SegmentPort[7 - i], seg & 1);
      seg >>= 1;
    }
	//อยากสลับ ใส่ 3 - j
    digitalWrite(SegmentPosition[j], segCommon);  // << แก้ตรงนี้
    delay(scanTimeMSec);
    digitalWrite(SegmentPosition[j], 1 - segCommon);
  }
}


/* ========================== */

void setup() {
  for (int i = 0; i < 8; i++)
    pinMode(SegmentPort[i], OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(SegmentPosition[i], OUTPUT);
    digitalWrite(SegmentPosition[i], 1 - segCommon);
  }
}

/* ========================== */

void loop() {
  char buf[4];

  // สร้าง buffer 4 หลัก
  for (int i = 0; i < 4; i++) {
    int idx = scrollPos + i;
    if (idx < 0 || idx >= textLen)
      buf[i] = '-';
    else
      buf[i] = text[idx];
  }

  // แสดงผลหลายรอบเพื่อให้ตาเห็น
  for (int n = 0; n < 80; n++)
    Display_4Digit_Buffer(buf);

  // เลื่อนซ้ายทีละ 1 ตัว
  scrollPos++;
  if (scrollPos > textLen)
    scrollPos = -4;
}
