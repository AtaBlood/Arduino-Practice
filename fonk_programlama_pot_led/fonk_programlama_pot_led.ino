int pot1_sure,pot2_parlaklik;
void setup(){
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop(){
  pot1_sure=map(analogRead(A0), 0, 1023, 100, 1000);
  pot2_parlaklik=map(analogRead(A1), 0, 1023, 0, 255);
  LED_animasyon(pot1_sure,pot2_parlaklik);
}

void LED_animasyon(int sure,int parlaklik){
  analogWrite(9,1);
  analogWrite(10,1);
  analogWrite(11,1);
  delay(sure);
  digitalWrite(9,0);
  digitalWrite(10,0);
  digitalWrite(11,0);
  delay(sure);
}