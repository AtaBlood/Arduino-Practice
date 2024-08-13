#include <LoRa_E22.h>
#include <SoftwareSerial.h>
const int analogPin = A1; // Analog pin A0'ı tanımlıyoruz
int analogValue = 0;      // Analog okunan değeri depolamak için değişken
float voltage = 0.0;      // Voltajı depolamak için değişken



SoftwareSerial mySerial(3,4);
LoRa_E22 E22(&mySerial);
#define M0 7
#define M1 6
#define zilGiris 10
struct veriler {   
 char deger[15];
} data;
void setup() {
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  Serial.begin(9600);
  E22.begin();
  delay(500);
}

void gonder()
{
  sprintf(data.deger,"Zil Çaldı");
  ResponseStatus rs = E22.sendFixedMessage(0, 2, 18, &data, sizeof(veriler));
  Serial.println(rs.getResponseDescription());
  delay(2000);
}

void loop() {
  analogValue = analogRead(analogPin); // A0 pininden analog değeri oku
  voltage = analogValue * (5.0 / 1023.0); // Analog değeri voltaja çevir
  if(voltage==0)
  {
    gonder();
    Serial.println(voltage);
  }
}