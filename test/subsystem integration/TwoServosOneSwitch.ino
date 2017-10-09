/*
 * Servo and Switch integreation testing
 */
#include <Servo.h>

Servo servoR;
Servo servoL;

void setup() {
 
  servoR.attach(6);
  servoL.attach(10);
  pinMode(INPUT,2);
}

void loop() {

  if (PIND & 2<<1){
    servoR.write(120);
    servoL.write(120);
  }
  else {
    servoR.write(60);
    servoL.write(60);
  }
  delay(1);
}
