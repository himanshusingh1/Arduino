#include "MCUFRIEND_kbv.h"
#include "face.h"
#include "face2.h"
#define BLACK   0x0000
#define WHITE   0xFFFF
MCUFRIEND_kbv tft;
void setup() {
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.fillScreen(BLACK);
  tft.setRotation(1);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
    setLeftEYEOPEN();
    delay(1000);
    setLeftEYEClose();
    delay(1000);
}
void setLeftEYEOPEN(){
  tft.fillRect(0,0,160,120,BLACK);
  tft.fillCircle(50,50,50,WHITE);
  tft.fillRect(0,120,320,120,BLACK);
  tft.drawBitmap(0, 120, face, 320, 120, WHITE);
  
   tft.fillRect(160,0,160,120,BLACK);
  tft.fillCircle(160+50,50,50,WHITE);
}
void setLeftEYEClose(){
   tft.fillRect(0,120,320,120,BLACK);
   tft.drawBitmap(0, 120, faceTitled, 320, 120, WHITE);
   tft.fillRect(0,0,160,120,BLACK);
   tft.drawBitmap(0, 0, blinkEye, 160, 120, WHITE);
  
}
