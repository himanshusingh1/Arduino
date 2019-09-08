#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <WiFiClient.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <TFT_22_ILI9225.h>
#define FS_NO_GLOBALS
#include <FS.h>
#include <WebSocketsServer.h>
#include <ESP8266WiFiMulti.h>

#ifdef ESP32
  #include "SPIFFS.h" // ESP32 only
#endif

// JPEG decoder library
#include <JPEGDecoder.h>


bool isWifiStarted = false;
int resetPIN = 9;

ESP8266WiFiMulti WiFiMulti;
WebSocketsServer webSocket = WebSocketsServer(81);

String Wifissid;
String Wifipassword;
double lastReset = millis();
#define temprature D2
#define light D3
#define soilMoisture D4

#define TFT_RST D0
#define TFT_RS  D1
#define TFT_CS  D8  // SS
#define TFT_SDI D7  // MOSI
#define TFT_CLK D5  // SCK
#define TFT_LED D2   // 0 if wired to +5V directly

TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);

void setup() {
  setupSensors();
  Serial.begin(250000);
  delay(10);
  Serial.println("\n Starting");

  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }
  pinMode(resetPIN,INPUT_PULLUP);
  tft.begin();
  tft.setOrientation(2);
  tft.setBackgroundColor(COLOR_BLACK);
  tft.fillRectangle(0,0,176,220,COLOR_BLACK);  
  wifi_station_set_hostname("Tapio");
  if (isWiFiCredentialsSaved()){
  WifiSTAMode();
  }else{
  WifiAPMode();
  }
  listFiles(); 
  drawJpeg("/l_eye_1.jpg",10,10);
  drawJpeg("/r_eye_1.jpg",100,10);
  
}


void loop() {
  drawJpeg("/l_eye_1.jpg",10,10);
  drawJpeg("/l_eye_2.jpg",10,10);
  drawJpeg("/l_eye_3.jpg",10,10);
  drawJpeg("/l_eye_4.jpg",10,10);
  drawJpeg("/l_eye_5.jpg",10,10);
  drawJpeg("/l_eye_5.jpg",10,10);
  drawJpeg("/l_eye_4.jpg",10,10);
  drawJpeg("/l_eye_3.jpg",10,10);
  drawJpeg("/l_eye_2.jpg",10,10);
  drawJpeg("/l_eye_1.jpg",10,10);
//    webSocket.loop();
//    WifiModeSelector();
//    readEmotions();
}
