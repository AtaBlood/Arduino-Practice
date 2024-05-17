#include <EEPROM.h>

int kayit_adresi, kaydedilecek_veri;
int okunacak_adres, okunan_veri;

#define k_led 2
#define s_led 3
#define y_led 4
#define buton 8
int sayac;
void setup() {
  Serial.begin(9600);

  pinMode(k_led, OUTPUT);
  pinMode(s_led, OUTPUT);
  pinMode(y_led, OUTPUT);
  pinMode(buton,INPUT);

}

void loop() {
  int btn_durum=digitalRead(buton);
  if(btn_durum==1){
    sayac++;
    delay(1000);
    if(sayac>4){
      sayac=0;
    }
  kayit_adresi=10;
  kaydedilecek_veri=255;
  EEPROM.write(kayit_adresi,kaydedilecek_veri);
  delay(100);
  }

  okunacak_adres=10;
  okunan_veri=EEPROM.read(okunacak_adres);
  delay(10);
  Serial.println(okunan_veri);

  if(okunan_veri==1){
    digitalWrite(k_led,1);
    digitalWrite(s_led,1);
    digitalWrite(y_led,1);
  }

  else if(okunan_veri=2){
    digitalWrite(k_led,0);
    digitalWrite(s_led,0);
    digitalWrite(y_led,1);
  }

  else if(okunan_veri==3){
    digitalWrite(k_led,1);
    digitalWrite(s_led,0);
    digitalWrite(y_led,1);
  }
  else{
    digitalWrite(k_led,0);
    digitalWrite(s_led,0);
    digitalWrite(y_led,0);
  }

}
