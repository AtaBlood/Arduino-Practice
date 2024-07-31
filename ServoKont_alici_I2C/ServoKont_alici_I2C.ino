#include <Wire.h>
#include <Servo.h>
Servo myservo;
int val;

void setup(){
  myservo.attach(9);
  Wire.begin(5); // slave adresi 5 yapıldı 
  Wire.onReceive(oku); 
}

void oku(int sayi){
  val=Wire.read();
}

void loop(){
  myservo.write(val);
}

//I2C haberleşme verici kodu 