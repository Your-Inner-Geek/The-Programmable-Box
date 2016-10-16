/*
  blink_longer
  
  Copy and past into the Arduino IDE
  name the program blink_longer
  
  Starts by turning on an LED on for onTime = onesecond, then off for one second
  Each time through the loop, onTime is increased 1/10 of a second, forever
  Introduces the concept of an int variable with global scope
 */
 
//  ------------------------------------------------------------------------------------
int led = 13;               // Pin 13 has an LED connected
int onTime = 1000;          // onTime variable will be used to modify the ON delay time

//  ------------------------------------------------------------------------------------
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}
//  ------------------------------------------------------------------------------------
void loop() {
  digitalWrite(led, HIGH);  	 // turn the LED on (HIGH is the voltage level)
  delay(onTime);                 // wait for time = onTime
  digitalWrite(led, LOW);    	 // turn the LED off by making the voltage LOW
  delay(1000);              	 // wait for a second
  onTime = onTime + 100;    	 // increase ON time by 1/10 of a second
}


