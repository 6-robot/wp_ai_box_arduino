#include <TFT_eSPI.h>
#include <WiFi.h>

const char* ssid = "xxxx";
const char* password = "xxxx";

const int blue_led_pin = 48;

TFT_eSPI tft = TFT_eSPI(320,480);
WiFiServer server(80);

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(1);
  tft.fillScreen(TFT_BLACK);
	tft.setTextSize(2);
  tft.setCursor(0,0);
  tft.print("Connecting to ");
  tft.print(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tft.print(".");
  }

  tft.setCursor(0,30);
  tft.println("WiFi connected.");
  tft.println("IP address: ");
  tft.println(WiFi.localIP());

  pinMode(blue_led_pin, OUTPUT);
  pinMode(blue_led_pin, HIGH);

  server.begin();
}

void loop() {
  WiFiClient client = server.accept();

  if (client) { 
    tft.println("New Client.");
    String currentLine = "";
    while (client.connected()) { 
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html; charset=utf-8");
            client.println();
            client.print("点击 <a href=\"/H\">这里</a> 熄灭蓝色LED<br>");
            client.print("点击 <a href=\"/L\">这里</a> 点亮蓝色LED<br>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /H")) {
          digitalWrite(blue_led_pin, HIGH);
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(blue_led_pin, LOW);
        }
      }
    }
    
    client.stop();
    tft.println("Client Disconnected.");
  }
}