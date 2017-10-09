/*
 * Testing servo and switch integration
 */
#include <Servo.h>

Servo servoR;
int servo_speed;

void setup() {
  // put your setup code here, to run once:
  servoR.attach(6);
  servo_speed = 45;
  pinMode(INPUT,2);
  Serial.begin(9600);
}

void loop() {
  if (PIND & 2<<1){
    servo_speed = 135;
  }
  else {
    servo_speed = 45;
  }
  servoR.write(servo_speed);
  delay(1);
}
