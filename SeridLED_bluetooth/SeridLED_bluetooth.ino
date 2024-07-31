#include <Adafruit_NeoPixel.h>
int veri;
int NeopixelPin=9;
#define PIXELSAYISI 11
Adafruit_NeoPixel SERIDLED(PIXELSAYISI, NeopixelPin, NEO_GRB+ NEO_KHZ800);
void setup(){
  Serial.begin(9600);  //seri haberleşmeyi başlatıyoruz 
  SERIDLED.begin();
}

void loop(){
  if(Serial.available()>0){ //seri haberleşmeden veri gelmesini bekliyoruz
    veri=Serial.read();     //seri haberleşmedn gelen veriyi okuyoruz 
  }
  if(veri=='k'){              //seri haberleşmeden k harfi gelirse bu kısmı çalıştır
    for(int i=0;i<11;i++){
      SERIDLED.setPixelColor(i,SERIDLED.Color(150,0,0));
      SERIDLED.show();
      delay(50);
    }
  }
  else if(veri=='y'){
    for(int i=0;i<11;i++){
      SERIDLED.setPixelColor(i,SERIDLED.Color(0,150,0));
      SERIDLED.show();
      delay(50);
    }
  }
    else if(veri=='m'){
    for(int i=0;i<11;i++){
      SERIDLED.setPixelColor(i,SERIDLED.Color(0,0,150));
      SERIDLED.show();
      delay(50);
    }
  }
}


//bluetooth ile şerit led kontrolü telefona bluetooth control yaz uygulamayı indir ve 
//bluetooth modülüne bağlan şifresini gir ve renkleri kontrol et.
//Terminal kullanarak k,y,m yazarak renklerini değiştir







