/*
 * Embedded build that will be going on the robot. Build 1.00, completed on 5/29/2017
*/

#include <Servo.h>
#include <stdlib.h>
#include <MusicLibrary.h>

//Music pin is 8
//IR Sensor pin is 2, ground is 3, voltage is 4
//Servos are attached to 9(right) and 11(left)
//Switches are on pins 7 and 6

//Servos are different, right servo write to 135 moves it backwards, left servo moves it forward
//So right servo is actually backwards, and opposite the servo speed integers
Servo servoR;
Servo servoL;
int servo_speed_f = 135; //forward servo speed
int servo_speed_b = 45; //backward servo speed
const int IR_PIN = 2;
const int Switch1_PIN = 7;
const int Switch2_PIN = 6;
const unsigned int MAX_PULSE = 65000;
const int RESOLUTION = 10;

int pulses[24][2];
int current_pulse =0;
int avg_pulses[17];
int speed_lock = 0;
char speed_input[3];
int speed_index = 0;
int command;

//signal commands expected
const int Up = 5995;
const int Right = 21867; 
const int Down = 11115; 
const int Left = 11627;
const int Stop = 2807; 
const int A = 5815; 
const int B = 11179; 
const int C = 6059; 
const int One = 1407; 
const int Two = 1471; 
const int Three = 2751;
const int Four = 1503;
const int Five = 2783;
const int Six = 2911; 
const int Seven = 5471;
const int Eight = 1519;
const int Nine = 2799; 
const int Zero = 767; 
const int Begin = 2999; //Use to start speed input, button is TV/VCR 
const int End = 1533; //Use to end speed input, button is HD Zoom

void setup() {
  DDRD = B11111010; //set pin 2 to input
  PORTD = B00010000; //set 3 low and 4 high
  pinMode(12,OUTPUT); 
  digitalWrite(12,LOW); //set 12 to ground piezo speaker
  servoR.attach(9);
  servoL.attach(11);
  servoR.write(90);
  servoL.write(90);
  Serial.begin(9600);
}

void loop() {
  unsigned int high_pulse = 0;
  unsigned int low_pulse = 0;
  
  //high when no signal
  while (PIND & B00000100){ 
    if ((PIND & B10000000 || PIND & B01000000) && current_pulse==0){
      switch_interrupt();
    }
    ++high_pulse;
    delayMicroseconds(RESOLUTION);
    
    if (high_pulse>=MAX_PULSE && current_pulse!=0){
      decode_signal();
      do_command();
      current_pulse = 0;
      return;  
    }
  }
  pulses[current_pulse][0] = high_pulse;
  
  //low when taking signal
  while (!(PIND & B00000100)){ 
    ++low_pulse;
    delayMicroseconds(RESOLUTION);

    if (low_pulse>=MAX_PULSE && current_pulse!=0){
      decode_signal();
      do_command();
      current_pulse = 0;
      return;
    }
  }
  pulses[current_pulse][1] = low_pulse;

  ++current_pulse;
}

void do_command(){
  switch (command){
    case Up:
      servoR.write(servo_speed_b);
      servoL.write(servo_speed_f);
      break;
    case Right:
      servoR.write(servo_speed_f);
      servoL.write(servo_speed_f);
      break;
    case Left:
      servoR.write(servo_speed_b);
      servoL.write(servo_speed_b);
      break;
    case Down:
      servoR.write(servo_speed_f);
      servoL.write(servo_speed_b);
      break;
    case Stop:
      servoR.write(90);
      servoL.write(90);
      break;
    case A: 
      play_song(MM2Wily,MM2WilyDurations,sizeof(MM2Wily)/sizeof(int),MM2WilyDelay);
      break;
    case B: 
      play_song(AOT,AOTDurations,sizeof(AOT)/sizeof(int),AOTDelay);
      break;
    case C: 
      play_song(heyy,heyyDurations,sizeof(heyy)/sizeof(int),heyyDelay);
      break;
    default:
      break;
  }
}

void decode_signal(){
  int decoded = 1;
  for (int i = 1;i<=8;++i){
    int steps = pulses[i][0]*RESOLUTION/2000;
    decoded = decoded<<steps | 1;
  }

  switch (decoded) {
    case Up:
      command = Up;
      break;
    case Right:
      command = Right;
      break;
    case Down:
      command = Down;
      break;
    case Left:
      command = Left;
      break;
    case Stop:
      command = Stop;
      break;
    case A:
      command = A;
      break;
    case B:
      command = B;
      break;
    case C:
      command = C;
      break;
    case One:
      command = One;
      break;
    case Two:
      command = Two;
      break;
    case Three:
      command = Three;
      break;
    case Four:
      command = Four;
      break;
    case Five:
      command = Five;
      break;
    case Six:
      command = Six;
      break;
    case Seven:
      command = Seven;
      break;
    case Eight:
      command = Eight;
      break;
    case Nine:
      command = Nine;
      break;
    case Zero:
      command = Zero;
      break;  
    case Begin:
      command = Begin;
      speed_lock = 1;
      break;
    case End:
      command = End;
      map_speed();
      speed_lock = 0;
      break;    
    default:
      command = 0;
      break;
  }

  if (speed_lock){
    if (speed_index>=2){
      return;
    }
    switch (decoded){
      case One:
        speed_input[speed_index] = '1';
        ++speed_index;
        break;
      case Two:
        speed_input[speed_index] = '2';
        ++speed_index;
        break;
      case Three:
        speed_input[speed_index] = '3';
        ++speed_index;
        break;
      case Four:
        speed_input[speed_index] = '4';
        ++speed_index;
        break;
      case Five:
        speed_input[speed_index] = '5';
        ++speed_index;
        break;
      case Six:
        speed_input[speed_index] = '6';
        ++speed_index;
        break;
      case Seven:
        speed_input[speed_index] = '7';
        ++speed_index;
        break;
      case Eight:
        speed_input[speed_index] = '8';
        ++speed_index;
        break;
      case Nine:
        speed_input[speed_index] = '9';
        ++speed_index;
        break;
      case Zero:
        speed_input[speed_index] = '0';
        ++speed_index;
      default:
        return;
      }
    }
}

void map_speed(){
  int sp = atoi(speed_input);
  if (sp >= 30 && sp <= 60) { //actual bounds are 0 and 180, but I dont want it going that fast
    servo_speed_f = 90 + sp;
    servo_speed_b = 90 - sp;
  }
  speed_index = 0;
}

void switch_interrupt(){
  servoR.write(100);
  servoL.write(80);
  play_backup_music();
  servoR.write(90);
  servoL.write(90);
}

void play_song(const int melody[],const int noteDurations[], int num_notes, const float Delay){
  //function should be interruptable by either a switch interrupt, or new intake of signal
  for (int thisNote = 0; thisNote < num_notes; thisNote++) {
    //Serial.println(PIND,BIN);
    if (!(PIND & B10000000 || PIND & B01000000) && (PIND & B00000100)){ //if not switch and 
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
    else if (PIND & B10000000 || PIND & B01000000){ //if switch interrupt
      switch_interrupt();
    }
    else if (!(PIND & B00000100)){
      return;
    }
  }
}
