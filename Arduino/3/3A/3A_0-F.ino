#define minData 0
#define maxData 15
int SegmentPort[] = {2, 4, 5, 18, 19, 21, 22, 23}; // tgfe dcba
int SegmentTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
  0x6D, 0x7D, 0x07, 0x7F, 0x6F,
  0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
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