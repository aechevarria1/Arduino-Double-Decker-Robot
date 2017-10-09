/*
 * C++ file for music library
*/

#include "pitches.h"
#include "MusicLibrary.h"
#include "Arduino.h"

const int Piezo_PIN = 8;

const int heyy[35] = {
  NOTE_E3, NOTE_E3, NOTE_E3, NOTE_CS4, NOTE_CS4, NOTE_A3, NOTE_A3, 
  NOTE_A3, NOTE_E3, NOTE_E3, NOTE_D3, NOTE_CS3, NOTE_CS3, NOTE_D3, 
  NOTE_D3, NOTE_CS4, NOTE_A3, NOTE_D3, NOTE_D3, NOTE_CS4, NOTE_B3,
  NOTE_B3, NOTE_B3, NOTE_D4, 0, NOTE_A3, NOTE_A3, NOTE_A3,
  0, NOTE_A3, NOTE_A3, NOTE_A3, NOTE_A3, NOTE_B2, NOTE_CS3
};

const int heyyDurations[35] {
  8,8,8,4,4,4,8,8,4,8,4,8,4,8,8,8,4,4,4,4,4,8,8,3,8,8,8,3,2,
  8,8,8,8,4,2
};

const float heyyDelay = 1.7;

  
const int AOT[43] = { 
  NOTE_CS4, NOTE_CS4, NOTE_E4, NOTE_DS4, NOTE_B3, NOTE_B3, NOTE_CS4,
  NOTE_CS4, NOTE_E4, NOTE_DS4, NOTE_B3, NOTE_GS3, NOTE_E3, NOTE_FS3,
  NOTE_DS3, NOTE_E3, NOTE_CS3, NOTE_DS3, NOTE_B2, NOTE_GS3, NOTE_E3,
  NOTE_FS3, NOTE_DS3, NOTE_E3, NOTE_DS3, NOTE_CS3, NOTE_B2, NOTE_B3,
  NOTE_G3, NOTE_A3, NOTE_FS3, NOTE_G3, NOTE_E3, NOTE_FS3,
  NOTE_D3, NOTE_B3, NOTE_G3, NOTE_A3, NOTE_FS3, NOTE_G3,
  NOTE_FS3, NOTE_E3, NOTE_DS3
};

const int AOTDurations[43] {
  8,8,8,4,8,8,4,8,8,4,3,4,8,4,4,4,4,4,3,4,8,4,4,4,4,4,3,4,8,4,4,
  4,4,4,3,4,8,4,4,4,4,4,3
};

const float AOTDelay = 1.4;

const int MM2Wily[67] =  {
  0, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_CS3,
  0, NOTE_CS3, NOTE_CS3, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_CS3,
  0, NOTE_GS3, NOTE_FS3, NOTE_GS3, 0, NOTE_E3, NOTE_E3, NOTE_E3, 
  NOTE_E3, NOTE_E3, NOTE_E3, NOTE_CS3, 0, NOTE_GS3, 0, NOTE_FS3,
  0, NOTE_E3, 0, NOTE_FS3, 0, NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_FS3,
  NOTE_FS3, NOTE_FS3, NOTE_DS3, 0, NOTE_GS3, 0, NOTE_FS3, 0, NOTE_E3,
  0, NOTE_DS3, 0, NOTE_CS3, 0, NOTE_CS3, NOTE_GS3, NOTE_B3, NOTE_AS3,
  NOTE_CS3, 0, NOTE_CS3, NOTE_GS3, NOTE_B3, NOTE_AS3, NOTE_DS4, NOTE_E4
};

const int MM2WilyDurations[67] = {
  8,16,16,8,16,16,8,8,8,16,16,8,16,16,8,8,8,8,8,8,8,16,16,8,16,16,
  8,8,8,8,8,8,8,8,8,8,3,16,16,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,3,8,8,8,8,8,4,8,8
};

const float MM2WilyDelay = 1.35;

void play_backup_music() {
   for (int i = 0; i<5; ++i){
    tone(Piezo_PIN,NOTE_B4,500);
    delay(1000);
    noTone(Piezo_PIN);
  }
}

