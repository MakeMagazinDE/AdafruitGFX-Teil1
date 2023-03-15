#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);

#define potPin 34

int range = 320;
int radius1 = 28;

/*************************************/
/*   Berechnung des Balken-Rahmens   */
/*************************************/

void border(int xCen, int yCen, int r, int color){

  int brSpace;
  int brHeight;

  int segHeight = r/5;      
  int segLength = r/5;       

  //Feste Rahmen-Abstände, falls Radius kleiner als 50
  if (r < 50){
    brHeight = 1;
    brSpace = 3;
  } else {
    brHeight = segHeight/4;
    brSpace = segHeight/3;
  }

  //Rahmen-Bögen zeichnen
  for (int i = 0; i < range; i += segLength){

    //Radien für den unteren Bogen
    int r1 = r - (segHeight + brSpace);
    int r1Inner = r1 - brHeight;
    //Radien für den oberen Bogen
    int r2 = r + (brSpace + brHeight);
    int r2Inner = r2 - brHeight;

    //Segment Startpunkt-Winkel berechnen
    float sx = cos(radians(i - (range/2 + 90)));
    float sy = sin(radians(i - (range/2 + 90)));

    //Segment Endpunkt-Winkel berechnen
    float ex = cos(radians(i - (range/2 + 90) + segLength));
    float ey = sin(radians(i - (range/2 + 90) + segLength));
    
    //Unterer Bogen Segment-Startkoordinaten
    int x = sx * r1Inner + xCen;
    int y = sy * r1Inner + yCen;
    int x1 = sx * r1 + xCen;
    int y1 = sy * r1 + yCen;

    //Unterer Bogen Segment-Endkoordinaten
    int x2 = ex * r1Inner + xCen;
    int y2 = ey * r1Inner + yCen;
    int x3 = ex * r1 + xCen;
    int y3 = ey * r1 + yCen;

    //Oberer Bogen Segment-Startkoordinaten
    int x4 = sx * r2Inner + xCen;
    int y4 = sy * r2Inner + yCen;
    int x5 = sx * r2 + xCen;
    int y5 = sy * r2 + yCen;
    //Oberer Bogen Segment-Endkoordinaten
    int x6 = ex * r2Inner + xCen;
    int y6 = ey * r2Inner + yCen;
    int x7 = ex * r2  + xCen;
    int y7 = ey * r2 + yCen;

    //Unteren Bogen zeichnen
    display.fillTriangle(x, y, x1, y1, x2, y2, color);
    display.fillTriangle(x1, y1, x2, y2, x3, y3, color);
    //Oberen Bogen zeichnen
    display.fillTriangle(x4, y4, x5, y5, x6, y6, color);
    display.fillTriangle(x5, y5, x6, y6, x7, y7, color);
  }
}

/******************************/
/*   Berechnung des Balkens   */
/******************************/

void bar(int xCen, int yCen, int r, int color, int potValue){
  
  int segLength = r/5;
  int rInner = r - r/5;

  for (int i = 0; i < range; i += segLength){  

    //Segment Startpunkt
    float sx = cos(radians(i - (range/2 + 90)));
    float sy = sin(radians(i - (range/2 + 90)));

    //Segment Endpunkt
    float ex = cos(radians(i - (range/2 + 90) + segLength));
    float ey = sin(radians(i - (range/2 + 90) + segLength));

    //Segment Startkoordinaten
    int x = sx * rInner + xCen;
    int y = sy * rInner + yCen;
    int x1 = sx * r + xCen;
    int y1 = sy * r + yCen;
    
    //Segment-Endkoordinaten
    int x2 = ex * rInner + xCen;
    int y2 = ey * rInner + yCen;
    int x3 = ex * r + xCen;
    int y3 = ey * r + yCen;

    if (i < potValue) {
      display.fillTriangle(x, y, x1, y1, x2, y2, color);
      display.fillTriangle(x1, y1, x2, y2, x3, y3, color);
    } else {
      display.fillTriangle(x, y, x1, y1, x2, y2, 0);
      display.fillTriangle(x1, y1, x2, y2, x3, y3, 0);
    }
  }
}

void setup() {
  Serial.begin(9600);
  delay(250);
  display.begin(SSD1306_SWITCHCAPVCC,0x03C);

  display.clearDisplay();
  border(63, 31, radius1, 1);
  display.display();
}

void loop(){

  int potValue = map(analogRead(potPin), 0, 4095, 0, range);    //Poti-Wert auf Balken übertragen
  bar(63, 31, radius1, 1, potValue);                            //Balken mit Poti-Wert zeichnen
  
  display.display();
}