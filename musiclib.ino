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
 // Case 3 - alarm
   if(txtMsg == "alarm") {
     // Set direction pin
     alarm();
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
   
    // Case 10 - tomas
   if(txtMsg == "tomas") {
     // Set direction pin
     tomas();
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

   if(txtMsg == "strum") {
     // Set direction pin
     strum();
     txtMsg = "";
     // return;
   }   
   
   // Case 4 - twinkle
   if(txtMsg == "twinkle") {
     // Set direction pin
     twinkle(250);
     txtMsg = "";
     return;
   }

   if(txtMsg == "shock") {
     // Set direction pin
     shock();
     txtMsg = "";
     return;
   }
   
   if(txtMsg == "p") {
     // Set direction pin
     parse("1*1|3\n2*1|1\n3*1|2\n1*1|3\n2*1|1\n3*1|2\n");
     txtMsg = "";
     return;
   }   
   
      //pluckString
   
   // Case list - list all functions
   
   // Case else - no function found
   
    txtMsg = ""; 
    
}

/**************************
* Parse song string

Argument strSong

Expected format "1*2|3\n3|1\n1|2\n1|3\n3|1\n1|2\n"
**************************/
void parse(String strSong) {

  int iLen = strSong.length();
  String sLineEnd = "\n";
  
  for(int i = 0; i < iLen;) {
    int iPos = strSong.indexOf(sLineEnd, i);
    if(iPos < 0) {break;} // last character expected to be newline, if not, stop
    String sCom = strSong.substring(i, iPos);
    play(sCom);
    //   break;
    i = iPos + 1;    
  }
}

/**************************
* Play note

Argument note

Expected format "1|3"

Parse note and duration
**************************/
void play(String note) {
  String strDelim = "|"; // TODO move to config file
  int iPos = note.indexOf(strDelim);
  String strNote = note.substring(0, iPos);
  lookup(strNote);
  String strPause =  note.substring(iPos+1);
  wait(strPause);
}

/**************************
* Lookup note

Argument note

Expected format "1"
e.g. play note 1 in lookup table
**************************/

void lookup(String noteXY) {
   // parse
  String strDelim = "*"; // TODO move to config file
  int iPos = noteXY.indexOf(strDelim);
  String strX = noteXY.substring(0, iPos);
  int iX = strX.toInt();
  String strY =  noteXY.substring(iPos+1);
  int iY = strY.toInt();  
  // compute_pause(iX, iY);
  pluckString(iY);
  slideFret(iX);
}

/**************************
* Pause to make up note duration

Argument rest

Expected format "3"
e.g. wait for the duration of 3 quavers before moving onto next note
**************************/
void wait(String rest) {
   //int iRest = rest.toInt(); 
   //vibrato(iRest);
   Serial.println(rest);
}

void vibrato(int iRest) {
  // forward 1.5mm, backward 1.5mm to make up for note duration
  
}
