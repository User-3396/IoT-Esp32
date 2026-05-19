// Demo based on:
// UTFT_Demo by Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
/*

 The delay between tests is set to 0. The tests run so fast you will need to
 change the WAIT value below to see what is being plotted!
 
 This sketch uses the GLCD and font 2 only.

 Make sure all the required fonts are loaded by editting the
 User_Setup.h file in the TFT_eSPI library folder.

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  ######            TO SELECT THE FONTS YOU USE, SEE ABOVE           ######
  #########################################################################
 */

#define CENTRE 120

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();                   // Invoke custom library with default width and height

#define TFT_GREY 0x7BEF

uint32_t runTime = 0;

void setup()
{
  randomSeed(analogRead(0));
  Serial.begin(115200);
  delay(1000);

// Setup the LCD
  tft.init();
  tft.setRotation(1);
}

void loop()
{
  //Serial.printf("ST7789_DRIVER: MOSI=%d SCL=%d CS=%d DC=%d RST=%d\n", TFT_MOSI, TFT_SCLK, TFT_CS, TFT_DC, TFT_RST);
  runTime = millis();

// Clear the screen and draw the frame
  tft.fillScreen(TFT_BLACK);

  tft.fillRect(0, 0, 240, 13, TFT_RED);

  tft.fillRect(0, 225, 240, 240, TFT_GREY);
  tft.setTextColor(TFT_BLACK, TFT_RED);

  tft.drawCentreString("* TFT_eSPI *", CENTRE, 3, 1);
  tft.setTextColor(TFT_YELLOW, TFT_GREY);
  tft.drawCentreString("Adapted by FSC", CENTRE, 229, 1);

  tft.fillRoundRect(60, 70, 120, 120, 3, TFT_RED);
 
  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.drawCentreString("That's it!", CENTRE, 83, 2);
  tft.drawCentreString("Some text here..", CENTRE, 130, 2);
  tft.drawCentreString("and here...", CENTRE, 150, 2);

  tft.setTextColor(TFT_WHITE);
  tft.drawString("And now, simple text, align left...!", 10, 200, 2);

  delay (10000);
}
