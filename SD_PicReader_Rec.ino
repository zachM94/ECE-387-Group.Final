#include <SPI.h>
#include <SD.h>
#include "RF24.h"

String RGB_HEX;
File myPic;

struct dataStruct{
  long R;
  long G;
  long B;
  long stat;
  }RGB;
  
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
      if (myPic){
        Serial.println("SD Working");  
      }  
      else{
      Serial.println("SD Failed");  
      }  
     

      //========================================================
     //Printing Payload and Manipulate/Save to SD card 
      if (RGB.stat == 1){
        myPic.close();
        delay(10000);//10Sec
      }
     else{
      Serial.print(F("Sent response "));
      Serial.println(RGB.R);
      Serial.println(RGB.G);
      Serial.println(RGB.B);
      RGB_HEX = "";
      RGB_HEX = String(RGB.R, HEX);//R
      RGB_HEX.concat(String(RGB.G, HEX));//G
      RGB_HEX.concat(String(RGB.B, HEX));//B  
      myPic.println(RGB_HEX);
     }
      //========================================================
      
   
 

} // Loop

