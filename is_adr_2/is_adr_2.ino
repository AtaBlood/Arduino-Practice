#include <OneWire.h> // OneWire kütüphanesini dahil eder
#include <DallasTemperature.h> // Dallas Temperature kütüphanesini dahil eder
#include <SoftwareSerial.h> // SoftwareSerial kütüphanesini dahil eder

// Sensör veri pini ve Nextion ekran pinleri tanımlanıyor
#define ONE_WIRE_BUS 8 // DS18B20 sıcaklık sensörünün veri pini
#define RX_PIN 50 // Nextion ekranının TX pini bağlantısı yapılacak arduino RX pini
#define TX_PIN 51 // Nextion ekranının RX pini bağlantısı yapılacak arduino TX pini
#define BUZZER_PIN 7 // Buzzer'ın bağlı olduğu pin

OneWire oneWire(ONE_WIRE_BUS); // OneWire nesnesi oluşturulur
DallasTemperature sensors(&oneWire); // Dallas Temperature nesnesi oluşturulur
SoftwareSerial nextion(RX_PIN, TX_PIN); // SoftwareSerial nesnesi oluşturulur

float sensorSicakligi = 0.0; // Sensörden okunan sıcaklık değeri
float manuelSicaklik = 0.0; // Manuel olarak ayarlanan sıcaklık değeri

void setup() {
  Serial.begin(9600); // Seri haberleşmeyi başlatır
  nextion.begin(9600); // Nextion ekranı ile seri haberleşmeyi başlatır
  sensors.begin(); // Dallas Temperature sensörünü başlatır
  pinMode(BUZZER_PIN, OUTPUT); // Buzzer pini çıkış olarak ayarlanır
}

// Sensörden sıcaklık verisini okuyan fonksiyon
void sensordenSicaklikOku() {
  sensors.requestTemperatures(); // Sensörden sıcaklık değerini ister
  sensorSicakligi = sensors.getTempCByIndex(0); // Sensörden okunan sıcaklık değeri alınır
  Serial.print("Sensör Sıcaklık: "); // Seri monitöre sıcaklık değeri yazdırılır
  Serial.print(sensorSicakligi);
  Serial.println(" °C");
}

// Nextion ekranından veri alan fonksiyon
void nextionVerisiAl() {
  if (nextion.available()) { // Nextion'dan veri gelip gelmediğini kontrol eder
    String gelenVeri = ""; // Gelen veriyi depolamak için bir string oluşturur
    while (nextion.available()) { // Nextion'dan veri gelmeye devam ettiği sürece
      char c = nextion.read(); // Bir karakter okur
      gelenVeri += c; // Karakteri stringe ekler
    }
    Serial.println(gelenVeri); // Gelen veriyi seri monitöre yazdırır

    // Gelen veriyi kontrol eder ve uygun işlemi yapar
    if (gelenVeri.indexOf("b0") != -1) { // Eğer "b0" (artırma butonu) bilgisi geldiyse
      manuelSicaklik++; // Manuel sıcaklık değerini artırır
    } else if (gelenVeri.indexOf("b1") != -1) { // Eğer "b1" (azaltma butonu) bilgisi geldiyse
      manuelSicaklik--; // Manuel sıcaklık değerini azaltır
    } else if (gelenVeri.indexOf("b2") != -1) { // Eğer "b2" (tamam butonu) bilgisi geldiyse
      sensorSicakligi = manuelSicaklik; // Sensör sıcaklık değerini manuel sıcaklık değeri ile günceller
    } else if (gelenVeri.indexOf("b3") != -1) { // Eğer "b3" (sıfırlama butonu) bilgisi geldiyse
      manuelSicaklik = 0; // Manuel sıcaklık değerini sıfırlar
    }
  }
}

// Nextion ekranına veri gönderen fonksiyon
void nextionVerisiGonder(String veriTipi, String veriAdresi, String veri) 

{
  if (veriTipi == "txt") {
    // Ekranda yazı güncelleme işlemi
    String komut = veriAdresi + ".txt=\"" + veri + "\""; // Text güncelleme komutu oluştur
    nextion.print(komut); // Komutu gönder
    nextion.write(0xff); // Komut sonlandırma baytları
    nextion.write(0xff);
    nextion.write(0xff);
  } else if (veriTipi == "val") {
    // Ekranda değer güncelleme işlemi
    String komut = veriAdresi + ".val=" + veri; // Değer güncelleme komutu oluştur
    nextion.print(komut); // Komutu gönder
    nextion.write(0xff); // Komut sonlandırma baytları
    nextion.write(0xff);
    nextion.write(0xff);
  } else {
    // Bilinmeyen veri tipi
    Serial.println("Hatalı veri tipi");
  }
}



// Buzzer kontrol eden fonksiyon
void buzzerKontrol() {
  if (manuelSicaklik >= 5) { // Eğer manuel sıcaklık değeri 5°C veya üstündeyse
    digitalWrite(BUZZER_PIN, HIGH); // Buzzer'ı açar
  } else {
    digitalWrite(BUZZER_PIN, LOW); // Buzzer'ı kapatır
  }
}

// Döngüde her işlev çağrılıyor
void loop() {
  sensordenSicaklikOku(); // Sensör sıcaklık değerini okur
  nextionVerisiAl(); // Nextion ekranından veri alır

  // Manuel sıcaklık değerini Nextion ekranına gönder
  nextionVerisiGonder("txt", "t1", String(manuelSicaklik, 2) + " °C");

  // İlerleme çubuğu değerini Nextion ekranına gönder
  int progressDegeri = map(manuelSicaklik, 0, 100, 0, 100); // Manuel sıcaklık değerini 0-100 arasında eşler
  nextionVerisiGonder("val", "n0", String(progressDegeri));

  // Sensör sıcaklık değerini Nextion ekranına gönder
  nextionVerisiGonder("txt", "t0", String(sensorSicakligi, 2) + " °C");

  buzzerKontrol(); // Buzzer'ı kontrol eder
  delay(1000); // 1 saniye bekler
}
