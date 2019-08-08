#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <WiFiClient.h>
#include <EEPROM.h>
#include <ArduinoJson.h>

bool isWifiStarted = false;
int resetPIN = 0;

WiFiServer server(80);
String Wifissid;
String Wifipassword;


void setup() {
  Serial.begin(115200);
  Serial.println("\n Starting");
  pinMode(resetPIN,INPUT_PULLUP);
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
  Serial.println("hey!");
  Serial.println(sizeof(read_String(0)));
  return ( (read_String(0) != NULL));
   
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
