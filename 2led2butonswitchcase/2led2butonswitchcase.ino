byte kled=2;
byte yled=3;
byte btkirmizi=8;
byte btyesil=9;
int durum=0;
void setup() {
  Serial.begin(9600);
  pinMode(kled,OUTPUT);
  pinMode(yled,OUTPUT);
  pinMode(btkirmizi,INPUT);
  pinMode(btyesil,INPUT);
}

void loop() {
  int btkrmz = digitalRead(btkirmizi);
  int btysl = digitalRead(btyesil);

  if(btkrmz==1){
    durum=1;  
  }

  else if(btysl==1){
    durum=2;
  }

  else {

  }
Serial.println(durum);
delay(100);

    switch(durum){
      case 1:
      digitalWrite(kled,1);
      digitalWrite(yled,0);

      case 2:
      digitalWrite(yled,1);
      digitalWrite(kled,0);

      break;
      default:
      digitalWrite(kled,0);
      digitalWrite(yled,0);
    }


}
