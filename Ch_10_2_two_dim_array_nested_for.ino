
/* Ch_10_2_two_dim_array_nested_for

  Using a two dimensional array and nested "for" loops to control the 6 LED light pattern
 
   copy and paste this program into the Arduino IDE
   name this program Ch_10_2_two_dim_array_nested_for
 */
 
//  ------------------------------------------------------------------------------------
int ledOn = 300;
int ledOff = 150;

int red = 3;
int orange = 5;
int yellow = 6;
int white = 9;
int green = 10;
int blue = 11;

// this is the sequence for the 6 LEDs
int ledArray[] = {red, orange, yellow, white, green, blue};

/*  the 6 x 6 array represents one entire display pattern. The columns represent the 6 LEDs (0 - 5) and the rows
    represent the the pattern that the 6 LEDs will display. A zero means the LED is off and a one means ON.
    So, the first row in the 6x6 array says LED 0 and 5 will be on, all other off, the second row indicates
    that LEd 1 and 4 will be on and so forth.
 */
int numCols = 6;
int numRows = 6;

int sequenceArray [] [6] {
  {1, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 1, 0},
  {0, 0, 1, 1, 0, 0},
  {1, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 1, 0},
  {0, 0, 1, 1, 0, 0}
};

//  ------------------------------------------------------------------------------------
void setup() {
// configure the LED pins as outputs and turn off the LEDs
  for(int i = 0 ; i < numCols ; i++) {
	pinMode(ledArray[i], OUTPUT);
	digitalWrite(ledArray[i], LOW);
  }
}

//  ------------------------------------------------------------------------------------
void loop() {
/* each row represents one LED illumination pattern, display that pattern for time ledOn
   then go to next row and display that pattern
 */
  for(int j = 0; j < numRows ; j++) {      // outter loop - ROW pointer   
    for(int i = 0 ; i < numCols ; i++) {   // inner loop - COLUMN pointer
      if(sequenceArray [j][i] == 0)  digitalWrite(ledArray[i], LOW);
      else                           digitalWrite(ledArray[i], HIGH);
    }
    delay(ledOn);
  }
}
