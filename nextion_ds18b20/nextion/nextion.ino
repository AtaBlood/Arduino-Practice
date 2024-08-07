#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>  // SoftwareSerial kütüphanesini dahil edin

#define ONE_WIRE_BUS 8
#define RX_PIN 50 // Nextion ekranının TX pinine bağlanacak Arduino pini
#define TX_PIN 51  // Nextion ekranının RX pinine bağlanacak Arduino pini

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
SoftwareSerial nextion(RX_PIN, TX_PIN);  // SoftwareSerial nesnesini oluşturun

void setup() {
  Serial.begin(9600);        // Arduino seri iletişimi başlat
  nextion.begin(9600);       // Nextion ekranı ile seri iletişim başlat
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  
  float temperatureC = sensors.getTempCByIndex(0);
  
  if (temperatureC == -127.00) {
    Serial.println("Hata: Sensör okunamadı!");
    nextion.print("t0.txt=\"Hata\"");
    nextion.write(0xff);   // Nextion komutu bitirme karakterleri
    nextion.write(0xff);
    nextion.write(0xff);
  } else {
    Serial.print("Sıcaklık: ");
    Serial.print(temperatureC);
    Serial.println(" °C");  
    
    // Nextion ekranına sıcaklık verisini gönder
    String tempStr = "t0.txt=\"" + String(temperatureC) + " ";
    nextion.print(tempStr);
    nextion.write(176);   // Derece sembolü için ASCII değeri
    nextion.print("C\"");
    nextion.write(0xff);   // Nextion komutu bitirme karakterleri
    nextion.write(0xff);  
    nextion.write(0xff);
  }
  
  delay(1000);
}
