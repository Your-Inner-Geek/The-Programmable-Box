 
 
#define RED      3
#define ORANGE   5
#define YELLOW   6
#define WHITE    9
#define GREEN    10
#define BLUE     11

// this is the sequence for the 6 LEDs
int ledArray[] = {RED, ORANGE, YELLOW, WHITE, GREEN, BLUE};

// dual LED pins for Blue and Red sides 
  #define DUAL_LED1_RED 12
  #define DUAL_LED1_BLUE  14
  #define DUAL_LED2_RED 13
  #define DUAL_LED2_BLUE  15
  
const int PUSH_BUTTON_SWITCH = 2;
#define BUZZER 8

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
 
void setup() {
  Serial.begin(9600);
    pinMode(PUSH_BUTTON_SWITCH, INPUT_PULLUP);
    
// set up dual LEDs pins as outputs
   pinMode(DUAL_LED1_BLUE, OUTPUT); 
   pinMode(DUAL_LED2_BLUE, OUTPUT);
   pinMode(DUAL_LED1_RED, OUTPUT); 
   pinMode(DUAL_LED2_RED, OUTPUT);
   
// turn off both sides of the two dual LEDs - LOW lights the LEDs
   digitalWrite(DUAL_LED1_BLUE, HIGH);
   digitalWrite(DUAL_LED2_BLUE, HIGH);
   digitalWrite(DUAL_LED1_RED, HIGH);
   digitalWrite(DUAL_LED2_RED, HIGH);
   attachInterrupt(0, switchPushed,LOW);
}

// ------------------------------------------------------
void loop() {
  
  if(applause) {
    tone(BUZZER, 1000);
    delay(100);
    noTone(BUZZER);
    
    delay(50);
    
    tone(BUZZER, 1000);
    delay(100);
    noTone(BUZZER);
    
    applause = false;
  }
  if(boo == true) {
    tone(BUZZER, 300);
    delay(1000);
    noTone(BUZZER);
    boo = false;
  }
   
    lightDualLeds(globalIndex = random(0, 15));
    
    for(int j = 0 ; j < 6 ; j++) {
      if(j<numCorrect) digitalWrite(ledArray[5-j], HIGH);
      else             digitalWrite(ledArray[5-j], LOW);
    }
    Serial.println(globalIndex);
    Serial.print("number correct = ");
    Serial.println(numCorrect);
    delay(dualLedDelayTime[numCorrect]);
  
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
 
  delayMicroseconds(100000);
  if(digitalRead(PUSH_BUTTON_SWITCH) == HIGH) return;	        // if 5v (HIGH) switch is NOT pushed, 0v (LOW) switch IS pushed
  else while(digitalRead(PUSH_BUTTON_SWITCH) == LOW) {
    // loop
  }
  if(globalIndex == 10) {
       numCorrect = numCorrect + 1;
       applause = true;
       return;
   }
   else {
     numCorrect = 0;
     boo = true;
   }
   return; 						
}
