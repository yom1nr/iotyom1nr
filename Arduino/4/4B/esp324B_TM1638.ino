#include <TM1638plus.h>
#define pin_STB 21
#define pin_CLK 19
#define pin_DIO 18
TM1638plus tm(pin_STB, pin_CLK , pin_DIO);
void setup() {
Serial.begin(115200);
tm.displayBegin();
tm.brightness(6);
}
void loop() {
tm.reset();
tm.displayText("B6708962");
delay(200);

}