/* Ch_11_1_range_screen
 
   copy and paste this program into the Arduino IDE
   name this program Ch_11_1_range_screen
   
   uses the ultra-sonic range detector to measure the distance in inches
   to an object and print distance on screen
   
   also plays a tone associated with the distance from MIN_FREQ (farthest away) to MAX_FREQ (closest)
 */
//  ------------------------------------------------------------------------------------

#define TRIG_PIN         	4             // trigger pin on range detector is digital pin D4
#define ECHO_PIN        	7             // echo pin is D7
#define BUZZER_PIN      	8             // buzzer is on pin D8

#define TRIG_PULSE_WIDTH	15            // use 15 uSec for trigger pulse width
#define SAMPLES                 3             // number of distance samples to average
#define	MIN_FREQ                60	      // 60 Hz minimum
#define MAX_FREQ                4000	      // 4 KHz maximum

int distanceInches = 0;			// used to hold the returned value of distance in inches


//  -----------------------------------------------------------------------------
void setup() {
  pinMode(TRIG_PIN, OUTPUT);           // set up trigger pin as an output pin
  pinMode(ECHO_PIN, INPUT);            // set up echo pin as an input
  
  digitalWrite(TRIG_PIN, LOW);         // make sure trigger pin is low to start

  Serial.begin(9600);                  // setup serial I/O to display
}
//  -----------------------------------------------------------------------------
void loop() {
 
    int duration, freq; 
    int distance = 0; 
    int accumDistance = 0;                  // reset accumulated distance to zero

    for(int i = 0 ; i < SAMPLES ; i++) {
      // send trigger pulse
      digitalWrite(TRIG_PIN, HIGH);        // measure the distance SAMPLES times and use average distance
      delayMicroseconds(TRIG_PULSE_WIDTH); // wait TRIG_PULSE_WIDTH micro seconds
      digitalWrite(TRIG_PIN, LOW);
    
      // wait for echo and measure it
      duration = pulseIn(ECHO_PIN, HIGH); 
      distance =(duration/2)*.0135135;     // get current distance measurement
 
     if(distance > 100)  distance = 100;   // largest distance allowed is 100 inches (completely arbitrary)
     if(distance <= 0)   distance = 0;     // just to be sure you dont get a negative number
     
     accumDistance = accumDistance + distance;  // add current distance to accumulated distance
     delay(100);                                // wait 1/10 second before taking another distance measurement
    }
    distance = accumDistance/SAMPLES;          // calculate the average distance
   
    freq = map(distance, 0, 100, MAX_FREQ, MIN_FREQ);  // map the measured distance from 0 - 100 inches
    
    Serial.print("distance = ");
    Serial.print(distance);

    Serial.print("         frequency = ");
    Serial.println(freq);                              // to a number between MAX_FREQ and MIN_FREQ

   tone(BUZZER_PIN, freq);
 }

