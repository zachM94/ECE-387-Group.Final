/*Here I am presenting a snippit of our final code for the receiver. Wilson Guo is the one that wrote the code for the RF24 Transceiver. However, the algorithm you see below for printing to the screen was part of my contribution.
 * I designed the algorithm to take the RGB data that is sent over and instantly draw that pixel to the TFT display. After each pixel print, the x and y coordinates are updated in preparation for the next pixel to be print. I also
 * set it up to clear the screen when a button is pressed on the transmitting end and data for a new picture is sent over.
 */

void loop() {     
    if ( radio.available()){
                              
      while (radio.available()) {                    
        if(RGB.state == 0 && RGB.R == 0 && RGB.G == 0 && RGB.B == 0){
          radio.read( &RGB, sizeof(RGB));  
          myGLCD.fillScr(0, 0, 0);
          x = 0;
          y = 0;
         
        }
        else{
        radio.read( &RGB, sizeof(RGB));  
        onetotone = 1;
        }
      }
      
      if (x == 320){
        y++;
        x = 0;
      }
      
      myGLCD.setColor(RGB.R, RGB.G, RGB.B);
      myGLCD.drawPixel(x, y);
      
      if (y > 240){
        y = 0;
        x = 0;
        RGB.state = 0;
      }
      if (onetotone == 1){
        x++;
      }
      onetotone = 0;
   }
 

}
