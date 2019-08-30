
DynamicJsonDocument loadWiFiConfig() {
  DynamicJsonDocument doc(1024);
  File configFile = SPIFFS.open("/wificonfig.json", "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return doc;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return doc;
  }

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  auto error = deserializeJson(doc, buf.get());
  if (error) {
    Serial.println("Failed to parse config file");
    return doc;
  }
  
  return doc;
}

bool saveWiFiConfig(DynamicJsonDocument doc) {  
  File configFile = SPIFFS.open("/wificonfig.json", "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }
  serializeJson(doc, configFile);
  return true;
}

DynamicJsonDocument loadPlantConfig() {
  DynamicJsonDocument doc(1024);
  File configFile = SPIFFS.open("/plantconfig.json", "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return doc;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return doc;
  }

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  auto error = deserializeJson(doc, buf.get());
  if (error) {
    Serial.println("Failed to parse config file");
    return doc;
  }
  
  return doc;
}

bool savePlantConfig(DynamicJsonDocument doc) {  
  File configFile = SPIFFS.open("/plantconfig.json", "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }
  serializeJson(doc, configFile);
  return true;
}
