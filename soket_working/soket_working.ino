#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include "DHT.h"
#define DHTPIN D2     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors
DHT dht(DHTPIN, DHTTYPE);
const char* SSID     = "craterzone_asus";
const char* PASSWORD = "Noida@Crater@Zone@666";
ESP8266WiFiMulti WiFiMulti;
WebSocketsServer webSocket = WebSocketsServer(81);
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    String t = String(dht.readTemperature());    
    String Recrequest = "";

    switch(type) {
        case WStype_DISCONNECTED:
            break;
        case WStype_CONNECTED:
            {
                IPAddress ip = webSocket.remoteIP(num);
                Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
            }
            break;
        case WStype_TEXT:
            for(int i = 0;i<length;i++){
            Recrequest = Recrequest + char(payload[i]);
            }
              Serial.println(Recrequest);
             Serial.printf("[%u] Text: %s\n", num, payload);
              t = String(dht.readTemperature());
              webSocket.sendTXT(num, Recrequest);
            
            break;
        case WStype_ERROR:
            break;
default:
            break;
    }
}
void setup() {
    Serial.begin(115200);
for(uint8_t t = 4; t > 0; t--) {
        delay(1000);
    }
WiFiMulti.addAP(SSID, PASSWORD);
while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
        Serial.println(".");
    }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}
void loop() {
    
    webSocket.loop();
}
