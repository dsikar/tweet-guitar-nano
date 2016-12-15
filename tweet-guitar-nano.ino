/**********************
START GUITAR INIT VALS
**********************/

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

// Exception case flag for homefwdx
bool bSafe;

// End Stop expected threshold AD Conversion
int iThreshold = 130;

// Serial debug. Set to 1 to debug.
#define SERIAL_DEBUG 1

// Current X and Y position markers
int iXPos;
int iYPos;
int iXInitPos = 25;
int iYInitPos = 36;
// Relative origin
int iYRelPos;
int iXRelPos;

// Fret position mapping

// String position mapping
int iOneStringStep = 50;
//int iPluckE = iOneStringStep;
//int iPluckA = iOneStringStep * 2;

/**********************
END GUITAR INIT VALS
**********************/

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

void movx(int iDir, int iSteps, int iDelay) {
  /*
  if(SERIAL_DEBUG) {
    Serial.print("Echoing back message: *");
    Serial.print(txtMsg);
    Serial.println("*");
  } 
  */
  
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
  /*
  if(SERIAL_DEBUG) {
    Serial.print("Echoing back message: *");
    Serial.print(txtMsg);
    Serial.println("*");
  }    
  */
   
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
      if(SERIAL_DEBUG) {
        Serial.print("Total Y move = ");
        Serial.println(iMove);
      }      
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
      return 1130;
    case 10:
      return 1230;      
    case 11:
      return 1320;
    case 12:
      return 1420; 
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


