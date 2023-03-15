#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/Picopixel.h>

#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define potPin 34
int potValue = 0;
int cMax = 255;


/************************************************/
/* Funktion zum Ausrichten der STANDARD-Schrift */
/************************************************/
/* Auch wenn die Standard-Schrift von sich aus  */
/* anbietet, eine Hintergrundfarbe zu wählen,   */
/* besteht das Problem, dass beim Wechsel von   */
/* z.B. 100 auf 99 links und rechts Artefakte   */
/* bleiben. Daher berechne ich auch für die     */
/* Standard-Schrift ein Rechteck mit cMax, dem  */
/* maximalen und somit ausladensten Wert, den   */
/* die Variable haben kann.                     */
/************************************************/

void standardFontAlign(String lorem, String maxValue, int option, int x, int y, int fontScale, int fontColor, int bgrColor){
  
  int16_t x1, y1;
  uint16_t w, h;
  uint16_t wL, hL;
  
  display.setTextSize(fontScale);
  display.setTextColor(fontColor, bgrColor);
  display.getTextBounds(lorem, x, y, &x1, &y1, &w, &h);       //Größe des Textes berechnen
  display.getTextBounds(maxValue, x, y, &x1, &y1, &wL, &hL);      //Größe des Löschrechtecks berechnen

  if(option == 0){
    display.setCursor(x-w/2, y);                              //MITTE OBEN
    display.fillRect(x-wL/2, y, wL, hL, 0);                   //Löschrechteck anwenden

  } else if(option == 1){
    display.setCursor(x-w, y);                                //RECHTS OBEN
    display.fillRect(x-wL, y, wL, hL, 0);                     //Löschrechteck anwenden

  } else if(option == 2){
    display.setCursor(x-w, y-h/2);                            //RECHTS MITTE
    display.fillRect(x-wL, y-hL/2, wL, hL, 0);                //Löschrechteck anwenden

  } else if(option == 3){
    display.setCursor(x-w, y-h);                              //RECHTS UNTEN
    display.fillRect(x-wL, y-hL, wL, hL, 0);                  //Löschrechteck anwenden

  } else if(option == 4){
    display.setCursor(x-w/2, y-h);                            //MITTE UNTEN
    display.fillRect(x-wL/2, y-hL, wL, hL, 0);                //Löschrechteck anwenden

  } else if(option == 5){
    display.setCursor(x, y-h);                                //LINKS UNTEN
    display.fillRect(x, y-hL, wL, hL, 0);                     //Löschrechteck anwenden

  } else if(option == 6){
    display.setCursor(x, y-h/2);                              //LINKS MITTE
    display.fillRect(x, y-hL/2, wL, hL, 0);                   //Löschrechteck anwenden

  } else if(option == 7){
    display.setCursor(x, y);                                  //LINKS OBEN
    display.fillRect(x, y, wL, hL, 0);                        //Löschrechteck anwenden


  } else if(option == 8){
    display.setCursor(x-w/2, y-h/2);                          //MITTE MITTE
    display.fillRect(x-wL/2, y-hL/2, wL, hL, 0);              //Löschrechteck anwenden
  }
  
  display.print(lorem);

}



/******************************************************/
/* Funktion zum Ausrichten SELBST GEWÄHLTER Schriften */
/* mit experimentellem Löschen des Texthintergrundes  */
/******************************************************/
/* Ändert fillRect in drawRect und wählt eine andere  */
/* Farbe für bgr, z.B. ILI9341_RED. Dann könnt ihr    */
/* sehen, wie der Löschbalken platziert wird. Ich     */
/* habe alle Werte mit Offsets versehen, weil sich    */
/* die Schrift mit zunehmender Skalierung weiter      */
/* verschiebt. Ich habe noch nicht herausgefunden,    */
/* woran das liegt.                                   */
/******************************************************/

void customFontAlign(String lorem, String maxValue, int option, int x, int y, int fontScale, int fontColor, int bgrColor){

  int16_t x1, y1;
  uint16_t w, h;

  uint16_t wL, hL;

  display.setTextSize(fontScale);
  display.setTextColor(fontColor);
  display.getTextBounds(lorem, x, y, &x1, &y1, &w, &h);         //Größe des Textes berechnen
  display.getTextBounds(maxValue, x, y, &x1, &y1, &wL, &hL);        //Größe des Löschrechtecks berechnen

  if(option == 0){
    display.setCursor(x-w/2, y+h-fontScale);                              //MITTE OBEN
    display.fillRect(x-wL/2-3, y-2, wL+6, hL+4, bgrColor);           //Löschrechteck

  } else if(option == 1){
    display.setCursor(x-w, y+h-fontScale);                                //RECHTS OBEN
    display.fillRect(x-wL, y-2, wL+3, hL+4, bgrColor);               //Löschrechteck

  } else if(option == 2){
    display.setCursor(x-w, y+h/2-fontScale);                              //RECHTS MITTE
    display.fillRect(x-wL-3, y-hL/2-2, wL+6, hL+4, bgrColor);        //Löschrechteck

  } else if(option == 3){
    display.setCursor(x-w, y-fontScale);                                  //RECHTS UNTEN
    display.fillRect(x-wL-3, y-hL-2, wL+6, hL+4, bgrColor);          //Löschrechteck

  } else if(option == 4){
    display.setCursor(x-w/2, y-fontScale);                            	  //MITTE UNTEN
    display.fillRect(x-wL/2-3, y-hL-2, wL+6, hL+4, bgrColor);        //Löschrechteck

  } else if(option == 5){
    display.setCursor(x, y-fontScale);                                	  //LINKS UNTEN
    display.fillRect(x-3, y-hL-2, wL+6, hL+4, bgrColor);             //Löschrechteck

  } else if(option == 6){
    display.setCursor(x, y+h/2-fontScale);				                        //LINKS MITTE
    display.fillRect(x-3, y-hL/2-2, wL+6, hL+4, bgrColor);           //Löschrechteck

  } else if(option == 7){
    display.setCursor(x, y+h-fontScale);                                  //LINKS OBEN
    display.fillRect(x-3, y-2, wL+6, hL+4, bgrColor);                //Löschrechteck

  } else if(option == 8){
    display.setCursor(x-w/2, y+h/2-fontScale);				                    //MITTE MITTE
    display.fillRect(x-wL/2-3, y-hL/2-2, wL+6, hL+4, bgrColor);      //Löschrechteck

  }

  display.print(lorem);

}





void setup() {

  Serial.begin(9600);
  delay(250);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

  display.clearDisplay();

  display.setTextWrap(false);
  display.setFont(&Picopixel);      //muss auskommentiert werden, wenn man standardFontAlign verwenden möchte

  display.display();

}

void loop() {

  int potValue = map(analogRead(potPin),0,4095,0,cMax);


  customFontAlign(String(potValue), String(cMax), 0, 63, 0, 1, 1, 0);
  customFontAlign(String(potValue), String(cMax), 1, 127, 0, 3, 1, 0);
  customFontAlign(String(potValue), String(cMax), 2, 127, 31, 1, 1, 0);
  customFontAlign(String(potValue), String(cMax), 3, 127, 63, 3, 1, 0);
  customFontAlign(String(potValue), String(cMax), 4, 63, 63, 1, 1, 0);
  customFontAlign(String(potValue), String(cMax), 5, 0, 63, 3, 1, 0);
  customFontAlign(String(potValue), String(cMax), 6, 0, 31, 1, 1, 0);
  customFontAlign(String(potValue), String(cMax), 7, 0, 0, 3, 1, 0);
  customFontAlign(String(potValue), String(cMax), 8, 63, 31, 5, 1, 0);


/*
  standardFontAlign(String(potValue), String(cMax), 0, 63, 0, 1, 1, 0);
  standardFontAlign(String(potValue), String(cMax), 1, 127, 0, 3, 1, 0);
  standardFontAlign(String(potValue), String(cMax), 2, 127, 31, 1, 1, 0);
  standardFontAlign(String(potValue), String(cMax), 3, 127, 63, 3, 1, 0);
  standardFontAlign(String(potValue), String(cMax), 4, 63, 63, 1, 1, 0);
  standardFontAlign(String(potValue), String(cMax), 5, 0, 63, 3, 1, 0);
  standardFontAlign(String(potValue), String(cMax), 6, 0, 31, 1, 1, 0);
  standardFontAlign(String(potValue), String(cMax), 7, 0, 0, 3, 1, 0);
  standardFontAlign(String(potValue), String(cMax), 8, 63, 31, 5, 1, 0);
*/

  display.display();
  
}
