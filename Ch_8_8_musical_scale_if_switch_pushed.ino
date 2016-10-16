/*
     basic_musical_scale_if_switch_pushed
      
     copy and paste this program into the Arduino IDE
     name this program basic_musical_scale_if_switch_pushed
   
     will play the musical scale on buzzer if momentary contact switch pushed
 */
//  ------------------------------------------------------------------------------------
// space for declaring global variables

//  -----------------------------------------------------------------------------------
void setup() {
// space to insert statements in the setup() function
}

//  ------------------------------------------------------------------------------------
void loop() {
if(switchStatus() == true)	playScale();
}

//  ------------------------------------------------------------------------------------
void playScale() {
  static const int Do = 440;
  static const int Re = 494;
  static const int Mi = 554;
  static const int Fa = 587;
  static const int Sol = 659;
  static const int La = 740;
  static const int Ti = 831;
  static const int Do2 = 880;
  
  static const int buzzer = 8;		        // the buzzer is on pin 8
  
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
  static const int pushButtonSwitch = 2;	                // switch is on pin D2, declare as constant, hide from other functions
  pinMode(pushButtonSwitch, INPUT_PULLUP);		        // D2 INPUT mode and attach a PULLUP resistor

  if(digitalRead(pushButtonSwitch) == HIGH) return false;	// if 5v (HIGH) switch is NOT pushed
  else return true;						// if 0v (LOW) switch IS pushed
}


