#include <UTFT.h>
#include <avr/pgmspace.h>

extern uint8_t SmallFont[];

// Set the pins to the correct ones for your development shield
// ------------------------------------------------------------
// Arduino Uno / 2009:
// -------------------
// Standard Arduino Uno/2009 shield            : <display model>,A5,A4,A3,A2
// DisplayModule Arduino Uno TFT shield        : <display model>,A5,A4,A3,A2
//
// Arduino Mega:
// -------------------
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Mega      : <display model>,38,39,40,41
//
// Remember to change the model parameter to suit your display module!
UTFT myGLCD(ILI9325D_16, 38, 39, 40, 41);

extern unsigned int pic1[4800];
//extern unsigned int pic2[2400];
/*
extern unsigned int wilson2[4800];
extern unsigned int wilson3[4800];
extern unsigned int wilson4[4800];
extern unsigned int wilson5[4800];
extern unsigned int wilson6[4800];
extern unsigned int wilson7[4800];
extern unsigned int wilson8[4800];
extern unsigned int wilson9[4800];
extern unsigned int wilson10[4800];
extern unsigned int wilson11[4800];
extern unsigned int wilson12[4800];
extern unsigned int wilson13[4800];
extern unsigned int wilson14[4800];
extern unsigned int wilson15[4800];
extern unsigned int wilson16[4800];
*/
int x = 0;
void setup()
{
  
  Serial.begin(9600);
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  myGLCD.fillScr(255, 255, 255);
  myGLCD.setColor(255, 255, 255);
 // Serial.println(pgm_read_word_near(pic1 + 0), HEX);
}

void loop()
{
 
 //myGLCD.drawBitmap (0, 0, 80, 60, pic1, 4);
  //myGLCD.drawBitmap (0, 30, 80, 30, pic2);


    
  unsigned int fun[1];
/*
  for(int i = 0; i < 60; i++){
    for(int j = 0; j < 80; j++){
      if(x == 4800){
        break;
      }
      fun[j] = pgm_read_word_near(pic1 + x);
      x++;
    }
    myGLCD.drawBitmap (0, i, 80, 1, fun, 4);
  }
*/
 
  for(int i = 0; i < 60; i++){
    for(int j = 0; j < 80; j++){
      if(x == 4800){
        break;
      }
      fun[0] = pgm_read_word_near(pic1 + x);
     // myGLCD.drawBitmap (j, i, 1, 1, fun);
      myGLCD.setColor(fun[0]);
      myGLCD.drawPixel(j, i);
     // Serial.print("******");
     // Serial.println(x);
     // Serial.println(fun[0], HEX);
     // Serial.println(pgm_read_word_near(pic1 + x), HEX);
      x++;
    }
  }
  
  
 /*
  myGLCD.drawBitmap (0, 60, 80, 60, wilson2);
  myGLCD.drawBitmap (0, 120, 80, 60, wilson3);
  myGLCD.drawBitmap (0, 180, 80, 60, wilson4);
  
  myGLCD.drawBitmap (80, 0, 80, 60, wilson5);
  myGLCD.drawBitmap (80, 60, 80, 60, wilson6);
  myGLCD.drawBitmap (80, 120, 80, 60, wilson7);
  myGLCD.drawBitmap (80, 180, 80, 60, wilson8);
 
  myGLCD.drawBitmap (160, 0, 80, 60, wilson9);
  myGLCD.drawBitmap (160, 60, 80, 60, wilson10);
  myGLCD.drawBitmap (160, 120, 80, 60, wilson11);
  myGLCD.drawBitmap (160, 180, 80, 60, wilson12);
  
  myGLCD.drawBitmap (240, 0, 80, 60, wilson13);
  myGLCD.drawBitmap (240, 60, 80, 60, wilson14);
  myGLCD.drawBitmap (240, 120, 80, 60, wilson15);
  myGLCD.drawBitmap (240, 180, 80, 60, wilson16);
  */
}
