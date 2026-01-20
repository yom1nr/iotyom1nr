#define minData 0
#define maxData 15
int SegmentPort[] = {2, 4, 5, 18, 19, 21, 22, 23}; // tgfe dcba
int SegmentTable[] = {0x00,0x7C, // ลำดับที่ 0: B (b เล็ก)
  0x00,
  0x7D, // ลำดับที่ 1: 6
  0x00,
  0x07, // ลำดับที่ 2: 7
  0x00,
  0x3F, // ลำดับที่ 3: 0
  0x00,
  0x7F, // ลำดับที่ 4: 8
  0x00,
  0x6F, // ลำดับที่ 5: 9
  0x00,
  0x7D, // ลำดับที่ 6: 6
  0x00,
  0x5B  // ลำดับที่ 7: 2
}; // tgfe dcba
int nCounter = 0;
void Display_1Digit_7Segment(int iData) {
int SegDecode = ~SegmentTable[iData]; // CK 7-Segment – GND

// int SegDecode = ~SegmentTable[iData]; // CA-Segment – Vcc

for (int i = 0; i < 8; i++) {
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
nCounter = nCounter < minData ? maxData : nCounter;
nCounter = nCounter > maxData ? minData : nCounter;
delay(1000);
}