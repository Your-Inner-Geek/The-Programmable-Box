/* Ch_11_2_range_leds
 
   copy and paste this program into the Arduino IDE
   name this program Ch_11_2_range_leds
   
  This program uses the ultra-sonic range detector to measure the distance in inches
  light from one to six LEDs based upon the distance (all 6 closest)
  play a tone from MIN_FREQ = 60Hz to MAX_FREQ = 4KHz based upon distance (4HKHz is closest)
  turn on/off tone using NOMC push button switch
  */
//  ------------------------------------------------------------------------------------
#define ON               true
#define OFF              false

#define TRIG_PIN         4             // trigger pin on range detector is digital pin D4
#define ECHO_PIN         7             // echo pin is D7
#define BUZZER_PIN       8             // buzzer is on pin D8

#define TRIG_PULSE_WIDTH 15            // use 15 uSec for trigger pulse width
#define SAMPLES          3             // number of distance samples to average
#define MAX_DISTANCE     100           // set maximum distance to 100 inches (quite arbitrary)

#define MIN_FREQ         60            // lowest frequency is 60 Hz
#define MAX_FREQ         4000          // highest frequency is 4KHz

int     playBuzzerFlag = OFF;          // global variable - changed by NOMC push button switch
int     distanceInches = 0;	       // used to hold the returned value of distance in inches

#define   RED            3     // six colored LED pins
#define   ORANGE         5
#define   YELLOW         6
#define   WHITE          9
#define   GREEN          10
#define   BLUE           11

// this is the sequence for the 6 LEDs
 int    ledArray[] = {RED, ORANGE, YELLOW, WHITE, GREEN, BLUE};

/*  the 6 x 6 array represents one entire display pattern. The columns represent the 6 LEDs (0 - 5) and the rows
    represent the the pattern that the 6 LEDs will display. A zero means the LED is off and a one means ON.
    So, the first row in the 6x6 array says LED 0 and 5 will be on, all other off, the second row indicates
    that LEd 1 and 4 will be on and so forth.
 */
int numCols = 6;
int numRows = 6;

int sequenceArray [] [6] {
    {1, 1, 1, 1, 1, 1},        // all lights on, closest
    {0, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 1},
    {0, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0, 1}        // only one light on, farthest
};
//  -----------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);   // set up trigger pin as an output pin
  pinMode(ECHO_PIN, INPUT);       // set up echo pin as an input
  
  digitalWrite(TRIG_PIN, LOW);  // make sure trigger pin is low to start

  // configure the LED pins as outputs and turn off the LEDs
  for(int i = 0 ; i < numCols ; i++) {
	pinMode(ledArray[i], OUTPUT);
	digitalWrite(ledArray[i], LOW);
  }
}
//  -----------------------------------------------------------------------------
void loop() {
 
    int pattern = 0;                    // current pattern of LEDs to display based upon distance
    int duration, freq;                 // frequence for buzzer from 60Hz to 4KHz
    int distance = 0;                   // initialize starting disance as zero
    int accumDistance = 0;              // reset accumulated distance to zero

    if(switchStatus() == true)      playBuzzerFlag = !playBuzzerFlag;  // toggle the playBuzzerFlag
    
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
    freq = map(distance, 0, 100, MAX_FREQ, MIN_FREQ);          // translate from 0 - 100 to 4KHz to 60Hz
    
    if(playBuzzerFlag == ON)  tone(BUZZER_PIN, freq);
    else                      noTone(BUZZER_PIN);
    
    pattern = map(distance, 0, 100, 0, 5);
 
/* each row represents one LED illumination pattern, display that pattern for time ledOn
   then go to next row and display that pattern
 */
    for(int i = 0 ; i < numCols ; i++) {   
      if(sequenceArray [pattern][i] == 0)  digitalWrite(ledArray[i], LOW);
      else                                 digitalWrite(ledArray[i], HIGH);
  }
   
 }
// ---------------------------------------------------------------------------
boolean switchStatus() {
  static const int pushButtonSwitch = 2;	                // switch is on pin D2, declare as constant, hide from other functions
  pinMode(pushButtonSwitch, INPUT_PULLUP);		        // D2 INPUT mode and attach a PULLUP resistor

  if(digitalRead(pushButtonSwitch) == HIGH) return false;	// if 5v (HIGH) switch is NOT pushed
  else                                      return true;	// if 0v (LOW) switch IS pushed
}
