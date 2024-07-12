#include <Servo.h>
#include "TeensyThreads.h"
#define HWSERIAL Serial1

const byte servoPins[] = {20, 21, 22, 23, 24, 25, 26, 27}; // Pins for the 8 servos
Servo servos[8];  
volatile int signal[8] = {0}; 
String string;
String string2;

void uartcomm(){
     while(1){
        if (Serial.available() > 0) {
          string = Serial.readString();
          Serial.print("Sending: ");
          Serial.println(string);
          HWSERIAL.print(string);
        }
        else if (HWSERIAL.available() > 0) {
          string2 = HWSERIAL.readString();
          Serial.print("Received: ");
          Serial.println(string2);
        }
        threads.yield();
     }
}

void thrusterControl(){
  while(1) {
    while (Serial.available() == 0);
    int thrusterIndex = Serial.parseInt();
    //signal[thrusterIndex] = Serial.parseInt(); // Set signal value from 1100 to 1900
    //Serial.print("Thruster ");
    //Serial.print(thrusterIndex);
    //Serial.print(": ");
    //Serial.println(signal[thrusterIndex]);
    if(signal[thrusterIndex] < 1100 || signal[thrusterIndex] > 1900 ){
      servos[thrusterIndex].writeMicroseconds(1500);
    }
    else{
      servos[thrusterIndex].writeMicroseconds(signal[thrusterIndex]);
    }
    threads.yield();
  }
}

void setup() {
   HWSERIAL.begin(9600);
   Serial.begin(9600);

   pinMode(13, OUTPUT);
   pinMode(14, OUTPUT);
   digitalWrite(14, HIGH);
   digitalWrite(13, HIGH);

   for (int i = 0; i < 8; i++) {
     servos[i].attach(servoPins[i]);
     servos[i].writeMicroseconds(1500); // Send "stop" signal to ESC
     delay(1000);
   }

  

   threads.addThread(uartcomm, 1);

   // Add threads for each thruster control
  for(int i=0; i<8; i++){ 
    threads.addThread(thrusterControl, i);
  }
   
}

void loop() {
  // Empty loop as everything is handled by threads
}
