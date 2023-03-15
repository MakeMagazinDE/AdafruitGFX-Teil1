#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Fonts/Picopixel.h>

#define TFT_DC 2
#define TFT_CS 15
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC);

#define potPin 34


/************************************************/
/* Funktion zum Ausrichten der STANDARD-Schrift */
/************************************************/

void standardFontAlign(const String &lorem, int option, int x, int y, int fontScale, int fontColor){
  
  int16_t x1, y1;
  uint16_t w, h;
  
  display.setTextSize(fontScale);
  display.setTextColor(fontColor);
  display.getTextBounds(lorem, x, y, &x1, &y1, &w, &h);       //Größe des Textes berechnen

  if(option == 0){
    display.setCursor(x-w/2, y);                              //MITTE OBEN
    
  } else if(option == 1){
    display.setCursor(x-w, y);                                //RECHTS OBEN
  
  } else if(option == 2){
    display.setCursor(x-w, y-h/2);                            //RECHTS MITTE
    
  } else if(option == 3){
    display.setCursor(x-w, y-h);                              //RECHTS UNTEN
    
  } else if(option == 4){
    display.setCursor(x-w/2, y-h);                            //MITTE UNTEN
    
  } else if(option == 5){
    display.setCursor(x, y-h);                                //LINKS UNTEN

  } else if(option == 6){
    display.setCursor(x, y-h/2);                              //LINKS MITTE

  } else if(option == 7){
    display.setCursor(x, y);                                  //LINKS OBEN

  } else if(option == 8){
    display.setCursor(x-w/2, y-h/2);                          //MITTE MITTE

  }
  
  display.print(lorem);

}



/******************************************************/
/* Funktion zum Ausrichten SELBST GEWÄHLTER Schriften */
/******************************************************/
void customFontAlign(const String &lorem, int option, int x, int y, int fontScale, int fontColor){

  int16_t x1, y1;
  uint16_t w, h;

  display.setTextSize(fontScale);
  display.setTextColor(fontColor);
  display.getTextBounds(lorem, x, y, &x1, &y1, &w, &h);         //Größe des Textes berechnen

  if(option == 0){
    display.setCursor(x-w/2, y+h-fontScale);                              //MITTE OBEN
    
  } else if(option == 1){
    display.setCursor(x-w, y+h-fontScale);                                //RECHTS OBEN
  
  } else if(option == 2){
    display.setCursor(x-w, y+h/2-fontScale);                              //RECHTS MITTE
    
  } else if(option == 3){
    display.setCursor(x-w, y-fontScale);                                  //RECHTS UNTEN
    
  } else if(option == 4){
    display.setCursor(x-w/2, y-fontScale);                            	  //MITTE UNTEN
    
  } else if(option == 5){
    display.setCursor(x, y-fontScale);                                	  //LINKS UNTEN

  } else if(option == 6){
    display.setCursor(x, y+h/2-fontScale);				                        //LINKS MITTE

  } else if(option == 7){
    display.setCursor(x, y+h-fontScale);                                  //LINKS OBEN

  } else if(option == 8){
    display.setCursor(x-w/2, y+h/2-fontScale);				                    //MITTE MITTE

  }

  display.print(lorem);

}




void setup() {

  display.begin();
  display.setRotation(1);

  display.fillScreen(ILI9341_BLACK);

  display.setTextWrap(false);
  display.setFont(&Picopixel);      //muss auskommentiert werden, wenn man standardFontAlign verwenden möchte


}

void loop() {

  int potValue = map(analogRead(potPin),0,4095,0,255);

  display.fillScreen(ILI9341_BLACK);


  customFontAlign(String(potValue), 0, 159, 0, 4, ILI9341_WHITE);
  customFontAlign(String(potValue), 1, 319, 0, 5, ILI9341_WHITE);
  customFontAlign(String(potValue), 2, 319, 119, 4, ILI9341_WHITE);
  customFontAlign(String(potValue), 3, 319, 239, 5, ILI9341_WHITE);
  customFontAlign(String(potValue), 4, 159, 239, 4, ILI9341_WHITE);
  customFontAlign(String(potValue), 5, 0, 239, 5, ILI9341_WHITE);
  customFontAlign(String(potValue), 6, 0, 119, 4, ILI9341_WHITE);
  customFontAlign(String(potValue), 7, 0, 0, 5, ILI9341_WHITE);
  customFontAlign(String(potValue), 8, 159, 119, 8, ILI9341_WHITE);


/*
  standardFontAlign(String(potValue), 0, 159, 0, 4, ILI9341_WHITE);
  standardFontAlign(String(potValue), 1, 319, 0, 4, ILI9341_WHITE);
  standardFontAlign(String(potValue), 2, 319, 119, 4, ILI9341_WHITE);
  standardFontAlign(String(potValue), 3, 319, 239, 4, ILI9341_WHITE);
  standardFontAlign(String(potValue), 4, 159, 239, 4, ILI9341_WHITE);
  standardFontAlign(String(potValue), 5, 0, 239, 4, ILI9341_WHITE);
  standardFontAlign(String(potValue), 6, 0, 119, 4, ILI9341_WHITE);
  standardFontAlign(String(potValue), 7, 0, 0, 4, ILI9341_WHITE);
  standardFontAlign(String(potValue), 8, 159, 119, 4, ILI9341_WHITE);
*/

  
}
