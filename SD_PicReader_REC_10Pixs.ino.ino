#include <SPI.h>
#include <SD.h>
#include "RF24.h"

String RGB_HEX;
File myPic;

struct dataStruct{
  char R_0;
  char G_0;
  char B_0;
  char R_1;
  char G_1;
  char B_1;
  char R_2;
  char G_2;
  char B_2;
  char R_3;
  char G_3;
  char B_3;
  char R_4;
  char G_4;
  char B_4;
  char R_5;
  char G_5;
  char B_5;
  char R_6;
  char G_6;
  char B_6;
  char R_7;
  char G_7;
  char B_7;
  char R_8;
  char G_8;
  char B_8; 
  char R_9;
  char G_9;
  char B_9;                 
  char stat;
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
      
   
 

} // Loop

