// each block of 4 LEDs in the array is groupled by a common anode (+, long leg)
// for simplicity of wiring on breadboard, using a colour code
#define GREEN 4
#define ORANGE    1
#define WHITE     2
#define BLUE      3
#define YELLOW    0
#define MAP_START 32

#define DISPLAY_WIDTH  4
#define DISPLAY_HEIGHT 5

// the text to display
#define HELLO_WORLD_STRING "HELLO WORLD"
#define BSIDES_KC_STRING "BSIDES KC"
#define SKCS "SECKC"

// pin definitions {GREEN, ORANGE, WHITE, BLUE, YELLOW}
const int charliePin[5] = {
  3, 4, 0, 1, 2
};


/*
   Grid format:

    0  4  8 12 16
    1  5  9 13 17
    2  6 10 14 18
    3  7 11 15 19
*/
int grid[20] = {
  1, 0, 0, 0, 1,
  1, 1, 0, 0, 0,
  1, 1, 1, 0, 0,
  1, 1, 1, 1, 0,
};

const int arrow[20] = {
  0, 0, 1, 0, 0,
  0, 1, 1, 1, 0,
  0, 0, 1, 0, 0,
  0, 0, 1, 0, 0,
};
int ega = HIGH;
// Charlieplexed LED definitions (current flowing from-to pairs)
int LED[20][2] = {
  {ORANGE, GREEN},                            // 0 (GREEN GROUP)*
  {GREEN, ORANGE},                            // 4 (ORANGE GROUP)
  {GREEN, WHITE},                             // 8 (WHITE GROUP)
  {GREEN, BLUE},                              // 12 (BLUE GROUP)
  {GREEN, YELLOW},                            // 16 (YELLOW GROUP)
  {WHITE, GREEN},                             // 1*
  {WHITE, ORANGE},                            // 5
  {ORANGE, WHITE},                            // 9
  {ORANGE, BLUE},                             // 13
  {ORANGE, YELLOW},                           // 17
  {BLUE, GREEN},                              // 2
  {BLUE, ORANGE},                             // 6
  {BLUE, WHITE},                              // 10
  {WHITE, BLUE},                              // 14*
  {WHITE, YELLOW},                            // 18
  {YELLOW, GREEN},                            // 3
  {YELLOW, ORANGE},                           // 7*
  {YELLOW, WHITE},                            // 11
  {YELLOW, BLUE},                             // 15
  {BLUE, YELLOW}                              // 19
};
