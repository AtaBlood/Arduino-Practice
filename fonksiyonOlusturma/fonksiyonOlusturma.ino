int kled=2;
int yled=3;
int sled=4;
int buzzer=5;
int buton=8;
int ldr =A0;
int zaman;

void setup(){
  Serial.begin(9600);
  pinMode(kled,OUTPUT);
  pinMode(yled,OUTPUT);
  pinMode(sled,OUTPUT);
  pinMode(buzzer,OUTPUT);

  pinMode(buton,INPUT);
  pinMode(ldr,INPUT);
}

void loop(){
  int ldrdeger=toplam();
  Serial.println(ldrdeger);

}

int toplam(){
  int ldrdeger=analogRead(ldr);
  delay(1000);
  return ldrdeger;
  }







