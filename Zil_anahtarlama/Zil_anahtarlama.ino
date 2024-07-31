const int buttonPin = 7;    
const int buzzerPin = 8;   
const int girisPin = 9;     

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(buzzerPin, OUTPUT);       
  pinMode(girisPin, OUTPUT);        
  
  digitalWrite(buzzerPin, LOW);
  digitalWrite(girisPin, LOW);

  Serial.begin(9600);
}

void loop() {
  bool buttonDurum = digitalRead(buttonPin);

  if (buttonDurum == LOW) { 
    digitalWrite(buzzerPin, 1); 
    digitalWrite(girisPin, 0); 
    Serial.println("Giriş pini: 5V"); 
  } else {
    digitalWrite(buzzerPin, 0); 
    digitalWrite(girisPin, 1); 
    Serial.println("Giriş pini: 0V"); 
  }
  delay(1000);
}