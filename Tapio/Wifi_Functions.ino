
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
       if (isValidJSON(myrequest)){
        delay(100);
        client.print((parseRequest(myrequest)));
//        client.stop();
       }
    }
    }
    client.stop();
    Serial.println("Client disconnected"); 
    
  } 
 }
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
if ((millis() > (0*60*1000)) && (WiFi.status() != WL_CONNECTED) && !isWifiStarted){
   WifiAPMode();
  }
  if (WiFi.status() == WL_CONNECTED){
      Serial.println("WiFi is connected");
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
   WiFi.softAP("TAPIOP");
   server.begin();
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
