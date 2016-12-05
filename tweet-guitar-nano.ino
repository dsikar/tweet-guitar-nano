
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
int iXRelPos;

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
     movx(iFwd, 1, 6);
     txtMsg = "";
    return;
   }
   // Case 2 - bwdx
   if(txtMsg == "bwdx") {
     // Set direction pin
    movx(iBwd, 1, 6);
    txtMsg = "";
    return;
   }   
   // Case 3 - fwdy
   if(txtMsg == "fwdy") {
     // Set direction pin
     movy(iFwd, 1, 6);
     txtMsg = "";
     return;
   }   
   // Case 4 - bwdy
   if(txtMsg == "bwdy") {
     // Set direction pin
     movy(iBwd, 1, 6);
     txtMsg = "";
     return;
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
 
     // Case 14 - slide1
   if(txtMsg == "slide1") {
     // Set direction pin
     slideFret(1);
     txtMsg = "";
     // return;
   }    
 
      // Case 15 - slide2
   if(txtMsg == "slide2") {
     // Set direction pin
     slideFret(2);
     txtMsg = "";
     // return;
   }  
 
   // Case 16 - slide3
   if(txtMsg == "slide3") {
     // Set direction pin
     slideFret(3);
     txtMsg = "";
     // return;
   }  
   
   // Case 17 - slide4
   if(txtMsg == "slide4") {
     // Set direction pin
     slideFret(4);
     txtMsg = "";
     // return;
   }
 
    // Case 18 - slide5
   if(txtMsg == "slide5") {
     // Set direction pin
     slideFret(5);
     txtMsg = "";
     // return;
   }    

    // Case 18 - slide6
   if(txtMsg == "slide6") {
     // Set direction pin
     slideFret(6);
     txtMsg = "";
     // return;
   }

    // Case 18 - slide7
   if(txtMsg == "slide7") {
     // Set direction pin
     slideFret(7);
     txtMsg = "";
     // return;
   }

    // Case 18 - slide8
   if(txtMsg == "slide8") {
     // Set direction pin
     slideFret(8);
     txtMsg = "";
     // return;
   }
   
    // Case 18 - slide9
   if(txtMsg == "slide9") {
     // Set direction pin
     slideFret(9);
     txtMsg = "";
     // return;
   }
   
       // Case 18 - slide10
   if(txtMsg == "slide10") {
     // Set direction pin
     slideFret(10);
     txtMsg = "";
     // return;
   }
   
      
   
   // Case 19 - fwdx10
   txtMsg.trim();
   if(txtMsg == "fwdx10") {
     // Set direction pin
     movx(iFwd, 10, 6);
     txtMsg = "";
    return;
   }
   // Case 20 - bwdx10
   if(txtMsg == "bwdx10") {
     // Set direction pin
    movx(iBwd, 10, 6);
    txtMsg = "";
    return;
   }   
   // Case 3 - fwdy10
   if(txtMsg == "fwdy10") {
     // Set direction pin
     movy(iFwd, 10, 6);
     txtMsg = "";
     return;
   }   
   // Case 4 - bwdy10
   if(txtMsg == "bwdy10") {
     // Set direction pin
     movy(iBwd, 10, 6);
     txtMsg = "";
     return;
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
  iXRelPos = 0;
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

int getXPos(int iIndex) {
  // dummy return value
  // if(iIndex == 1
  // return (iIndex) * 50;
  // create lookup table from calibration 
  
  switch (iIndex) {
    case 1:
      return 10;
    case 2:
      return 185;
    case 3:
      return 350;
    case 4:
      return 495;
    case 5:
      return 640;      
    case 6:
      return 780;      
    case 7:
      return 905;      
    case 8:
      return 1030;
    case 9:
      return 1155;
    case 10:
      return 1280;      
    default: 
      // if nothing else matches, do the default
      // default is optional
    break;
  }
  
}

void slideFret(int iIndex) {
   // iIndex
   // 1-F#, 2-G, 3-G#, 4-A, etc
   
      // Safety net
   if(iIndex > 16) {
     return;
   }
   
   int iMove;
   int iMoveXPos = getXPos(iIndex);
   Serial.print("iMoveXPos = ");
   Serial.println(iMoveXPos);
   Serial.print("iXRelPos = ");
   Serial.println(iXRelPos);   
   if(iXRelPos < iMoveXPos) {
     iMove = iMoveXPos - iXRelPos;
     Serial.print("iMove = ");
     Serial.println(iMove);
     movx(iFwd, iMove, 1);
      iXRelPos = iXRelPos + iMove;
      Serial.print("iXRelPos = ");
       Serial.println(iXRelPos); 
      return;
   }
   
   if(iXRelPos > iMoveXPos) {
     iMove = iXRelPos - iMoveXPos;
     movx(iBwd, iMove, 1);
      iXRelPos = iXRelPos - iMove;
      return;
   }
}
