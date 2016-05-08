#include <Adafruit_TFTLCD.h>
#include <pin_magic.h>
#include <registers.h>


#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>


File myFile;
void setup() {
Serial.begin(115200);
    //set up SD card
  pinMode(10, OUTPUT);

  if (!SD.begin(10)) {
    Serial.println("SD Failed!");
    return;
  }
  else {
    Serial.println("SD READY!");
  }
  myFile = SD.open("test.bmp");
  if (myFile) {
    Serial.println("test:");
//Reading Bitmap file Header
    for(int x = 0; x< 14; x++){
      myFile.read();
      Serial.println(x);
      }
//Reading DIB header
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  //Width
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  //Height
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  Serial.println(myFile.read());
  //Start Pixel value
  Serial.println("Pixel Color");
  long count = 0;
  while (count != 76800){
  Serial.println(myFile.read());//R
  Serial.println(myFile.read());//B
  Serial.println(myFile.read());//G
  count = count + 1;
  Serial.println("_________________________");
  }
  
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening Bliss");
  }
}

void loop() {
  
 
} // Loop

