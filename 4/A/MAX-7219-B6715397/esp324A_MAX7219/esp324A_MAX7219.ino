#include "LedController.hpp"
#define Pin_DIN 19 // D19
#define Pin_CS 18 // D18
#define Pin_CLK 5 // D5
LedController<1, 1> lc;
void setup() {
lc = LedController<1, 1>(Pin_DIN,
Pin_CLK, Pin_CS);
lc.setIntensity(8);
lc.clearMatrix();
}
void loop()
{ lc.setChar(0, 7, 'B', false);
lc.setDigit(0, 6, 6, false);
lc.setDigit(0, 5, 7, false);
lc.setDigit(0, 4, 2, false);
lc.setDigit(0, 3, 9, false);
lc.setDigit(0, 2, 8, false);
lc.setDigit(0, 1, 7, false);
lc.setDigit(0, 0, 5, false);
delay(1000);
}