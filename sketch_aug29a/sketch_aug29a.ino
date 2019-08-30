#define temprature D2
#define light D3
#define soilMoisture D4
void setup() {
  // put your setup code here, to run once:
Serial.begin(250000);
pinMode(temprature,OUTPUT);
pinMode(light,OUTPUT);
pinMode(soilMoisture,OUTPUT);
pinMode(A0,INPUT);
digitalWrite(temprature,HIGH);
digitalWrite(light,LOW);
digitalWrite(soilMoisture,LOW);}

void loop() {
  getAnalogSensorValue();
//Serial.println(getAnalogSensorValue());
delay(1000);
}
float getAnalogSensorValue() 
{
  float val = analogRead(A0);
  float mv = (val / 1023.0);
  float vAtAnalog = (val / 1023.0) * 3.3;
  mv = vAtAnalog * 1000;
  Serial.println(mv);
  return mv;
}
