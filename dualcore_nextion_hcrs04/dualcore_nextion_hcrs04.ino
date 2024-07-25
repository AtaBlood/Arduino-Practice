#include <Nextion.h>
#include <Arduino.h>
#include "EasyNextionLibrary.h"

TaskHandle_t Task1;
TaskHandle_t Task2;

const int TrigPin = 4;
const int EchoPin = 5;

EasyNex ekran(Serial);

volatile long distance = 0;  // Mesafe değişkeni global ve volatile olarak tanımlandı

void Task1kodu(void *pvParameters) {
  Serial.print("task1'in calisacagi core: ");
  Serial.println(xPortGetCoreID());

  for (;;) {
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(2);
    digitalWrite(TrigPin, LOW);

    long duration = pulseIn(EchoPin, HIGH);

    distance = duration * 0.034 / 2;  // Global mesafe değişkenini güncelle
    /*Serial.print("olculen mesafe: ");
    Serial.print(distance);
    Serial.println(" cm ");*/
    delay(500);
  }
}

void Task2kodu(void *pvParameters) {
  Serial.print("task2'nin calisacagi core: ");
  Serial.println(xPortGetCoreID());

  for (;;) {
    // Metin nesnesini güncelle
    String distanceStr = "t0.txt=\"" + String(distance) + " cm\"";
    ekran.writeStr(distanceStr.c_str());

    // Bar nesnesini güncelle
    String barCmd = "j0.val=" + String(distance);
    ekran.writeStr(barCmd.c_str());

    delay(100);  // Ekranın güncellenme sıklığı
  }
}

void setup() {
  Serial.begin(9600);
  ekran.begin(9600);  // EasyNextionLibrary başlatma

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
