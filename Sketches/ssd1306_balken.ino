#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);

#define potPin 34


void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x03C);

  display.clearDisplay();
  display.display();

}

void loop(){

  int potValue = map(analogRead(potPin), 0, 4095, 0, 56);
  
  int x = 128/2 - 60/2 - 1;
  int y = 64/2 - 12/2 - 1;

  display.drawRect(x, y, 60, 12, 1);
  display.fillRect(x+1, y+1, 58, 10, 0);
  display.fillRect(x+2, y+2, potValue, 8, 1);
  display.display();
}