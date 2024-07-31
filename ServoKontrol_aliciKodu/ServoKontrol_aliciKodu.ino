#include <Servo.h>
Servo myservo;
int val;
void setup(){
  myservo.attach(9);
  Serial.begin(9600);
}
void loop(){
  if(Serial.available()>0){
    val=Serial.read();
    myservo.write(val);
  }
  delay(15);
}


//UART ÜZERİNDEN HABERLEŞME(RX-TX)