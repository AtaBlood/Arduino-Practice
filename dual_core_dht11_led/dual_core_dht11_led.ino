#include "DHT.h"  // DHT kütüphanesini dahil et
#define DHTPIN 13  // DHT sensörünün bağlı olduğu pin
#define DHTTYPE DHT11  // Kullanılan DHT sensör tipi

const int led = 2;  // LED'in bağlı olduğu pin

DHT dht(DHTPIN, DHTTYPE);  // DHT sensörünü tanımla

// LED'in yanıp sönmesi için Task1 kodu
void Task1code(void * pvParameters) {
  Serial.print("Task1 çekirdeğinde çalışıyor: ");
  Serial.println(xPortGetCoreID());

  for(;;) {
    digitalWrite(led, HIGH);  // LED'i yak
    delay(1000);
    digitalWrite(led, LOW);  // LED'i söndür
    delay(1000);
  } 
}

// DHT11 sensöründen sıcaklık ve nem okuması için Task2 kodu
void Task2code(void * pvParameters) {
  Serial.print("Task2 çekirdeğinde çalışıyor: ");
  Serial.println(xPortGetCoreID());

  for(;;) {
    float nem = dht.readHumidity();  // Nem değerini oku
    float sicaklik = dht.readTemperature();  // Sıcaklık değerini oku (Celsius)
    float sicaklikF = dht.readTemperature(true);  // Sıcaklık değerini oku (Fahrenheit)

    if (isnan(nem) || isnan(sicaklik) || isnan(sicaklikF)) {
      Serial.println("DHT sensöründen okuma başarısız!");
    } else {
      Serial.print("Nem: ");
      Serial.print(nem);
      Serial.print("%\t");
      Serial.print("sicaklik°C: ");
      Serial.print(sicaklik);
      Serial.print(" °C\t");
      Serial.print("sicaklik°F: ");
      Serial.print(sicaklikF);
      Serial.println(" °F");
    }
    delay(2000);  // 2 saniye bekle
  }
}

void setup() {
  Serial.begin(115200);  // Seri haberleşmeyi başlat
  pinMode(led, OUTPUT);  // LED pinini çıkış olarak ayarla
  dht.begin();  // DHT sensörünü başlat

  // LED yanıp sönmesi için Task1'i çekirdek 1'e sabitle
  xTaskCreatePinnedToCore(
    Task1code,  // Görev fonksiyonu
    "Task1",  // Görev adı
    10000,  // Yığın boyutu
    NULL,  // Görev parametreleri
    1,  // Görev önceliği
    NULL,  // Görev tanıtıcısı
    1  // Çekirdek numarası
  ); 
  delay(500); 

  // DHT11 sensöründen okuma yapmak için Task2'yi çekirdek 0'a sabitle
  xTaskCreatePinnedToCore(
    Task2code,  // Görev fonksiyonu
    "Task2",  // Görev adı
    10000,  // Yığın boyutu
    NULL,  // Görev parametreleri
    1,  // Görev önceliği
    NULL,  // Görev tanıtıcısı
    0  // Çekirdek numarası
  ); 
  delay(500); 
}

void loop() {
  // Döngüde yapılacak bir şey yok
}
