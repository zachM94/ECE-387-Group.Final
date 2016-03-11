
#include <SPI.h>
#include "RF24.h"
#include <printf.h>
RF24 radio(7,8);
byte pipe = 0xE8E8F0F0E1LL;
byte msg = 11;

void setup() {
    Serial.begin(115200);
    printf_begin();
    Serial.println("Transmitter");
    pinMode(9, INPUT);
    radio.begin();
    radio.setChannel(108);
    radio.openWritingPipe(pipe);
    radio.startListening();
    radio.printDetails();
}

void loop() {
  radio.stopListening();
  if (digitalRead(9) == HIGH)
  {
    while (!radio.write(&msg, sizeof(msg))){radio.write(&msg, sizeof(msg));}
  Serial.println("Sending.....");
  }
  else {
    Serial.println("Awaiting Input....");
  }
  delay(500); 

}
