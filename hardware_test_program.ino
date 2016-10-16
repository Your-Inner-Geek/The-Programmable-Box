/*
  hardware_test_program
  
    Copy and past into the Arduino IDE
    name the program hardware_test_program
    
    Will test the following components:
    
      - Buzzer will play do-re-mi for 1/2 second per note from low note to high note - will reverse direction upon momentary contact button push
      - 6 colored LED's will light in sequence from RED to BLUE for 1/2 second and reverse direction upon momentary contact button push
      - the intensity of the 6 LED's is based upon the potentiometer setting - full CCW is off, full CW is maximum brightness
      - flashes the two dual-color LED's red-red-blue-blue for 1/2 second each
      - uses the ultra-sonic range detector to measure distance and displays the distance in inches on the Serial Monitor. Drives the buzzer from a low tone 
      - if the distance is far away to a higher and higher tone as the distance becomes smaller
     
  */

//  ------------------------------------------------------------------------------------
 /*
   Define all the I/O pins being used
  */
 // six colored LED pins
  #define  red      11
  #define  orange   10
  #define  yellow   9
  #define  white    6
  #define  green    5
  #define  blue     3
  
 // dual LED pins for Blue and Red sides 
  #define dualLed1Blue 12
  #define dualLed1Red  14
  #define dualLed2Blue 13
  #define dualLed2Red  15
  
// buzzer
  #define  buzzer   8
  
//  ultra-sonic distance sensor trigger and echo pins
  #define  trigPin   4   
  #define  echoPin   7
 
  int ledDelayTime =     500;
  int dualLedDelayTime = 500;
  int MusicDelayTime =   500;
  
// select the input pin for the potentiometer Analog Pin 7
#define sensorPin  A7
  
// frequencies for musical scale
  #define  Do  440
  #define  Re  494
  #define  Mi  554
  #define  Fa  587
  #define  Sol 659
  #define  La  740
  #define  Ti  830
  #define  Do2 880
 
  int    ledArray[] = {red, orange, yellow, white, green, blue};  // order that the LED's should be turned on and off
  int    toneArray[] = {Do, Re, Mi, Fa, Sol, La, Ti, Do2};        // array of notes to play musical scale
  
  int  freq = toneArray[1];
  int sensorValue = 0;  // variable to store the value coming from the potentiometer
  
  #define up   true
  #define down false
 
 //declare upDownFlag as volatile since the interrupt routine can change its value 
  volatile boolean upDownFlag = up;

  

//  ---------------------------------------------------------------------------
void  setup() {
  
//  setup the push button switch (NOMC) as in input and pull it up to +5v
   pinMode(2, INPUT_PULLUP);
   
// sep up the 6 LED pins as OUTPUT
   for(int ledIndex=0; ledIndex<6; ledIndex++) {
      pinMode(ledArray[ledIndex], OUTPUT);             
   }
   
// set up dual LEDs pins as outputs
   pinMode(dualLed1Blue, OUTPUT); 
   pinMode(dualLed2Blue, OUTPUT);
   pinMode(dualLed1Red, OUTPUT); 
   pinMode(dualLed2Red, OUTPUT);
   
// turn off both sides of the two dual LEDs - LOW lights the LEDs
   digitalWrite(dualLed1Blue, HIGH);
   digitalWrite(dualLed2Blue, HIGH);
   digitalWrite(dualLed1Red, HIGH);
   digitalWrite(dualLed2Red, HIGH);
    
 // make sure that there is no tone from the buzzer
   noTone(buzzer); 
   
 // set up ultra-sonic range detector Trigger pin as OUTPUT and Echo pin as INPUT 
   pinMode(trigPin, OUTPUT); 
   pinMode(echoPin, INPUT); 
   digitalWrite(trigPin, LOW);    // trigger goes high then low to trigger
   Serial.begin(9600);
   attachInterrupt(0, toggleState,LOW);  // attach an interrupt on int0 and program to generate an interrupt when state changes
}

// -----------------------------------------------------------------------
void loop() {
  
// call ultraSonic() function before each other program in order to update distance since that influences the behavior of the other programs
    ultraSonic();
    ledprogram();
    
    ultraSonic();
    testDualLeds();
    
    ultraSonic();
    playSong();
}
// ------------------------------------------------------------------------
void  ledprogram() {
  
/*  This routine will turn on and off the 6 different colored LEDs
    Each LED is on and then off for a period of time ledDelayTime
    The potentiometer determines the brightness of the LED by using PWM (Pulse Width Modulation)
    The lights will ether light from Red to Blue or from Blue to Red as determined by the upDownFlag
    The upDownFlag is toggled by pressing the NOMC push button switch which generates an interrupt on int0
 */
    
    int i = 0;        // loop counter
    int j = 0;        // index into ledArray 0-5 for up, 5-0 for down
    int brightness = potValue();
      
 //   noTone(Buzzer);
    noTone(buzzer);
   
    for(i=0; i<6; i++)
    { 
       if(upDownFlag == up) {
      j = i;          // count 0 to 5
    }
    else {
      j = 5-i;        // count 5 down to 0
    }
      analogWrite(ledArray[j], brightness/4);
      delay(ledDelayTime);

      digitalWrite(ledArray[j], LOW);
      delay(ledDelayTime);
      
    }
}


// ------------------------------------------
void testDualLeds()
{
 
   digitalWrite(dualLed1Red, LOW);
   delay(dualLedDelayTime);
   digitalWrite(dualLed1Red, HIGH);
   delay(dualLedDelayTime);
  
  digitalWrite(dualLed2Red, LOW);
  delay(dualLedDelayTime);
  digitalWrite(dualLed2Red, HIGH);
  delay(dualLedDelayTime);
  
  digitalWrite(dualLed1Blue, LOW);
  delay(dualLedDelayTime);
  digitalWrite(dualLed1Blue, HIGH);
  delay(dualLedDelayTime);
  
  digitalWrite(dualLed2Blue, LOW);
  delay(dualLedDelayTime);
  digitalWrite(dualLed2Blue, HIGH);
  delay(dualLedDelayTime);
 
  
  
}
//------------------------------------------
int  potValue() {
  
// read the value from the potentiometer
  sensorValue = analogRead(sensorPin); 
  return(sensorValue);
}

// ------------------------------------------------------------------------
 
 void playSong() {
 //   Serial.println("playSong program");
    int i ;
    int j = 0;
    for(i=0; i< 8; i++) {
      
      if(upDownFlag == up) {
      j = i;          // count 0 to 5
    }
    else {
      j = 5-i;        // count 5 down to 0
    }
 //    Serial.println(toneArray[i]); 
     tone(buzzer, toneArray[j]); // play a 1000Hz tone on buzzer
     delay(MusicDelayTime);        // wait 
     noTone(buzzer);         // stop the sound
     delay(MusicDelayTime);       // wait 
  
    }
 }
    // ------------------------------------------------------------------------
    
 void  ultraSonic()  { 
   
    long duration, distance, freq; 

    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(15); 
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); 
    distance = (duration/2) / 74; 
   Serial.println(distance);
   if(distance > 80) {
       ledDelayTime =     500;
       dualLedDelayTime = 500;
       MusicDelayTime =   500;
   }
   else {
      ledDelayTime =     20 + 5 * distance;
      dualLedDelayTime = 20 + 5 * distance;
      MusicDelayTime =   20 + 5 * distance;
   }
 /*
    tone(buzzer, 60);
    delay(100);
    noTone(buzzer);
   } 
   else {
       freq = 4060-(40*distance);
       Serial.println(freq);
       tone(buzzer, freq);
       delay(100);
       noTone(buzzer);
   }
 */
 
 }
 
 void toggleState() {
   upDownFlag = !upDownFlag;
 }
