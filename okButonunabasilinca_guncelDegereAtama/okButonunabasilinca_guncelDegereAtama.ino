#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

#define ONE_WIRE_BUS 8
#define RX_PIN 10
#define TX_PIN 11
#define BUZZER_PIN 7

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
SoftwareSerial nextion(RX_PIN, TX_PIN);

float sensorTemperature = 0.0;
float manualTemperature = 0.0;

void setup() {
  Serial.begin(9600);
  nextion.begin(9600);
  sensors.begin();
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  sensors.requestTemperatures();
  sensorTemperature = sensors.getTempCByIndex(0);

  // Sensör sıcaklık değerini seri monitöre yazdır
  Serial.print("Sensör Sıcaklık: ");
  Serial.print(sensorTemperature);
  Serial.println(" °C");

  // Nextion'dan gelen veriyi oku
  if (nextion.available()) {
    String receivedData = "";
    while (nextion.available()) {
      char c = nextion.read();
      receivedData += c;
    }
    Serial.println(receivedData);

    // Veriyi kontrol et ve işle
    if (receivedData.indexOf("b0") != -1) {
      manualTemperature++;
    } else if (receivedData.indexOf("b1") != -1) {
      manualTemperature--;
    } else if (receivedData.indexOf("b2") != -1) {
      sensorTemperature = manualTemperature;
    } else if (receivedData.indexOf("b3") != -1) {
      manualTemperature = 0;
    }

    // Güncellenmiş sıcaklık değerini ve progress barı Nextion'a gönder
    String tempStr = "t1.txt=\"" + String(manualTemperature, 2) + " ";
    nextion.print(tempStr);
    nextion.write(176);   // Derece sembolü için ASCII değeri
    nextion.print("C\"");
    nextion.write(0xff);
    nextion.write(0xff);
    nextion.write(0xff);

    int progressValue = map(manualTemperature, 0, 100, 0, 100);
    String progressStr = "j0.val=" + String(progressValue);
    nextion.print(progressStr);
    nextion.write(0xff);
    nextion.write(0xff);
    nextion.write(0xff);
  }

  // Buzzer kontrolü
  if (manualTemperature >= 5) { // 30°C olarak değiştirildi
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Sensör sıcaklık değerini ekrana güncelle
  String sensorTempStr = "t0.txt=\"" + String(sensorTemperature, 2) + " ";
  nextion.print(sensorTempStr);
  nextion.write(176);
  nextion.print("C\"");
  nextion.write(0xff);
  nextion.write(0xff);
  nextion.write(0xff);

  delay(1000);
}
