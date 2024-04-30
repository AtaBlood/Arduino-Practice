String mesaj="bir sayi girin:";
int gelenSayi;
void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.println(mesaj);
  while (Serial.available()==0){
  }
  gelenSayi=Serial.parseInt();

  Serial.print("girdiginiz syi:");
  Serial.print(gelenSayi);
  Serial.println("dir.");
}