#include "HX711.h"

// Pin HX711
#define DT A1       // Data pin
#define SCK A0      // Clock pin

// Pin output analog (PWM)
#define ANALOG_OUT 9

// Objek HX711
HX711 scale;

// Variabel
float calibrationFactor = 2280.0; // Faktor kalibrasi (sesuaikan)
float weight = 0;                // Berat dalam gram
float voltage = 0;               // Tegangan output PWM
const float maxVoltage = 5.0;    // Tegangan maksimum Arduino (5V)

void setup() {
  Serial.begin(9600);
  
  // Inisialisasi HX711
  scale.begin(DT, SCK);
  scale.set_scale(calibrationFactor);
  scale.tare(); // Atur nol pada timbangan
  
  // Inisialisasi pin output analog
  pinMode(ANALOG_OUT, OUTPUT);

  Serial.println("HX711 dan Output Analog Siap");
}

void loop() {
  // Membaca berat
  if (scale.is_ready()) {
    weight = scale.get_units();
    weight = constrain(weight, 0, 5000); // Batasi berat pada rentang 0-5000g
    Serial.print("Berat: ");
    Serial.print(weight );
    Serial.println(" gram");
  } else {
    Serial.println("HX711 tidak siap");
  }

  // Konversi berat ke nilai PWM (255-0 dengan rentang 5000g)
  int pwmValue = map(weight, 0, 5000, 255, 0); // Berat 0g = PWM 255, Berat 5000g = PWM 0
  pwmValue = constrain(pwmValue, 0, 255);     // Batasi nilai PWM ke rentang 0-255

  // Hitung tegangan berdasarkan nilai PWM
  voltage = (float)pwmValue / 255.0 * maxVoltage;

  // Menulis nilai ke output analog
  analogWrite(ANALOG_OUT, pwmValue);

  // Tampilkan nilai berat, PWM, dan tegangan
  Serial.print("Nilai PWM: ");
  Serial.print(pwmValue);
  Serial.print(" | Tegangan PWM: ");
  Serial.print(voltage, 2); // Tampilkan tegangan dengan 2 digit desimal
  Serial.println(" V");

  delay(500);
}
