/* Ch_10_1_6leds
 
   copy and paste this program into the Arduino IDE
   name this program Ch_10_1_6leds
   
   illuminates the 6 colored LEDs in the sequence contained in the array ledArray[]  
 */
 
//  ------------------------------------------------------------------------------------
int	ledOn = 250;
int	ledOff = 100;

int red = 3;
int orange = 5;
int yellow = 6;
int white = 9;
int green = 10;
int blue = 11;

int ledArray[] = {red, orange, yellow, white, green, blue};

//  ------------------------------------------------------------------------------------
void setup() {
	
  for(int i = 0 ; i < 6 ; i++) {                // make LED pins OUTPUTs and turn off LEDs
	pinMode(ledArray[i], OUTPUT);
	digitalWrite(ledArray[i], LOW);
  }
}

//  ------------------------------------------------------------------------------------
void loop() {
	// turn on each LED, one at a time for time = ledOn
	// and then off for time = ledOff
  for(int i = 0 ; i < 6 ; i++) {
	digitalWrite(ledArray[i], HIGH);
	delay(ledOn);
	digitalWrite(ledArray[i], LOW);
	delay(ledOff);
  }
}

