//Snippet from the Final Code. Final form of the reading function
void readPic(String picName){
  
  delay(200);
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

  RGB.B = 0;
  RGB.R = 0;
  RGB.G = 0;
  RGB.state = 0;
  if (!radio.write( &startPrint, sizeof(unsigned long) )){
    Serial.println(F("failed"));
  }
}
