
//  ------------------------------------------------------------------------------------
/*
   Define all the I/O pins being used
  */
  
#define   RED                  3     // six colored LED pins
#define   ORANGE               5
#define   YELLOW               6
#define   WHITE                9
#define   GREEN               10
#define   BLUE                11

#define   DUAL_LED1_BLUE       12    // dual LED pins for Blue and Red sides 
#define   DUAL_LED1_RED        14
#define   DUAL_LED2_BLUE       13
#define   DUAL_LED2_RED        15  

#define   BUZZER               8  
  
int ledDelayTime       =     500;
int dualLedDelayTime   =     500;
int toggle             =     false;

int    ledArray[]      =     {RED, ORANGE, YELLOW, WHITE, GREEN, BLUE};  // order that the LED's should be turned on and off

//  ------------------------------------------------------------------------------------
void setup() {

   // sep up the 6 LED pins as OUTPUT and turn ON
   for(int ledIndex=0; ledIndex<6; ledIndex++) {
      pinMode(ledArray[ledIndex], OUTPUT); 
      digitalWrite(ledArray[ledIndex], HIGH);   // HIGH turns ON these LED's   
   }
   // set up dual LEDs pins as outputs
   pinMode(DUAL_LED1_BLUE, OUTPUT);   
   pinMode(DUAL_LED2_BLUE, OUTPUT);
   pinMode(DUAL_LED1_RED, OUTPUT); 
   pinMode(DUAL_LED2_RED, OUTPUT);
 
   pinMode(BUZZER, OUTPUT);
   tone(BUZZER, 1000);
}

//  ------------------------------------------------------------------------------------
void loop() {
   
  digitalWrite(DUAL_LED1_BLUE, LOW); // LOW turns ON these dual colored LED's
  digitalWrite(DUAL_LED2_BLUE, LOW);
  digitalWrite(DUAL_LED1_RED, HIGH);
  digitalWrite(DUAL_LED2_RED, HIGH);

  delay(100);
  
   digitalWrite(DUAL_LED1_BLUE, HIGH); 
  digitalWrite(DUAL_LED2_BLUE, HIGH);
  digitalWrite(DUAL_LED1_RED, LOW);
  digitalWrite(DUAL_LED2_RED, LOW);

  delay(100);
 }
