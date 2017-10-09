/*
 * Testing two switches
 */

void setup() {
  DDRD = B00111110; //set pins 7 and 6 to read
  Serial.begin(9600);
}

void loop() {
 
  Serial.println(PIND,BIN);
  if (PIND & B10000000){
    Serial.println("7 is on");
    delay(1000);
  }
  if (PIND & B01000000){
    Serial.println("6 is on");
    delay(1000);
  }
}
