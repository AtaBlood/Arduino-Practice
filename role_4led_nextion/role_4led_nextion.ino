#include <EasyNextionLibrary.h>

#define LED_PIN 2 // LED'in bağlı olduğu pin

EasyNex myNex(Serial2);

// Buton değeri için global değişken
int buttonState = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT); // LED pinini çıkış olarak ayarla
  digitalWrite(LED_PIN, LOW); // LED'i başlangıçta kapalı tut

  Serial.begin(9600);
  myNex.begin(9600);
}

void loop() {
  myNex.NextionListen(); // Nextion ekranından gelen verileri dinle

  // Butonun değerini oku
  buttonState = myNex.readNumber("bt1.val");

  checkButtonPress();
}

void checkButtonPress() {
  if (buttonState == 1) { // Butona basıldığında değer 1 olur
    digitalWrite(LED_PIN, HIGH); // LED'i yak
    delay(500); // LED'i bir süre yanık tut
    digitalWrite(LED_PIN, LOW); // LED'i söndür
    myNex.writeNum("bt1.val", 0); // Değeri sıfırla
    buttonState = 0; // Global değişkeni sıfırla
  }
}
