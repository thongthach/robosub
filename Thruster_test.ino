#include <Servo.h>
#include "TeensyThreads.h"
#define HWSERIAL Serial1
byte servoPin = 20;
byte servoPin2 = 13;
Servo servo;
Servo servo1;

volatile int signal = 0;
String string;
String string2;
void uartcomm(){
     while(1){
        //HWSERIAL.print("Hello Dat");
        //threads.delay(1000);
        if(Serial.available()==0){
          string= Serial.readString();
          Serial.print("Sending: ");
          Serial.println(string);
          HWSERIAL.print(string);
        }
        else if(HWSERIAL.available() >0){
          string2=HWSERIAL.readString();
          Serial.print("Received: ");
          Serial.println(string2);
        }
      

     }



}
// void printstring(){
//   while(1){
//       Serial.println("Thruster hello of machine printing threads Thruster secondary printing line for testing purposes Thruster secondary printing line for testing purposes Thruster secondary printing line for testing purposes Thruster secondary printing line for testing purposes ");
//       threads.delay(100);
//        Serial.println("Thruster secondary printing line for testing purposes");
//         threads.delay(100);

      
	    


//   }
// }
void thrusterControl(){
  while(1) {
    while (Serial.available() == 0);
	
	  signal= Serial.parseInt(); // Set signal value from 1100 to 1900
    Serial.println(signal);
	  servo.writeMicroseconds(signal);

    //for the second thruster
    signal1= Serial.parseInt(); // Set signal value from 1100 to 1900
    Serial.println(signal1);
	  servo.writeMicroseconds(signal1);



   
    threads.yield();
  }

}
void setup() {
	servo.attach(servoPin); //if you have a brusless motors
   HWSERIAL.begin(9600);
   Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  digitalWrite(14,HIGH);
   digitalWrite(13,HIGH);
  threads.addThread(thrusterControl,1);
  //threads.addThread(printstring,2);
    threads.addThread(uartcomm,2);

 
  
	servo.writeMicroseconds(1500); // send "stop" signal to ESC. //put 1500 first and then adjust it later

	delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
 
  
	
   // Send signal to ESC.
}