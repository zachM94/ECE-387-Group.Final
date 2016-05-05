#include <SPI.h>
#include <SD.h>
#include "RF24.h"
#include <UTFT.h>
#include <avr/pgmspace.h>

extern uint8_t SmallFont[];
UTFT myGLCD(ILI9325D_16, 38, 39, 40, 41);

String RGB_HEX;
File myPic;

struct dataStruct{
  int R_0;
  int G_0;
  int B_0;
  int R_1;
  int G_1;
  int B_1;
  int R_2;
  int G_2;
  int B_2;
  int R_3;
  int G_3;
  int B_3;
  int R_4;
  int G_4;
  int B_4;               
  char stat;
  }RGB;
  
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"};

int x = 0;
//int x1 = 1;
//int x2 = 2;
//int x3 = 3;
//int x4 = 4;
int y = 0;

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
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
   // Start the radio listening for data
  radio.startListening();
}

void loop() {    
   //Getting data from Payload================================
    if( radio.available()){                                                   
      while (radio.available()) {
        radio.read( &RGB, sizeof(RGB));         
      }
    }
    //========================================================

    //Initializing SD card====================================
      myPic = SD.open("myPic.txt", FILE_WRITE);

          
      myGLCD.setColor(RGB.R_0, RGB.G_0, RGB.B_0);
      myGLCD.drawPixel(x, y);
      x = x + 1;
      myGLCD.setColor(RGB.R_1, RGB.G_1, RGB.B_1);
      myGLCD.drawPixel(x, y);
      x = x + 1;
      myGLCD.setColor(RGB.R_2, RGB.G_2, RGB.B_2);
      myGLCD.drawPixel(x, y);
      x = x + 1;
      myGLCD.setColor(RGB.R_3, RGB.G_3, RGB.B_3);
      myGLCD.drawPixel(x, y);
      x = x + 1;
      myGLCD.setColor(RGB.R_4, RGB.G_4, RGB.B_4);
      myGLCD.drawPixel(x, y);
      x = x + 1;
      
      if(x == 320){
        y++;
        x = 0;
      }
      if(y > 240){
        y = 0;
      }


/*
      //========================================================
     //Printing Payload and Manipulate/Save to SD card 
      if (RGB.stat == 1){
        myPic.close();
        delay(10000);//10Sec
      }
     else{
      Serial.print(F("Sent response "));
      Serial.println(RGB.R_0);
      Serial.println(RGB.G)_0;
      Serial.println(RGB.B_0);
      RGB_HEX = "";
      RGB_HEX = String(RGB.R, HEX);//R
      RGB_HEX.concat(String(RGB.G, HEX));//G
      RGB_HEX.concat(String(RGB.B, HEX));//B  
      myPic.println(RGB_HEX);
     }
      //========================================================
  */    
   
 

} // Loop

