#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define SDA_PIN 8
#define SCL_PIN 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid = "YOUR_WIFI";// REPLACE
const char* password = "YOUR_WIFI_PASSWORD"; //REPLACE

String serverName = "http://YOUR_LOCAL_MACHINE_IP:5000/stats"; //REPLACE

int currentPage = 0;
unsigned long lastPageChange = 0;
const int pageInterval = 4000; 

unsigned long lastRequest = 0;
const int requestInterval = 1000; 

int cpu = 0;
int ram = 0;
float cpuTemp = 0.0;
float gpuTemp = 0.0;
int storage = 0;
String uptime= "0h 0m";

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED NOT FOUND");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  WiFi.begin(ssid, password);
  display.setCursor(0, 0);
  display.println("CONNECTING WiFi...");
  display.display();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WiFi SUCCES!");
  display.display();
  delay(1000);
}
void loop() {
  if (millis() - lastRequest > requestInterval) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      int httpResponseCode = http.GET();
      if (httpResponseCode > 0) {
        String payload = http.getString();
        DynamicJsonDocument doc(512); 
        DeserializationError error = deserializeJson(doc, payload);
        if (!error) {
          cpu = doc["cpu"].as<int>();
          ram = doc["ram"].as<int>();
          cpuTemp = doc["temp"].as<float>();
          gpuTemp = doc["gpu_temp"].as<float>();
          storage = doc["storage"].as<int>();
          uptime = doc["uptime"].as<String>();
        } else {
          Serial.print("Error JSON: ");
          Serial.println(error.c_str());
        }
      }
      http.end();
    }
    lastRequest = millis();
  }

  if (millis() - lastPageChange > pageInterval) {
    int oldPage = currentPage;
    currentPage++;
    if(currentPage >4 ) currentPage = 0; 
    animateTransition(oldPage, currentPage);
    lastPageChange = millis();
  }
  display.clearDisplay();
  drawPage(currentPage, 0);
  display.display();
}
void drawBar(int x, int y, int w, int h, int percent) {
  display.drawRect(x, y, w, h, WHITE);
  int fill = (w - 2) * percent / 100;
  display.fillRect(x + 1, y + 1, fill, h - 2, WHITE);
}
void animateTransition(int oldPage, int newPage) {
  for(int x = 0; x <= 128; x += 16) {
    display.clearDisplay();
    drawPage(oldPage, -x);
    drawPage(newPage, 128 - x);
    display.display();
    delay(20);
  }
}
void drawPage(int page, int offsetX) {
  switch(page) {
    case 0: pageCPU_RAM(offsetX); break;
    case 1: pageTemps(offsetX); break;
    case 2: pageStorage(offsetX); break;
    case 3: pageSystem(offsetX); break;
    case 4: pageTime(offsetX); break;
  }
}
void pageCPU_RAM(int offsetX) {
  display.setTextSize(2);
  display.setCursor(offsetX + 0,0);
  display.print("CPU ");
  display.print(cpu);
  display.print("%");
  drawBar(offsetX + 0,16,120,8,cpu);
  display.setCursor(offsetX + 0,32);
  display.print("RAM ");
  display.print(ram);
  display.print("%");
  drawBar(offsetX + 0,48,120,8,ram);
}
void pageTemps(int offsetX) {
  display.setTextSize(2);
  display.setCursor(offsetX + 0,0);
  display.print("TEMP");
  display.setCursor(offsetX + 0,28);
  display.print("CPU:");
  display.print(cpuTemp);
  display.setCursor(offsetX + 0,48);
  display.print("GPU:");
  display.print(gpuTemp);
}
void pageStorage(int offsetX) {
  display.setTextSize(1);
  display.setCursor(offsetX + 0, 0);
  display.print("MAIN DISK: ");
  display.setTextSize(2);
  display.setCursor(offsetX + 0, 15);
  display.print(storage);
  display.print("%");
  drawBar(offsetX + 0, 32, 120, 8, storage); 
}
void pageSystem(int offsetX) {
  display.setTextSize(1);
  display.setCursor(offsetX + 0,0);
  display.print("PC MONITOR");
  display.setCursor(offsetX + 0,25);
  display.print(WiFi.localIP());
}
void pageTime(int offsetX){
  display.setTextSize(1); 
  display.setCursor(offsetX + 0, 0);
  display.print("USAGE TIME:");
  display.setTextSize(2); 
  display.setCursor(offsetX + 0, 25);
  display.print(uptime);
}





