#define BLYNK_TEMPLATE_ID "TMPL6aUh65nGe"   // Ganti dengan Template ID kau
#define BLYNK_TEMPLATE_NAME "esp32dht11"
#define BLYNK_AUTH_TOKEN "KRjCe2I_zfEexrAiYnNyzV0kQlxZYRuU" // Paste Auth Token dari email Blynk

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define DHTPIN 4           // Pin Data DHT11
#define DHTTYPE DHT11      // Jenis DHT11
#define LED_PIN 27         // Pin LED


char ssid[] = "HafizTM 2.4GHz";      // Nama WiFi rumah kau
char pass[] = "h@f1z53355";        // Password WiFi

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 + DHT11 + Blynk Siap!");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Connecting to Blynk...");
}

void loop() {
  Blynk.run();  // Wajib untuk Blynk sync

  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();

  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("Gagal baca DHT11! Semak wiring/resistor.");
    //delay(2000);
    //return;
  }else{
     // Debug Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" °C | Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %");

  }

  // Hantar data ke Blynk app (V0 suhu, V1 kelembapan)
  Blynk.virtualWrite(V0, suhu);
  Blynk.virtualWrite(V1, kelembapan);
  Serial.println("Bacaan berjaya dihantar ke dashboard");

  // Kawal LED ikut suhu
  if (suhu > 40.0) {
    digitalWrite(LED_PIN, HIGH);
    Blynk.virtualWrite(V2, 255);          // LED di Blynk ON (255 = full bright)
    Serial.println("Suhu tinggi! LED ON");
  } else {
    digitalWrite(LED_PIN, LOW);
    Blynk.virtualWrite(V2, 0);          // LED di Blynk ON (255 = full bright)
    Serial.println("Suhu normal, LED OFF");
  }

  delay(2000);  // Update setiap 2 saat
}
