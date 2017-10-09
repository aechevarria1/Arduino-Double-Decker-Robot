//IR/Servo Testing for one single Servo

#include <Servo.h>

//Servo variables
Servo servoR;
int servo_speed;

//IR variables
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
String command;

String Up = "42242442222224224";
String Right = "44442442222222442";
String Down = "44242442222222224";
String Left = "42442442222224442";
String Stop = "44222422222222444";
String A = "42442422222224224";
String B = "44224442222222242";
String C = "42224442222224242";

void setup() {
  Serial.begin(9600);
  
  //IR initialization
  current_pulse = 0;
  high_pulse = 0;
  low_pulse = 0;
  pinMode(INPUT,2);

  //Servo initialization
  servoR.attach(6);
  servo_speed = 45;
}

void loop() {
  high_pulse = 0;
  low_pulse = 0;

  while (PIND & IR_PIN<<1){ 
    high_pulse++;
    delayMicroseconds(RESOLUTION);

    if (high_pulse>=MAX_PULSE && current_pulse!=0){
      current_pulse = 0;
      decode_signal(command);
      if (command == "Up"){
        servoR.write(135);
      }
      else if (command == "Down"){
        servoR.write(45);
      }
      return;     
    }
  }
  pulses[current_pulse][0] = high_pulse;
  
  //low when taking signal
  while (!(PIND & IR_PIN<<1)){ 
    low_pulse++;
    delayMicroseconds(RESOLUTION);
    
    if (low_pulse>=MAX_PULSE && current_pulse!=0){
      current_pulse = 0;
      decode_signal(command);
      if (command == "Up"){
        servoR.write(135);
      }
      else if (command == "Down"){
        servoR.write(45);
      }
      return;
      
    }
  }
  pulses[current_pulse][1] = low_pulse;

  current_pulse++;
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
      current_pulse = 0;
      decode_signal(command);
      //Serial.println(copy);
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
      current_pulse = 0;
      decode_signal(command);
      //Serial.println(copy);
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
//Up 42242442222224224
//Right 44442442222222442
//Down 44242442222222224
//Left 42442442222224442
//Stop 44222422222222444
//A 42442422222224224
//B 44224442222222242
//C 42224442222224242


