//IR/Two Servo/Speaker Testing
//Remember, output is high if no signal is received and low if signal is received
//high pulses occur in either ~450 or ~225. low pulses occur at ~500, for resolution of 10
#include <Servo.h>
#include "pitches.h"

Servo servoR;
Servo servoL;

const int IR_PIN = 2;
const int Switch_PIN = 7;
const int Piezo_PIN = 8;
const int servoR_PIN = 9;
const int servoL_PIN = 11;

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

int heyy[] = {
  NOTE_E3, NOTE_E3, NOTE_E3, NOTE_CS4, NOTE_CS4, NOTE_A3, NOTE_A3, 
  NOTE_A3, NOTE_E3, NOTE_E3, NOTE_D3, NOTE_CS3, NOTE_CS3, NOTE_D3, 
  NOTE_D3, NOTE_CS4, NOTE_A3, NOTE_D3, NOTE_D3, NOTE_CS4, NOTE_B3,
  NOTE_B3, NOTE_B3, NOTE_D4, 0, NOTE_A3, NOTE_A3, NOTE_A3,
  0, NOTE_A3, NOTE_A3, NOTE_A3, NOTE_A3, NOTE_B2, NOTE_CS3
};

int heyyDurations[] {
  8,8,8,4,4,4,8,8,4,8,4,8,4,8,8,8,4,4,4,4,4,8,8,3,8,8,8,3,2,
  8,8,8,8,4,2
};

float heyyDelay = 1.7;

  
int AOT[] = { 
  NOTE_CS4, NOTE_CS4, NOTE_E4, NOTE_DS4, NOTE_B3, NOTE_B3, NOTE_CS4,
  NOTE_CS4, NOTE_E4, NOTE_DS4, NOTE_B3, NOTE_GS3, NOTE_E3, NOTE_FS3,
  NOTE_DS3, NOTE_E3, NOTE_CS3, NOTE_DS3, NOTE_B2, NOTE_GS3, NOTE_E3,
  NOTE_FS3, NOTE_DS3, NOTE_E3, NOTE_DS3, NOTE_CS3, NOTE_B2, NOTE_B3,
  NOTE_G3, NOTE_A3, NOTE_FS3, NOTE_G3, NOTE_E3, NOTE_FS3,
  NOTE_D3, NOTE_B3, NOTE_G3, NOTE_A3, NOTE_FS3, NOTE_G3,
  NOTE_FS3, NOTE_E3, NOTE_DS3
};

int AOTDurations[] {
  8,8,8,4,8,8,4,8,8,4,3,4,8,4,4,4,4,4,3,4,8,4,4,4,4,4,3,4,8,4,4,
  4,4,4,3,4,8,4,4,4,4,4,3
};

float AOTDelay = 1.4;

int MM2Wily[] =  {
  0, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_CS3,
  0, NOTE_CS3, NOTE_CS3, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_CS3,
  0, NOTE_GS3, NOTE_FS3, NOTE_GS3, 0, NOTE_E3, NOTE_E3, NOTE_E3, 
  NOTE_E3, NOTE_E3, NOTE_E3, NOTE_CS3, 0, NOTE_GS3, 0, NOTE_FS3,
  0, NOTE_E3, 0, NOTE_FS3, 0, NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_FS3,
  NOTE_FS3, NOTE_FS3, NOTE_DS3, 0, NOTE_GS3, 0, NOTE_FS3, 0, NOTE_E3,
  0, NOTE_DS3, 0, NOTE_CS3, 0, NOTE_CS3, NOTE_GS3, NOTE_B3, NOTE_AS3,
  NOTE_CS3, 0, NOTE_CS3, NOTE_GS3, NOTE_B3, NOTE_AS3, NOTE_DS4, NOTE_E4
};

int MM2WilyDurations[] {
  8,16,16,8,16,16,8,8,8,16,16,8,16,16,8,8,8,8,8,8,8,16,16,8,16,16,
  8,8,8,8,8,8,8,8,8,8,3,16,16,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,3,8,8,8,8,8,4,8,8
};

float MM2WilyDelay = 1.35;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  DDRD = B01111010; //set pin 2 and 7 to input
  PORTD = B00010000; //set 3 low and 4 high
  current_pulse = 0;
  high_pulse = 0;
  low_pulse = 0;
  servoR.attach(servoR_PIN);
  servoL.attach(servoL_PIN);
  servoR.write(90);
  servoL.write(90);
}

void loop() {
  listen_for_IR(decoded);
  //Serial.println(digitalRead(Switch_PIN));
  /*if (command == "Up"){
    Serial.println("Up");
  }*/
  
}

void listen_for_IR(String &command){
  //Serial.println(PIND,BIN);
  while (digitalRead(Switch_PIN)){
    servoR.write(80);
    servoL.write(80);
    tone(Piezo_PIN,NOTE_B4,1000);
    delay(2000);
    noTone(Piezo_PIN);
  }
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
      //print_decoded();
      control_servo();
      play_melody();
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
      play_melody();
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

void play_song(int melody[],int noteDurations[], int num_notes, float Delay){
  for (int thisNote = 0; thisNote < num_notes; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(Piezo_PIN, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * Delay;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(Piezo_PIN);
  }
}

void play_melody(){
  if (decoded == "A"){
    play_song(AOT,AOTDurations,sizeof(AOT)/sizeof(int),AOTDelay);
  }
  else if (decoded == "B"){
    play_song(heyy,heyyDurations,sizeof(heyy)/sizeof(int),heyyDelay);
  }
  else if (decoded == "C"){
    play_song(MM2Wily,MM2WilyDurations,sizeof(MM2Wily)/sizeof(int),MM2WilyDelay);
  }
  else {
    return;
  }
}


