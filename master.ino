

// generally useful #defines that can be used by other functions
#define ON               true
#define OFF              false
#define UP               true
#define DOWN             false

//  ------------------------------------------------------------------------------------
// hardware pin numbers that can be used by other functions
#define   PUSH_BUTTON_SWITCH   2
#define   BUZZER               8

#define   RED                  3     // six colored LED pins
#define   ORANGE               5
#define   YELLOW               6
#define   WHITE                9
#define   GREEN               10
#define   BLUE                11

#define   DUAL_LED1_BLUE       12      // dual LED pins for Blue and Red sides 
#define   DUAL_LED1_RED        14
#define   DUAL_LED2_BLUE       13
#define   DUAL_LED2_RED        15

#define   TRIG_PIN             4       // trigger pin on range detector is digital pin D4
#define   ECHO_PIN             7       // range detector echo pin is D7

#define   POT_PIN              A7      // potentiometer input
//  ------------------------------------------------------------------------------------

// global variables that are changed by the interrupt routine and read by other functions
volatile boolean longPush   = false;    // this is reset to false by the loop() program after pointing to the next function to run
volatile boolean shortPush  = false;
volatile boolean needToBuzz  = false;
volatile boolean firstCall = false;    // for functions that you only want to run once, function should reset to false before exiting
volatile boolean upDownFlag = UP;

// global variables that can be accessed by any function
int     playBuzzerFlag     = OFF;
int     programToRun       = 0;
 int    ledPatternNo = 0;    // current pattern to display
//  ------------------------------------------------------------------------------------
// constants used by various programs - user can change these values
  
  #define TRIG_PULSE_WIDTH   15            // use 15 uSec for trigger pulse width
  #define MAX_DISTANCE       100           // set maximum distance to 100 inches (quite arbitrary)
 
// variables that MAY remain constant but MAY be changed by user inputs or functions
  int ledDelayTime         =   100;
  int MusicDelayTime       =   300;
  int sensorValue          =   0;          // variable to store the value coming from the potentiometer

// frequencies for musical scale
  #define  Do  440
  #define  Re  494
  #define  Mi  554
  #define  Fa  587
  #define  Sol 659
  #define  La  740
  #define  Ti  830
  #define  Do2 880
  
  int    ledArray[] = {RED, ORANGE, YELLOW, WHITE, GREEN, BLUE};  // order that the LED's should be turned on and off
  int    toneArray[] = {Do, Re, Mi, Fa, Sol, La, Ti, Do2};        // array of notes to play musical scale
  
  int dualLedArray[] = {DUAL_LED1_BLUE, DUAL_LED1_RED, DUAL_LED2_BLUE, DUAL_LED2_RED};
  int dualLedDelayTime[] = {500, 450,  400, 350, 325, 300};
 
 boolean displayCombos[] [4] {
   {0,0,0,0},
   {0,0,0,1},
   {0,0,1,0},
   {0,0,1,1},
   {0,1,0,0},
   {0,1,0,1},
   {0,1,1,0},
   {0,1,1,1},
   {1,0,0,0},
   {1,0,0,1},
   {1,0,1,0},
   {1,0,1,1},
   {1,1,0,0},
   {1,1,0,1},
   {1,1,1,0},
   {1,1,1,1}
 };

 int globalIndex = 0;
 int numCorrect = 0;
 boolean applause = false;
 boolean boo = false;
//  ---------------------------------------------------------------------------
// enumeration of programs for switch statement

int numberOfPrograms = 5;

#define BLINK_LEDS      0
#define PLAY_SCALE      1
#define THREE_ARRAY     2
#define ULTRA_BAR_GRAPH 3
#define LED_GAME        4

// --------------------------------------------
void setup() {

   pinMode(PUSH_BUTTON_SWITCH, INPUT_PULLUP);     //  setup the push button switch (NOMC) as in input and pull it up to +5v
   for(int ledIndex=0; ledIndex<6; ledIndex++) {  // sep up the 6 LED pins as OUTPUT
      pinMode(ledArray[ledIndex], OUTPUT);             
   }
   pinMode(DUAL_LED1_RED, OUTPUT);                 // set up dual LEDs pins as outputs
   pinMode(DUAL_LED1_BLUE, OUTPUT);
   pinMode(DUAL_LED2_RED, OUTPUT); 
   pinMode(DUAL_LED2_BLUE, OUTPUT);
   
   digitalWrite(DUAL_LED1_RED, HIGH);            // turn off both sides of the two dual LEDs - LOW lights the LEDs
   digitalWrite(DUAL_LED1_BLUE, HIGH);
   digitalWrite(DUAL_LED2_RED, HIGH);
   digitalWrite(DUAL_LED2_BLUE, HIGH);
    
   noTone(BUZZER);                             // make sure that there is no tone from the BUZZER
   
   pinMode(TRIG_PIN, OUTPUT);                 // range detector Trigger pin as OUTPUT
   pinMode(ECHO_PIN, INPUT);                  // Echo pin as INPUT
   digitalWrite(TRIG_PIN, LOW);               // trigger goes high then low to trigger
  
  
  attachInterrupt(0, switchPushed,LOW);
}

// --------------------------------------------
void loop() {

 if(longPush == true) {    // for longPush, point to next program to run
   longPush = false;      // reset longPush flag
   LongBuzz();            // do a long buzz, then reset the needToBuzz flag      
   needToBuzz = false;
   
   programToRun++;      // a long push moves to the next program to run
   if(programToRun >= numberOfPrograms)         programToRun = 0;
 } 
 else if(needToBuzz == true) {  // for short buzz (or beepBeep), call beepBeep, reset needToBuzz, but do not reset shortPush
     beepBeep();
     needToBuzz = false;
 }
   switch(programToRun) {
     
     case BLINK_LEDS:
          ledprogram();
          break;
          
     case PLAY_SCALE:
          playScale();
          break;
          
     case THREE_ARRAY:
          threeArray();
          break;
         
     case ULTRA_BAR_GRAPH:
          ultraBarGraph();
          break;
         
     case LED_GAME:
          ledGame();
          break;
         
     default:
         break;
   } 
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
    noTone(BUZZER);
    firstCall = false;
    if(shortPush == true) {
      shortPush = false;
      upDownFlag = !upDownFlag;  // shortPush will make LED's blink in opposite direction
   }
   for(i=0; i<6; i++) { 
       if(upDownFlag == UP)      j = i;          // count 0 to 5
       else                      j = 5-i;        // count 5 down to 0
       
       if (brightness < 50) brightness = 50;
       analogWrite(ledArray[j], brightness/4);
       delay(ledDelayTime);

       digitalWrite(ledArray[j], LOW);
       delay(ledDelayTime);
    }
}

//------------------------------------------

void playScale() {
 /*
   to insert your own code rather than playing the misical scale:
   1. only run your code if(shortPush || firstCall == true) (e.g. if shortPush or firstCall are true)
   2. be sure to reset shortPush = false; so it only runs once per short push
 */

    
    if(firstCall || shortPush == true) {  
// ---------------------------------------------------------------------------------------------------
//  place your code to execute here and replace this code     
       for(int i = 0 ; i < 8 ; i++) {
	      tone(BUZZER, toneArray[i]);		// send the frequency toneArray[i] to the pin “buzzer”

       	delay(MusicDelayTime);
        noTone(BUZZER); //turn off buzzer at the end of playing scale
        if(longPush) return;
        delay(200);			
        }
 // reset flags before exit
 // ---------------------------------------------------------------------------------------------------			
       firstCall = false;
       shortPush = false;
     }
}
     
//------------------------------------------
void ultraBarGraph() {
  
  int  numCols = 6;
  
  int sequenceArray [] [6] {
     {1, 1, 1, 1, 1, 1},       // all lights on, closest
     {0, 1, 1, 1, 1, 1},
     {0, 0, 1, 1, 1, 1},
     {0, 0, 0, 1, 1, 1},
     {0, 0, 0, 0, 1, 1},
     {0, 0, 0, 0, 0, 1}       // only one light on, farthest
  };
  
    int pattern = 0;                    // current pattern of LEDs to display based upon distance
    int SAMPLES = 3;                    // number of distance samples to average
    int duration, freq;                 // frequence for buzzer from 60Hz to 4KHz
    int distance = 0;                   // initialize starting disance as zero
    int accumDistance = 0;              // reset accumulated distance to zero

    firstCall = false;
    if(shortPush == true) {
      playBuzzerFlag = !playBuzzerFlag;  // toggle the playBuzzerFlag
      shortPush = false;
    }
    noTone(BUZZER);
    for(int i = 0 ; i < SAMPLES ; i++) {
      // send trigger pulse
      digitalWrite(TRIG_PIN, HIGH); 
      delayMicroseconds(TRIG_PULSE_WIDTH);         // wait TRIG_PULSE_WIDTH micro seconds
      digitalWrite(TRIG_PIN, LOW);
    
      // wait for echo and measure it
      duration = pulseIn(ECHO_PIN, HIGH); 
      distance =(duration/2)*.0135135;             // get current distance measurement
 
     if(distance > MAX_DISTANCE)  distance = 100;  // largest distance allowed is MAX_DISTANCE inches
     if(distance <= 0)   distance = 0;             // just to be sure you dont get a negative number
     
     accumDistance = accumDistance + distance;     // add current distance to accumulated distance
     delay(60);                                    // wait 60ms before taking another distance measurement
    }
    
    distance = accumDistance/SAMPLES;              // calculate the average distance
 
    // average distance now constrained from 0" to 100"
    freq = map(distance, 0, 100, 4000, 60);            // translate from 0 - 100 to 4KHz to 60Hz

    if(playBuzzerFlag == ON){
      tone(BUZZER, freq);
      delay(25);
    }
    else                      noTone(BUZZER);
    
    pattern = int(map(distance, 0, 100, 0, 5));

/* each row represents one LED illumination pattern, display that pattern for time ledOn
   then go to next row and display that pattern
 */
    for(int i = 0 ; i < numCols ; i++) {   
      if(sequenceArray [pattern][i] == 0)  digitalWrite(ledArray[i], LOW);
      else                                 digitalWrite(ledArray[i], HIGH);
    }
}

//------------------------------------------

void threeArray() {
 
const  int  numRows = 6;
const  int numCols = 6;
  
  int     numPatterns = 3;     // number of patterns 
  int sequenceArray [3] [numRows] [numCols] {
   {                                  // light LEDs from outside -> center
    {1, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 1, 0},
    {0, 0, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 1, 0},
    {0, 0, 1, 1, 0, 0}
   },
   {                                  // light LEDs from top to bottom
    {1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1}
   },
   {                                  // light two LEDs and have them travel
    {1, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 1, 1}
   }
  };
    for(int j = 0; j < numRows ; j++) {
      for(int i = 0 ; i < numCols ; i++) {
        if(sequenceArray [ledPatternNo][j][i] == 0)  digitalWrite(ledArray[i], LOW);
        else                                         digitalWrite(ledArray[i], HIGH);
      }
      delay(ledDelayTime);
    }
     
   if(shortPush == true){            // select next pattern if switch is pressed

        ledPatternNo++;
        if(ledPatternNo >= numPatterns) ledPatternNo = 0;
      shortPush = false;
      } 
      return;
}
// ------------------------------------------------------
void ledGame() {
 
  if(shortPush == true) {
    shortPush = false;
     if(globalIndex == 10) {
       numCorrect = numCorrect + 1;
   
       tone(BUZZER, 1000);
       delay(100);
       noTone(BUZZER);
    
       delay(50);
    
       tone(BUZZER, 1000);
       delay(100);
       noTone(BUZZER);
    
    } else {
        tone(BUZZER, 300);
        delay(1000);
        noTone(BUZZER);
        numCorrect = 0;
    }
  }
    lightDualLeds(globalIndex = random(0, 15));
    
    for(int j = 0 ; j < 6 ; j++) {
      if(j<numCorrect) digitalWrite(ledArray[5-j], HIGH);
      else             digitalWrite(ledArray[5-j], LOW);
    }
   
    delay(dualLedDelayTime[numCorrect]);
   
   digitalWrite(DUAL_LED1_RED, HIGH);            // turn off both sides of the two dual LEDs - LOW lights the LEDs
   digitalWrite(DUAL_LED1_BLUE, HIGH);
   digitalWrite(DUAL_LED2_RED, HIGH);
   digitalWrite(DUAL_LED2_BLUE, HIGH);
   
}  
 

// ------------------------------------------------------
void lightDualLeds(int index) {
  for(int i = 0 ; i < 4 ; i++) {
    if(displayCombos[index][i] == 0) {
         digitalWrite(dualLedArray[i], HIGH);
    }
    else digitalWrite(dualLedArray[i], LOW);
  }

}
// ---------------------------------------------------------------------------
void switchPushed() {
  
 long  int     lengthCounter = 0;
       int     unPushedCounter = 0;
       boolean switchIsPushed = false;
 
  // wait for 5000 samples after button released
  while(unPushedCounter	<5000) {                        
    if((switchIsPushed = digitalRead(PUSH_BUTTON_SWITCH)) == LOW)  lengthCounter = lengthCounter + 1;
    else                                                           unPushedCounter = unPushedCounter + 1;
  }
//  if button was pushed for a long time then set needToBuzz flag, longPush flag, and firstCall flag
  if(lengthCounter > 40000) {
    needToBuzz = true;
    firstCall = true;
    longPush = true;
    
    shortPush = false;
  } 
  else {
    needToBuzz = true;
    longPush = false;
    shortPush = true;
    }
    delayMicroseconds(200000);
    return;				
}
// ------------------------------------------------------
void beepBeep() {
   tone(BUZZER, 2000);
   delay(50);
     
   noTone(BUZZER);
   delay(100);
     
   tone(BUZZER, 2000);
   delay(50);
     
   noTone(BUZZER);
   delay(100);
}
// ------------------------------------------------------
void LongBuzz(){
   tone(BUZZER, 1000);
   delay(500);
   noTone(BUZZER);
   delay(300);
}
//------------------------------------------
int  potValue() {
  
// read the value from the potentiometer
  sensorValue = analogRead(POT_PIN); 
  return(sensorValue);
}
