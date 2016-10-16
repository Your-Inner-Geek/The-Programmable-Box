/*
  blink_with_if_else
  
  Copy and past into the Arduino IDE
  name the program blink_with_if_else
  
  Starts by turning on an LED on for onTime = onesecond, then off for one second
  Each time through the loop, onTime is increased 1/5 of a second,
  until onTime > 3 seconds, then reset to one second
  
  Introduces the concept of an else statement where one block of code executes 
  if the if(test) is true and a different block of code executes if the 
  if(test) is false
 */
//  ------------------------------------------------------------------------------------
int  led = 13;             // Pin 13 has an LED

int  onTime = 1000;        // initial value of time to stay ON
int  offTime = 1000;       // value of time to stay OFF
int  increaseTime = 200;   // increase onTime by 200 ms each time through the loop

//  ------------------------------------------------------------------------------------
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}
//  ------------------------------------------------------------------------------------
void loop() {
  digitalWrite(led, HIGH);           // turn the LED on (HIGH is the voltage level)
  delay(onTime);                     // wait for onTime ms
  digitalWrite(led, LOW);            // turn the LED off by making the voltage LOW
  delay(offTime);                    // wait for offTime ms
   
  if(onTime > 3000)  onTime = 1000;
  else               onTime = onTime + increaseTime; 
}
