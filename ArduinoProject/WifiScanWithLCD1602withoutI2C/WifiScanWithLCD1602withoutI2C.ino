#include <LiquidCrystal.h>
#include "WiFi.h"

// กำหนดขาเชื่อมต่อ LCD1602 (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(21, 34, 18, 33, 12, 11);

void setup() {
  lcd.begin(16, 2);              // เริ่มต้นจอ LCD ขนาด 16 ตัวอักษร 2 แถว
  lcd.print("WiFi Scan Start");  // แสดงข้อความเริ่มต้น
  WiFi.mode(WIFI_STA);           // ตั้งโหมด WiFi เป็น Station (สำหรับสแกน)
  WiFi.disconnect();             // ตัดการเชื่อมต่อ WiFi ที่อาจค้างอยู่
  delay(1000);                   // หน่วง 1 วินาที
  lcd.clear();                   // ล้างหน้าจอ
}

void loop() {
  lcd.setCursor(0, 0);            // เคอร์เซอร์ไปแถว 0 คอลัมน์ 0
  lcd.print("Scanning...     ");  // แสดงข้อความกำลังสแกน WiFi
  int n = WiFi.scanNetworks();    // สแกนหา WiFi เก็บจำนวนที่พบใน n

  lcd.clear();  // ล้างหน้าจอ

  // แสดงจำนวน WiFi ที่พบก่อนแสดงรายละเอียด
  lcd.setCursor(0, 0);
  lcd.print("WiFi found: ");  // ข้อความแสดงจำนวน WiFi ที่เจอ
  lcd.print(n);               // แสดงค่าตัวแปร n (จำนวน WiFi)
  delay(1500);                // หน่วงให้เห็นจำนวน WiFi ที่เจอ

  if (n == 0) {  // ถ้าไม่เจอ WiFi
    lcd.setCursor(0, 1);
    lcd.print("No WiFi found  ");  // แสดงข้อความไม่มี WiFi
    delay(2000);                   // หน่วงให้ผู้ใช้เห็นข้อความ
  } else {
    for (int i = 0; i < n; ++i) {  // วนลูปแสดงแต่ละ WiFi ที่เจอ
      lcd.clear();
      lcd.setCursor(0, 0);
      String ssid = WiFi.SSID(i);  // ดึงชื่อ WiFi ตัวที่ i

      if (ssid.length() > 16) ssid = ssid.substring(0, 16);  // ตัดชื่อ SSID ให้ไม่เกิน 16 ตัว
      lcd.print(ssid);                                       // แสดงชื่อ SSID

      lcd.setCursor(0, 1);
      lcd.print("RSSI: ");      // แสดง RSSI
      lcd.print(WiFi.RSSI(i));  // แสดงค่าความแรงสัญญาณ
      delay(2000);              // หน่วง 2 วินาทีแต่ละเครือข่าย
    }
  }

  // นับถอยหลัง 5 วินาทีก่อนสแกนใหม่
  for (int sec = 5; sec > 0; --sec) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(String(sec) + " sec remain");  // แสดงเวลาคงเหลือจริง
    lcd.setCursor(0, 1);
    lcd.print("for next scan ");  // แสดงข้อความเตรียมสแกนใหม่
    delay(1000);                  // หน่วง 1 วินาที
  }
}