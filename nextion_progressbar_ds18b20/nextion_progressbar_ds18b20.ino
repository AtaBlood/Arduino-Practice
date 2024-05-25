#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>  // SoftwareSerial kütüphanesini dahil edin

#define ONE_WIRE_BUS 8
#define RX_PIN 10 // Nextion ekranının TX pinine bağlanacak Arduino pini
#define TX_PIN 11  // Nextion ekranının RX pinine bağlanacak Arduino pini

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
    
    nextion.print("j0.val=0");
    nextion.write(0xff);
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
    
    // Progress bar değerini ayarla
    int progressValue = map(temperatureC, 0, 100, 0, 100); // Sıcaklığı 0-100 aralığına eşle
    String progressStr = "j0.val=" + String(progressValue);
    nextion.print(progressStr);
    nextion.write(0xff);
    nextion.write(0xff);
    nextion.write(0xff);
  }
  
  delay(1000);
}
