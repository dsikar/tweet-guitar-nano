
// To accept commands via serial monitor
String txtMsg = ""; 

// Use these pins on Nano to match NodeMCU
int iXStepPin = 16;
int iXDirPin = 5;
int iYStepPin = 4;
// Changed to pin 2 to avoid potential Serial RX TX pin conflicts
// int iYDirPin = 0;
int iYDirPin = 2;

// Direction generics
int iFwd = 1;
int iBwd = 0;

// Exception case flag for home

bool bSafe;

// End Stop expected threshold AD Conversion
int iThreshold = 130;

// Serial debug. Set to 1 to debug.
#define SERIAL_DEBUG 0

// Current X and Y position markers

int iXPos;
int iYPos;
int iXInitPos = 25;
int iYInitPos = 56;
// Relative origin
int iYRelPos;

// Fret position mapping

// String position mapping

int iOneStringStep = 50;
int iPluckE = iOneStringStep;
int iPluckA = iOneStringStep * 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // init pins
  initGuitar();
}

void initGuitar() {
  pinMode(iXDirPin, OUTPUT);
  pinMode(iXStepPin, OUTPUT);  
  pinMode(iYDirPin, OUTPUT);
  pinMode(iYStepPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Serial.println(analogRead(0));
  //delay(1000);
  
  
  
  // receive message from serial and deal with it
  // 1. SEND - Assemble message sent via Serial Monitor
  while (Serial.available() > 0) {
    char inChar = Serial.read();
    txtMsg += inChar;
  }
  // Delay used for human readability so we don't split messages
  // typed in Serial Monitor. 
  // If application at the other end can identify beginning and end
  // of message such as delimiters, delay is not required.
  delay(200);
  if (txtMsg.length() > 0) {
    processMsg(txtMsg);  
  }
}

void processMsg(String &txtMsg) {
   // Echo message to Serial Monitor. 
   
   // Case 1 - fwdx
   txtMsg.trim();
   if(txtMsg == "fwdx") {
     // Set direction pin
     movx(iFwd, 5, 6);
     txtMsg = "";
    // return;
   }
   // Case 2 - bacx
   if(txtMsg == "bwdx") {
     // Set direction pin
    movx(iBwd, 5, 6);
    txtMsg = "";
    // return;
   }   
   // Case 3 - fwdy
   if(txtMsg == "fwdy") {
     // Set direction pin
     movy(iFwd, 5, 6);
     txtMsg = "";
     // return;
   }   
   // Case 4 - bacy
   if(txtMsg == "bwdy") {
     // Set direction pin
     movy(iBwd, 5, 6);
     txtMsg = "";
     // return;
   }   
   // Case 5 - homeX
   if(txtMsg == "homeX") {
     // Set direction pin
     homeX();
     txtMsg = "";
     // return;
   }      
   // Case 6 - homeY
   if(txtMsg == "homeY") {
     // Set direction pin
     homeY();
     txtMsg = "";
     // return;
   }   
   // Case 7 - homeXY
   if(txtMsg == "homeXY") {
     // Set direction pin
     homeXY();
     txtMsg = "";
     // return;
   }
   
   // Case 8 - pluck1
   if(txtMsg == "pluck1") {
     // Set direction pin
     pluckString(1);
     txtMsg = "";
     // return;
   }   
   
   // Case 9 - pluck2
   if(txtMsg == "pluck2") {
     // Set direction pin
     pluckString(2);
     txtMsg = "";
     // return;
   }   
   
   // Case 10 - pluck3
   if(txtMsg == "pluck3") {
     // Set direction pin
     pluckString(3);
     txtMsg = "";
     // return;
   }      
   
   // Case 11 - pluck4
   if(txtMsg == "pluck4") {
     // Set direction pin
     pluckString(4);
     txtMsg = "";
     // return;
   }   
   
     // Case 12 - pluck5
   if(txtMsg == "pluck5") {
     // Set direction pin
     pluckString(5);
     txtMsg = "";
     // return;
   }   
   
    // Case 13 - pluck6
   if(txtMsg == "pluck6") {
     // Set direction pin
     pluckString(6);
     txtMsg = "";
     // return;
   }   
   
   //pluckString
   
   // Case list - list all functions
   
   // Case else - no function found
   
    txtMsg = ""; 
    

}

void movx(int iDir, int iSteps, int iDelay) {
  if(SERIAL_DEBUG) {
    Serial.print("Echoing back message: *");
    Serial.print(txtMsg);
    Serial.println("*");
  } 
  
  digitalWrite(iXDirPin, iDir); 
  
  for(int i = 0; i < iSteps; i++) {
    digitalWrite(iXStepPin, LOW);
    delay(iDelay);
    digitalWrite(iXStepPin, HIGH);
    if(bEnd() && bSafe) {
      break; 
    }
  }
}

void movy(int iDir, int iSteps, int iDelay) {
  if(SERIAL_DEBUG) {
    Serial.print("Echoing back message: *");
    Serial.print(txtMsg);
    Serial.println("*");
  }    
   
  digitalWrite(iYDirPin, iDir);

  for(int i = 0; i < iSteps; i++) {
    digitalWrite(iYStepPin, LOW);
    delay(iDelay);
    digitalWrite(iYStepPin, HIGH);
    if(bEnd() && bSafe) {
      break; 
    }
  }
}

bool bEnd() {
  if(analogRead(0) > iThreshold) {
   return true;
  }
  return false; 
}

void homeX() {
  while(!(bEnd())) {
    movx(iBwd, 1, 1);  
  }
  bSafe = false;
  movx(iFwd, iXInitPos, 1);
  iXPos = iXInitPos;
  bSafe = true;  
}

void homeY() {
  while(!(bEnd())) {
    movy(iBwd, 1, 1);  
  } 
  bSafe = false;
  movy(iFwd, iYInitPos , 1);
  iYPos = iYInitPos; 
  iYRelPos = 0;
  bSafe = true;  
}

void homeXY() {
  homeY();
  homeX();
}

void pluckString(int iIndex) {
   // iIndex
   // 1-E, 2-A, 3-D, 4-G, 5-B, 6-E
   
   // Safety net
   if(iIndex > 6) {
     return;
   }
   
   int iMove;
   
   // Downwards movement
   if(iYRelPos < (iOneStringStep * iIndex)) {
      iMove = (iOneStringStep * iIndex) - iYRelPos;
      movy(iFwd, iMove, 1);
      iYRelPos = iYRelPos + iMove;
      if(SERIAL_DEBUG) {
        Serial.print("Current relative position = ");
        Serial.println(iYRelPos);
      }
      return;     
   }
   
   // Upwards movement
   if(iYRelPos >= (iOneStringStep * iIndex)) {
      iMove = iYRelPos - (iOneStringStep * (iIndex - 1));
      movy(iBwd, iMove, 1);
      iYRelPos = iYRelPos - iMove;
      if(SERIAL_DEBUG) {
        Serial.print("Current relative position = ");
        Serial.println(iYRelPos);
      }
      return;     
   }   
}



