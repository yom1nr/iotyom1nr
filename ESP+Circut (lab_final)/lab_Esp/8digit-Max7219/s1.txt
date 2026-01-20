#define minData 0
#define maxData 9
int SegmentPort[] = { 16, 17, 5, 18, 19, 21, 22, 23 };
int SegmentTable[] = {
  0x7C,                                         // B
  0x7D,                                         // 6
  0x07,                                         // 7
  0x3F,                                         // 0
  0x7F,                                         // 8
  0x66,                                         // 4
  0x5B,                                         // 2
  0x6F                                          // 9
};                                              // tgfe dcba
int displaySeq[] = { 0, 1, 2, 3, 4, 5, 6, 7 };  // B 6 7 0 8 4 2 9
int seqIndex = 0;
int seqLen = 8;
void Display_1Digit_7Segment(int iData) {
  //  int SegDecode = SegmentTable[iData]; // CK 7-Segment – GND

  int SegDecode = ~SegmentTable[iData];  // CA-Segment – Vcc

  for (int i = 0; i < 8; i++) {
    digitalWrite(SegmentPort[7 - i], SegDecode & 1);
    SegDecode = SegDecode >> 1;
  }
}
void setup() {
  for (int i = 0; i < 8; i++)
    pinMode(SegmentPort[i], OUTPUT);
  Serial.begin(115200);
}
void loop() {
  Display_1Digit_7Segment(displaySeq[seqIndex]);
  Serial.println(displaySeq[seqIndex]);

  seqIndex++;
  if (seqIndex >= seqLen)
    seqIndex = 0;

  delay(1000);
}