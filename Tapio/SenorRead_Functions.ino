
double lastSensorMillis = 0;

double tempratureAverage = 0;
double lightAverage = 0;
double moistureAverage = 0;

double timeThresold = 60 * 1000;

void setupSensors(){
  pinMode(temprature,OUTPUT);
  pinMode(light,OUTPUT);
  pinMode(soilMoisture,OUTPUT);
  pinMode(A0,INPUT);
  delay(100);
  tempratureAverage = getTemprature();
  moistureAverage = getSoilMoisture();
  lightAverage = getLightIntensity();
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
  delay(100);
  float sensorValue = getAnalogSensorValue(); 
  stopAllSensors();
  delay(100);
  return sensorValue/10;
}
 
float getSoilMoisture(){
  stopAllSensors();
  digitalWrite(soilMoisture,HIGH);
  delay(100);
  float sensorValue = getAnalogSensorValue(); 
  stopAllSensors();
  delay(100);
  return (sensorValue/1023)*100;
}
  
float getLightIntensity(){
  stopAllSensors();
  digitalWrite(light,HIGH);
  delay(100);
  float sensorValue = getAnalogSensorValue(); 
  stopAllSensors();
  delay(100);
  return (sensorValue/1023)*100;
}


enum emotions{
happy,
yawning,
blinking,
sleeping,
superhappy,
anoyed,
confused,
squint,
vampire,
hot,
cold,
thirsty,
hydrated,
};

void readEmotions(){
  tempratureAverage = (tempratureAverage + getTemprature())/2.0;
  moistureAverage = (moistureAverage + getSoilMoisture())/2.0;
  lightAverage = (lightAverage + getLightIntensity())/2.0;
 
  if (lastSensorMillis == 0){
    lastSensorMillis = millis();
    calculateEmotions(); 
  }else if ((millis() - lastSensorMillis) > timeThresold){
      lastSensorMillis = millis();
      calculateEmotions(); 
  }
//  Serial.println("temparture =>");
//  Serial.println(tempratureAverage);
//  Serial.println("moisture =>");
//  Serial.println(moistureAverage);
//  Serial.println("light =>");
//  Serial.println(lightAverage);
}
void calculateEmotions(){
  if (isPlantConfigSaved()){
  if (tempratureAverage < getTempMin()){
          drawJpeg("/4.jpg",0,0);
  }else if (tempratureAverage > getTempMax()){
          drawJpeg("/15.jpg",0,0);
  }else if (moistureAverage < getMoistureMin()){
          drawJpeg("/12.jpg",0,0);
  }else if (moistureAverage > getMoistureMax()){
          drawJpeg("/6.jpg",0,0);
  }else if (lightAverage < getLightMin()){
         drawJpeg("/9.jpg",0,0);
  }else if (lightAverage > getLightMax()){
          drawJpeg("/13.jpg",0,0);
  }else{
          drawJpeg("/5.jpg",0,0);
  }
  tempratureAverage = getTemprature();
  moistureAverage = getSoilMoisture();
  lightAverage = getLightIntensity();
  }else{
        drawJpeg("/logo.jpg",0,0);
  }
}

bool isPlantConfigSaved(){
  DynamicJsonDocument doc = loadPlantConfig();
  return true;
  return (doc.containsKey("temp_min") && doc.containsKey("temp_max") && doc.containsKey("light_min") && doc.containsKey("light_max") && doc.containsKey("moisture_min") && doc.containsKey("moisture_max"));
}

int getTempMin(){
  DynamicJsonDocument doc = loadPlantConfig();
  String result =  doc["temp_min"];
  Serial.println("saved temp min");
  Serial.println(result);
  return result.toInt();
}
int getTempMax(){
  DynamicJsonDocument doc = loadPlantConfig();
  String result =  doc["temp_max"];
  Serial.println("saved temp max");
  Serial.println(result);
   return result.toInt();

}
int getLightMin(){
  DynamicJsonDocument doc = loadPlantConfig();
  String result = doc["light_min"];
  Serial.println("saved light min");
  Serial.println(result);
  return result.toInt();
}
int getLightMax(){
  DynamicJsonDocument doc = loadPlantConfig();
  String result = doc["light_max"];
  Serial.println("saved light max");
  Serial.println(result);
  return result.toInt();
}
int getMoistureMin(){
  DynamicJsonDocument doc = loadPlantConfig();
  String result = doc["moisture_min"];
  Serial.println("saved moisture min");
  Serial.println(result);
   return result.toInt();
}
int getMoistureMax(){
  DynamicJsonDocument doc = loadPlantConfig();
  String result = doc["moisture_max"];
  Serial.println("saved moisture max");
  Serial.println(result);
  return result.toInt();
}
