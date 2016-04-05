
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
File aFile;
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"};

void setup() {
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  
  radio.begin();
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);  
  //set up SD card
  pinMode(10, OUTPUT);

  if (!SD.begin(10)) {
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

/****************** Pong Back Role ***************************/
    unsigned long got_time;
    unsigned long msg;    
    
    if( radio.available()){
                                                                    // Variable for the received timestamp
      while (radio.available()) {                                   // While there is data ready
        radio.read( &msg, sizeof(unsigned long) );             // Get the payload
      }
     
      radio.stopListening();                                        // First, stop listening so we can talk   
      radio.write( &got_time, sizeof(unsigned long) );              // Send the final one back.      
      radio.startListening();                                       // Now, resume listening so we catch the next packets.     
      if (msg == 10011){
        digitalWrite(2,HIGH);
        digitalWrite(3,LOW);
        digitalWrite(4,LOW);
      }
      else if (msg == 10101){
        digitalWrite(2,LOW);
        digitalWrite(3,HIGH);
        digitalWrite(4,LOW);        
      }
      else if (msg == 11001){
        digitalWrite(2,LOW);
        digitalWrite(3,LOW);
        digitalWrite(4,HIGH);         
      }
      else {
        digitalWrite(2,LOW);
        digitalWrite(3,LOW);
        digitalWrite(4,LOW);         
      }
      Serial.print(F("Sent response "));
      Serial.println(msg);  
      
      aFile = SD.open("aFile.txt", FILE_WRITE);
      if (aFile){
        Serial.println("Writing to File");
        aFile.println(msg);
        aFile.close();  
      }
      else {
        Serial.println("Could not write to file");
        aFile.close();
      }
   }
 




/****************** Change Roles via Serial Commands ***************************/


} // Loop

