//We always have to include the library
#include "LedControl.h"
// Déclaration des deux matrices de LED
LedControl M1=LedControl(13,12,11,1);// Matrix 1 :  pin 13 is connected to the DataIn  pin 11 is connected to the CLK  pin 12 is connected to LOAD 
LedControl M2=LedControl(10,8,9,1);// Matrix 1 :  pin 10 is connected to the DataIn  pin 9 is connected to the CLK  pin 8 is connected to LOAD 

/* we always wait a bit between updates of the display */
unsigned long delaytime=500;

void setup() {
  // put your setup code here, to run once:
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  M1.shutdown(0,false);
  M2.shutdown(0,false);
  /* Set the brightness to a medium values */
  M1.setIntensity(0,2);
  M2.setIntensity(0,2);
  /* and clear the display */
  M1.clearDisplay(0);
  M2.clearDisplay(0);
}

void loop() {
  // put your main code here, to run repeatedly:



// Essai de Remplissage de M1 

// Ligne 1
M1.setLed(0,0,7,true); 
delay(delaytime);


// Ligne 2
M1.setLed(0,1,7,true);
delay(delaytime);

M1.setLed(0,0,6,true);
delay(delaytime);

//Ligne 3
M1.setLed(0,1,6,true);
delay(delaytime);

M1.setLed(0,0,5,true);
delay(delaytime);

M1.setLed(0,2,7,true);
delay(delaytime);

//Ligne 4

M1.setLed(0,1,5,true);
delay(delaytime);

M1.setLed(0,2,6,true);
delay(delaytime);

M1.setLed(0,3,7,true);
delay(delaytime);

M1.setLed(0,0,4,true);
delay(delaytime);

M1.clearDisplay(0);

}

void DiagDescenteM2(){
for(int i=0;i<8;i++){ // Boucle qui décrit la diagonale descendante de M2
M2.setLed(0,i,7-i,true);
delay(delaytime);
M2.setLed(0,i,7-i,false);
}
}

void DiagDescenteM1(){

for(int i=0;i<8;i++){ // Boucle qui décrit la diagonale descendante de M1
M1.setLed(0,7-i,i,true);
delay(delaytime);
M1.setLed(0,7-i,i,false); 
}
}

