#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "İbrahim";        // WiFi ağının SSID'si
const char* password = "44444444";   // WiFi ağının şifresi
const char* mqtt_server = "test.mosquitto.org"; // MQTT sunucusunun IP adresi

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  // WiFi ağına bağlanma
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
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Bağlantı kurulana kadar döngü
  while (!client.connected()) {
    Serial.print("MQTT sunucusuna bağlanılıyor...");
    // Client ID oluşturma
    String clientId = "mqtt-explorer-d4965f4f";
    clientId += String(random(0xffff), HEX);

    // Sunucuya bağlanma
    if (client.connect(clientId.c_str())) {
      Serial.println("bağlandı");
      // Abone olunan konu
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
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}