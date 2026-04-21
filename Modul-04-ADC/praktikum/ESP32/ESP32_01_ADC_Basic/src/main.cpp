#include <Arduino.h>
#include "DHT.h"

// Konfigurasi PIN
#define DHTPIN 14        // Pindahkan ke GPIO 14 (Lebih stabil)
#define DHTTYPE DHT22    
#define POT_PIN 34       // ADC1_CH6
#define PHOTO_PIN 35     // ADC1_CH7

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(2000);           // Jeda awal untuk stabilitas power
  dht.begin();
  Serial.println("--- Sistem Monitoring Terintegrasi ---");
}

void loop() {
  // --- PEMBACAAN ADC (AVERAGING 10X) ---
  long sumPot = 0;
  long sumPhoto = 0;
  
  for(int i = 0; i < 10; i++) {
    sumPot += analogRead(POT_PIN);
    sumPhoto += analogRead(PHOTO_PIN);
    delay(10);
  }
  
  int avgPot = sumPot / 10;
  int avgPhoto = sumPhoto / 10;
  
  float voltPot = (avgPot / 4095.0) * 3.3;
  float vol tPhoto = (avgPhoto / 4095.0) * 3.3;

  // --- PEMBACAAN DIGITAL (DHT22) ---
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  // --- OUTPUT KE SERIAL MONITOR ---


  if (isnan(hum) || isnan(temp)) {
    Serial.println("DHT Error!");
  } else {
    Serial.print("Temp: "); Serial.print(temp); Serial.print("C | ");
    Serial.print("Hum: "); Serial.print(hum); Serial.println("%");
  }

  delay(2000); // DHT22 butuh jeda minimal 2 detik
}