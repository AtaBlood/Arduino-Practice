#include <SoftwareSerial.h>

#define RX_PIN 10  // Nextion ekranının TX pinine bağlanacak Arduino pini
#define TX_PIN 11  // Nextion ekranının RX pinine bağlanacak Arduino pini
#define BUZZER_PIN 12 // Buzzer pini

SoftwareSerial nextion(RX_PIN, TX_PIN);  // SoftwareSerial nesnesini oluşturun

int currentTemperature = 0; // Başlangıç sıcaklık değeri

void setup() {
  Serial.begin(9600);        // Arduino seri iletişimi başlat
  nextion.begin(9600);       // Nextion ekranı ile seri iletişim başlat
  pinMode(BUZZER_PIN, OUTPUT); // Buzzer pini çıkış olarak ayarla

  // Başlangıç sıcaklık değerini ekranda göster
  updateTemperature();
}

void loop() {
  if (nextion.available()) {
    String cmd = nextion.readStringUntil('\xFF'); // Tam bir komutu al
    
    // Komutun geçerli olup olmadığını kontrol et ve işleme al
    if (cmd.length() >= 4 && cmd[0] == 0x23 && cmd[1] == 0x02 && cmd[2] == 0x54 && cmd[3] == 0x31) {
      char action = cmd[4]; // Komutun 5. karakteri eylemi belirtir
      Serial.print("Received action: ");
      Serial.println(action, HEX); // Gelen komutu seri monitörde göster (Hex formatında)

      if (action == 0x01) {  // Artırma butonuna basıldı
        currentTemperature++;
        updateTemperature();
      } else if (action == 0x02) {  // Azaltma butonuna basıldı
        currentTemperature--;
        updateTemperature();
      } else if (action == 0x03) {  // Reset butonuna basıldı
        currentTemperature = 0;
        updateTemperature();
      }
    }
  }

  // Sıcaklık 30 °C'ye ulaştığında buzzer'ı çal
  if (currentTemperature >= 30) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(100);  // Döngüyü yavaşlat
}

void updateTemperature() {
  // Sıcaklık değerini ekranda güncelle
  String tempStr = "t1.txt=\"" + String(currentTemperature) + " ";
  nextion.print(tempStr);
  nextion.write(176);   
  nextion.print("C\"");
  nextion.write(0xff);   
  nextion.write(0xff);
  nextion.write(0xff);

  // Progress bar değerini güncelle
  int progressValue = map(currentTemperature, 0, 100, 0, 100); // Sıcaklığı 0-100 aralığına eşle
  String progressStr = "j0.val=" + String(progressValue);
  nextion.print(progressStr);
  nextion.write(0xff);   // Nextion komutu bitirme karakterleri
  nextion.write(0xff);
  nextion.write(0xff);
}
