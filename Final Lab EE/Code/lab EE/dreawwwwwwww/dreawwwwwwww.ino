// Use the MD_MAX72XX library to display a Pacman animation
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES 1
#define DATA_PIN  23  // or MOSI
#define CLK_PIN   18  // or SCK
#define CS_PIN    5  // or SS

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);                      // SPI hardware interface

void setup() {
  mx.begin();

}

void loop(void) {
  mx.setColumn(0, 0x03);
  mx.setColumn(1, 0x03);
  mx.setColumn(2, 0x03);
  mx.setColumn(5, 0x03);
  mx.setColumn(6, 0x03);
  mx.setColumn(7, 0x03);
  mx.setColumn(3, 0xFF);
  mx.setColumn(3, 0xFF);
  mx.setColumn(4, 0xFF);
}
