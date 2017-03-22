/*************************************************
 * Public Constants
 *************************************************/

/*  Duration = 4000 / X_NOTE
 *  e.g. 1000 = 4000 / WHOLE_NOTE, a whole note will play for
 *  1000 milliseconds, or 1 second.
 *
 *  4000 = duration of four bars or measures of music
 *  > 4000, slower melody
 *  < 4000, faster melody
 *
 *  These constants are designed to be written as uint8_t or
 *  single byte data types. The length of these notes goes up to
 *  the 64th note. For > 95% of music, this is absolutely fine.
 */

#define FOUR_BARS                   1
#define TWO_BARS                    2
#define ONE_AND_A_HALF_BARS         3
#define WHOLE_NOTE                  4
#define SEVEN_EIGHTHS_NOTE          5
#define THREE_QUARTERS_NOTE         6
#define FIVE_EIGHTHS_NOTE           7
#define HALF_NOTE                   8
#define THREE_EIGHTHS_NOTE          12
#define QUARTER_NOTE                16
#define EIGHTH_NOTE                 32
#define SIXTEENTHS_NOTE             64
#define THIRTY_SECOND_NOTE          128
#define SIXTY_FOURTH_NOTE           255 // We shave a 1/128 off
