bool parseWiFiConfigRequest(DynamicJsonDocument doc){
  if (doc.containsKey("password") && doc.containsKey("ssid")){
    saveWiFiConfig(doc);
    return true;
  }else{
    return false;
  }
}
bool parsePlantConfigRequest(DynamicJsonDocument doc){
  if (doc.containsKey("temp_min") && doc.containsKey("temp_max") && doc.containsKey("light_min") && doc.containsKey("light_max") && doc.containsKey("moisture_min") && doc.containsKey("moisture_max")){
    savePlantConfig(doc);
    return true;
  }else{
    return false;
  }
}
