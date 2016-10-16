/*
     read_keyboard_play_scale
      
     copy and paste this program into the Arduino IDE
     name this program read_keyboard_play_scale
   
     reads characters from the keyboard, prints on Serial Monitor, plays scale if "P" or "p" received
     introduces the use of the Serial Monitor
 */
 
//  ------------------------------------------------------------------------------------
// space for declaring global variables
 
//  ------------------------------------------------------------------------------------
void setup() {
  	Serial.begin(9600);
}

// ---------------------------------------------------------------------------
void loop() {
  if(switchPushed() == true)	playScale();
  char  inputChar;
  	if(Serial.available() > 0) {
     	    inputChar = Serial.read();
     	    if(inputChar == 'p' || inputChar =='P') {
        	Serial.println("Play scale command received from keyboard");
        	playScale();  
     	    }
	}
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

  static const int buzzer = 8;					        // the buzzer is on D8
  static const int toneArray[] = {Do, Re, Mi, Fa, Sol, La, Ti, Do2};	// moved this into playScale function
  
  for(int i = 0 ; i < 8 ; i++) {
	tone(buzzer, toneArray[i]);	// send the frequency toneArray[i] to the pin “buzzer”
       	delay(1000);			// play tone for one second
  }
 	noTone();			//turn off buzzer at the end of playing scale
}

// ---------------------------------------------------------------------------
boolean switchPushed() {
  const int pushButtonSwitch = 2;	          // switch is on pin D2, declare as constant, hide from other functions
  pinMode(pushButtonSwitch, INPUT_PULLUP);	  // D2 INPUT mode and attach a PULLUP resistor
  if(digitalRead(pushButtonSwitch) == HIGH) return false;	// if 5v (HIGH) switch is NOT pushed
  else return true;						// if 0v (LOW) switch IS pushed
}


