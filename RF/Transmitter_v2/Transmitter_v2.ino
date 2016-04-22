
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

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"};
//unsigned long msg;
char msg;
int buttonState = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(108);
 // pinMode(9,INPUT);
  //pinMode(10,INPUT);
 // pinMode(11,INPUT);
  // Open a writing and reading pipe on each radio, with opposite addresses
  
    //set up SD card
  pinMode(10, OUTPUT);

  if (!SD.begin(10)) {
    Serial.println("SD Failed!");
    return;
  }
  else {
    Serial.println("SD READY!");
  }
  
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
  
  
/****************** Ping Out Role ***************************/  
    
    radio.stopListening();                                    // First, stop listening so we can talk.
   /* if (digitalRead(9) == HIGH){
      msg = 10011;
      buttonState = 1;
    }
    else if(digitalRead(10) == HIGH){
      msg = 10101;
      buttonState = 1;
    }
    else if(digitalRead(11) == HIGH){
      msg = 11001;
      buttonState = 1;
    }
    else{
      msg = 10001;
      buttonState = 0;
    }
    */
    if (true){
    Serial.println(F("Now sending"));

    msg = 'f' + 'u' + 'n';
    unsigned long start_time = micros();                             // Take the time, and send it.  This will block until complete
     if (!radio.write( &msg, sizeof(char) )){
       Serial.println(F("failed"));
     }
        
    radio.startListening();                                    // Now, continue listening
    
    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
    
    while ( ! radio.available() ){                             // While nothing is received
      if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
          timeout = true;
          break;
      }      
    }
        
    if ( timeout ){                                             // Describe the results
        Serial.println(F("Failed, response timed out."));
    }else{
        unsigned long got_time;                                 // Grab the response, compare, and send to debugging spew
        radio.read( &got_time, sizeof(unsigned long) );
        unsigned long end_time = micros();
        
        // Spew it
        Serial.print(F("Sent msg = "));
        Serial.print(msg);
//        Serial.print(F(", Got response "));
//        Serial.print(got_time);
//        Serial.print(F(", Round-trip delay "));
//        Serial.print(end_time-start_time);
//        Serial.println(F(" microseconds"));
    }
    }
    // Try again 1s later
    delay(1000);
} // Loop

