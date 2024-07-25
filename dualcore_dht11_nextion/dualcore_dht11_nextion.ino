#include <Nextion.h>
#include <Arduino.h>
#include "EasyNextionLibrary.h"
#include "DHT.h"

#define DHTPIN 13  // DHT sensörünün bağlı olduğu pin
#define DHTTYPE DHT11  // Kullanılan DHT sensör tipi

DHT dht(DHTPIN, DHTTYPE);

TaskHandle_t Task1;
TaskHandle_t Task2;

EasyNex ekran(Serial);

volatile float temperature = 0.0;
volatile float humidity = 0.0;

void Task1kodu(void *pvParameters) {
  Serial.print("task1'in calisacagi core: ");
  Serial.println(xPortGetCoreID());

  for (;;) {
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("DHT sensöründen okuma başarısız!");
    } else {
      Serial.print("Nem: ");
      Serial.print(humidity);
      Serial.print("%\t");
      Serial.print("Sıcaklık: ");
      Serial.print(temperature);
      Serial.println(" °C");
    }
    delay(2000);
  }
}

void Task2kodu(void *pvParameters) {
  Serial.print("task2'nin calisacagi core: ");
  Serial.println(xPortGetCoreID());

  for (;;) {
    // Nem nesnesini güncelle
    String humidityStr = "t0.txt=\"" + String(humidity) + " %\"";
    ekran.writeStr(humidityStr.c_str());

    // Sıcaklık nesnesini güncelle
    String temperatureStr = "t1.txt=\"" + String(temperature) + " C\"";
    ekran.writeStr(temperatureStr.c_str());

    delay(500);  // Ekranın güncellenme sıklığı
  }
}

void setup() {
  Serial.begin(9600);
  ekran.begin(9600);  // EasyNextionLibrary başlatma

  dht.begin();

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
