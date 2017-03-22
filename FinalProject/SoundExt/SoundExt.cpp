/*  Sound Extensions
 *  soundExt.cpp
 *
 *  - Start-up Melody based off toneMelody example.
 *  - High Beep Tone
 *  - Low Beep Tone
 *  - Custom Song: Stars and Stripes Forever by John Philip Sousa
 *
 *  Based off code by Tom Igoe.
 */

#include <Arduino.h>
#include <avr/pgmspace.h>

#include "SoundExt.h"

// Plays a melody with an array of notes, durations, and the size of the arrays
void playMelody (const uint16_t melody[], const uint8_t durations[], int numNotes) {
  for (int i = 0; i < numNotes; i++) {
    int noteDuration = FOUR_BAR_LENGTH / pgm_read_byte_near(durations + i);

    uint16_t note = pgm_read_word_near(melody + i);

    tone(SPKR_PIN, note, noteDuration);

    // To distinguish between notes, set a delay between them.
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(SPKR_PIN);
  }
}

// Plays the starting melody.
void playStartMelody () {
  playMelody(StartMelody, StartMelodyDurations, START_NUM_NOTES);
}

// Plays Stars and Stripes Forever melody.
void playStarsAndStripes () {
  playMelody(StarsAndStripesMelody, StarsAndStripesDurations, STARS_NUM_NOTES);
}

// Plays a high beep for a short time.
void playHighBeep () {
  tone(SPKR_PIN, HIGH_BEEP, BEEP_LENGTH);
}

// Plays a low beep for a short time.
void playLowBeep () {
  tone(SPKR_PIN, LOW_BEEP, BEEP_LENGTH);
}
