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
bool radioNumber = 0;
String RGB;
File myPic;
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"};

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
     
      Serial.print(F("Sent response "));
      Serial.println(RGB);  
      
      myPic = SD.open("myPic.txt", FILE_WRITE);
      if (myPic){
        Serial.println("Writing to File");
        myPic.println(RGB);
        myPic.close();  
      }
      else {
        Serial.println("Could not write to file");
        myPic.close();
      }
   }
 

} // Loop
