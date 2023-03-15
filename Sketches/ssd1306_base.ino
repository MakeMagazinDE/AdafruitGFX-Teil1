#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);

#define potPin 34

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC,0x03C);

  display.clearDisplay();
  display.display();
}

void loop(){

  int potValue = map(analogRead(potPin), 0, 4095, 0, 1234);
  
  display.display();
}