int sayac;
unsigned long simdiki_zaman;
unsigned long onceki_zaman=0;
unsigned long onceki_zaman_yesil=0;
#define kirmizi 2
#define yesil 3
bool led_durum = HIGH;
bool led_durum_yesil = HIGH;

void setup(){
  pinMode(kirmizi, OUTPUT);
  pinMode(yesil,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  simdiki_zaman = millis();

  if(simdiki_zaman-onceki_zaman>=2000){
    Serial.print("burasi ifin icerisi:");
    Serial.println(simdiki_zaman);
    led_durum=!led_durum;
    digitalWrite(kirmizi,led_durum);
    onceki_zaman=simdiki_zaman;
  }

  if(simdiki_zaman-onceki_zaman_yesil>=1000){
    Serial.print("burasi yesil ifin ici:");
    Serial.println(simdiki_zaman);
    led_durum_yesil=!led_durum_yesil;
    digitalWrite(yesil,led_durum_yesil);
    onceki_zaman_yesil=simdiki_zaman;
  }
}