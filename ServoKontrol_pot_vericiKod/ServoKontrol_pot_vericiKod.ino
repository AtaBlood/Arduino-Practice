int potpin =A0;
int val;
void setup(){
  Serial.begin(9600);
}

void loop(){
  val =analogRead(potpin);
  val=map(val, 0, 1023, 0, 180);
  Serial.write(val);
  delay(15);
}