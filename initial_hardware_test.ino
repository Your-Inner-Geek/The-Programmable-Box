/*
  kit hardware test
  
    Copy and past into the Arduino IDE
    name the program initial_hardware_test
    
    This will test the board that is shipped with the kit with the arduino nano and the
    ultra-sonic range detector installed.

    This program will blink the on-board LED faster and faster as the distance measured by
    the range detector is decreased.
    
    By moving your hand closer to the range detector, the LED should flash faster and faster.  

    By setting toScreen to true, the program will also print the distance to the screen if serial monitor is enabled
  */

//  ------------------------------------------------------------------------------------
//  ultra-sonic distance sensor trigger and echo pins
  #define  trigPin   4   
  #define  echoPin   7

  #define  toScreen true  // if true, then print distance to computer screen as well as flash the LED
  
  int ledDelayTime =     500;

//  ---------------------------------------------------------------------------
void  setup() {
if(toScreen) Serial.begin(9600);  // if toScreen is true, enable serial monitor

// sep up the LED pin as OUTPUT
  pinMode(LED_BUILTIN, OUTPUT); 
   
 // set up ultra-sonic range detector Trigger pin as OUTPUT and Echo pin as INPUT 
   pinMode(trigPin, OUTPUT); 
   pinMode(echoPin, INPUT); 
   digitalWrite(trigPin, LOW);    // trigger goes high then low to trigger
}

// -----------------------------------------------------------------------
void loop() {
  
// call ultraSonic() function before each other program in order to update distance since that influences the behavior of the other programs
    
    ledprogram(ultraSonic());
    
}
// ------------------------------------------------------------------------
void  ledprogram(int ledDelayTime) {
  
      digitalWrite(LED_BUILTIN, HIGH);
      delay(ledDelayTime);

      digitalWrite(LED_BUILTIN, LOW);
      delay(ledDelayTime);
}

    // ------------------------------------------------------------------------
    
 int  ultraSonic()  { 
   
    long duration, distance, freq; 

    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(15); 
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH); 
    distance = (duration/2) / 74; 
  //  Serial.println(distance);
    if(distance > 100) distance = 100;
    if(distance < 0) distance = 0;
 
    ledDelayTime =     20 + 5 * distance;
    
    if(ledDelayTime < 0) ledDelayTime = 0;
    delay(10);
   if(toScreen) Serial.println(ledDelayTime); // if toScreen is true then print to serial monitor
   return ledDelayTime;
   }
 
