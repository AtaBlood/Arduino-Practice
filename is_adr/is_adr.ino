#include <OneWire.h> // OneWire kütüphanesini dahil eder
#include <DallasTemperature.h> // Dallas Temperature kütüphanesini dahil eder
#include <SoftwareSerial.h> // SoftwareSerial kütüphanesini dahil eder

// Sensör veri pini ve Nextion ekran pinleri tanımlanıyor
#define ONE_WIRE_BUS 8 // DS18B20 sıcaklık sensörünün veri pini
#define RX_PIN 10 // Nextion ekranının TX pini bağlantısı yapılacak arduino RX pini
#define TX_PIN 11 // Nextion ekranının RX pini bağlantısı yapılacak arduino TX pini
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
void nextionVerisiGonder(string veriTipi,string veriAdresi,String veri) {
  String sicaklikStr = "t1.txt=\"" + String(manuelSicaklik, 2) + " "; // Manuel sıcaklık değerini stringe dönüştürür
  nextion.print(sicaklikStr); // Nextion ekranına gönderir
  nextion.write(176); // Derece sembolü gönderir
  nextion.print("C\"");
  nextion.write(0xff); // Komut sonlandırma baytları
  nextion.write(0xff);
  nextion.write(0xff);

  int progressDegeri = map(manuelSicaklik, 0, 100, 0, 100); // Manuel sıcaklık değerini 0-100 arasında eşler
  String progressStr = "j0.val=" + String(progressDegeri); // Eşlenen değeri stringe dönüştürür
  nextion.print(progressStr); // Nextion ekranına gönderir
  nextion.write(0xff); // Komut sonlandırma baytları
  nextion.write(0xff);
  nextion.write(0xff);

  String sensorSicaklikStr = "t0.txt=\"" + String(sensorSicakligi, 2) + " "; // Sensör sıcaklık değerini stringe dönüştürür
  nextion.print(sensorSicaklikStr); // Nextion ekranına gönderir
  nextion.write(176); // Derece sembolü gönderir.ASCII tablosunda, 176 numaralı karakter derece sembolüne karşılık gelir.
  nextion.print("C\"");
  nextion.write(0xff); // Komut sonlandırma baytları
  nextion.write(0xff);
  nextion.write(0xff);
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
  nextionVerisiGonder(); // Nextion ekranına veri gönderir
  buzzerKontrol(); // Buzzer'ı kontrol eder
  delay(1000); // 1 saniye bekler
}
