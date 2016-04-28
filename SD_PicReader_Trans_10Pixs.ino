 #include <SPI.h>
#include <SD.h>
#include "RF24.h"

int picNum = 1;
//String RGB;
long count;
String FILE_NAME = "test";

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"};
int startButton = 1;
int DIBSize;
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
  
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(108);   
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);
  radio.stopListening();
}

void loop() {
 if (startButton){
  //Looping through Picture Files
  for (int k = 0; k < picNum; k++){
    //Name picture as such test0.bmp, test1.bmp, test2.bmp
    FILE_NAME.concat(String("").concat(".bmp"));
    myPic = SD.open(FILE_NAME);
    if (myPic){
      Serial.println("SD Ready");
      }//if myPic
    else{
      Serial.println("SD Failed");
      }//else
      //Reading Bitmap File Header
    for(int x = 0; x < 14; x ++){
      myPic.read();
      Serial.println(x);
      }//End Reading Bitmap File Header
      //Reading DIB Header
    DIBSize = myPic.read();
    for(int j = 0; j < DIBSize - 1; j++){
      myPic.read();
      Serial.println(j);
      }//End Reading DIB Header  
    //Reading Pixel RGB
    count  = 0;
    while (count != 76800){
      RGB.R_0 = myPic.read();
      RGB.G_0 = myPic.read();
      RGB.B_0 = myPic.read();
      RGB.R_1 = myPic.read();
      RGB.G_1 = myPic.read();
      RGB.B_1 = myPic.read();
      RGB.R_2 = myPic.read();
      RGB.G_2 = myPic.read();
      RGB.B_2 = myPic.read();
      RGB.R_3 = myPic.read();
      RGB.G_3 = myPic.read();
      RGB.B_3 = myPic.read();
      RGB.R_4 = myPic.read();
      RGB.G_4 = myPic.read();
      RGB.B_4 = myPic.read();
      RGB.R_5 = myPic.read();
      RGB.G_5 = myPic.read();
      RGB.B_5 = myPic.read();
      RGB.R_6 = myPic.read();
      RGB.G_6 = myPic.read();
      RGB.B_6 = myPic.read();
      RGB.R_7 = myPic.read();
      RGB.G_7 = myPic.read();
      RGB.B_7 = myPic.read();
      RGB.R_8 = myPic.read();
      RGB.G_8 = myPic.read();
      RGB.B_8 = myPic.read();
      RGB.R_9 = myPic.read();
      RGB.G_9 = myPic.read();
      RGB.B_9 = myPic.read();                        
      if (RGB.R == -1 || RGB.G == -1 || RGB.B == -1){
        RGB.stat = 1;
        break;
        }//End if
      else{
        RGB.stat = 0;
        }//End else
        //Printing RGB values and send RGB as Payload
      Serial.println("Printing RGB:");
      Serial.println(RGB.R);
      Serial.println(RGB.G);
      Serial.println(RGB.B);
      if (!radio.write( &RGB, sizeof(RGB) )){
       Serial.println(F("failed"));
       }//End Transmission      
      }//End Reading Pixel RGB  
      delay(10000);//Delay between Picture Transition.
    }//Pic Loop
  }//StartButton
}
