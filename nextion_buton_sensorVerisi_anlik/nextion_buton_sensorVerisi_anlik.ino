#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>  // SoftwareSerial kütüphanesini dahil edin

#define ONE_WIRE_BUS 8
#define RX_PIN 10 // Nextion ekranının TX pinine bağlanacak Arduino pini
#define TX_PIN 11  // Nextion ekranının RX pinine bağlanacak Arduino pini
#define BUZZER_PIN 7 // Buzzer pinini tanımlayın

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
SoftwareSerial nextion(RX_PIN, TX_PIN);  // SoftwareSerial nesnesini oluşturun

int manualTemperature = 0; // Başlangıç değeri

void setup() {
  Serial.begin(9600);        // Arduino seri iletişimi başlat
  nextion.begin(9600);       // Nextion ekranı ile seri iletişim başlat
  sensors.begin();
  pinMode(BUZZER_PIN, OUTPUT); // Buzzer pinini çıkış olarak ayarla
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
  
  // Manuel sıcaklık değeri
  if (nextion.available()) {
    String receivedData = "";
    while (nextion.available()) {
      receivedData += char(nextion.read());
    }

    Serial.print("Received: ");
    Serial.println(receivedData);

    if (receivedData.indexOf("b0") != -1) {
      manualTemperature++;
    } else if (receivedData.indexOf("b1") != -1) {
      manualTemperature--;
    } else if (receivedData.indexOf("b3") != -1) {
      manualTemperature = 0;
    }

    // Manuel sıcaklık değeri güncelleme
    String manualTempStr = "t1.txt=\"" + String(manualTemperature) + " ";
    nextion.print(manualTempStr);
    nextion.write(176); // Derece sembolü için ASCII değeri
    nextion.print("C\"");
    nextion.write(0xff);
    nextion.write(0xff);
    nextion.write(0xff);

    // 30°C'yi geçtiğinde buzzer çalıştır
    if (manualTemperature >= 10) {
      digitalWrite(BUZZER_PIN, HIGH);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
  
  delay(1000);
}
