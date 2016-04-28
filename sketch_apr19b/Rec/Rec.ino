/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include <SD.h>
#include "RF24.h"
#include <UTFT.h>
#include <avr/pgmspace.h>

extern uint8_t SmallFont[];
UTFT myGLCD(ILI9325D_16, 38, 39, 40, 41);
/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;
//String RGB;
File myPic;

struct dataStruct{
  long R;
  long G;
  long B;
  }RGB;
  
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"};

int x = 0;
int y = 0;
int x1 = 0;
int y1 = 0;
int num = 0;
long num2 = 0;
//unsigned int pic[4800];
void setup() {
  Serial.begin(115200);
  radio.begin();

  //set up TFT display
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  myGLCD.fillScr(0, 0, 0);
  myGLCD.setColor(255, 255, 255);

  //set up SD card
  pinMode(53, OUTPUT);

  if (!SD.begin(53)) {
    Serial.println("SD Failed!");
    return;
  }
  else {
    Serial.println("SD READY!");
  }


  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(108);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  
  // Start the radio listening for data
  radio.startListening();
}

void loop() {     
    if( radio.available()){
                                                      // Variable for the received timestamp
      while (radio.available()) {                     // While there is data ready
        radio.read( &RGB, sizeof(RGB));             // Get the payload
      }
     
      //Serial.print(F("Sent response "));
      //Serial.println(RGB.R);
      //Serial.println(RGB.G);
      //Serial.println(RGB.B);
      
      /*
      byte red = RGB.R;
      byte green = RGB.G;
      byte blue = RGB.B;
      int col = ((red & 0xF8) << 8)|((green & 0xFC) << 3)|((blue & 0xF8) >> 3);
      if(num > 4800){
        myGLCD.drawBitmap (x, y, 320, 15, pic);
        num = 0;
        y += 15;
      }
      pic[num] = col;
      num++;
     */
      
      myGLCD.setColor(RGB.R, RGB.G, RGB.B);
      myGLCD.drawPixel(x, y);

      if(x == 320){
        y++;
        x = 0;
      }
      if(y > 240){
        y = 0;
      }
      x++;
      
      /*
      myPic = SD.open("myPic.txt", FILE_WRITE);
      if (myPic){
        Serial.println("Writing to File");
        myPic.println(RGB.R);
        myPic.println(RGB.G);
        myPic.println(RGB.B);
        myPic.close();  
      }
      else {
        Serial.println("Could not write to file");
        myPic.close();
      }
      */
   }
 

} // Loop
