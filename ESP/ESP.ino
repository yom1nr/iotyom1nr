#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BluetoothSerial.h" // เรียกใช้ Library บลูทูธที่มีในตัว ESP32

// ตั้งค่าจอ OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// สร้างตัวแปร Bluetooth
BluetoothSerial SerialBT;

String message = ""; // ตัวแปรเก็บข้อความ

void setup() {
  Serial.begin(115200);

  // 1. เริ่มต้น Bluetooth
  // ชื่อนี้จะไปโชว์ในมือถือตอนค้นหา
  SerialBT.begin("ESP32_CPE_Display"); 
  Serial.println("Bluetooth Started! Ready to pair...");

  // 2. เริ่มต้นจอ OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  // โชว์หน้าจอเริ่มต้น
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Waiting for");
  display.println("Bluetooth...");
  display.display();
}

void loop() {
  // ถ้ามีข้อมูลส่งมาจากมือถือ via Bluetooth
  if (SerialBT.available()) {
    // อ่านข้อความที่ส่งมาจนจบคำ (เครื่องหมายขึ้นบรรทัดใหม่)
    message = SerialBT.readString();
    
    // ลบช่องว่างส่วนเกิน (เช่น Enter) ออก
    message.trim(); 

    // โชว์ข้อความใหม่บนจอ
    Serial.print("Received: ");
    Serial.println(message);
    
    display.clearDisplay();
    display.setTextSize(2); // ปรับขนาดตัวอักษรใหญ่หน่อย
    display.setCursor(0, 10);
    display.println(message);
    display.display();
  }
  delay(20);
}