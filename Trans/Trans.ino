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
RF24 radio(8,9);
/**********************************************************/

//Button Setup 
const int buttonPin7 = 7;
const int buttonPin6 = 6;
const int buttonPin5 = 5;
const int buttonPin4 = 4;
const int buttonPin3 = 3;
const int buttonPin2 = 2;
int buttonState7 = 0;
int buttonState6 = 0;
int buttonState5 = 0;
int buttonState4 = 0;
int buttonState3 = 0;
int buttonState2 = 0;
int pressed7 = 0;
int pressed6 = 0;
int pressed5 = 0;
int pressed4 = 0;
int pressed3 = 0;
int pressed2 = 0;

byte addresses[][6] = {"1Node","2Node"};
unsigned long startPrint;
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
  radio.setDataRate(RF24_2MBPS);
  
  //set up SD card 
  pinMode(10, OUTPUT);
  if (!SD.begin(10)) {
    Serial.println("SD Failed!");
    return;
  }
  else {
    Serial.println("SD READY!");
  }


  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(108);    
  radio.setPayloadSize(12);
    
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  radio.stopListening();
}
void loop() {

  buttonState7 = digitalRead(buttonPin7);
  buttonState6 = digitalRead(buttonPin6);
  buttonState5 = digitalRead(buttonPin5);
  buttonState4 = digitalRead(buttonPin4);
  buttonState3 = digitalRead(buttonPin3);
  buttonState2 = digitalRead(buttonPin2);

  //*********Print Picture 1*********
  if (buttonState7 == LOW){
    pressed7 = 1;
  }
  else if (buttonState7 == HIGH){
    if (pressed7 == 1) {
      startPrint = 1;
      if (!radio.write( &startPrint, sizeof(unsigned long) )){
        Serial.println(F("failed"));
      }
      
      readPic("pic1.bmp");
      pressed7 = 0;
    }
  }
  //*********************************

  //*********Print Picture 2*********
  if (buttonState6 == LOW){
    pressed6 = 1;
  }
  else if (buttonState6 == HIGH){
    if (pressed6 == 1) {
      startPrint = 1;
      if (!radio.write( &startPrint, sizeof(unsigned long) )){
        Serial.println(F("failed"));
      }
      
      readPic("pic2.bmp");
      pressed6 = 0;
    }
  }
  //*********************************

  //*********Print Picture 3*********
  if (buttonState5 == LOW){
    pressed5 = 1;
  }
  else if (buttonState5 == HIGH){
    if (pressed5 == 1) {
      startPrint = 1;
      if (!radio.write( &startPrint, sizeof(unsigned long) )){
        Serial.println(F("failed"));
      }
      
      readPic("pic3.bmp");
      pressed5 = 0;
    }
  }
  //*********************************

  //*********Print Picture 4*********
  if (buttonState4 == LOW){
    pressed4 = 1;
  }
  else if (buttonState4 == HIGH){
    if (pressed4 == 1) {
      startPrint = 1;
      if (!radio.write( &startPrint, sizeof(unsigned long) )){
        Serial.println(F("failed"));
      }
      
      readPic("pic4.bmp");
      pressed4 = 0;
    }
  } 
  //*********************************
}

void readPic(String picName){
  myPic = SD.open(picName);

  for(int x = 0; x < 14; x++){
    myPic.read();
  }    
  
  DIBSize = myPic.read();

  for(int j = 0; j < (DIBSize-1); j++ ){
    myPic.read();
  }
  
  count = 0;
  
  while (count != 76800){
    RGB.R = myPic.read();
    RGB.G = myPic.read();
    RGB.B = myPic.read();
    count++;
    if (!radio.write( &RGB, sizeof(RGB) )){
      Serial.println(F("failed"));
    }
  }
  myPic.close();
  
  startPrint = 0;
  if (!radio.write( &startPrint, sizeof(unsigned long) )){
    Serial.println(F("failed"));
  }
}

