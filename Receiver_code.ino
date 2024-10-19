// Receiver Code

// Pins: 
// MISO - 12, MOSI - 11, SCK - 13 (specific for Arduino UNO / Nano)
// CSN - 7, CE - 8 (any two digital pins)
// m1 - 3, m2 - 5, m3 - 6, m4 - 9

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 rad(7,8); // CSN, CE

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  rad.begin();
  rad.openReadingPipe(0, address);
  rad.setPALevel(RF24_PA_MIN); // power amplitude level
  rad.startListening();

  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  char dutyC[9] = {0}; 
  if(rad.available()){
    rad.read(&dutyC, sizeof(dutyC)-1);
  }
  dutyC[8] = '\0'; // ensuring the string is null-terminated
  Serial.println(dutyC);

  int m1 = (dutyC[0] - '0')*10 + (dutyC[1] - '0'); // Convert char to integers
  int m2 = (dutyC[2] - '0')*10 + (dutyC[3] - '0');
  int m3 = (dutyC[4] - '0')*10 + (dutyC[5] - '0');
  int m4 = (dutyC[6] - '0')*10 + (dutyC[7] - '0');

  int pwm1 = map(m1, 0, 100, 0, 255); // mapping the percentage to get the respective PWM values 
  int pwm2 = map(m2, 0, 100, 0, 255);
  int pwm3 = map(m3, 0, 100, 0, 255);
  int pwm4 = map(m4, 0, 100, 0, 255);

  analogWrite(3, pwm1); // Motors
  analogWrite(5, pwm2);
  analogWrite(6, pwm3);
  analogWrite(9, pwm4);

  delay(300);
}
