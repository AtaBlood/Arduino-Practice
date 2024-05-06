#include <DHT.h>

#define DHTPIN 2       // DHT sensörünün bağlı olduğu pin
#define DHTTYPE DHT11  // DHT sensör tipi

DHT dht_sensor(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Sensörden verileri oku
  float humidity = dht_sensor.readHumidity();
  float temperature = dht_sensor.readTemperature();
  float heatIndex = dht_sensor.computeHeatIndex(temperature, humidity);

  // Verileri seri porta yazdır
  Serial.print("Nem: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Sıcaklık: ");
  Serial.print(temperature);
  Serial.print("°C\t");
  Serial.print("Isı İndeksi: ");
  Serial.print(heatIndex);
  Serial.println("°C");

  delay(5000);  // 1 saniye bekle
}