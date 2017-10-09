/*
 * Library for all the music related functions and song definitions
*/

#ifndef MusicLibrary_h
#define MusicLibrary_h

extern const int Piezo_PIN;
extern const int AOT[43];
extern const int AOTDurations[43];
extern const float AOTDelay;
extern const int MM2Wily[67];
extern const int MM2WilyDurations[67];
extern const float MM2WilyDelay;
extern const int heyy[35];
extern const int heyyDurations[35];
extern const float heyyDelay;

void play_backup_music();

#endif
