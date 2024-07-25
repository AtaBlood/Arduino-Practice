//ESP32 çift çekirdek kullanımı
TaskHandle_t Task1;
TaskHandle_t Task2;

//led pinleri
const int led1 = 2;
const int led2 = 4;

// Task1 kodu led1'i 2000ms de bir yakıp söndürecek
void Task1kodu(void *pvParameters) {
  Serial.print("Task1'in çalıştığı çekirdek: ");
  Serial.println(xPortGetCoreID());

  for (;;) {   // sonsuz döner
    digitalWrite(led1, HIGH);
    delay(10000);
    digitalWrite(led1, LOW);
    delay(2000);
  }
}

// Task2 kodu led2'yi 3000ms de bir yakıp söndürecek
void Task2kodu(void *pvParameters) {
  Serial.print("Task2'nin çalıştırılacağı çekirdek: ");
  Serial.println(xPortGetCoreID());

  for (;;) {
    digitalWrite(led2, HIGH);
    delay(5000);
    digitalWrite(led2, LOW);
    delay(2000);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  xTaskCreatePinnedToCore(
    Task1kodu,   // Görevin çalışacağı fonksiyon
    "Task1",     // Görevin adı
    10000,       // Görev stack boyutu
    NULL,        // İlave parametre
    1,           // Görevin önceliği
    &Task1,      // Görevin işaretçisi
    0);          // Görevi 0 numaralı çekirdeğe atayalım

  delay(500);

  xTaskCreatePinnedToCore(
    Task2kodu,   // Görevin çalışacağı fonksiyon
    "Task2",     // Görevin adı
    10000,       // Görev stack boyutu
    NULL,        // İlave parametre
    1,           // Görevin önceliği
    &Task2,      // Görevin işaretçisi
    1);          // Görevi 1 numaralı çekirdeğe atayalım

  delay(500);
}

void loop() {
  // Boş. Görevler artık bağımsız olarak çalışıyor.
}
