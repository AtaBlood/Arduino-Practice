#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 8

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  
  float temperatureC = sensors.getTempCByIndex(0);
  
  if (temperatureC == -127.00) {
    Serial.println("Hata: Sensör okunamadı!");
  } else {
    Serial.print("Sıcaklık: ");
    Serial.print(temperatureC);
    Serial.println(" °C");  
  }
   delay(1000);
}
