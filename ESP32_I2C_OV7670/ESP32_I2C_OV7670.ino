#include <WiFi.h>
#include <HTTPClient.h>
#include "OV7670.h"
#include <SPIFFS.h>

#define SIOD 21
#define SIOC 22
#define VSYNC 15
#define HREF 2
#define XCLK 13
#define PCLK 4
#define D0 35
#define D1 32
#define D2 33
#define D3 25
#define D4 26 
#define D5 27
#define D6 14
#define D7 12

#define ssid        "İbrahim"      // WiFi ağınızın adı
#define password    "44444444"  // WiFi şifreniz

OV7670 *camera;

void uploadPhoto(const char* serverName) {
  File file = SPIFFS.open("/photo.jpg", FILE_READ);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  HTTPClient http;
  http.begin(serverName);
  http.addHeader("Content-Type", "multipart/form-data");

  int httpResponseCode = http.sendRequest("POST", &file, file.size());

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }

  file.close();
  http.end();
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Initialize the camera with lower resolution and color depth
  camera = new OV7670(OV7670::Mode::QQVGA_RGB565, SIOD, SIOC, VSYNC, HREF, XCLK, PCLK, D0, D1, D2, D3, D4, D5, D6, D7);
}

void loop() {
  // Capture a frame
  camera->oneFrame();

  // Create a temporary file to store the image
  File file = SPIFFS.open("/photo.jpg", FILE_WRITE); // Dosya adını .jpg olarak değiştirdik
  if (!file) {
    Serial.println("Failed to create file");
    return;
  }

  // Write frame buffer to file in JPEG format
  size_t bytesWritten = file.write(camera->frame, camera->xres * camera->yres * 2); // Tüm kareyi dosyaya yazdık
  if (bytesWritten != camera->xres * camera->yres * 2) {
    Serial.println("Error writing to file");
    file.close();
    return;
  }

  Serial.println("Frame buffer written.");
  file.close();
  Serial.println("File closed.");

  // Upload the photo to the server
  uploadPhoto("http://waspopy.pythonanywhere.com/upload");

  delay(20000);   // Wait 5 seconds before taking another photo
}
