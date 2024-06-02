#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// WiFi bilgileri
const char* ssid = "ADR";
const char* password = "engin5656";

// MQTT sunucusu
const char* mqtt_server = "test.mosquitto.org";

// LCD ekran adresi ve boyutu
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C adresi 0x27, 16x2 ekran

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("WiFi'a bağlanılıyor: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi bağlandı");
  Serial.println("IP adresi: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Topic: ");
  Serial.println(topic);

  Serial.print("Payload: ");
  String message = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    message += (char)payload[i];
  }
  Serial.println();

  // Mesajı LCD'ye yaz
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Topic: ");
  lcd.setCursor(0, 1);
  lcd.print(message);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("MQTT sunucusuna bağlanılıyor...");
    String clientId = "mqtt-explorer-d4965f4f";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("bağlandı");
      client.subscribe("atakan/ibo324214213534");
    } else {
      Serial.print("başarısız, hata kodu=");
      Serial.print(client.state());
      Serial.println(" 5 saniye sonra tekrar denenecek");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // LCD ekranı başlat
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MQTT Client");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
