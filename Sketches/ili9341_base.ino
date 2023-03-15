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

  int potValue = map(analogRead(potPin),0,4095,0,1234);
  
}
