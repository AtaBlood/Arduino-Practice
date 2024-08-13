#include "LoRa_E22.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 4);
LoRa_E22 E22(&mySerial);
#define M0 7
#define M1 6
#define buzzer 9
struct veriler {
  char deger[15];
} data;
void setup() {
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  Serial.begin(9600);
  E22.begin();
  delay(500);
  Serial.begin(9600);
  Serial.println("KART BAŞLADI");
}

void melodi() {
  // Melodi notaları ve süreleri (milisaniye cinsinden)
  int melodi[] = {
    330, 200, // E4
    392, 200, // G4
    440, 200, // A4
    494, 200, // B4
    523, 400, // C5
    494, 200, // B4
    440, 200, // A4
    392, 200, // G4
    330, 400  // E4
  };

  // Melodiyi oynatma
  for (int i = 0; i < sizeof(melodi) / sizeof(melodi[0]); i += 2) {
    int frekans = melodi[i];
    int sure = melodi[i + 1];
    tone(buzzer, frekans, sure);
    delay(sure * 1.3); // Nota süresinin %130'u kadar bekle
  }
  noTone(buzzer); // Buzzer'ı kapat
}



void loop() {
  while (E22.available()  > 1) {
    ResponseStructContainer rsc = E22.receiveMessage(sizeof(veriler));
    
    struct veriler data = *(veriler*) rsc.data;
    Serial.println("Gelen Mesaj: ");
    Serial.println(data.deger);
    melodi();
    melodi();
     
    rsc.close();
  }
  
}

//alıcıı 