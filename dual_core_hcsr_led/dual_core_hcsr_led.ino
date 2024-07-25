#include <Arduino.h>

// ESP32 çift çekirdek kullanımı
TaskHandle_t Task1;
TaskHandle_t Task2;

// Led ve sensör pinleri
const int led1 = 2;
const int TrigPin = 4;
const int EchoPin = 5;

// Task1 kodu led1'i 2000ms de bir yakıp söndürecek
void Task1kodu(void *pvParameters) {
  Serial.print("Task1'in çalıştığı çekirdek: ");
  Serial.println(xPortGetCoreID());

  for (;;) {   // Sonsuz döner
    digitalWrite(led1, HIGH);
    delay(2000);
    digitalWrite(led1, LOW);
    delay(2000);
  }
}

// Task2 kodu mesafe ölçümü yapacak
void Task2kodu(void *pvParameters) {
  Serial.print("Task2'nin çalıştırılacağı çekirdek: ");
  Serial.println(xPortGetCoreID());

  for (;;) {
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);

    // Echo pinine gelen sinyali ölç
    long duration = pulseIn(EchoPin, HIGH);

    // Süreyi mesafeye çevir
    long distance = duration * 0.034 / 2;
    Serial.print("Ölçülen mesafe: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(1000);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  xTaskCreatePinnedToCore(
    Task1kodu,   // Görevin çalışacağı fonksiyon
    "Task1",     // Görevin adı
    10000,       // Görev stack boyutu
    NULL,        // İlave parametre
    1,           // Görevin önceliği
    &Task1,      // Görevin işaretçisi
    0);          // Görevi 0 numaralı çekirdeğe atayalım

  delay(500);

  xTaskCreatePinnedToCore(
    Task2kodu,   // Görevin çalışacağı fonksiyon
    "Task2",     // Görevin adı
    10000,       // Görev stack boyutu
    NULL,        // İlave parametre
    1,           // Görevin önceliği
    &Task2,      // Görevin işaretçisi
    1);          // Görevi 1 numaralı çekirdeğe atayalım

  delay(500);
}

void loop() {
  // Boş. Görevler artık bağımsız olarak çalışıyor.
}
