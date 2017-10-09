/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Tone

 */
#include "pitches.h"

// notes in the melody:

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
  // iterate over the notes of the melody:
  //play_song(heyy,heyyDurations,sizeof(heyy)/sizeof(int),heyyDelay);
  //play_song(AOT,AOTDurations,sizeof(AOT)/sizeof(int),AOTDelay);
  //pinMode(OUTPUT,3);
  //digitalWrite(3,LOW);
  pinMode(12,OUTPUT); 
  digitalWrite(12,LOW); //set 12 to ground piezo speaker
  play_song(MM2Wily,MM2WilyDurations,sizeof(MM2Wily)/sizeof(int),MM2WilyDelay);
}

void loop() {
  //play_song(MM2Wily,MM2WilyDurations,sizeof(MM2Wily)/sizeof(int),MM2WilyDelay);
}

void play_song(int melody[],int noteDurations[], int num_notes, float Delay){
  for (int thisNote = 0; thisNote < num_notes; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * Delay;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

