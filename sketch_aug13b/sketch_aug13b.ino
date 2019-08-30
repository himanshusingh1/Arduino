#define temprature D2
#define light D3
#define soilMoisture D4
void setup() {
  // put your setup code here, to run once:
pinMode(D2,OUTPUT);
pinMode(D3,OUTPUT);
pinMode(A0,INPUT);
Serial.begin(9600);
}

void loop() {
 
}
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
