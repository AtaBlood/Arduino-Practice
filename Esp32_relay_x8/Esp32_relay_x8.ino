const int relayPins[] = {13, 12, 14, 27, 26, 25, 33, 32};


void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(relayPins[i], OUTPUT);
  }
  Serial.begin(9600);    // Seri haberleşmeyi başlat
}

void loop() {
  for (int i = 0; i < 8; i++) {

    digitalWrite(relayPins[i], HIGH);
    delay(100); 

    digitalWrite(relayPins[i], LOW);
    delay(100); 
  }

}

