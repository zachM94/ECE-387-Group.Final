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

extern unsigned int pic1[0x12C0];
extern unsigned int pic2[0x12C0];
extern unsigned int pic3[0x12C0];
extern unsigned int pic4[0x12C0];


void setup()
{
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
}

void loop()
{
  myGLCD.drawBitmap (0, 0, 80, 60, pic1);
  myGLCD.drawBitmap (80, 0, 80, 60, pic2);
  myGLCD.drawBitmap (0, 60, 80, 60, pic3);
  myGLCD.drawBitmap (80, 60, 80, 60, pic4);
  
  myGLCD.drawBitmap (160, 0, 80, 60, pic1);
  myGLCD.drawBitmap (240, 0, 80, 60, pic2);
  myGLCD.drawBitmap (160, 60, 80, 60, pic3);
  myGLCD.drawBitmap (240, 60, 80, 60, pic4);
  
  myGLCD.drawBitmap (0, 120, 80, 60, pic1);
  myGLCD.drawBitmap (80, 120, 80, 60, pic2);
  myGLCD.drawBitmap (0, 180, 80, 60, pic3);
  myGLCD.drawBitmap (80, 180, 80, 60, pic4);
  
  myGLCD.drawBitmap (160, 120, 80, 60, pic1);
  myGLCD.drawBitmap (240, 120, 80, 60, pic2);
  myGLCD.drawBitmap (160, 180, 80, 60, pic3);
  myGLCD.drawBitmap (240, 180, 80, 60, pic4);

}
