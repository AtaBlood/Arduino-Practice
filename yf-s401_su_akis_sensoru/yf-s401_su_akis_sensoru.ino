// YF-S401 Su Akış Sensörü
// VCC -> 5V
// GND -> GND
// Sinyal -> Dijital pin (örneğin D2)

const int sensorPin = 2;  // Sensör sinyal pini (dijital pin 2)
volatile int pulseCount = 0;  // Darbe sayısı

unsigned long oldTime = 0;
float calibrationFactor = 7.5;  // Kalibrasyon faktörü (her litredeki darbe sayısı)
float flowRate = 0.0;
unsigned int flowMilliLitres = 0;
unsigned long totalMilliLitres = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
}

void loop() {
  if ((millis() - oldTime) > 1000) {  // Her saniyede bir hesapla
    detachInterrupt(digitalPinToInterrupt(sensorPin));

    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    oldTime = millis();
    pulseCount = 0;

    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;

    Serial.print("Akış Hızı: ");
    Serial.print(flowRate);  // Litre/dakika
    Serial.print(" L/min");
    Serial.print("  Bu Saniyedeki Akış: ");
    Serial.print(flowMilliLitres);
    Serial.print(" mL/Sec");
    Serial.print("  Toplam Akış: ");
    Serial.print(totalMilliLitres);
    Serial.println(" mL");

    attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
  }
}

void pulseCounter() {
  pulseCount++;
}
