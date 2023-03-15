#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_DC 2
#define TFT_CS 15
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC);

#define potPin 34


void setup() {

  display.begin();
  display.setRotation(1);

  display.fillScreen(ILI9341_BLACK);

}

void loop() {

  int potValue = map(analogRead(potPin),0,4095,0,56);
  
  int x = 320/2 - 60/2 - 1;
  int y = 240/2 - 12/2 - 1;

  display.drawRect(x, y, 60, 12, ILI9341_WHITE);
  display.fillRect(x+1, y+1, 58, 10, ILI9341_BLACK);
  display.fillRect(x+2, y+2, potValue, 8, ILI9341_RED);

}
