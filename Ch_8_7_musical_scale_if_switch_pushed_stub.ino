/*
     basic_musical_scale_if_switch_pushed_stub
      
     copy and paste this program into the Arduino IDE
     name this program basic_musical_scale_if_switch_pushed_stub
   
     this lesson creates a stub function for testing
 */
//  ------------------------------------------------------------------------------------ 
void setup() {
// space to insert statements in the setup() function
}

// ---------------------------------------------------------------------------
void loop() {
  if(switchStatus() == true)	playScale();
}

// ---------------------------------------------------------------------------
void playScale() {
  static const int Do = 440;
  static const int Re = 494;
  static const int Mi = 554;
  static const int Fa = 587;
  static const int Sol = 659;
  static const int La = 740;
  static const int Ti = 831;
  static const int Do2 = 880;

  static const int buzzer = 8;				// the buzzer is on pin 8

  pinMode(buzzer, OUTPUT);
  
  static const int toneArray[] = {Do, Re, Mi, Fa, Sol, La, Ti, Do2};	// moved this into playScale function
  
  for(int i = 0 ; i < 8 ; i++) {
	tone(buzzer, toneArray[i]);		// send the frequency toneArray[i] to the pin “buzzer”
       	delay(400);
        noTone(buzzer);
        delay(100);
  }
}

// ---------------------------------------------------------------------------
boolean switchStatus() {
// returns true if pushed and false if not pushed
	return true;	// return true for now
}


