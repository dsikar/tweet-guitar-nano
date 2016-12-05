
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
     movx(iFwd, 200, 6);
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
   
   // Case 8 - PluckE
   if(txtMsg == "PluckE") {
     // Set direction pin
     PluckE();
     txtMsg = "";
     // return;
   }
   
   // Case 9 - moveOneStringFWD
   if(txtMsg == "moveOneStringFWD") {
     // Set direction pin
     moveOneStringFWD();
     txtMsg = "";
     // return;
   }
   
   // Case 10 - moveOneStringBWD
   if(txtMsg == "moveOneStringBWD") {
     // Set direction pin
     moveOneStringBWD();
     txtMsg = "";
     // return;
   }   
   
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

void PluckEOld() {
  // check position and compute distance
  int iMove;
  if(iYPos > iYInitPos) {
    iMove = iYPos - iPluckE;
    movy(iBwd, iPluckE, 1);
    iYPos = iYInitPos;
    return;
  }
  // Otherwise, we are in the init position, just pluck
  // decide if going fwd or bwd
   movy(iFwd, iPluckE, 1);
   iYPos = iYInitPos + iPluckE;
}

void PluckEOld2() {
  // we are at the top
  if(iYPos == iYInitPos) {
    movy(iFwd, iPluckE, 1);
    iYPos = iYInitPos + iPluckE;    
    return;
  } 
  // we are above A
  if(iYPos == iYInitPos + iPluckE) {
    movy(iBwd, iPluckE, 1);
    iYPos = iYInitPos;
    return;    
  }
  // we are further down
  if(iYPos > iYInitPos + iPluckE) {
    int iMove = iYPos - iYInitPos;
    movy(iBwd, iPluckE, 1);
    iYPos = iYInitPos;
    return;
  }
}

void PluckE() {
 // if we are at top
 // move forward one string
 if(iYPos == iYInitPos) {
    movy(iFwd, iOneStringStep, 1);
    iYPos = iYPos + iOneStringStep;
    Serial.print("Current absolute position = ");
    Serial.println(iYPos);
   return;   
 } 
 // anything else, move back to iYinitPos
 if(iYPos > iYInitPos) {
    int iMove = iYPos - iYInitPos;
    movy(iBwd, iMove, 1);
    iYPos = iYInitPos;
    return;   
 }
}

void pluckString(int iIndex) {
   // iIndex
   // 1-E, 2-A, 3-D, 4-G, 5-B, 6-E
   int iMove;
   if(iYRelPos < (iOneStep * iIndex)) {
      iMove = (iOneStep * iIndex) - iYRelPos;
      movy(iFwd, iMove, 1);
      iYRelPos =+ 
   }
}


void Pluck(int iPluckIndex) {
 // if we are at top
 // move forward one string
 if(iYPos == iYInitPos) {
    movy(iFwd, iOneStringStep, 1);
    iYPos = iYPos + iOneStringStep;
    Serial.print("Current absolute position = ");
    Serial.println(iYPos);
   return;   
 } 
 // anything else, move back to iYinitPos
 if(iYPos > iYInitPos) {
    int iMove = iYPos - iYInitPos;
    movy(iBwd, iMove, 1);
    iYPos = iYInitPos;
    return;   
 }
}

void moveOneStringFWD() {
    movy(iFwd, iOneStringStep, 1);
    iYPos = iYPos + iOneStringStep;
    Serial.print("Current absolute position = ");
    Serial.println(iYPos);    
}

void moveOneStringBWD() {
    movy(iBwd, iOneStringStep, 1);
    iYPos = iYPos - iOneStringStep;
    Serial.print("Current absolute position = ");
    Serial.println(iYPos);    
}

void PluckA() {
  // check position and compute distance
  if(iYPos < (iPluckA + iYInitPos)) {
    int iMove = iYPos - iPluckA;
    movy(iBwd, iPluckA, 1);
    iYPos = iYInitPos;
    return;
  }
  // if
  // Otherwise, we are in the init position, just pluck
  // decide if going fwd or bwd
   
   movy(iFwd, iPluckE, 1);
   iYPos = iYInitPos + iPluckE;
}

/*
void movAbsPos(int iPos) {
  if(iPos 
}
*/
