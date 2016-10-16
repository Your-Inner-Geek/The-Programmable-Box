/*
      basic_buzzer_1khz
      
      copy and paste this program into the Arduino IDE
      name this program basic_buzzer_1khz
      
      first introduction of the tone() and noTone() functions
 */
//  ------------------------------------------------------------------------------------
//	play a tone of 1000 Hz on the buzzer connected to pin 8 for 3 seconds and then silence
int	buzzer = 8;			// buzzer is on Digital pin 8
int	frequency = 1000;		// play frequency of 1000 Hz
int	duration = 3000;		// duration of 3 seconds

//  ------------------------------------------------------------------------------------
void setup() {
	pinMode(buzzer, OUTPUT);	// set the pin D8 as an OUTPUT pin
	tone(buzzer, frequency)	;	// apply tone of frequency “frequency” to pin “buzzer”)
	delay(duration);		// play tone for time = duration ms
	noTone(buzzer);		        // stop playing the tone on pin “buzzer”
}

//  ------------------------------------------------------------------------------------
void loop() {
					// nothing to do over and over again
}


