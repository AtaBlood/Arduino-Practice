const int analogPin = A1; // Analog pin A0'ı tanımlıyoruz
int analogValue = 0;      // Analog okunan değeri depolamak için değişken
float voltage = 0.0;      // Voltajı depolamak için değişken

void setup() {
  Serial.begin(9600); // Seri haberleşmeyi başlat
}

void loop() {
  analogValue = analogRead(analogPin); // A0 pininden analog değeri oku
  voltage = analogValue * (5.0 / 1023.0); // Analog değeri voltaja çevir

  Serial.print("Analog Değer: ");
  Serial.print(analogValue);
  Serial.print(" - Voltaj: ");
  Serial.println(voltage, 3); // Voltajı 3 ondalık basamakla yazdır

  delay(1000); // 1 saniye bekle
}
