#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

// Pin tanımları (ESP32'ye göre ayarlayın)
const int trigPin = 23;  // HC-SR04 trig pin
const int echoPin = 22;  // HC-SR04 echo pin
const int ledPin = 2;    // LED pin

// Değişkenler
int distance = 0;  // Mesafe değeri
bool ledStatus = false;  // LED durumu

// Mesafe sensörü görevi (Core 0)
void Task1(void *pvParameters) {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    for (;;) {
        // Mesafe ölçümü için tetikleme sinyali gönder
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        
        // Echo pininden mesafe verisini oku
        long duration = pulseIn(echoPin, HIGH);
        distance = duration * 0.034 / 2;  // Ses hızına göre mesafe hesaplama
        
        // Serial monitöre mesafe değerini yazdır
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
        
        vTaskDelay(pdMS_TO_TICKS(100)); // Örnek amaçlı gecikme
    }
}

// LED kontrol görevi (Core 1)
void Task2(void *pvParameters) {
    pinMode(ledPin, OUTPUT);
    
    for (;;) {
        // Core 0'dan gelen mesafe verisine göre LED'i kontrol etme
        
        // Örnek olarak her 50 cm'de LED'i yak ve söndür
        if (distance >= 50) {
            digitalWrite(ledPin, HIGH);
            ledStatus = true;
        } else {
            digitalWrite(ledPin, LOW);
            ledStatus = false;
        }
        
        // Serial monitöre LED durumunu yazdır
        Serial.print("LED Status: ");
        Serial.println(ledStatus ? "ON" : "OFF");
        
        vTaskDelay(pdMS_TO_TICKS(500)); // Örnek amaçlı gecikme
    }
}

void setup() {
    Serial.begin(9600);
    
    // FreeRTOS işletim sistemini başlat
    xTaskCreatePinnedToCore(Task1, "Task1", 10000, NULL, 1, NULL, 0); // Core 0
    xTaskCreatePinnedToCore(Task2, "Task2", 10000, NULL, 1, NULL, 1); // Core 1
}

void loop() {
    // Ana döngü, boş bırakılabilir veya başka işlemler eklenilebilir
}
