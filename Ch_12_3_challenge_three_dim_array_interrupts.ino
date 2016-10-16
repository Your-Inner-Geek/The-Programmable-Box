
/* Using a three dimensional array to control the 6 LED light pattern
   selecting the lighting sequence by using an interrupt routine for the push button switch
 
   copy and paste this program into the Arduino IDE
   name this program Ch_12_3_challenge_three_dim_array_interrupts
 */

//  ------------------------------------------------------------------------------------
volatile int     ledPatternNo = 0;  // which pattern to display
int     numPatterns = 3;            // total number of patterns - NOT starting from zero, loop counters go from 0 -> numPatterns -1

int	ledOn = 300;
int	ledOff = 150;

int red = 3;
int orange = 5;
int yellow = 6;
int white = 9;
int green = 10;
int blue = 11;

// this is the sequence for the 6 LEDs
int ledArray[] = {red, orange, yellow, white, green, blue};

/*  each 6 x 6 array represents one entire display pattern. The columns represent the 6 LEDs (0 - 5) and the rows
    represent the the pattern that the 6 LEDs will display. A zero means the LED is off and a one means ON.
    So, the first row in the first 6x6 array says LED 0 and 5 will be on, all other off, the second row indicates
    that LEd 1 and 4 will be on and so forth.
 */
int sequenceArray [] [6] [6] {
 {                                // light LEDs from outside -> center
  {1, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 1, 0},
  {0, 0, 1, 1, 0, 0},
  {1, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 1, 0},
  {0, 0, 1, 1, 0, 0}
 },
 {                             // light LEDs from top to bottom
  {1, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 1}
 },
 {                             // light two LEDs and have them travel
  {1, 0, 0, 0, 0, 0},
  {1, 1, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 1, 1}
 }
};

//  ------------------------------------------------------------------------------------
void setup() {
// configure the LED pins as outputs and turn off the LEDs
    for(int i = 0 ; i < 6 ; i++) {
	pinMode(ledArray[i], OUTPUT);
	digitalWrite(ledArray[i], LOW);
  }
     attachInterrupt(0, switchPushed,LOW);  // attach an interrupt on int0 and call switchPushed() when triggered
}

//  ------------------------------------------------------------------------------------
void loop() {
  /* for the current pattern being pointed to (which plane in the 3D cube pointed to by ledPatternNo)
   each row represents one LED illumination pattern, display that pattern for time ledOn
   then go to next row and display that pattern
 */
  for(int j = 0; j < 6 ; j++) {                // outter loop - ROW pointer
    for(int i = 0 ; i < 6 ; i++) {             // inner loop - COLUMN pointer
      if(sequenceArray [ledPatternNo][j][i] == 0)  digitalWrite(ledArray[i], LOW);
      else                                         digitalWrite(ledArray[i], HIGH);
    }
    delay(ledOn);
 
  }
}

// ---------------------------------------------------------------------------
void switchPushed() {
  const int pushButtonSwitch = 2;	                        // switch is on pin D2, declare as constant, hide from other functions
  pinMode(pushButtonSwitch, INPUT_PULLUP);		        // D2 INPUT mode and attach a PULLUP resistor
  if(digitalRead(pushButtonSwitch) == HIGH) return;	        // if 5v (HIGH) switch is NOT pushed, 0v (LOW) switch IS pushed
  else {
    ledPatternNo++;
    if(ledPatternNo > (numPatterns -1)) ledPatternNo = 0;
    return;
  }						
}

