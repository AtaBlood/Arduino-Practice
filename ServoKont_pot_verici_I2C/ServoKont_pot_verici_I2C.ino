#include <Wire.h> //I2C haberleşmesini sağlayacak kütüphane 
int potpin = A0;
int val;
int alici = 0x05; // 5 numaralı adres girdik alıcı ile haberlşeme mümkün
                  //yani benim bu vericimi master yapıyor, diğerlerini slave yapıyor 
void setup(){
  Wire.begin(); //wire kütüphanesindeki I2C haberleşmemizi başlatıyoruz 
}
void loop(){
  val = analogRead(potpin); 
  val = map(val,0,1023,0,180);
  Wire.beginTransmission(alici); //bu adresteki alıcıya veri gönderimi yapcağım 
  Wire.write(val); //bu adrese bir val değerini gönder 
  Wire.endTransmission(); //haberleşmeyi bitir
  delay(50);
}

//VERİCİ KODU//