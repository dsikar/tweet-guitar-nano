
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

// End Stop expected threshold AD Conversion
int iThreshold = 130;

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
   // Case list - list all functions
   
   // Case else - no function found
   
   
   /*
    Serial.print("Echoing back message: *");
    Serial.print(txtMsg);
    Serial.println("*");
    txtMsg.trim();
    if(txtMsg == "stuff") {
    Serial.println("Msg == stuff");
    
    }
    */
    txtMsg = ""; 
    

}

void movx(int iDir, int iSteps, int iDelay) {
    Serial.print("Echoing back message: *");
    Serial.print(txtMsg);
    Serial.println("*");
    digitalWrite(iXDirPin, iDir);
   
    for(int i = 0; i < iSteps; i++) {
      digitalWrite(iXStepPin, LOW);
      delay(iDelay);
      digitalWrite(iXStepPin, HIGH);
  }
}

void movy(int iDir, int iSteps, int iDelay) {
    Serial.print("Echoing back message: *");
    Serial.print(txtMsg);
    Serial.println("*");
    digitalWrite(iYDirPin, iDir);
   
    for(int i = 0; i < iSteps; i++) {
      digitalWrite(iYStepPin, LOW);
      delay(iDelay);
      digitalWrite(iYStepPin, HIGH);
  }
}

bool bEnd() {
  if(analogRead(0) > iThreshold) {
   return true;
  }
  return false; 
}

void homeX() {
  while(!bEnd) {
    movx(iBwd, 1, 10);  
  } 
}
