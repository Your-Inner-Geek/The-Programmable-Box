/* basic_musical_scale_array_define
 
   copy and paste this program into the Arduino IDE
   name this program basic_musical_scale_array_define
   
   Plays Do-Re-Mi... on the buzzer connected to D8
   
   introduces the use of #define rather than use of int for note
 */
//  ------------------------------------------------------------------------------------

// declare and initialize outside of any function so they are global
#define DO   440
#define RE   494
#define MI   554
#define FA   587
#define SOL  659
#define LA   740
#define TI   831
#define DO2  880

int toneArray[] = {DO, RE, MI, FA, SOL, LA, TI, DO2};
#define BUZZER 8

//  ------------------------------------------------------------------------------------
void setup() {
  pinMode(BUZZER, OUTPUT);
  for(int i = 0 ; i < 8 ; i++) {
	tone(BUZZER, toneArray[i]);	// sent the frequency toneArray[i] to the pin buzzer
        delay(400);
        noTone(BUZZER);
        delay(100);
  }
}

//  ------------------------------------------------------------------------------------
void loop() {
// space to insert statements in the loop() function
}

