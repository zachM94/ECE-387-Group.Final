
#include <SPI.h>
#include "RF24.h"
#include <printf.h>
RF24 radio(7,8);
unsigned long pipe = 0xE8E8;
unsigned long msg = 10001;

void setup() {
    Serial.begin(115200);
    printf_begin();
    Serial.println("Transmitter");
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    pinMode(11, INPUT);
    radio.begin();
    radio.setChannel(108);
    radio.openWritingPipe(pipe);
    radio.startListening();
    radio.printDetails();
}

void loop() {
  radio.stopListening();
  if (digitalRead(9) == HIGH){      
    msg = 10011;                
  }
  else if (digitalRead(10) == HIGH){
    msg = 10101;
  }
  else if (digitalRead(11) == HIGH) {
    msg = 11001;
  }
  else{
    msg = 10001;
    Serial.println("Awaiting Input....");
  }
  
  while (!radio.write(&msg, sizeof(msg))){
      radio.write(&msg, sizeof(msg));
      Serial.println("Sending.....");
    }
  delay(500); 
  }
    



