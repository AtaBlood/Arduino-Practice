#include <Wire.h>  // I2C kütüphanesi
#include <Adafruit_BMP3XX.h>  // BMP3XX sensör kütüphanesi

#define BMP_SDA A4  // SDA pini (Analog pin A4)
#define BMP_SCL A5  // SCL pini (Analog pin A5)

Adafruit_BMP3XX bmp;  // BMP3XX sensör nesnesi oluşturuluyor

void setup() {
  Serial.begin(9600);  // Seri haberleşme başlatılıyor
  Wire.begin();  // I2C bağlantısı başlatılıyor
  if (!bmp.begin_I2C(0x76)) {
    Serial.println("BMP388 sensörü bulunamadı. Bağlantıyı kontrol edin!");
    while (1);
  }
  Serial.println("BMP388 sensörüne bağlanıldı.");
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);  // Sıcaklık örnekleme ayarı
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);  // Basınç örnekleme ayarı
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);  // Veri güncelleme hızı
}

void loop() {
  if (!bmp.performReading()) {
    Serial.println("Sensör veri okuması başarısız!");
    return;
  }
  float temperature = bmp.temperature;  // Sıcaklık okuma
  float pressure = bmp.pressure / 100.0;  // Basınç okuma (Pa cinsinden)
  
  Serial.print("Sıcaklık: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Basınç: ");
  Serial.print(pressure);
  Serial.println(" hPa");
  
  delay(1000);  // 1 saniye bekleme
}