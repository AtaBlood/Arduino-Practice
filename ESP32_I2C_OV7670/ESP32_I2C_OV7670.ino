#include "OV7670.h"

#include <Adafruit_GFX.h>    // Core graphics library

#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include "BMP.h"

const int SIOD = 21; //SDA
const int SIOC = 22; //SCL

const int VSYNC = 15;
const int HREF = 2;

const int XCLK = 13;
const int PCLK = 4;

const int D0 = 35;
const int D1 = 32;
const int D2 = 33;
const int D3 = 25;
const int D4 = 26;
const int D5 = 27;
const int D6 = 14;
const int D7 = 12;

//DIN <- MOSI 23
//CLK <- SCK 18

#define ssid1        "net"
#define password1    "boran123.."

OV7670 *camera;

WiFiMulti wifiMulti;
WiFiServer server(80);

unsigned char bmpHeader[BMP::headerSize];

void serve()
{
  WiFiClient client = server.available();
  if (client) 
  {
    //Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        
        if (c == '\n') 
        {
          if (currentLine.length() == 0) 
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print(
              "<style>body{margin: 0}\nimg{height: 100%; width: auto}</style>"
              "<img id='a' src='/camera' onload='this.style.display=\"initial\"; var b = document.getElementById(\"b\"); b.style.display=\"none\"; b.src=\"camera?\"+Date.now(); '>"
              "<img id='b' style='display: none' src='/camera' onload='this.style.display=\"initial\"; var a = document.getElementById(\"a\"); a.style.display=\"none\"; a.src=\"camera?\"+Date.now(); '>");
            client.println();
            break;
          } 
          else 
          {
            currentLine = "";
          }
        } 
        else if (c != '\r') 
        {
          currentLine += c;
        }
        
        if(currentLine.endsWith("GET /camera"))
        {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:image/bmp");
            client.println();
            
            client.write(bmpHeader, BMP::headerSize);
            client.write(camera->frame, camera->xres * camera->yres * 2);
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }  
}

void setup() 
{
  Serial.begin(115200);

  wifiMulti.addAP(ssid1, password1);
  
  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
  }

  Serial.println("Camera init started.");  
  camera = new OV7670(OV7670::Mode::QQVGA_RGB565, SIOD, SIOC, VSYNC, HREF, XCLK, PCLK, D0, D1, D2, D3, D4, D5, D6, D7);
  Serial.println("Camera inited.");

  Serial.println("BMP init started.");
  BMP::construct16BitHeader(bmpHeader, camera->xres, camera->yres);
  Serial.println("BMP inited.");
  
  Serial.println("Server beginning.");
  server.begin();
  Serial.println("Server started.");
}

void loop()
{
  camera->oneFrame();
  serve();
}
