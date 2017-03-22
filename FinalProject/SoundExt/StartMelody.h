/*************************************************
 * Start Melody
 * by Tome Igoe
 * 
 * Number of Notes: 8
 * Expected Length: ~ 2 seconds
 *************************************************/

#include <avr/pgmspace.h>

#include "pitches.h"
#include "NoteLengths.h"

#define START_NUM_NOTES 8

const PROGMEM uint16_t StartMelody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

const PROGMEM uint8_t StartMelodyDurations[] = {
 QUARTER_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, QUARTER_NOTE, QUARTER_NOTE, 
 QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE
};
