

/* Ch_12_challange_pwm_intensity_leds
 
   copy and paste this program into the Arduino IDE
   name this program Ch_12_challange_pwm_intensity_leds
 */

//  ------------------------------------------------------------------------------------
volatile int     ledPatternNo = 0;  // which pattern to display
         int     numPatterns = 3;   // total number of patterns - NOT starting from zero, loop counters go from 0 -> numPatterns -1

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
 {                               // light LEDs from outside -> center
  {1, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 1, 0},
  {0, 0, 1, 1, 0, 0},
  {1, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 1, 0},
  {0, 0, 1, 1, 0, 0}
 },
 {                              // light LEDs from top to bottom
  {1, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 1}
 },
 {                              // light two LEDs and have them travel
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

    for(int i = 0 ; i < 6 ; i++) {          // configure the LED pins as outputs and turn off the LEDs
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
  unsigned int brightness = potValue();
  if (brightness < 100) brightness = 100;
  
  for(int j = 0; j < 6 ; j++) {                // outter loop - ROW pointer
    for(int i = 0 ; i < 6 ; i++) {             // inner loop - COLUMN pointer
      if(sequenceArray [ledPatternNo][j][i] == 0) analogWrite(ledArray[i], LOW);
      else                                        analogWrite(ledArray[i], brightness/4);
    }
    delay(ledOn);
  }
}

// ---------------------------------------------------------------------------
void switchPushed() {

  int j = 0;                                    // debounce counter, require at least 3 times detecting button pushed to declare valid
  const int pushButtonSwitch = 2;	        // switch is on pin D2, declare as constant, hide from other functions
  pinMode(pushButtonSwitch, INPUT_PULLUP);      // D2 INPUT mode and attach a PULLUP resistor
  delay(10);                                    // button was pushed to trigger interrup, wait 10 ms before looking at switch again
  		        
  if(digitalRead(pushButtonSwitch) == HIGH) return;	// if 5v (HIGH) switch is NOT pushed - probably bouncing
  else {                                                // if 0v (LOW) switch IS pushed, now see if it stays pushed
    while(digitalRead(pushButtonSwitch)== LOW) {        // as long as it stays pushed, stay in loop and increment j the bounce counter
        delay(10);                                      // sample switch every 10 ms
        if(digitalRead(pushButtonSwitch)== LOW) j++;    // is still pushed after 10 ms, increment j counter and loop again
        
    }                                            // button no longer pushed, check to see how many 10 ms intervals it was pushed
    if(j >= 3) {                                 // is detected "pushed" more that 3 times over at least 30 ms, declare valid push
      ledPatternNo++;                            // valid push, point to next LED sequence
      if(ledPatternNo > (numPatterns -1)) ledPatternNo = 0;
      return;
    }
  }						
}
//------------------------------------------
int  potValue() {
  int potPin = 7;
// read the value from the potentiometer
  return(analogRead(A7));
}
