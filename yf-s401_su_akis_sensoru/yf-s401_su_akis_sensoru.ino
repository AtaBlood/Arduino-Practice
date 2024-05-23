const int sensorPin = 2;          // Sensör sinyal pini (dijital pin 2)
volatile int pulseCount = 0;      // Darbe sayısı

unsigned long oldTime = 0;
float calibrationFactor = 7.5;    // Kalibrasyon faktörü (her litredeki darbe sayısı)
float flowRate = 0.0;
unsigned int flowMilliLitres = 0;
unsigned long totalMilliLitres = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
}

void loop() {
  unsigned long currentTime = millis();
  if ((currentTime - oldTime) > 1000) { 
    detachInterrupt(digitalPinToInterrupt(sensorPin));

    flowRate = ((1000.0 / (currentTime - oldTime)) * pulseCount) / calibrationFactor;
    oldTime = currentTime;
    pulseCount = 0;

    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;

    printFlowInfo(flowRate, flowMilliLitres, totalMilliLitres);

    attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
  }
}

void pulseCounter() {
  pulseCount++;
}

void printFlowInfo(float flowRate, unsigned int flowMilliLitres, unsigned long totalMilliLitres) {
  Serial.print("Akış Hızı: ");
  Serial.print(flowRate);            // Litre/dakika
  Serial.print(" L/dakika  ");
  Serial.print("Bu Saniyedeki Akış: ");
  Serial.print(flowMilliLitres);
  Serial.print(" mL/saniye  ");
  Serial.print("Toplam Akış: ");
  Serial.print(totalMilliLitres);
  Serial.println(" mL");
}
