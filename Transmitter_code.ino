// Transmitter Code

// Pins: 
// MISO - 12, MOSI - 11, SCK - 13 (specific for Arduino UNO / Nano)
// CSN - 7, CE - 8 (any two digital pins)

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 rad(7,8); // CSN, CE

const byte address[6] = "00001";

void setup() {
  //Serial.begin(9600);
  rad.begin();
  rad.openWritingPipe(address);
  rad.setPALevel(RF24_PA_MIN); // power amplitude level
  rad.stopListening();
}

void loop() {
  char dutyCycles[9] = "234567"; // input 
  int len = strlen(dutyCycles);

  while(len < 8){
    dutyCycles[len] = '0';
    len++;
  }
  dutyCycles[8] = '\0'; // ensuring the string is null-terminated

  rad.write(dutyCycles, sizeof(dutyCycles)); // pointer to the first element, &dutyCycles[0]
  delay(300);
}
