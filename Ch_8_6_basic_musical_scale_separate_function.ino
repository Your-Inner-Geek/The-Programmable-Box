/* basic_musical_scale_separate_function
 
   copy and paste this program into the Arduino IDE
   name this program basic_musical_scale_separate_function
   
   Plays Do-Re-Mi... on the buzzer connected to D8
   introduces the use of #define rather than use of int for notes 
 */
 
//  ------------------------------------------------------------------------------------
// declare and initialize outside of any function so they are global
#define DO  	440		// declare and initialize outside of any function so they are global
#define RE  	494		// later we will reconsider where these should be placed
#define MI  	554
#define FA  	587
#define SOL	659
#define LA  	740
#define TI  	831
#define DO2  	880
#define BUZZER 	8		// the buzzer is on D8

int toneArray[] = {DO, RE, MI, FA, SOL, LA, TI, DO2};	// probably move this to playScale function
							// so other functions can’t change the values
// --------------------------------------------------------------------------
void setup() {
  pinMode(BUZZER, OUTPUT);				
}

// ---------------------------------------------------------------------------
void loop() {
  playScale();					// call the playScale function to play the scale
}

// ---------------------------------------------------------------------------
void playScale() {
   for(int i = 0 ; i < 8 ; i++) {
	tone(BUZZER, toneArray[i]);	// sent the frequency toneArray[i] to the pin “buzzer”
       	delay(400);
        noTone(BUZZER);
        delay(100);
   }

}


