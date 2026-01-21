#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define MAX_DEVICES 1
#define CS_PIN 5  // DIO=23, CLK=18
// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
// #define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
void setup() {
  Display.begin();
  Display.setIntensity(6);
  Display.displayClear();
}
void loop() {
  Display.setTextAlignment(PA_CENTER);
  Display.setInvert(true);
  Display.print("W");
  delay(1000);
  Display.setInvert(false);
  Display.print("W");
  delay(1000);
  Display.print("I");
  delay(1000);
  Display.print("C");
  delay(1000);
  Display.print("H");
  delay(1000);
  Display.print("A");
  delay(1000);
  Display.print("I");
  delay(1000);
}