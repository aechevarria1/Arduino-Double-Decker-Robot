/*
 * Testing two servos
 */
#include <Servo.h>

Servo servoR;
Servo servoL;
void setup() {
  // put your setup code here, to run once:
  servoR.attach(9);
  servoL.attach(11);
  //Serial.begin(9600);
  //pinMode(INPUT,11);
  //servoR.write(120);
  //servoL.write(120);
  //delay(3000);
  servoR.write(110);
  servoL.write(110);
  //delay(10000);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*servoR.write(120);
  servoL.write(120);
  delay(3000);
  servoR.write(90);
  servoL.write(90);
  delay(10000);*/
  //digitalWrite(8,HIGH);
  //Serial.println(digitalRead(11));
}
