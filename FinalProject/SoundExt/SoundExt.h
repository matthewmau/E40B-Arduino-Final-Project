// SoundExt.h - Library for sounds and music

#ifndef SoundExt_h
#define SoundExt_h

#include "pitches.h"
#include "noteLengths.h"

#include "StartMelody.h"
#include "StarsAndStripes.h"

// Pin for the output speaker
#define SPKR_PIN 7 

// Duration of four bars or measures of music in milliseconds
#define FOUR_BAR_LENGTH 4000 

// Duration of a beep in milliseconds
#define BEEP_LENGTH 200

#define HIGH_BEEP NOTE_C6   // High beep note
#define LOW_BEEP  NOTE_C3   // Low beep note

// Plays a melody with an array of notes, durations, and length of the arrays
void playMelody (const uint16_t melody[], const uint8_t durations[], int numNotes);

// Plays the starting melody
void playStartMelody(void);

// Plays Stars and Stripes Forever melody
void playStarsAndStripes(void);

// Plays a high beep
void playHighBeep(void);

// Plays a low beep
void playLowBeep(void);

#endif
