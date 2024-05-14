#include <Wire.h>
#include <Servo.h>
#define TCS34725_ADDR 0x29 //renk sensörü adresi

typedef struct //RGB verilerini tutan yapı
{
  uint16_t Red;
  uint16_t Green;
  uint16_t Blue;
  uint16_t Clear;
} RGB;
//Global değişkenler
RGB rgb; //renk verileri
uint16_t maxRGB = 0; // maks RGB değeri
uint16_t CT = 0, Lux = 0; //renk sıcaklığı ve ışık seviyesi
byte color = 0, rgb_data[3] = {0}; //renk ve RGB verileri

char kanal; //Renk kanaklı (R,G,B,C)
int renkFarkininKanalDegeri; //Renk farkının belirlenen kanaldaki değeri

Servo servo1; // Sağ üst servo
Servo servo2; // Sol üst servo
Servo servo3; // Sağ alt servo
Servo servo4; // Sol alt servo

//renk sensörü pin bağlantıları
int renkSensorPinDR = A5; // Renk sensörü DR pin bağlantısı
int renkSensorPinCT = A4; // Renk sensörü CT pin bağlantısı
int renkSensorOkuma;

//başlangıç ayarları burada yapılıyor
void setup()
{
  Serial.begin(115200);
  Wire.begin();
  delay(1);

  //renk sensörü için ayarlar
  Wire.beginTransmission(TCS34725_ADDR);
  Wire.write(0x00); // Control register
  Wire.write(0x01); // ATIME değeri (örneğin, 1 ms)
  Wire.endTransmission();

  //servo motorları başlat
  servo1.attach(3);
  servo2.attach(10);
  servo3.attach(6);
  servo4.attach(9);

  Serial.begin(9600);

  //RGB değerimi oku,renk farkını belirle ve ekrana yazır
  RGB renk1 = renkAl(1);
  printColor(renk1);
  RGB renk2 = renkAl(2);
  printColor(renk2);

  RGB renkFarki = renkcikar(renk1, renk2);
  kanal = KanalBelirle(renkFarki);
  renkFarkininKanalDegeri = kanalGetir(renkFarki, kanal);
  Serial.println(kanal);
}

//Ana döngü sürekli çalışan kod burada bulunuyor
void loop()
{
  readColor(); //renk sensöründen veriyi oku
  normalizeRGB(); //RGB verilerini normalize et
  calistir(); //belirlenen şartlara göre başlat
  printColor(rgb); //renk verilerini ekrana yazdır
  delay(1000); //1saniye bekle
}

//renk kanalını belirleme fonksiyonu
char KanalBelirle(RGB renk)
{
  if(renk.Red > renk.Blue && renk.Red > renk.Green && renk.Red > renk.Clear)
  {
    return 'R';
  }
  else if(renk.Green > renk.Red && renk.Green > renk.Blue && renk.Green > renk.Clear)
  {
    return 'G';
  }
  else if(renk.Blue > renk.Red && renk.Blue > renk.Green && renk.Blue > renk.Clear)
  {
    return 'B';
  }
  else
  {
    return 'C';
  }
}

//belirlenen kanaldaki değeri döndüren fonksiyon
int kanalGetir(RGB renk, char kanal)
{
  int kanalDegeri = 0;

  if(kanal == 'R')
  {
    kanalDegeri = renk.Red;
  } 
  else if (kanal == 'G')
  {
    kanalDegeri = renk.Green;
  }
  else if (kanal == 'B')
  {
    kanalDegeri = renk.Blue;
  }
  else 
  {
    kanalDegeri = renk.Clear;
  }

  return kanalDegeri;
}
// iki renk arasındaki farkı hesaplayan fonksiyon
RGB renkcikar(RGB renk1, RGB renk2)
{
  int renkRfark = renk1.Red - renk2.Red;
  int renkGfark = renk1.Green - renk2.Green;
  int renkBfark = renk1.Blue - renk2.Blue;
  int renkCfark = renk1.Clear - renk2.Clear;

  if(renkRfark < 0) renkRfark *= -1;
  if(renkGfark < 0) renkGfark *= -1;
  if(renkBfark < 0) renkBfark *= -1;
  if(renkCfark < 0) renkCfark *= -1;

  RGB renkFark;
  renkFark.Red = renkRfark;
  renkFark.Green = renkGfark;
  renkFark.Blue = renkBfark;
  renkFark.Clear = renkCfark;

  return renkFark;
}

//belirtilen şartlara göre aksiyonları başlatan fonksiyon
void calistir()
{
  int kanalDegeri = kanalGetir(rgb, kanal);

  if(kanalDegeri > renkFarkininKanalDegeri)
  {
    OrtayaDn();
    kiskaciAc();
    kiskaciKapat();
    SagaDnme();
    delay(500);
    kiskaciAc();
    delay(2000);
    Serial.println("Beyaz");
  }
  else
  {
    OrtayaDn();
    kiskaciAc();
    kiskaciKapat();
    SolaDnme();
    delay(500);
    kiskaciAc();
    delay(2000);
    Serial.println("Siyah");
  }
  
  OrtayaDn();
}

//belirtilen sıradaki renk örneğini okuyan fonksiyon
RGB renkAl(int sira)
{
  Serial.print(sira);
  Serial.println(".objeyi göster");
  delay(5000);

  int toplam_r = 0;
  int toplam_g = 0;
  int toplam_b = 0;
  int toplam_c = 0;

  //5 örnek al ve ortalamsını hesapla
  for(int i = 0; i<5; i++)
  {
    readColor();
    normalizeRGB();

    toplam_r += rgb.Red;
    toplam_g += rgb.Green;
    toplam_b += rgb.Blue;
    toplam_c += rgb.Clear;
  }
  
  RGB okunanRenk;
  okunanRenk.Red = toplam_r/5;
  okunanRenk.Green = toplam_g/5;
  okunanRenk.Blue = toplam_b/5;
  okunanRenk.Clear = toplam_c/5;

  Serial.println("Renk okundu");

  return okunanRenk;
}

//renk sensörüden veriyi okuyan fonksiyon
void readColor()
{ 
  //renk sensöründen veriyi talep et
  Wire.beginTransmission(TCS34725_ADDR);
  Wire.write(0x80 | 0x14); // Data register
  Wire.endTransmission();

  Wire.requestFrom(TCS34725_ADDR, 8);
  rgb.Clear = Wire.read();
  rgb.Clear |= Wire.read() << 8;
  rgb.Red = Wire.read();
  rgb.Red |= Wire.read() << 8;
  rgb.Green = Wire.read();
  rgb.Green |= Wire.read() << 8;
  rgb.Blue = Wire.read();
  rgb.Blue |= Wire.read() << 8;

  // Maksimum RGB değeri güncelle
  maxRGB = max(rgb.Red, max(rgb.Green, rgb.Blue));

  //daha fazla renk değeri verisi oku
  Wire.beginTransmission(TCS34725_ADDR);
  Wire.write(0x80 | 0x10); // daha fazla veri register
  Wire.endTransmission();

  Wire.requestFrom(TCS34725_ADDR, 1);
  color = Wire.read();
}

//RGB verilerini normalize eden fonskiyon
void normalizeRGB()
{
  rgb.Red = map(rgb.Red, 0, maxRGB, 0, 255);
  rgb.Green = map(rgb.Green, 0, maxRGB, 0, 255);
  rgb.Blue = map(rgb.Blue, 0, maxRGB, 0, 255);
}

//RGB verilerini ekrana yazdıran fonksiyon
void printColor(RGB rgb)
{
  Serial.print("Normalized Red: ");
  Serial.print(rgb.Red);
  Serial.print(", Normalized Green: ");
  Serial.print(rgb.Green);
  Serial.print(", Normalized Blue: ");
  Serial.print(rgb.Blue);
  Serial.print(", Clear: ");
  Serial.println(rgb.Clear);
}

//kol öne inme fonksiyonu
void koluIndir()
{
  // Kol öne inme
  servo1.write(170);
  servo2.write(120);
  servo3.write(80);
  servo4.write(90);
  delay(1000);
}

void kiskaciAc()
{
  // Kıskaç açılması
  servo1.write(10);
  delay(1000);
}

void kiskaciKapat()
{
  // Kıskaç kapanması
  servo1.write(170);
  servo2.write(150);
  servo3.write(80);
  servo4.write(90);
  delay(1000);
}

void SagaDnme()
{
  // Sağa dönme
  servo1.write(170);
  servo2.write(120);
  servo3.write(100);
  servo4.write(20);
  delay(1000);
}

void SolaDnme()
{
  // Sola dönme
  servo1.write(170);
  servo2.write(120);
  servo3.write(120);
  servo4.write(150);
  delay(1000);
}

void OrtayaDn()
{
  // Orta pozisyona dönme
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  delay(1000);
}