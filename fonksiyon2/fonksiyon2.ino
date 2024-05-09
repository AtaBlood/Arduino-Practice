int kled=2;
int yled=3;
int sled=4;
int buzzer=5;
int buton=8;
int ldr=A0;
int zaman=500;
void setup() {
  Serial.begin(9600);
  pinMode(kled,OUTPUT);
  pinMode(yled,OUTPUT);
  pinMode(sled,OUTPUT);
  pinMode(buzzer,OUTPUT);

  pinMode(buton,INPUT);
  pinMode(ldr,INPUT);
}

void loop() {
int toplamdgr=toplam(5, 4);
Serial.println(toplamdgr);
while(1);
}

int toplam(int a, int b){
  int sonuc=a+b;
  return sonuc;
}
