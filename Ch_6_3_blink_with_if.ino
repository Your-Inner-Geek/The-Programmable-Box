/*
  blink_with_if
  
  Copy and past into the Arduino IDE
  name the program blink_with_if
  
  Starts by turning on an LED on for onTime = onesecond, then off for one second
  Each time through the loop, onTime is increased 2/10 of a second,
  until onTime > 3 seconds, then reset to on second
  
  Introduces the concept of an if statement and testing a variable value
 */
 
//  ------------------------------------------------------------------------------------
int  led = 13;             // Pin 13 has an LED

int  onTime = 1000;        // initial value of time to stay ON
int  offTime = 1000;       // initial value of time to stay OFF
int  increaseTime = 200;   // increase onTime by 200 ms each time through the loop
//  ------------------------------------------------------------------------------------
void setup() {             
  pinMode(led, OUTPUT);    // initialize the digital pin as an output
}
//  ------------------------------------------------------------------------------------
void loop() {
  digitalWrite(led, HIGH);           // turn the LED on (HIGH is the voltage level)
  delay(onTime);                     // wait for onTime ms
  digitalWrite(led, LOW);            // turn the LED off by making the voltage LOW
  delay(offTime);                    // wait for offTime ms
  
  onTime = onTime + increaseTime;    //  increment onTime by increaseTime ms
  
  if(onTime > 3000) {                // once you get to onTime of 3 seconds, reset to 1 second
    onTime = 1000;
  };
}
