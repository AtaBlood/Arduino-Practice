#include <SoftwareSerial.h>
#define Rx 7
#define Tx 8

SoftwareSerial Bluetooth(Rx,Tx);

void setup(){
  Serial.begin(9600);
  Bluetooth.begin(9600);
  Serial.println("kod icin hazir ");
  pinMode(Rx, INPUT);
  pinMode(Tx,OUTPUT);
}

void loop(){
  if(Bluetooth.available()){ //bluetooth dan bir veri gelirse 
    int deger=Bluetooth.read(); //deger diye bir değişken tanımla ve bunu bluetooth dan gelen değişkeni oku bu deger at
    Serial.write((char) deger); //sonrada ekranda yazdır
  }
  if(Serial.available()){ //eüer seri ekrandan bir veri gelirse 
    int deger = Serial.read(); //deger diye bir değişken oluştur buna okuduktan sonra deger yaz 
    Bluetooth.print((char)deger);//sonrada bunu bluetooth a yaz 
  }
}


//Serial monitörden message yerine (AT) bluetooth modülü hazır
//2.komut olarak aynı yere şifresini soracak olursak message yerine (AT+PSWD) yazılmalı 
//ismini değiştirmek istersek eğer (AT+NAME=buraya hangi ismi yazmak isterseniz)
//şifre değiştirmek için ise (AT+PSWD=4321) yazarak şifresini 4321 yapmış oluruz 