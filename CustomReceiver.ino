#include <SPI.h>
#include "RF24.h"
#include <printf.h>
RF24 radio(2,3);
unsigned long pipe = 0xE8E8;
unsigned long msg;

void setup() {
    Serial.begin(115200);
    printf_begin();
    Serial.println("Receiver");
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    radio.begin();
    radio.setChannel(108);
    radio.openReadingPipe(0,pipe);
    radio.printDetails();
 
}

void loop() {
   radio.startListening();
   digitalWrite(9, LOW);
   digitalWrite(10, LOW);
   digitalWrite(11, LOW);
  if(radio.available()){
    while(radio.available())
    {
    radio.read(&msg, sizeof(msg));
    Serial.println("Incoming...");
    delay(500);
    Serial.println(msg);
    }
  }
  else{
    Serial.println("No Msg");
  }
  Serial.println(msg);
  if (msg == 10011){
    digitalWrite(9, HIGH);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  }
  else if (msg == 10101) {
    digitalWrite(9, LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  }
  else if (msg == 11001){
    digitalWrite(9, LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
    }
}
