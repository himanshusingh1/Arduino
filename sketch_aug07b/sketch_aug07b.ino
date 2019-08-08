#include <SPI.h>
#include <TFT_22_ILI9225.h>
#include "face.h"
#include "face2.h"
// #define TFT_RST 8
// #define TFT_RS  9
// #define TFT_CS  10  // SS
// #define TFT_SDI 11  // MOSI
// #define TFT_CLK 13  // SCK
// #define TFT_LED 3   // 0 if wired to +5V directly

#define TFT_RST D4
#define TFT_RS  D2
#define TFT_CS  D8  // SS
#define TFT_SDI D7  // MOSI
#define TFT_CLK D5  // SCK
#define TFT_LED D1   // 0 if wired to +5V directly

// Use hardware SPI (faster - on Uno: 13-SCK, 12-MISO, 11-MOSI)
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);
// Use software SPI (slower)
//TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_SDI, TFT_CLK, TFT_LED);

// Variables and constants
// uint16_t x, y;
// boolean flag = false;

// Setup

void setup() {
  Serial.begin(115200);
  Serial.println("STARTED");
  tft.begin();
  SPI.beginTransaction(SPISettings(12000000, MSBFIRST, SPI_MODE0));

  Serial.begin(9600);
  tft.setBackgroundColor(COLOR_BLACK);
  tft.drawBitmap(0,0,blinkEye,160,120,COLOR_WHITE);


}

// Loop
void loop() {
}
