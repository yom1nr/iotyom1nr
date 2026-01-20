#include "DHTesp.h"
#define pinDHT22 15
DHTesp dht;
void setup()
{
Serial.begin(115200);
Serial.println();
String thisBoard = ARDUINO_BOARD;
Serial.println(thisBoard);
Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
dht.setup(pinDHT22, DHTesp::DHT22);
}
void loop() {
delay(dht.getMinimumSamplingPeriod());
float humidity = dht.getHumidity();
float temperature = dht.getTemperature();
Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
Serial.print(dht.getStatusString());
Serial.print("\t"); Serial.print(humidity, 1);
Serial.print("\t\t"); Serial.print(temperature, 1);
Serial.print("\t\t"); Serial.print(dht.toFahrenheit(temperature), 1);
Serial.print("\t\t");
Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
Serial.print("\t\t");
Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity,
true), 1);
delay(2000);
}