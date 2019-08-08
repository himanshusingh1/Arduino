#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

#define tempraturePIN  A0
double temprature = 0;

#define lightPIN  A1
double light = 0;

#define moisturePIN  A2
double moisture = 0;

LiquidCrystal_PCF8574 lcd(0x27);  

double tempratureMin = 22;
double tempratureMax = 30;

double moistureMin = 40;
double moistureMax = 75;

double lightMin = 10;
double lightMax = 60;


enum Moods {
  cold,
  hot,
  thirsty,
  sick,
  vampire,
  flashy,
  awake,
  yawn,
  blinky
};

void setup() {
  initilize();
}

void loop() {
  Serial.println("temparture");
  temprature = getTemprature();
  Serial.println(temprature);
  Serial.println("moisture");
  moisture = getMoisture();
  Serial.println(moisture);
  Serial.println("light percentage");
  light = getLight();
  Serial.println(light);
  showEmotion();
  delay(1000);
}
void initilize(){
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(0x27);
  lcd.begin(16, 2);
  pinMode(tempraturePIN,INPUT);
  pinMode(lightPIN,INPUT);
  pinMode(moisturePIN,INPUT);
  Serial.println("INITIALIZING");
  lcd.setBacklight(255);
  lcd.home(); lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("INITIALIZING...");
  for(int i = 0; i < 1;i++){
  temprature = getTemprature();
  light = getLight();
  moisture = getMoisture();
  }
  lcd.clear();
  lcd.print("wake up");
  }
  double getTemprature(){
    double temp = 0.0;
    for (int i = 0 ; i < 10; i++){
      temp = temp + (analogRead(tempraturePIN)*500)/1023;
      delay(50);
      }
    return temp/10;
    }
   double getLight(){
      return ((1023.0-analogRead(lightPIN))/1023)*100;
    }
    double getMoisture(){
      return (analogRead(moisturePIN)/1023.0)*100;
   }
   void showEmotion(){
    if (temprature < tempratureMin){
      lcd.clear();
      lcd.print("COLD");
     }else if (temprature > tempratureMax){
      lcd.clear();
      lcd.print("HOT");
     }else if (moisture < moistureMin){
      lcd.clear();
      lcd.print("Thirsty");
     }else if (moisture > moistureMax){
      lcd.clear();
      lcd.print("Sick");
     }else if (light < lightMin){
      lcd.clear();
      lcd.print("Vampire");
     }else if (light > lightMax){
      lcd.clear();
      lcd.print("Flashy");
     }else{
      showNormalRandomEmotion();
     }
   }
   void showNormalRandomEmotion(){
      lcd.clear();
      lcd.print("Random");
    }
