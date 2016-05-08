/* I am proving this snippit of the Transmitting code to show the contribution I made to this section. What I did here was set up the button press algorithm to only begin sending data once a button is pressed. By doing this, I designed a way for us to send 
 * data to the reciver for multiple pictures. I made it so each button send a signal to the reciever to begin the print cycle. However, don't confuse my contribution here with Wilson Guo's work. The "readPic();" function below was written by wilson guo, 
 * and this code can be seen in the "Added Value_Final Code" section.
 */

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
      RGB.state = 1;
      if (!radio.write( &RGB, sizeof(RGB) )){
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
      RGB.state = 1;
      if (!radio.write( &RGB, sizeof(RGB) )){
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
      RGB.state = 1;
      if (!radio.write( &RGB, sizeof(RGB) )){
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
      RGB.state = 1;
      if (!radio.write( &RGB, sizeof(RGB) )){
        Serial.println(F("failed"));
      }
      
      readPic("pic4.bmp");
      pressed4 = 0;
    }
  } 
  //*********************************
}

