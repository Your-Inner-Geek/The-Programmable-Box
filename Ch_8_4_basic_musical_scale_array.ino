/* Basic_musical_scale_array
 
   copy and paste this program into the Arduino IDE
   name this program Basic_musical_scale_array
   
   Plays Do-Re-Mi... on the buzzer connected to D8
   
   first introduction of the use of an array[] and also the for loop
   
 */
//  ------------------------------------------------------------------------------------  

// declare and initialize outside of any function so they are global
int Do = 440;
int Re = 494;
int Mi = 554;
int Fa = 587;
int Sol = 659;
int La = 740;
int Ti = 831;
int Do2 = 880;

int toneArray[] = {Do, Re, Mi, Fa, Sol, La, Ti, Do2};
int buzzer = 8;

//  ------------------------------------------------------------------------------------
void setup() {
  pinMode(buzzer, OUTPUT);
  for(int i = 0 ; i < 8 ; i++) {
	tone(buzzer, toneArray[i]);	// sent the frequency toneArray[i] to the pin “buzzer”
        delay(400);
        noTone(buzzer);
        delay(100);
  }
}
//  ------------------------------------------------------------------------------------
void loop() {
// space to insert statements in the loop() function
}

  
