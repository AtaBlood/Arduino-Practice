#define led 13
#define button 3
boolean btn_durum;

void setup(){
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
}

void loop(){
  btn_durum = (digitalRead(button));

  if(btn_durum==1){
    digitalWrite(led, 1);
  }
  else {
    digitalWrite(led, 0);
  }

}