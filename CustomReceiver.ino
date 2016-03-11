//#include <DigitalIO.h>
#include <SPI.h>
#include "RF24.h"
#include <printf.h>
RF24 radio(2,3);
byte pipe = 0xE8E8F0F0E1LL;
unsigned long msg;

void setup() {
    Serial.begin(115200);
    printf_begin();
    Serial.println("Receiver");
    pinMode(9, OUTPUT);
    radio.begin();
    radio.setChannel(108);
    radio.openReadingPipe(0,pipe);
    radio.printDetails();
 
}

void loop() {
   radio.startListening();
   digitalWrite(9, LOW);
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
  if (msg == 835716){
    digitalWrite(9, HIGH);
    Serial.println(msg);
  }

}
