
String parseRequest(String req){
Serial.println("========REQ========");
Serial.println(req);
DynamicJsonDocument doc(1024);
deserializeJson(doc, req);
String id = doc["id"];
Serial.println(id);
// for plant enviroment
if (id == "0"){
if (parsePlantConfigRequest(doc)){
  return "GOOD";
  }else{
  return "BAD";
  }
}
//for wifi configuration
if (id == "1"){
 if (parseWiFiConfigRequest(doc)){
  delay(100);
  WifiSTAMode();
  return "GOOD";
 }else{
   return "BAD";
 }
}
//for ssid 
if (id == "2"){
  return getAvialableSSIDList();
}
return "N/A";
}


//handle wifiModes
void WifiModeSelector(){
if ((millis() > (1*60*1000)) && (WiFi.status() != WL_CONNECTED) && !isWifiStarted){
   WifiAPMode();
  }
  if (WiFi.status() == WL_CONNECTED){
      Serial.println("WiFi is connected");
      if ((millis() - lastReset) > 60){
        Serial.println("closing wifi");
       webSocket.close();
       WiFi.mode(WIFI_STA);
      }
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
   WiFi.softAP("TAPIOP");
   webSocket.begin();
   webSocket.onEvent(webSocketEvent);
}   


bool isWiFiCredentialsSaved(){
  DynamicJsonDocument doc = loadWiFiConfig();
  return (doc.containsKey("password") && doc.containsKey("ssid"));
}

String getWiFiSSID(){
  DynamicJsonDocument doc = loadWiFiConfig();
  return doc["ssid"];
}

String getWiFiPassword(){
  DynamicJsonDocument doc = loadWiFiConfig();
  return doc["password"];
}

String getAvialableSSIDList(){
  DynamicJsonDocument doc(1024);
  int numberOfNetworks = WiFi.scanNetworks();
 
  for(int i =0; i<numberOfNetworks; i++){
  DynamicJsonDocument wifiOBJ(1024);
    wifiOBJ["ssid"] = WiFi.SSID(i);
    wifiOBJ["rssi"] = WiFi.RSSI(i);
    doc.add(wifiOBJ);
  }
  String results;
  serializeJson(doc, results);
  return results;
  }

bool isValidJSON(String req){
  Serial.println(req);
  DynamicJsonDocument doc(1024);
  DeserializationError err = deserializeJson(doc, req);
  Serial.println(err.c_str());
  switch (err.code()) {
    case DeserializationError::Ok:
      Serial.println("is valid");
  return true;
        break;
    default:
  return false;
        break;
}
  return false;
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
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
             Serial.printf("[%u] Text: %s\n", num, payload);
              if (isValidJSON(Recrequest)){
               String response = parseRequest(Recrequest);
              webSocket.sendTXT(num, response);
              }else{
               webSocket.sendTXT(num, "BAD");
              }
            break;
        case WStype_ERROR:
            break;
        default:
            break;
    }
}
