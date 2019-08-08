#include "MCUFRIEND_kbv.h"
#include "bitmap_mono.h"
#include "b.h"
#include "c.h"
#include "d.h"
#include "e.h"
#include "f.h"
#include "g.h"
#include "h.h"
#include "i.h"
#include "j.h"
#include "k.h"
#include "l.h"
#include "m.h"
#include "n.h"
#include "o.h"

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0x8410
#define ORANGE  0xE880
MCUFRIEND_kbv tft;

void setup()
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();

    Serial.print(F("ID = 0x"));
    Serial.println(ID, HEX);

    Serial.println(F("GFX drawBitmap() plots one mono pixel at a time"));
    Serial.println(F("it defaults to transparent plotting"));
    Serial.println(F("unless you specify foreground and background colours"));
    Serial.println(F("it can plot a monochrome bitmap from Flash or SRAM"));

    Serial.println(F(""));
    Serial.println(F("GFX drawGrayscaleBitmap() is not relevant for OLED, TFT"));
    Serial.println(F("GFX drawRGBBitmap() plots one colour pixel at a time"));
    Serial.println(F("from Flash or SRAM and with a monochrome transparent bitmask"));
    Serial.println(F(""));
    Serial.println(F("Using the hardware pushColors() methods is faster"));
    Serial.println(F("pushColors() expects uint16 array in SRAM"));
    Serial.println(F("for any runtime generated images"));
    Serial.println(F("but it expects uint8_t array of serialised bytes in Flash"));
    Serial.println(F(""));

    Serial.println(F("Colour TFTs are natively big-endian"));
    Serial.println(F("Many microcontrollers and Tools are little-endian"));
    Serial.println(F("you can use the optional argument to select big-end"));
    tft.begin(ID);
    tft.fillScreen(GREY);
}

void loop(void)
{
tft.fillCircle(100,100,50,WHITE);
}
void bla(int x, int y){
      tft.drawBitmap(x,y, tractorb_128x64,128,64,BLUE);
  }
