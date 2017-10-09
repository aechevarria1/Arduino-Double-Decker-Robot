//IR/Two Servo Testing
//Remember, output is high if no signal is received and low if signal is received
//high pulses occur in either ~450 or ~225. low pulses occur at ~500, for resolution of 10
#include <Servo.h>

Servo servoR;
Servo servoL;

const int IR_PIN = 2;
const unsigned int MAX_PULSE = 65000;
const int RESOLUTION = 10;
int pulses[100][2];
int current_pulse ;
unsigned int high_pulse;
unsigned int low_pulse;
int looped = 0;
int avg_pulses[17];
int num_pulses_avg = 0;
//String command;
String decoded;

String Up = "42242442222224224";
String Right = "44442442222222442";
String Down = "44242442222222224";
String Left = "42442442222224442";
String Stop = "44222422222222444";
String A = "42442422222224224";
String B = "44224442222222242";
String C = "42224442222224242";

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  DDRD = B11111010; //set pin 2 to input
  current_pulse = 0;
  high_pulse = 0;
  low_pulse = 0;
  servoR.attach(6);
  servoL.attach(10);
}

void loop() {
  listen_for_IR(decoded);
  
  //Serial.println(command);
  /*if (command == "Up"){
    Serial.println("Up");
  }*/
}

void listen_for_IR(String &command){
  high_pulse = 0;
  low_pulse = 0;
  //Serial.println("listening");
  //high when no signal
  while (PIND & IR_PIN<<1){ 
    //return "high";
    high_pulse++;
    delayMicroseconds(RESOLUTION);
    //Serial.println(high_pulse);
    //Serial.println(high_pulse);
    if (high_pulse>=MAX_PULSE && current_pulse!=0){
      decode_signal(command);
      //print_pulses();
      current_pulse = 0;
      //Serial.println(copy);
      print_decoded();
      control_servo();
      return;
      //print_pulses();
      //read_pulses();
      /*decoded = decode_signal();
      Serial.println(decoded);*/
      
    }
  }
  pulses[current_pulse][0] = high_pulse;
  
  //low when taking signal
  while (!(PIND & IR_PIN<<1)){ 
    //return "low";
    low_pulse++;
    delayMicroseconds(RESOLUTION);
    //Serial.println(low_pulse);
    if (low_pulse>=MAX_PULSE && current_pulse!=0){
      decode_signal(command);
      //print_pulses();
      current_pulse = 0;
      //Serial.println(copy);
      print_decoded();
      control_servo();
      return;
      //print_pulses();
      //read_pulses();
      /*decoded = decode_signal();
      current_pulse = 0;
      Serial.println(decoded);*/
      
    }
  }
  pulses[current_pulse][1] = low_pulse;

  current_pulse++;
}

void print_pulses(){
  Serial.print("Printing: HIGH LOW ");
  Serial.println(current_pulse);
  for (int i = 0;i<current_pulse;i++){
    Serial.print(pulses[i][0] * RESOLUTION, DEC);
    Serial.print(" usec, ");
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
    Serial.println(" usec");
  }
}

void read_pulses(){ //only need to read from indexes 1-17
  for (int i = 1;i<=17;i++){
    avg_pulses[i-1] += pulses[i][0]*RESOLUTION;
  }
  num_pulses_avg++;
  if (num_pulses_avg == 5){
    String seq = "";
    Serial.println("Printing base signal");
    for (int j = 0;j<17;j++){
      seq+=avg_pulses[j]/5000;
      avg_pulses[j] = 0;
    }
    num_pulses_avg = 0;
    Serial.println(seq); 
  }
}

void decode_signal(String &copy){
  String seq = "";
  for (int i = 1;i<=17;i++){
     seq += pulses[i][0]/100;
  }
  if (seq == Up){
    copy = "Up";
  }
  else if (seq == Right){
    copy = "Right";
  }
  else if (seq == Down){
    copy = "Down";
  }
  else if (seq == Left){
    copy = "Left";
  }
  else if (seq == Stop){
    copy = "Stop";
  }
  else if (seq == A){
    copy = "A";
  }
  else if (seq == B){
    copy = "B";
  }
  else if (seq == C){
    copy = "C";
  }
  else {
    Serial.println("Signal not recognized");
    copy = "N/A";
  }
}

void print_decoded(){
  if (decoded == "Up"){
    Serial.println("Up");
  }
  else if (decoded == "Right"){
    Serial.println("Right");
  }
  else if (decoded == "Down"){
    Serial.println("Down");
  }
  else if (decoded == "Left"){
    Serial.println("Left");
  }
  else if (decoded == "Stop"){
    Serial.println("Stop");
  }
  else if (decoded == "A"){
    Serial.println("A");
  }
  else if (decoded == "B"){
    Serial.println("B");
  }
  else if (decoded == "C"){
    Serial.println("C");
  }
  else {
    Serial.println("N/A");
  }
}

void control_servo(){
  if (decoded == "Up"){
    servoR.write(110);
    servoL.write(110);
  }
  else if (decoded == "Right"){
    servoR.write(70);
    servoL.write(110);
  }
  else if (decoded == "Left"){
    servoR.write(110);
    servoL.write(70);
  }
  else if (decoded == "Down"){
    servoR.write(70);
    servoL.write(70);
  }
  else if (decoded == "Stop"){
    servoR.write(90);
    servoL.write(90);
  }
  else {
    return;
  }
}

