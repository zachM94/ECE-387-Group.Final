/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include <SD.h>
#include "RF24.h"

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 1;
int picNum = 3;
String RGB;
long count;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"};
unsigned long msg;
int startButton = 0;
int DIBSize;
File myPic;

void setup() {
  Serial.begin(115200);
  radio.begin();
    //set up SD card
  pinMode(53, OUTPUT);
  if (!SD.begin(53)) {
    Serial.println("SD Failed!");
    return;
  }
  else {
    Serial.println("SD READY!");
  }
   myPic = SD.open("test.bmp");
  if (myPic) {
    Serial.println("test:");
    
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  radio.stopListening();
}
}
void loop() {
  if (startButton) {
    for(int k = 0; k < picNum; k++) {
      myPic = SD.open("pic1.bmp");
      if (myPic) {
        Serial.println(k);
      }
    }
    for(int x = 0; x<14;x++){
      myPic.read();
      Serial.println(x);
    }    
    DIBSize = myPic.read();
    for(int j = 0;j < (DIBSize-1); j++ ){
      myPic.read();
    }
    count = 0;
    while (count != 76800){
      RGB = "";
      RGB = String(myPic.read(), HEX);//R
      RGB.concat(String(myPic.read(), HEX));//G
      RGB.concat(String(myPic.read(), HEX));//B
      if (!radio.write( &RGB, sizeof(RGB) )){
       Serial.println(F("failed"));
     }
    }
    }
  else {
    delay(1000);
  }
}
