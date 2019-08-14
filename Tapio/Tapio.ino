#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <WiFiClient.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <TFT_22_ILI9225.h>



bool isWifiStarted = false;
int resetPIN = 9;

WiFiServer server(80);
String Wifissid;
String Wifipassword;

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
  pinMode(temprature,OUTPUT);
  pinMode(light,OUTPUT);
  pinMode(soilMoisture,OUTPUT);
  pinMode(A0,INPUT);
  Serial.begin(115200);
  Serial.println("\n Starting");
  pinMode(resetPIN,INPUT_PULLUP);
  tft.begin();
  tft.setOrientation(2);
  tft.setFont(Terminal6x8);
  tft.drawText(10, 10, "Tapio !");
  tft.drawText(10, 30, "eabjhpio !");
  wifi_station_set_hostname("TapioPlant");
  if (isWiFiCredentialsSaved()){
  WifiSTAMode();
  }else{
  WifiAPMode();
  }
}


void loop() {
  WifiModeSelector();
  getSocketRequests();
}





//handle socket
void getSocketRequests(){
  WiFiClient client = server.available();
  if (client) {
    client.flush();
    if(client.connected())
    {
      Serial.println("Client Connected");
    }
    String myrequest = "";
    while(client.connected()){    
      while(client.available()>0){
        char c = client.read();
        myrequest += c;
      }
    }
    Serial.println(myrequest);
    if (myrequest.length() > 10){
    parseRequest(myrequest);
    }
    client.stop();
    Serial.println("Client disconnected"); 
    
  } 
 }
bool parseRequest(String req){
DynamicJsonDocument doc(1024);
deserializeJson(doc, req);
String ssid = doc["ssid"];
String password = doc["password"];
if (ssid != NULL && password != NULL){
  saveSSIDandPassword(ssid,password);
  delay(100);
  WifiSTAMode();
  return true;
}else{
  return false;
}
}


//handle wifiModes
void WifiModeSelector(){
if ((millis() > (1*60*1000)) && (WiFi.status() != WL_CONNECTED) && !isWifiStarted){
   WifiAPMode();
  }
  if (WiFi.status() == WL_CONNECTED){
       server.stop();
       WiFi.mode(WIFI_STA);
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

void WifiSTAMode(){
  isWifiStarted = false;
  Serial.println("Connecting to WIFI");
  Serial.println(getWiFiSSID());
  Serial.println(getWiFiPassword());
  WiFi.begin(getWiFiSSID(),getWiFiPassword());
  WiFi.mode(WIFI_STA);
 }
 
void WifiAPMode(){
   Serial.println("WIFI AP MODE");
   isWifiStarted = true;
   WiFi.mode(WIFI_AP_STA);  //Both hotspot and client are enabled
   WiFi.softAP("TAPIO");
   server.begin();
}   






//Handle saving of wifi credentials
void saveSSIDandPassword(String ssid,String password){
  writeString(0,ssid);
  writeString(sizeof(ssid),password);
}
bool isWiFiCredentialsSaved(){
  return ( (sizeof(read_String(0)) > 12));
}
String getWiFiSSID(){
  return read_String(0);
}

String getWiFiPassword(){
  return read_String(sizeof(read_String(0)));
}

void writeString(char add,String data)
{
  EEPROM.begin(512);
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
}
 
 
String read_String(char add)
{
  EEPROM.begin(512);
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}



//Reading Sensors
float getAnalogSensorValue() 
{
  float val = analogRead(A0);
  float mv = (val / 1023.0);
  float vAtAnalog = (val / 1023.0) * 3.3;
  mv = vAtAnalog * 1000;
  return mv;
}
void stopAllSensors(){
  digitalWrite(temprature,LOW);
  digitalWrite(light,LOW);
  digitalWrite(soilMoisture,LOW);
}
float getTemprature(){
  stopAllSensors();
  digitalWrite(temprature,HIGH);
  delay(1000);
  float sensorValue = getAnalogSensorValue(); 
  stopAllSensors();
  delay(1000);
  return sensorValue;
 }
 float getSoilMoisture(){
  stopAllSensors();
  digitalWrite(soilMoisture,HIGH);
  delay(1000);
  float sensorValue = getAnalogSensorValue(); 
  stopAllSensors();
  delay(1000);
  return sensorValue;
  }
  float getLightIntensity(){
  stopAllSensors();
  digitalWrite(light,HIGH);
  delay(1000);
  float sensorValue = getAnalogSensorValue(); 
  stopAllSensors();
  delay(1000);
  return sensorValue;
  }
