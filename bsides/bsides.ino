/*
   ____ _                _ _            _           ____   ___
  / ___| |__   __ _ _ __| (_) ___ _ __ | | _____  _|___ \ / _ \ ___ _ __   _____      __
  | |   | '_ \ / _` | '__| | |/ _ \ '_ \| |/ _ \ \/ / __) | | | / __| '_ \ / _ \ \ /\ / /
  | |___| | | | (_| | |  | | |  __/ |_) | |  __/>  < / __/| |_| \__ \ | | | (_) \ V  V /
  \____|_| |_|\__,_|_|  |_|_|\___| .__/|_|\___/_/\_\_____|\___/|___/_| |_|\___/ \_/\_/
                                 |_|

  Charlieplexing 20 LEDs using 5 ATTiny85 pins with fading by
  varying the duty cycle of each LED in the 'tail'.

  ATTiny85 connections
  Leg  Function
  1    Reset, no connection
  2    D3 GREEN - Vertex 5 (was 0)
  3    D4 ORANGE - Vertex 2 (was 1)
  4    GND
  5    D0 WHITE - Vertex 3 (was 2)
  6    D1 BLUE - Vertex 4 (was 3)
  7    D2 YELLOW - Vertex 1 (was 4)
  8    +5V

  Tested on ATTiny85 running at 8MHz.
*/

#include "bsides.h"

// maps characters to their 4x5 grid
unsigned long characterMap[59];

int disp[20];

// other
int current = 0;                              // LED in array with current focus
int previous = 0;                             // previous LED that was lit
bool ontime = false;
unsigned long toggleTime;
const int stepsize = 5;
int offset = 0;
int egr;

void setup() {
  randomSeed(analogRead(0));
  //Fill the display buffer.
  int dispidx = 0;
  for (dispidx = 0; dispidx < 20; dispidx++) {
    disp[dispidx] = grid[dispidx];
  }

  pinMode(1, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(1, LOW);

  egr = digitalRead(1);
  pinMode(2, INPUT);

    // Rows:   2---5---1---4---3---
  Chr('A', 0b01101001111110011001);
  Chr('B', 0b00111101111001101011);
  Chr('C', 0b00011011110100100010);
  Chr('D', 0b00111101111001100110);
  Chr('E', 0b00011111111100101011);
  Chr('F', 0b11111000111010001000);
  Chr('G', 0b01111000101110010110);
  Chr('H', 0b00110110001101101111);
  Chr('I', 0b10001011110100010001);
  Chr('J', 0b01110010001010100100);
  Chr('K', 0b10010110001100111010);
  Chr('L', 0b00011111001000100010);
  Chr('M', 0b10011111111110011001);
  Chr('N', 0b10011101101110011001);
  Chr('O', 0b00111001110001100110);
  Chr('P', 0b11101001111010001000);
  Chr('Q', 0b01101001101101100001);
  Chr('R', 0b00110110111000111011);
  Chr('S', 0b00011111111101001111);
  Chr('T', 0b01110010001000100010);
  Chr('U', 0b10011001100110010110);
  Chr('V', 0b10011001100110100100);
  Chr('W', 0b00111001001111111111);
  Chr('X', 0b10011001011010011001);
  Chr('Y', 0b10011001011000101100);
  Chr('Z', 0b11110001001001001111);
  Chr(' ', 0b00000000000000000000);
  Chr('!', 0b01001000010000001000);

}

void loop() {
  if(egr == ega) {
    return renderString(SKCS);
  }

  int randomNumber = random(6);
  if (randomNumber == 1) {
    race();
  } else if (randomNumber == 2) {
    bounce();
  } else if (randomNumber == 3) {
    fallingAnimation();
  } else if (randomNumber == 4) {
    renderString(BSIDES_KC_STRING);
  } else if (randomNumber == 5) {
    snow();
  } else {
    scanLines();
  }
}

void race() {
  int carAPosition = 0;
  int carBPosition = 15;
  bool direction = 0;
  int step = 0;
  while (step <= 4) {
    int displayIndex = 1000;
    while(displayIndex > 0) {
      int nextPositionCarA = carAPosition + step;
      int nextPositionCarB = carBPosition + step;
      charlieON(nextPositionCarA);
      charlieOFF(nextPositionCarA);
      charlieON(nextPositionCarB);
      charlieOFF(nextPositionCarB);
      displayIndex--;
    }

    if(direction == 0) {
      step++;
    } else {
      step--;
    }

    if(step >= 4){
      direction    = 1;
      carAPosition = 5;
      carBPosition = 10;
    } else if(step <= 0){
      direction    = 0;
      carAPosition = 0;
      carBPosition = 15;
    }
  }
}

void bounce() {
  while (1) {
    int dispidx = 19;
    bool direction = 0;
    while (dispidx >= 0) {
      charlieON(dispidx);
      if(dispidx == 0) { direction = 1; }
      if(dispidx == 19) { direction = 0; }
      delay(100);
      if (direction == 0) {
        dispidx--;
      } else {
        dispidx++;
      }
    }
  }
}

void fallingAnimation() {
  while (1) {
    unsigned long timeNow     = millis();
    unsigned long loopCount   = 0;  // used to determine duty cycle of each LED
    unsigned long displayTime = 250; //10 + random(90); // milliseconds to spend at each focus LED in descent
    handleTime(timeNow, displayTime);
  }
}

void fastSnow() {
  while (1) {
    unsigned long timeNow     = millis();
    unsigned long loopCount   = 0;  // used to determine duty cycle of each LED
    unsigned long displayTime = 60; //10 + random(90); // milliseconds to spend at each focus LED in descent
    while (millis() - timeNow < (displayTime + current * 2)) { // animation slows toward end
      loopCount++;
      // the "snowflake" gets full duty cycle.  When it gets to the end, hold it at the end until the tail collapses
      if (current > 19) charlieON(19);
      else charlieON(current);
      // each member of tail has reduced duty cycle, and never get to the final position
      if (!(loopCount % 3) && (current - 1 >= 0 && current - 1 < 19))  charlieON(current - 1);
      if (!(loopCount % 6) && (current - 2 >= 0 && current - 2 < 19))  charlieON(current - 2);
      if (!(loopCount % 9) && (current - 3 >= 0 && current - 3 < 19))  charlieON(current - 3);
      if (!(loopCount % 12) && (current - 4 >= 0 && current - 4 < 19)) charlieON(current - 4);
    }

    handleTime(timeNow, displayTime);
  }
}

void snow() {
  while (true) {
    unsigned long timeNow     = millis();
    unsigned long loopCount   = 0; // used to determine duty cycle of each LED
    unsigned long displayTime = 250; //10 + random(90); // milliseconds to spend at each focus LED in descent
    while (millis() - timeNow < (displayTime + current * 2)) { // animation slows toward end
      loopCount++;
      // the "snowflake" gets full duty cycle.  When it gets to the end, hold it at the end until the tail collapses
      if (current > 19) {
        charlieON(19);
      } else {
        charlieON(current);
      }
      // each member of tail has reduced duty cycle, and never get to the final position
      if (!(loopCount % 3) && (current - 1 >= 0 && current - 1 < 19))  charlieON(current - 1);
      if (!(loopCount % 6) && (current - 2 >= 0 && current - 2 < 19))  charlieON(current - 2);
      if (!(loopCount % 9) && (current - 3 >= 0 && current - 3 < 19))  charlieON(current - 3);
      if (!(loopCount % 12) && (current - 4 >= 0 && current - 4 < 19)) charlieON(current - 4);
    }

    handleTime(timeNow, displayTime);
  }
}

void scanLines() {
  while (1) {
    int offset = rand() % 5;
    for(int modulusIndex = 2; modulusIndex <= 4; modulusIndex++) {
      for(int pinIndex = 0; pinIndex <= 19; pinIndex++) {
        if (pinIndex == 0 || pinIndex % modulusIndex == 0) charlieON(pinIndex+offset);
        delay(50);
      }
      delay(75);
    }
    delay(100);
  }
}

// --------------------------------------------------------------------------------
// turns on LED #thisLED.  Turns off all LEDs if the value passed is out of range
//
void charlieON(int thisLED) {
  // turn off previous (reduces overhead, only switch 2 pins rather than 5)
  digitalWrite(charliePin[LED[previous][1]], LOW);   // ensure internal pull-ups aren't engaged on INPUT mode
  pinMode(charliePin[LED[previous][0]], INPUT);
  pinMode(charliePin[LED[previous][1]], INPUT);
  // turn on the one that's in focus
  if (thisLED >= 0 && thisLED <= 19) {
    pinMode(charliePin[LED[thisLED][0]], OUTPUT);
    pinMode(charliePin[LED[thisLED][1]], OUTPUT);
    digitalWrite(charliePin[LED[thisLED][0]], LOW);
    digitalWrite(charliePin[LED[thisLED][1]], HIGH);
  }
  previous = thisLED;
}
// --------------------------------------------------------------------------------
// turns off LED #thisLED.
//
void charlieOFF(int thisLED) {
  digitalWrite(charliePin[LED[thisLED][1]], LOW);   // ensure internal pull-ups aren't engaged on INPUT mode
  pinMode(charliePin[LED[thisLED][0]], INPUT);
  pinMode(charliePin[LED[thisLED][1]], INPUT);
}

void handleTime(unsigned long timeNow, unsigned long displayTime) {
  if (ontime) {
    if (timeNow > (toggleTime + displayTime)) {
      // Has been on for delay time.  Switch off.
      // Step thru (scroll) the array - move everything "down" 5 steps.
      offset += stepsize;
      if (offset >= 20) { offset = 0; }

      for (int dispidx = 19; dispidx >= 0; dispidx--) {
        if ((dispidx - offset) >= 0) {
          disp[dispidx] = grid[dispidx - offset];
        } else {
          disp[dispidx] = 0;
        }
      }
      toggleTime = timeNow;
    }
  } else {
    if (timeNow > (toggleTime + displayTime)) {
      toggleTime = timeNow;
    }
  }
  ontime = 1;
  // Cycle thru each LED
  if (ontime) {
    if (current > 0) { charlieOFF(current - 1); }
    if (disp[current]) { charlieON(current); }
  }
  current++;
  if (current > 19) {
    charlieOFF(19);
    current = 0;
  }
}

//Start Marquee Logic

// set up a character in the characterMap
void Chr(char theChar, unsigned long value) {
  characterMap[theChar - MAP_START] = value;
}

// render the string on the given offset
void renderString(char *theString) {
  while(1){
    int index = 0;
    int renderCount = 0;
    while (theString[index]) {
      while (renderCount <= 60) {
        renderCharacter(theString[index]);
        renderCount++;
      }
      index++;
      delay(250);
      renderCount = 0;
    }
  }
}

// render a character on the given offset
void renderCharacter(char theChar) {

  unsigned long graphic = characterMap[theChar - MAP_START];

  for (byte y = 0; y < DISPLAY_HEIGHT; y++) {
    for (byte x = 0; x < DISPLAY_WIDTH; x++) {
      // 3 - x to reverse order
      setPixel(3 - x, y, graphic & 0x1);
      graphic = graphic >> 1;
    }
  }
}

// light a pixel at the given coordinates
void setPixel(byte x, byte y, boolean ledStatus) {
  if (x >= 0 && x < DISPLAY_WIDTH) {
    if (y <= x) { x++; }
    setLed(y, x, ledStatus);
  }
}

// turn on the pins to light a LED
void setLed(byte vin, byte gnd, boolean ledStatus) {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  if (!ledStatus) return;

  pinMode(vin, OUTPUT);
  pinMode(gnd, OUTPUT);
  digitalWrite(vin, HIGH);
  digitalWrite(gnd, LOW);
  delay(1);
}


