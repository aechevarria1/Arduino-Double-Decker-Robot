/*
 * Script to test most efficient method of comparing inputted signals
 * Found const int to be best
 * Stored command a char array, but switched to int so switch case could be used instead for other areas
 */
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
int command;
int decoded;
int speed_lock = 0; 
int speed_index = 0;
char speed_input[3];
int servo_speed_f;
int servo_speed_b;

/*const int Up = 2997;//0xBB5,B101110110101;
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
*/
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
//const String decoded

const String Up = "42242442222224224";
const String Right = "44442442222222442";
const String Down = "44242442222222224";
const String Left = "42442442222224442";
const String Stop = "44222422222222444";
const String A = "42442422222224224";
const String B = "44224442222222242";
const String C = "42224442222224242";
const String One = "44222222222224444";
const String Two = "42422222222222444";
const String Three = "44422222222224244";
const String Four = "42242222222222244";
const String Five = "44242222222224424";
const String Six = "42442222222222424";
const String Seven = "44442222222224224";
const String Eight = "42224222222222224";
const String Nine = "44224222222224442";
const String Zero = "42222222222222222";
const String Begin="42242422222224424";
const String End="42222224222222244";


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
  //int test = 1;
  DDRD = B11111010; //set pin 2 to input
  PORTD = B00010000; //set 3 low and 4 high
  current_pulse = 0;
  high_pulse = 0;
  low_pulse = 0;
  decoded = 1;
  //print_decoded();
  //Serial.println(stringOne.substring(10));
  //char test[8];
  //compareSignal();
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
    if ((PIND & B10000000) && current_pulse!=0){
      switch_interrupt();
    } 
    //return "high";
    high_pulse++;
    delayMicroseconds(RESOLUTION);
    
    if (high_pulse>=MAX_PULSE && current_pulse!=0){
      //print_pulses();
      read_pulses();
      //print_decoded();
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
      read_pulses();
      //print_decoded();
      current_pulse = 0;
      return;
    }
  }
  pulses[current_pulse][1] = low_pulse;

  current_pulse++;
}
void map_speed(){
  int sp = atoi(speed_input);
  if (sp >= 30 && sp <= 60) { //actual bounds are 0 and 180, but I dont want it going that fast
    servo_speed_f = 90 + sp;
    servo_speed_b = 90 - sp;
  }
  speed_index = 0;
}
/*void print_decoded(){
  decoded = 1;
  for (int i = 1;i<=7;++i){
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
    case Mute:
      command = Mute;
      speed_lock = 1;
      break;
    case Fav:
      command = Fav;
      map_speed();
      speed_lock = 0;
      break;    
    default:
      Serial.println("N/A");
      break;
  }
    Serial.println(command);
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
}*/


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
  //int pulse[17];
  String seq = "";
  int pulse = 1;
  int current_pulse;
  for (int i = 1;i<=8;i++){
    //Serial.println(pulse,BIN);
    current_pulse = pulses[i][0]*RESOLUTION/2000;
    pulse = pulse<<current_pulse | 1;
    seq+=pulses[i][0]*RESOLUTION/1000;
  }    
  Serial.println(pulse);
  Serial.println(pulse,BIN);
  Serial.println(pulse,HEX);
  Serial.println(seq);
}



  


void compareSignal(){ //use to find minimum signal length needed for unique decodings
  //Must be strings
  //Must comment out Listen for IR or too much memory is taken up
  //Serial.println(stringOne.substring(10));
  //String all[1] = {Up,Right,Down,Left,Stop,A,B,C,One,Two,Three,Four,Five,Six,Seven,Eight,Nine,Zero};
  String all[20] = {Up,Right,Down,Left,Stop,A,B,C,One,Two,Three,Four,Five,Six,Seven,Eight,Nine,Zero,Begin,End};
  int signal_length = 17;
  int all_length = sizeof(all)/sizeof(String);
  //Serial.println(stringOne.substring(10));
  //String temp[17];
  while (signal_length>0){
    for (int i=0;i<all_length;i++){
      //Serial.println(all[i].substring(0,signal_length));
      //Serial.println(all[i]);
      /*Serial.print("i:");
      Serial.println(i);*/
      for (int j=i+1;j<all_length;j++){
        /*Serial.print("j:");
        Serial.println(j);
        Serial.println(all[i].substring(0,signal_length));
        Serial.println(all[j].substring(0,signal_length));*/
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
}



void switch_interrupt(){
  Serial.println("Switch");
}



