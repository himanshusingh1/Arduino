/*====================================================================================

  This sketch demonstrates loading images which have been stored as files in the
  built-in FLASH memory on a NodeMCU 1.0 (ESP8266 based, ESP-12E Module) or ESP32
  board, rendering the images onto a ILI9341 SPI 320 x 240 pixel TFT screen.

  The images are stored in the SPI FLASH Filing System (SPIFFS), which effectively
  functions like a tiny "hard drive". This filing system is built into the ESP8266
  Core that can be loaded from the IDE "Boards manager" menu option. This is at
  version 2.3.0 at the time of sketch creation.

  The size of the SPIFFS partition can be set in the IDE as 1Mbyte or 3Mbytes. Either
  will work with this sketch. Typically most sketches easily fit within 1 Mbyte so a
  3 Mbyte SPIFS partition can be used, in which case it can contain ~18 full screen
  320 x 240 raw images (150 Kbytes each) or 100's of Jpeg full screem images.

  The ESP8266 or ESP32 with the TFT and sketch works with the library here:
  https://github.com/Bodmer/TFT_eSPI

  The Jpeg library can be found here:
  https://github.com/Bodmer/JPEGDecoder
 
  Images in the Jpeg format can be created using Paint or IrfanView or other picture
  editting software.

  Place the images inside the sketch folder, in a folder called "Data".  Then upload
  all the files in the folder using the Arduino IDE "ESP8266 Sketch Data Upload" or
  "ESP32 Sketch Data Upload" option in the "Tools" menu:
  http://www.esp8266.com/viewtopic.php?f=32&t=10081
  https://github.com/esp8266/arduino-esp8266fs-plugin/releases

  https://github.com/me-no-dev/arduino-esp32fs-plugin
  
  Upload takes some time, but the SPIFFS content is not altered when a new sketch is
  uploaded, so there is no need to upload the same files again!
  Note: If open, you must close the "Serial Monitor" window to upload data to SPIFFS!

  The IDE will not copy the "data" folder with the sketch if you save the sketch under
  another name. It is necessary to manually make a copy and place it in the sketch
  folder.

  The sketch may crash on an ESP32 if the jpeg file does not exist in the SPIFFS

  This sketch includes example images in the Data folder.

  Saving images, uploading and rendering on the TFT screen couldn't be much easier!

  The typical setup for a NodeMCU1.0 (ESP-12 Module) is :

  Display SDO/MISO      to NodeMCU pin D6 <<<<<< This is not used by this sketch
  Display LED           to NodeMCU pin  5V or 3.3V
  Display SCK           to NodeMCU pin D5
  Display SDI/MOSI      to NodeMCU pin D7
  Display DC/RS (or AO) to NodeMCU pin D3
  Display RESET         to NodeMCU pin D4 <<<<<< Or connect to NodeMCU RST pin
  Display CS            to NodeMCU pin D8
  Display GND           to NodeMCU pin GND (0V)
  Display VCC           to NodeMCU pin 5V or 3.3V

  Note: only some versions of the NodeMCU provide the USB 5V on the VIN pin
  If 5V is not available at a pin you can use 3.3V but backlight brightness
  will be lower.

  If the TFT RESET signal is connected to the NodeMCU RST line then define the pin
  in the TFT library User_Config.h file as negative so the library ignores it,
  e.g. TFT_RST -1

  Created by Bodmer 24th Jan 2017 - Tested in Arduino IDE 1.8.0 esp8266 Core 2.3.0
  ==================================================================================*/

//====================================================================================
//                                  Libraries
//====================================================================================
// Call up the SPIFFS FLASH filing system this is part of the ESP Core
#define FS_NO_GLOBALS
#include <FS.h>

#ifdef ESP32
  #include "SPIFFS.h" // ESP32 only
#endif

// JPEG decoder library
#include <JPEGDecoder.h>

#include <TFT_22_ILI9225.h>

#define TFT_RST D0
#define TFT_RS  D1
#define TFT_CS  D8  // SS
#define TFT_SDI D7  // MOSI
#define TFT_CLK D5  // SCK
#define TFT_LED D2   // 0 if wired to +5V directly

// Use hardware SPI (faster - on Uno: 13-SCK, 12-MISO, 11-MOSI)
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);

//====================================================================================
//                                    Setup
//====================================================================================
void setup()
{
  Serial.begin(250000); // Used for messages and the C array generator

  delay(10);
  Serial.println("NodeMCU decoder test!");

  tft.begin();
  tft.setOrientation(0);  // 0 & 2 Portrait. 1 & 3 landscape
  tft.setBackgroundColor(COLOR_WHITE);
  tft.fillRectangle(0,0,176,220,COLOR_WHITE);
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }
  Serial.println("\r\nInitialisation done.");
  listFiles(); // Lists the files so you can see what is in the SPIFFS
}

//====================================================================================
//                                    Loop
//====================================================================================
void loop()
{
//  for(int i = 0 ; i < 100 ; i ++){
//  tft.clear();
  drawJpeg("/l_eye_1.jpg", 20 , 20);
  drawJpeg("/r_eye_1.jpg", 100 , 20);
  drawJpeg("/mouth_6.jpg", 63 , 110);

//  drawJpeg("/l_eye_2.jpg", 20 , 20);
//  drawJpeg("/r_eye_2.jpg", 100 , 20);
//  drawJpeg("/mouth_2.jpg", 63 , 150);

//  drawJpeg("/l_eye_3.jpg", 20 , 20);
//  drawJpeg("/r_eye_3.jpg", 100 , 20);
//  drawJpeg("/mouth_3.jpg", 63 , 150);
  
//  drawJpeg("/l_eye_4.jpg", 20 , 20);
//  drawJpeg("/r_eye_4.jpg", 100 , 20);
//  drawJpeg("/mouth_4.jpg", 63 , 150);

//  drawJpeg("/l_eye_5.jpg", 20 , 20);
//  drawJpeg("/r_eye_5.jpg", 100 , 20);
//  drawJpeg("/mouth_5.jpg", 63 , 150);

  drawJpeg("/l_eye_6.jpg", 20 , 20);
//  drawJpeg("/r_eye_6.jpg", 100 , 20);
//  drawJpeg("/mouth_6.jpg", 63 , 150);
//  } 
delay(1000);
}
//====================================================================================
