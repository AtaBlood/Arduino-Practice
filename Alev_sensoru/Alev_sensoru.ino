#define ALEV_SENSORU_PIN D0 // Alev sensörünün bağlı olduğu dijital pin
#define BUZZER_PIN 7 // Buzzer'ın bağlı olduğu pin

bool oncekiDurum = LOW; // Önceki alev durumu (başlangıçta alev algılanmıyor)

void setup() {
  pinMode(ALEV_SENSORU_PIN, INPUT); // Alev sensörünün pinini giriş olarak ayarla
  pinMode(BUZZER_PIN, OUTPUT); // Buzzer'ın pinini çıkış olarak ayarla
}

void loop() {
  int alevDurumu = digitalRead(ALEV_SENSORU_PIN); // Alev sensöründen okunan değeri al

  if (alevDurumu == HIGH && oncekiDurum == LOW) { // Eğer alev algılandıysa ve önceki durum algılanmadıysa
    digitalWrite(BUZZER_PIN, HIGH); // Buzzer'ı aktif et
    delay(1000); // 1 saniye bekle
    digitalWrite(BUZZER_PIN, LOW); // Buzzer'ı kapat
    oncekiDurum = HIGH; // Önceki durumu güncelle
  } else if (alevDurumu == LOW && oncekiDurum == HIGH) { // Eğer alev algılanmadıysa ve önceki durum algılandıysa
    oncekiDurum = LOW; // Önceki durumu güncelle
  }
}