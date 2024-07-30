const int buttonPin = 7;    
const int buzzerPin = 8;   
const int inputPin = 9;     

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(buzzerPin, OUTPUT);       
  pinMode(inputPin, OUTPUT);        
  
  digitalWrite(buzzerPin, LOW);
  digitalWrite(inputPin, LOW);

  Serial.begin(9600);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) { 
    digitalWrite(buzzerPin, 1); 
    digitalWrite(inputPin, 0); 
    Serial.println("Giriş pini: 5V"); 
  } else {
    digitalWrite(buzzerPin, 0); 
    digitalWrite(inputPin, 1); 
    Serial.println("Giriş pini: 0V"); 
  }
  delay(1000);
}