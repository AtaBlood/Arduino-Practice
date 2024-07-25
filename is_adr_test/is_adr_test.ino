#include <Nextion.h>

// Nextion ekranı için nesneler tanımlanıyor
NexButton bPlus = NexButton(0, 1, "b0");    // "+" butonu
NexButton bMinus = NexButton(0, 2, "b1");  // "-" butonu
NexButton bOk = NexButton(0, 3, "b2");        // "OK" butonu
NexNumber nValue1 = NexNumber(0, 4, "n0");// İlk değer
NexNumber nValue2 = NexNumber(0, 5, "n1");// İkinci değer

// Değer değişkenleri
int value1 = 0;
int value2 = 0;

// Olaylar için geri çağırma fonksiyonları
void bPlusPopCallback(void *ptr) {
  value1++;
  nValue1.setValue(value1);
}

void bMinusPopCallback(void *ptr) {
  value1--;
  nValue1.setValue(value1);
}

void bOkPopCallback(void *ptr) {
  value2 = value1;
  nValue2.setValue(value2);
}

// Nextion ekranı için olay listesi
NexTouch *nex_listen_list[] = {
  &bPlus,
  &bMinus,
  &bOk,
  NULL
};

void setup() {
  Serial.begin(9600); // Seri monitör için
  Serial2.begin(9600);
  nexInit();

  // Geri çağırma fonksiyonları atanıyor
  bPlus.attachPop(bPlusPopCallback, &bPlus);
  bMinus.attachPop(bMinusPopCallback, &bMinus);
  bOk.attachPop(bOkPopCallback, &bOk);

  // Başlangıç değerleri ayarlanıyor
  nValue1.setValue(value1);
  nValue2.setValue(value2);
}

void loop() {
  // Nextion olaylarını dinle
  nexLoop(nex_listen_list);

  // Seri veriyi kontrol et ve Nextion'a geri gönder
  while (Serial2.available()) {
    char c = Serial2.read();
    Serial2.write(c);
  }
}
