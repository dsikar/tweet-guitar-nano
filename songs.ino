void twinkle(int iDelay) {
 homeXY();
 
// POSITION
 pluckString(3);
 delay(iDelay*2);
 
 // open 3rd string
 pluckString(3);
 delay(iDelay/2);
 pluckString(3);
 // delay(iDelay/2);
 
 //4th string 2nd fret

 slideFret(7);
 pluckString(3);
 delay(iDelay); 
 pluckString(3);
delay(iDelay/2);

 //4th string 4nd fret
 slideFret(9);
 pluckString(3);
 delay(iDelay); 
 pluckString(3);
delay(iDelay/2);

 //4th string OPEN
 slideFret(7);
 pluckString(3);
 //slideFret(7);
 delay(iDelay * 2); 
 pluckString(3);
 
 //3th string 4nd fret
 slideFret(12);
 pluckString(2);
 delay(iDelay); 
 pluckString(2);
delay(iDelay);

 //3th string 4nd fret
 slideFret(11);
 pluckString(2);
 delay(iDelay); 
 pluckString(2);
delay(iDelay);

 //3th string 4nd fret
 slideFret(9);
 pluckString(2);
 delay(iDelay); 
 pluckString(2);
delay(iDelay);

 //3rd string OPEN
 slideFret(7);
 pluckString(2);

 delay(iDelay * 2); 
 // homeY();
}

void strum() {
 
 homeXY();
 for(int i = 0; i < 5; i++) {
  pluckString(6);
  pluckString(1);
   
 }
 
 slideFret(5);
 for(int i = 0; i < 5; i++) {
  pluckString(6);
  pluckString(1);
   
 }
 
 slideFret(7);
 
  for(int i = 0; i < 5; i++) {
  pluckString(6);
  pluckString(1);
   
 }
 
 slideFret(1);
 
  for(int i = 0; i < 5; i++) {
  pluckString(6);
  pluckString(1);
   
 }
 
}

void shock() {
for(int i = 0; i < 4; i++) {
  pluckString(2);
slideFret(7);
pluckString(1);
slideFret(6);
}
}

void tomas(){
  homeXY();
  slideFret(7);
  pluckString(5);
  pluckString(3);
  slideFret(3);
}
void alarm(){
  pluckString(6);
  slideFret(2);
  pluckString(1);
  slideFret(1);
   pluckString(6);
  slideFret(2);
  pluckString(1);
  slideFret(1);
}
