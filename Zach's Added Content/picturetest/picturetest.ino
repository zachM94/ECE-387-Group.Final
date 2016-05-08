/* I am Providing this code in my contribtuion section because this was the beginning stages of my picture print algorithm.
 * In this code, I am printing and 80x60 pixel image. The pixel data for this image is saved in an array with a size of 4800 values. 
 * For the final version of our code, we did not use arrays because we had to print pictures of size 320x240 pixels. These pictures
 * would require an array with 76800 elements. The algorithm here is still the same general technique used in the final code.
 */




#include <UTFT.h>
#include <avr/pgmspace.h>

extern uint8_t SmallFont[];

UTFT myGLCD(ILI9325D_16, 38, 39, 40, 41);

extern unsigned int pic1[4800];

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
    
  unsigned int picture[1];

 
  for(int i = 0; i < 60; i++){
    for(int j = 0; j < 80; j++){
      if(x == 4800){
        break;
      }
      picture[0] = pgm_read_word_near(pic1 + x);
      myGLCD.setColor(picture[0]);
      myGLCD.drawPixel(j, i);
      x++;
    }
  }
  
 
}
