#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

bool isWifiStarted = false;
int resetPIN = 0;

WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  Serial.println("\n Starting");
  pinMode(resetPIN,INPUT_PULLUP);
  WiFi.begin("realme 2","12345678");
  
}


void loop() {
  WifiModeSelector();
  setUpServer();
}
WiFiClient client;
void setUpServer(){
  client = server.available();
 
  if (client) {
    if(client.connected())
    {
      Serial.println("Client Connected");
    }
    
    while(client.connected()){      
      while(client.available()>0){
        // read data from the connected client
//        Serial.write(client.read()); 
      }
      //Send Data to connected client
      while(Serial.available()>0)
      {
        client.write(Serial.read());
      }
    }
    client.stop();
    Serial.println("Client disconnected");    
  } 
 }
void WifiModeSelector(){
if ((millis() > (60*1000)) && (WiFi.status() != WL_CONNECTED) && !isWifiStarted){
   WifiAPMode();
  }
  if (WiFi.status() == WL_CONNECTED){
       server.stop();
       WiFi.mode(WIFI_STA);  //Both hotspot and client are enabled
  }
  if (digitalRead(resetPIN) == LOW && !isWifiStarted){
  double buttonClickMillis = millis();
  while(digitalRead(resetPIN) == LOW){
    delay(100);
    Serial.println("LOW");
   if ((millis() - buttonClickMillis > 3*1000) && !isWifiStarted){
     WifiAPMode();
    break;
    }
  }
  }
}
void WifiAPMode(){
   Serial.println("WIFI AP MODE");
   isWifiStarted = true;
   WiFi.mode(WIFI_AP_STA);  //Both hotspot and client are enabled
   WiFi.softAP("TAPIO");
  server.begin();
}   
