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
int picNum = 1;
//String RGB;
long count;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"};
unsigned long msg;
int startButton = 1;
int DIBSize;
File myPic;

struct dataStruct{
  long R;
  long G;
  long B;
  }RGB;

void setup() {
  Serial.begin(115200);
  radio.begin();
    //set up SD card
  pinMode(startButton, INPUT);  
  pinMode(10, OUTPUT);
  if (!SD.begin(10)) {
    Serial.println("SD Failed!");
    return;
  }
  else {
    Serial.println("SD READY!");
  }
   myPic = SD.open("test.bmp");
  if (myPic) {
    Serial.println("test:");

  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(108);    
    
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
      myPic = SD.open("wilson.bmp");
      if (myPic) {
        Serial.println(k);
      }
    }
    for(int x = 0; x<14;x++){
      myPic.read();
      Serial.println(x);
    }    
    DIBSize = myPic.read();
    Serial.println(DIBSize);
    for(int j = 0;j < (DIBSize-1); j++ ){
      myPic.read();
      Serial.println(j);
    }
    count = 0;
    while (count != 76800){
//      RGB = "";
//      RGB = String(myPic.read(), HEX);//R
//      RGB.concat(String(myPic.read(), HEX));//G
//      RGB.concat(String(myPic.read(), HEX));//B
      RGB.R = myPic.read();
      RGB.G = myPic.read();
      RGB.B = myPic.read();
      Serial.println("Printing RGB:");
      Serial.println(RGB.R);
      Serial.println(RGB.G);
      Serial.println(RGB.B);
      if (!radio.write( &RGB, sizeof(RGB) )){
       //Serial.println(F("failed"));
     }
    }
   myPic.close();     
    }
  else 
    delay(1000);

  
}
