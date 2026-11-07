#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

// Inisialisasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C untuk modul LCD (sesuaikan jika berbeda)

// Pin HX711
#define DT A0 // Pin data HX711
#define SCK A1 // Pin clock HX711

HX711 scale;

void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(9600);

  // Inisialisasi LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Load Cell Init");

  // Inisialisasi HX711
  scale.begin(DT, SCK);
  delay(1000);

  // Kalibrasi awal
  lcd.setCursor(0, 1);
  lcd.print("Tare... Wait...");
  scale.set_scale(); // Atur skala default
  scale.tare();      // Reset ke nol (tare)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ready");
  delay(2000);
}

void loop() {
  // Baca berat dari load cell
  float weight = scale.get_units(10); // Baca rata-rata dari 10 sampel

  // Tampilkan berat di serial monitor
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" kg");

  // Tampilkan berat di LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weight:");
  lcd.setCursor(0, 1);
  lcd.print(weight, 2); // Tampilkan 2 angka desimal
  lcd.print(" kg");

  delay(500); // Tunggu 0,5 detik sebelum pembaruan
}
