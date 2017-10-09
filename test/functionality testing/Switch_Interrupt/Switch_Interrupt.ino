//testing switch being able to interrupt program at any point. During IR receiving and music loop specifically
//Tested music interrupt
//Tested servo interrupt

#include <Servo.h>
#include <stdlib.h>
#include "pitches.h"

Servo servoR;
Servo servoL;
int servo_speed_f = 135; //forward servo speed
int servo_speed_b = 45; //backward servo speed
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
int decoded;
int speed_lock = 0;
char speed_input[3];
int speed_index = 0;
char command[6];

const int Up = 2997;//0xBB5,B101110110101;
const int Right = 10933; //0x2AB5 B10101010110101;
const int Down = 5557; //0x15B5 B1010110110101; 
const int Left = 5813; //0x16B5 B1011010110101;
const int Stop = 1403; //0x57B B10101111011;
const int A = 2907; //0xB5B B101101011011;
const int B =5589; //0x15D5 B1010111010101;
const int C = 3029; //0xBD5 B101111010101;
const int One = 703; //0x2BF B1010111111;
const int Two = 735; //0x2DF B1011011111;
const int Three = 1375; //0x55F B10101011111;
const int Four = 751; //0x2EF B1011101111;
const int Five = 1391; //0x56F B10101101111;
const int Six = 1455; //0x5AF B10110101111;
const int Seven = 2735; //0xAAF B101010101111;
const int Eight = 759; //0x2F7 B1011110111;
const int Nine = 1399; //0x577 B10101110111;
const int Zero = 383; //0x17F B101111111;
const int Mute = 95; //0x5F B1011111; Use to start speed input
const int Fav = 2779; //0xADB B101011011011; Use to end speed input

int Switch_PIN = 7;
int Piezo_PIN = 8;

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

void setup() {
  Serial.begin(9600);
  DDRD = B11111010; //set pin 2 to input
  PORTD = B00010000; //set 3 low and 4 high
  current_pulse = 0;
  high_pulse = 0;
  low_pulse = 0;
  decoded = 1;
  servoR.attach(11);
  servoL.attach(9);
  servoR.write(90);
  servoL.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  listen_for_IR();
  if (strcmp(command,"Up") == 0|| strcmp(command,"Right") == 0|| strcmp(command,"Down") == 0 || strcmp(command,"Left") == 0 || strcmp(command,"Stop") == 0){
    control_servo();
  }
  else if(strcmp(command,"A") == 0|| strcmp(command,"A") == 0|| strcmp(command,"A") == 0){
    play_song(AOT,AOTDurations,sizeof(AOT)/sizeof(int),AOTDelay);
  }
}


void listen_for_IR(){
  high_pulse = 0;
  low_pulse = 0;
  
  //high when no signal
  while (PIND & B00000100){ 
    if (PIND & B10000000){
      switch_interrupt();
    }
    high_pulse++;
    delayMicroseconds(RESOLUTION);
    if (high_pulse>=MAX_PULSE && current_pulse!=0){
      //print_pulses();
      //read_pulses();
      print_decoded();
      current_pulse = 0;
      return;  
    }
  }
  pulses[current_pulse][0] = high_pulse;
  
  //low when taking signal
  while (!(PIND & B00000100)){ 
    low_pulse++;
    delayMicroseconds(RESOLUTION);

    if (low_pulse>=MAX_PULSE && current_pulse!=0){
      //print_pulses();
      //read_pulses();
      print_decoded();
      current_pulse = 0;
      return;
    }
  }
  pulses[current_pulse][1] = low_pulse;

  current_pulse++;
}

void print_decoded(){
  int steps = 0;
  decoded = 1;
  for (int i = 1;i<=7;i++){
    //Serial.println(pulse,BIN);
    steps = pulses[i][0]*RESOLUTION/2000;
    //Serial.println(steps);
    decoded = decoded<<steps | 1;
  }
  //Serial.println(decoded);
  switch (decoded) {
    case Up:
      strcpy(command,"Up");
      break;
    case Right:
      strcpy(command,"Right");
      break;
    case Down:
      strcpy(command,"Down");
      break;
    case Left:
      strcpy(command,"Left");
      break;
    case Stop:
      strcpy(command,"Stop");
      break;
    case A:
      strcpy(command,"A");
      break;
    case B:
      strcpy(command,"B");
      break;
    case C:
      strcpy(command,"C");
      break;
    case One:
      strcpy(command,"1");
      break;
    case Two:
      strcpy(command,"2");
      break;
    case Three:
      strcpy(command,"3");
      break;
    case Four:
      strcpy(command,"4");
      break;
    case Five:
      strcpy(command,"5");
      break;
    case Six:
      strcpy(command,"6");
      break;
    case Seven:
      strcpy(command,"7");
      break;
    case Eight:
      strcpy(command,"8");
      break;
    case Nine:
      strcpy(command,"9");
      break;
    case Zero:
      strcpy(command,"0");
      break;      
    case Mute:
      Serial.println("Start speed input");
      strcpy(command,"Mute");
      speed_lock = 1;
      break;
    case Fav:
      Serial.println("Stop speed input");
      strcpy(command,"Fav");
      print_speed();
      speed_lock = 0;
      break;
    default:
      strcpy(command,"N/A");
      break;
  }
  Serial.println(command);
  if (speed_lock){
    if (speed_index>=2){
      Serial.println("Too many inputs. Please press Fav to map speed");
      return;
    }
    if (isdigit(command[0])){
    speed_input[speed_index] = command[0];
    ++speed_index;
    }
    else {
      Serial.println("Please input a number");
    }
  }
}

void print_speed(){
  int sp = atoi(speed_input);
  if (sp >= 30 && sp <= 60) { //actual bounds are 0 and 180, but I dont want it going that fast
    servo_speed_f = sp + 90;
    servo_speed_b = 90 - sp;
  }
  else {
    Serial.println("Invalid input. Please press Mute again to re-enter speed. Acceptable range is [30,60]");
  }
  speed_index = 0;
}

void control_servo(){
  if (strcmp(command,"Up") == 0){
    servoR.write(servo_speed_f);
    servoL.write(servo_speed_f);
  }
  else if (strcmp(command,"Right") == 0){
    servoR.write(servo_speed_b);
    servoL.write(servo_speed_f);
  }
  else if (strcmp(command,"Left") == 0){
    servoR.write(servo_speed_f);
    servoL.write(servo_speed_b);
  }
  else if (strcmp(command,"Down") == 0){
    servoR.write(servo_speed_b);
    servoL.write(servo_speed_b);
  }
  else if (strcmp(command,"Stop") == 0){
    servoR.write(90);
    servoL.write(90);
  }
  else {
    return;
  }
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

void read_pulses(){ //only need to read from indexes 1-7
  //int pulse[17];
  //String seq = "";
  int pulse = 1;
  int current_pulse;
  for (int i = 1;i<=7;i++){
    //Serial.println(pulse,BIN);
    current_pulse = pulses[i][0]*RESOLUTION/2000;
    pulse = pulse<<current_pulse | 1;
  }    
  Serial.println(pulse);
  Serial.println(pulse,BIN);
  Serial.println(pulse,HEX);
}

void play_song(int melody[],int noteDurations[], int num_notes, float Delay){
  for (int thisNote = 0; thisNote < num_notes; thisNote++) {
    if (!(PIND & B10000000)){
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
    else {
      switch_interrupt();
    }
  }
}

void switch_interrupt(){
  Serial.println("Switch");
  servoR.write(80);
  servoL.write(80);
  for (int i = 0; i<5; ++i){
    tone(Piezo_PIN,NOTE_B4,500);
    delay(1000);
    noTone(Piezo_PIN);
  }
  servoR.write(90);
  servoL.write(90);
}






