//implementation of function that allows the speed of the servos to be changed, when they are moving
//Expect inputs 1-90, with 1 being the slowest and 90 being the fastest
//However, dont want servos going near the fastest or slowest possible. Will limit input to range [30,60], limiting
//servo range to [30,150]

#include <Servo.h>
#include <stdlib.h>

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


/*const String Up = "4224244";
const String Right = "4444244";
const String Down = "4424244"; 
const String Left = "4244244";
const String Stop = "4422242";
const String A = "4244242";
const String B = "4422444";
const String C = "4222444";
const String One = "4422222";
const String Two = "4242222";
const String Three = "4442222";
const String Four = "4224222";
const String Five = "4424222";
const String Six = "4244222";
const String Seven = "4444222";
const String Eight = "4222422";
const String Nine = "4422422";
const String Zero = "4222222";*/
//const String decoded;

/*const char Up[18] = "42242442222224224";
const char Right[18] = "44442442222222442";
const char Down[18] = "44242442222222224";
const char Left[18] = "42442442222224442";
const char Stop[18] = "44222422222222444";
const char A[18] = "42442422222224224";
const char B[18] = "44224442222222242";
const char C[18] = "42224442222224242";
//const char decoded[18] = "42224442222224242";
char decoded[18];*/
/*const long long Up = 42242442222224224;
const long long Right = 44442442222222442;
const long long Down = 44242442222222224;
const long long Left = 42442442222224442;
const long long Stop = 44222422222222444;
const long long A = 42442422222224224;
const long long B = 44224442222222242;
const long long C = 42224442222224242;
long long decoded;*/
int input[7] = {400,200,200,200,400,400,400};
int steps;
//long long decoded;


//Tests for simple check and print
//String memory: 3432,426
//char[18]: 1428,188
//long long: 1428,188

//Tests for for loop transcribe to check and print
//String 3874, 460
//char: 1990,414

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
}


void listen_for_IR(){
  high_pulse = 0;
  low_pulse = 0;
  
  //high when no signal
  while (PIND & IR_PIN<<1){ 
    high_pulse++;
    delayMicroseconds(RESOLUTION);
    if (high_pulse>=MAX_PULSE && current_pulse!=0){
      //print_pulses();
      //read_pulses();
      print_decoded();
      control_servo();
      current_pulse = 0;
      return;  
    }
  }
  pulses[current_pulse][0] = high_pulse;
  
  //low when taking signal
  while (!(PIND & IR_PIN<<1)){ 
    low_pulse++;
    delayMicroseconds(RESOLUTION);

    if (low_pulse>=MAX_PULSE && current_pulse!=0){
      //print_pulses();
      //read_pulses();
      print_decoded();
      control_servo();
      current_pulse = 0;
      return;
    }
  }
  pulses[current_pulse][1] = low_pulse;

  current_pulse++;
}
void print_decoded(){
  steps = 0;
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


/*void compareSignal(){ //use to find minimum signal length needed for unique decodings
  String all[18] = {Up,Right,Down,Left,Stop,A,B,C,One,Two,Three,Four,Five,Six,Seven,Eight,Nine,Zero};
  //Serial.println(all[3].substring(0,3)); 424
  int signal_length = 17;
  int all_length = sizeof(all)/sizeof(String);
  //Serial.println(signal_length);
  //String temp[17];
  while (signal_length>0){
    for (int i=0;i<all_length;i++){
      //Serial.println(all[i].substring(0,signal_length));
      //Serial.println(all[i]);
      for (int j=i+1;j<all_length;j++){
        if (all[i].substring(0,signal_length)==(all[j].substring(0,signal_length))){
          Serial.print("Repeat at length ");
          Serial.println(signal_length);
          Serial.print("Shortest unique signal length is ");
          Serial.println(signal_length + 1);
          return;
        }
      }
    }
    signal_length--;
  }
}*/







