//We always have to include the library
#include "LedControl.h"
// Déclaration des deux matrices de LED
LedControl Led_Display=LedControl(13,12,11,2);// Matrix 1 :  pin 13 is connected to the DataIn  pin 11 is connected to the CLK  pin 12 is connected to LOAD 


/* we always wait a bit between updates of the display */
unsigned long delaytime=50;
int adresse_matrice_haut=1;
int adresse_matrice_bas=0;

void setup() {
  // put your setup code here, to run once:
  
  
   for(int address=0;address<2;address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    Led_Display.shutdown(address,false);
    /* Set the brightness to a medium values */
    Led_Display.setIntensity(address,0);
    /* and clear the display */
    Led_Display.clearDisplay(address);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

  Remplir_matrice(adresse_matrice_haut);
  
for(int i=0;i<65;i++)
{
  Vider_matrice(i,adresse_matrice_haut);
  Remplir_matrice(i,adresse_matrice_bas);
  delay(200);
}
delay(1000);
for(int i=0;i<65;i++)
{
  Vider_matrice(i,adresse_matrice_bas);
  Remplir_matrice(i,adresse_matrice_haut);
  delay(200);
}

Led_Display.clearDisplay(0);
Led_Display.clearDisplay(1);
}

void Remplir_matrice(int adresse){
for(int i=0;i<65;i++){
  for(int j=0;j<8;j++){
    Led_Display.setLed(adresse,i,j,true);
  delay(5);
}
}
}



void Descente_limitee_diag_matrice(int limite,int adresse){
for(int i=0;i<limite;i++){ // Boucle qui décrit la diagonale descendante de M1
Led_Display.setLed(adresse,7-i,i,true);
delay(delaytime);
Led_Display.setLed(adresse,7-i,i,false); 
}
}

void Remplir_matrice(int etat_de_remplissage,int adresse){

// la matrice fait 64 Leds, on a une animation pour chacune de ces 64 Leds, la variable etat de remplissage permet de choisir quelle animation on veut.

switch (etat_de_remplissage) {
  case 1: 
    Descente_limitee_diag_matrice(8,adresse);

    Led_Display.setLed(adresse,0,7,true);            //1
    delay(delaytime);
  break;

 case 2:
Descente_limitee_diag_matrice(7,adresse);

// Ligne 2
Led_Display.setLed(adresse,1,7,true);            //2
delay(delaytime);
  break;

 case 3:
    Descente_limitee_diag_matrice(7,adresse);
      
    Led_Display.setLed(adresse,0,6,true);            //3
    delay(delaytime);
break;
 
 case 4:   
    Descente_limitee_diag_matrice(6,adresse);
    
    //Ligne 3
    Led_Display.setLed(adresse,1,6,true);            //4
    delay(delaytime);
break;

 case 5:
    Descente_limitee_diag_matrice(6,adresse);
    
    //Anim 5
    Led_Display.setLed(adresse,1,5,true); 
    delay(delaytime);
    Led_Display.setLed(adresse,1,5,false);
    
    Led_Display.setLed(adresse,0,5,true);            //5
    delay(delaytime);

break;

 case 6:
    Descente_limitee_diag_matrice(6,adresse);
    
    //Anim 6 
    Led_Display.setLed(adresse,2,6,true); 
    delay(delaytime);
    Led_Display.setLed(adresse,2,6,false);
    
    Led_Display.setLed(adresse,2,7,true);           //6
delay(delaytime);
break;

 case 7:
    //Ligne 4
    
    Descente_limitee_diag_matrice(6,adresse);
    
    Led_Display.setLed(adresse,1,5,true);             //7
    delay(delaytime);
break;

 case 8:
    Descente_limitee_diag_matrice(6,adresse);
    
    Led_Display.setLed(adresse,2,6,true);              //8
    delay(delaytime);
break;

 case 9:
    Descente_limitee_diag_matrice(5,adresse);
    
    Led_Display.setLed(adresse,2,5,true);              //9
    delay(delaytime);
break;

 case 10:
    Descente_limitee_diag_matrice(5,adresse);
    
    //Anim 10
    
    Led_Display.setLed(adresse,3,5,true); 
    delay(delaytime);
    Led_Display.setLed(adresse,3,5,false);
    
    Led_Display.setLed(adresse,3,6,true); 
    delay(delaytime);
    Led_Display.setLed(adresse,3,6,false);
    
    Led_Display.setLed(adresse,3,7,true);                //10
    delay(delaytime);
break; 

case 11:
Descente_limitee_diag_matrice(5,adresse);

for(int i=0;i<3;i++){ // Anim 11
Led_Display.setLed(adresse,2-i,4,true);
delay(delaytime);
Led_Display.setLed(adresse,2-i,4,false);
}

Led_Display.setLed(adresse,0,4,true);              //11
delay(delaytime);
break; 

case 12:
    Descente_limitee_diag_matrice(5,adresse);
    
    for(int i=0;i<2;i++){ // Anim 11
    Led_Display.setLed(adresse,2-i,4,true);
    delay(delaytime);
    Led_Display.setLed(adresse,2-i,4,false);
    }
    
    Led_Display.setLed(adresse,1,4,true);               //12
    delay(delaytime);
break;

case 13: 
    Descente_limitee_diag_matrice(5,adresse);
    
    for(int i=0;i<2;i++){ // Anim 13
    Led_Display.setLed(adresse,3,5+i,true);
    delay(delaytime);
    Led_Display.setLed(adresse,3,5+i,false);
    }
    
    Led_Display.setLed(adresse,3,6,true);          //13
    delay(delaytime);
break;


case 14 :
    Descente_limitee_diag_matrice(5,adresse);
    
    Led_Display.setLed(adresse,3,5,true);          //14
    delay(delaytime);
break;

case 15 :
Descente_limitee_diag_matrice(5,adresse);

Led_Display.setLed(adresse,2,4,true);            //15
delay(delaytime);
break;

case 16 :
Descente_limitee_diag_matrice(4,adresse);

Led_Display.setLed(adresse,3,4,true);            //16
delay(delaytime);
break;


case 17 :
    Descente_limitee_diag_matrice(4,adresse);
    
    for(int i=0;i<4;i++){ // Anim 17
    Led_Display.setLed(adresse,3-i,3,true);
    delay(delaytime);
    Led_Display.setLed(adresse,3-i,3,false);
    }
    
    Led_Display.setLed(adresse,0,3,true);            //17
    delay(delaytime);
break;


case 18 :
Descente_limitee_diag_matrice(4,adresse);

for(int i=0;i<3;i++){ // Anim 18
      Led_Display.setLed(adresse,4,4+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,4,4+i,false);
      }
      
      Led_Display.setLed(adresse,4,7,true);            //18
      delay(delaytime);
break;


case 19 :
    Descente_limitee_diag_matrice(3,adresse);

for(int i=0;i<3;i++){ // Anim 18
      Led_Display.setLed(adresse,4-i,3,true);
      delay(delaytime);
      Led_Display.setLed(adresse,4-i,3,false);
      }
    
    Led_Display.setLed(adresse,1,3,true);        //19
    delay(delaytime);
break;

case 20 :
      
      Descente_limitee_diag_matrice(3,adresse);
      
      for(int i=0;i<3;i++){ // Anim 18
      Led_Display.setLed(adresse,4,4+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,4,4+i,false);
      }
      
      
      Led_Display.setLed(adresse,4,6,true);     //20
      delay(delaytime);
break;

case 21 :
      Descente_limitee_diag_matrice(3,adresse);
      
      for(int i=0;i<2;i++){ // Anim 18
      Led_Display.setLed(adresse,4,4+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,4,4+i,false);
      }
      Led_Display.setLed(adresse,5,6,true);
      delay(delaytime);
      Led_Display.setLed(adresse,5,6,false);
      
      Led_Display.setLed(adresse,5,7,true);     //21
      delay(delaytime);      
      
break;

case 22 :
      Descente_limitee_diag_matrice(3,adresse);
      
      // Anim 22
      Led_Display.setLed(adresse,3,3,true);
      delay(delaytime);
      Led_Display.setLed(adresse,3,3,false);
      
      Led_Display.setLed(adresse,2,3,true);          //22
      delay(delaytime);         
break;

case 23 :
      Descente_limitee_diag_matrice(3,adresse);
      
      // Anim 22
      Led_Display.setLed(adresse,3,3,true);
      delay(delaytime);
      Led_Display.setLed(adresse,3,3,false);

      for(int i=0;i<3;i++){ // Anim 18
      Led_Display.setLed(adresse,3-i,2,true);
      delay(delaytime);
      Led_Display.setLed(adresse,3-i,2,false);
      }
      
      Led_Display.setLed(adresse,0,2,true);          //23 
      delay(delaytime);  
break;

case 24 :
      Descente_limitee_diag_matrice(3,adresse);
      delay(delaytime);
      // Anim 22
      Led_Display.setLed(adresse,3,3,true);
     //23
      delay(delaytime);                             //24
      
break;

case 25 :
      Descente_limitee_diag_matrice(3,adresse);
      
      // Anim 25
      Led_Display.setLed(adresse,4,4,true);
      delay(delaytime);
      Led_Display.setLed(adresse,4,4,false);

      Led_Display.setLed(adresse,4,5,true);          //25
      delay(delaytime);  
break;      
      
case 26 :
      Descente_limitee_diag_matrice(3,adresse);
      
      // Anim 25
      Led_Display.setLed(adresse,4,4,true);
      delay(delaytime);            
break;

case 27 :
      Descente_limitee_diag_matrice(2,adresse);
      Led_Display.setLed(adresse,4,3,true);
      delay(delaytime); 
break;

case 28 :
      Descente_limitee_diag_matrice(2,adresse);
      
      for(int i=0;i<4;i++){ // Anim 18
      Led_Display.setLed(adresse,5,3+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,5,3+i,false);
      }
      
      Led_Display.setLed(adresse,5,6,true);     //28
      delay(delaytime);        
      
break;

case 29 :
      Descente_limitee_diag_matrice(2,adresse);
      
      for(int i=0;i<3;i++){ // Anim 18
      Led_Display.setLed(adresse,5,3+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,5,3+i,false);
      }
      
      Led_Display.setLed(adresse,5,5,true);     //29
      delay(delaytime);        
break;

case 30 :
      Descente_limitee_diag_matrice(2,adresse);
      
      for(int i=0;i<2;i++){ // Anim 30
      Led_Display.setLed(adresse,4-i,2,true);
      delay(delaytime);
      Led_Display.setLed(adresse,4-i,2,false);
      }
      
      Led_Display.setLed(adresse,1,2,true);     //30
      delay(delaytime);           
break;

case 31 :
      Descente_limitee_diag_matrice(2,adresse);
      
      for(int i=0;i<2;i++){ // Anim 30
      Led_Display.setLed(adresse,4-i,2,true);
      delay(delaytime);
      Led_Display.setLed(adresse,4-i,2,false);
      }
      for(int i=0;i<2;i++){ // Anim 30
      Led_Display.setLed(adresse,2-i,1,true);
      delay(delaytime);
      Led_Display.setLed(adresse,2-i,1,false);
      }
      
      Led_Display.setLed(adresse,0,1,true);     //31
      delay(delaytime);         
      
break;

case 32 :
      Descente_limitee_diag_matrice(2,adresse);
      
      for(int i=0;i<2;i++){ // Anim 30
      Led_Display.setLed(adresse,4-i,2,true);
      delay(delaytime);
      Led_Display.setLed(adresse,4-i,2,false);
      }
      
      Led_Display.setLed(adresse,2,2,true);     //32
      delay(delaytime);       
      
break;

case 33 :
      Descente_limitee_diag_matrice(2,adresse);
      
      // Anim 33
      Led_Display.setLed(adresse,5,3,true);
      delay(delaytime);
      Led_Display.setLed(adresse,5,3,false);
 
      Led_Display.setLed(adresse,5,4,true);     //33
      delay(delaytime);         
      
break;

case 34 :
      Descente_limitee_diag_matrice(2,adresse);
      
      // Anim 33
      Led_Display.setLed(adresse,5,3,true);
      delay(delaytime);
      Led_Display.setLed(adresse,5,3,false);
      
      for(int i=0;i<3;i++){ // Anim 30
      Led_Display.setLed(adresse,6,4+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,6,4+i,false);
      }
      Led_Display.setLed(adresse,6,7,true);     //33
      delay(delaytime);         
      
break;

case 35 :
      Descente_limitee_diag_matrice(2,adresse);
      
      // Anim 33
      Led_Display.setLed(adresse,5,3,true);
      delay(delaytime);
      Led_Display.setLed(adresse,5,3,false);
      
      for(int i=0;i<2;i++){ // Anim 30
      Led_Display.setLed(adresse,6,4+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,6,4+i,false);
      }
      Led_Display.setLed(adresse,6,6,true);     //33
      delay(delaytime);           
      
break;

case 36 :
      Descente_limitee_diag_matrice(2,adresse);
      
      for(int i=0;i<1;i++){ // Anim 30
      Led_Display.setLed(adresse,4-i,2,true);
      delay(delaytime);
      Led_Display.setLed(adresse,4-i,2,false);
      }
      
      Led_Display.setLed(adresse,3,2,true);     //32
      delay(delaytime);      
      
break;

case 37 :
      Descente_limitee_diag_matrice(2,adresse);
           
      Led_Display.setLed(adresse,5,3,true);     //32
      delay(delaytime);        
      
break;

case 38 :
      Descente_limitee_diag_matrice(2,adresse);
           
      Led_Display.setLed(adresse,4,2,true);     //32
      delay(delaytime);         
      
break;

case 39 :
      Descente_limitee_diag_matrice(1,adresse);
           
      Led_Display.setLed(adresse,5,2,true);     //32
      delay(delaytime);         
        
      
break;

case 40 :
      Descente_limitee_diag_matrice(1,adresse);
      
      for(int i=0;i<4;i++){ // Anim 30
      Led_Display.setLed(adresse,6,2+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,6,2+i,false);
      }
      
      Led_Display.setLed(adresse,6,5,true);     //33
      delay(delaytime);       
      
break;

case 41 :
      Descente_limitee_diag_matrice(2,adresse);
      
      for(int i=0;i<4;i++){ // Anim 30
      Led_Display.setLed(adresse,5-i,1,true);
      delay(delaytime);
      Led_Display.setLed(adresse,5-i,1,false);
      }
      
      Led_Display.setLed(adresse,1,1,true);     //41
      delay(delaytime);       
      
break;

case 42 :
      Descente_limitee_diag_matrice(1,adresse);
      
      for(int i=0;i<3;i++){ // Anim 30
      Led_Display.setLed(adresse,5-i,1,true);
      delay(delaytime);
      Led_Display.setLed(adresse,5-i,1,false);
      }
      
      Led_Display.setLed(adresse,2,1,true);     //33
      delay(delaytime);        
      
break;

case 43 :
      Descente_limitee_diag_matrice(1,adresse);
      
      for(int i=0;i<3;i++){ // Anim 30
      Led_Display.setLed(adresse,5-i,1,true);
      delay(delaytime);
      Led_Display.setLed(adresse,5-i,1,false);
      }

      for(int i=0;i<3;i++){ // Anim 30
      Led_Display.setLed(adresse,3-i,0,true);
      delay(delaytime);
      Led_Display.setLed(adresse,3-i,0,false);
      }
      
      Led_Display.setLed(adresse,0,0,true);     //33
      delay(delaytime);       
      
break;

case 44 :
      Descente_limitee_diag_matrice(1,adresse);
      
      for(int i=0;i<2;i++){ // Anim 30
      Led_Display.setLed(adresse,5-i,1,true);
      delay(delaytime);
      Led_Display.setLed(adresse,5-i,1,false);
      }
      
      Led_Display.setLed(adresse,3,1,true);     //33
      delay(delaytime);      
      
break;

case 45 :
      Descente_limitee_diag_matrice(1,adresse);
      
      for(int i=0;i<3;i++){ // Anim 30
      Led_Display.setLed(adresse,6,2+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,6,2+i,false);
      }
      
      Led_Display.setLed(adresse,6,4,true);     //33
      delay(delaytime);        
      
break;

case 46 :
      Descente_limitee_diag_matrice(1,adresse);

      for(int i=0;i<2;i++){ // Anim 30
      Led_Display.setLed(adresse,6,2+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,6,2+i,false);
      }

      for(int i=0;i<4;i++){ // Anim 30
      Led_Display.setLed(adresse,7,3+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,7,3+i,false);
      }
      
      Led_Display.setLed(adresse,7,7,true);     //33
      delay(delaytime);        
      
break;

case 47 :
      Descente_limitee_diag_matrice(1,adresse);
      
      for(int i=0;i<1;i++){ // Anim 30
      Led_Display.setLed(adresse,5-i,1,true);
      delay(delaytime);
      Led_Display.setLed(adresse,5-i,1,false);
      }
      
      Led_Display.setLed(adresse,4,1,true);     //33
      delay(delaytime);      
            
      
break;

case 48 :
      Descente_limitee_diag_matrice(1,adresse);

      for(int i=0;i<2;i++){ // Anim 30
      Led_Display.setLed(adresse,6,2+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,6,2+i,false);
      }

      for(int i=0;i<4;i++){ // Anim 30
      Led_Display.setLed(adresse,7,3+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,7,3+i,false);
      }
      
      Led_Display.setLed(adresse,7,6,true);     //33
      delay(delaytime);      
      
break;

case 49 :
      Descente_limitee_diag_matrice(1,adresse);
           
      Led_Display.setLed(adresse,5,1,true);     //32
      delay(delaytime);         
              
break;

case 50 :
      Descente_limitee_diag_matrice(1,adresse);

      Led_Display.setLed(adresse,6,2,true);
      delay(delaytime);
      Led_Display.setLed(adresse,6,2,false);
           
      Led_Display.setLed(adresse,6,3,true);     //32
      delay(delaytime);         
                    
      
break;

case 51 :
      Descente_limitee_diag_matrice(1,adresse);

      Led_Display.setLed(adresse,6,2,true);
      delay(delaytime);      
      
break;

case 52 :
      Led_Display.setLed(adresse,7,0,true);
      delay(delaytime);
      Led_Display.setLed(adresse,7,0,false);      

      Led_Display.setLed(adresse,6,1,true);
break;

case 53 :
      for(int i=0;i<4;i++){ // Anim 30
      Led_Display.setLed(adresse,7,0+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,7,0+i,false);
      }

      Led_Display.setLed(adresse,7,5,true);       //53
break;

case 54 :
for(int i=0;i<6;i++){ // Anim 30
      Led_Display.setLed(adresse,7-i,0,true);
      delay(delaytime);
      Led_Display.setLed(adresse,7-i,0,false);
      }      

      Led_Display.setLed(adresse,1,0,true);
break;

case 55 :
      for(int i=0;i<3;i++){ // Anim 30
      Led_Display.setLed(adresse,7,0+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,7,0+i,false);
      }

      Led_Display.setLed(adresse,7,4,true);      
      
break;

case 56 :
for(int i=0;i<5;i++){ // Anim 30
      Led_Display.setLed(adresse,7-i,0,true);
      delay(delaytime);
      Led_Display.setLed(adresse,7-i,0,false);
      }      

      Led_Display.setLed(adresse,2,0,true);      
      
break;

case 57 :
      for(int i=0;i<4;i++){ // Anim 30
      Led_Display.setLed(adresse,7-i,0,true);
      delay(delaytime);
      Led_Display.setLed(adresse,7-i,0,false);
      }      

      Led_Display.setLed(adresse,3,0,true);      
       
      
break;

case 58 :
      for(int i=0;i<3;i++){ // Anim 30
      Led_Display.setLed(adresse,7,0+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,7,0+i,false);
      }

      Led_Display.setLed(adresse,7,3,true);     
      
break;

case 59 :
      for(int i=0;i<2;i++){ // Anim 30
      Led_Display.setLed(adresse,7,0+i,true);
      delay(delaytime);
      Led_Display.setLed(adresse,7,0+i,false);
      }
      
      Led_Display.setLed(adresse,7,2,true);      
      
break;

case 60 :
      for(int i=0;i<3;i++){ // Anim 30
      Led_Display.setLed(adresse,7-i,0,true);
      delay(delaytime);
      Led_Display.setLed(adresse,7-i,0,false);
      }      

      Led_Display.setLed(adresse,4,0,true);       
      
break;

case 61 :
      for(int i=0;i<2;i++){ // Anim 30
      Led_Display.setLed(adresse,7-i,0,true);
      delay(delaytime);
      Led_Display.setLed(adresse,7-i,0,false);
      }      

      Led_Display.setLed(adresse,5,0,true);      
      
break;

case 62 :
    Led_Display.setLed(adresse,7,0,true); 
    delay(delaytime);
    Led_Display.setLed(adresse,7,0,false);

    Led_Display.setLed(adresse,7,1,true);            //1
    delay(delaytime);      
      
break;

case 63 :
    Led_Display.setLed(adresse,7,0,true); 
    delay(delaytime);
    Led_Display.setLed(adresse,7,0,false);

    Led_Display.setLed(adresse,6,0,true);            //1
    delay(delaytime);      
      
break;

case 64 :
    Led_Display.setLed(adresse,7,0,true);            //64
    delay(delaytime);      
      
break;
}
}

void Vider_matrice(int etat_de_remplissage, int adresse){

switch (etat_de_remplissage) {
  case 1: 
    Led_Display.setLed(adresse,0,7,false);
  break;

  case 2: 
    Led_Display.setLed(adresse,1,7,false);
  break;
 
  case 3: 
    Led_Display.setLed(adresse,0,6,false);
  break;

  case 4: 
    Led_Display.setLed(adresse,1,6,false);
  break;

  case 5: 
    Led_Display.setLed(adresse,2,7,false);
  break;

  case 6: 
    Led_Display.setLed(adresse,0,5,false);
  break;
  
  case 7: 
    Led_Display.setLed(adresse,1,5,false);
  break;

  case 8: 
    Led_Display.setLed(adresse,2,6,false);
  break;

  case 9: 
    Led_Display.setLed(adresse,0,4,false);
    
  break;

  case 10: 
    Led_Display.setLed(adresse,2,4,false);
    delay(delaytime);
    Led_Display.setLed(adresse,1,4,false);
    Led_Display.setLed(adresse,2,4,true);
  break;

  case 11: 
    Led_Display.setLed(adresse,3,7,false);
  break;

  case 12: 
    Led_Display.setLed(adresse,2,5,false);
  break;

  case 13: 
    Led_Display.setLed(adresse,3,6,false);
  break;

  case 14: 
    Led_Display.setLed(adresse,3,5,false); // doublon
  break;

  case 15: 
    Led_Display.setLed(adresse,0,3,false);
  break;

  case 16: 
    Led_Display.setLed(adresse,2,4,false);
  break;

  case 17: 
    Led_Display.setLed(adresse,4,7,false);
  break;

  case 18: 
    Led_Display.setLed(adresse,1,3,false);
  break;

  case 19: 
    Led_Display.setLed(adresse,5,7,false);
  break;

  case 20: 
    Led_Display.setLed(adresse,5,6,false); 
    delay(delaytime);
    Led_Display.setLed(adresse,4,6,false);
    Led_Display.setLed(adresse,5,6,true);
    
  break;

  case 21: 
    Led_Display.setLed(adresse,3,4,false);
  break;
  
  case 22: 
    Led_Display.setLed(adresse,5,6,false);
  break; 

  case 23: 
    Led_Display.setLed(adresse,4,5,false); /// attention, stop relecture ici, décalage car doublon avec cas 17
  break;

  case 24: 
    Led_Display.setLed(adresse,2,3,false);
  break;

  case 25: 
    Led_Display.setLed(adresse,0,2,false);
  break;

  case 26: 
    Led_Display.setLed(adresse,6,7,false); 
  break;

  case 27: 
    Led_Display.setLed(adresse,1,2,false);
  break; 

  case 28: 
    Led_Display.setLed(adresse,4,4,false);
  break; 

  case 29: 
    Led_Display.setLed(adresse,3,3,false);
  break; 

  case 30: 
    Led_Display.setLed(adresse,4,3,false);
  break;
  
  case 31: 
    Led_Display.setLed(adresse,5,5,false);
  break;

  case 32: 
    Led_Display.setLed(adresse,5,4,false);
  break; 

  case 33: 
    Led_Display.setLed(adresse,2,2,false);
  break; 

  case 34: 
    Led_Display.setLed(adresse,0,1,false);
  break; 

  case 35: 
    Led_Display.setLed(adresse,6,6,false);
  break; 

  case 36: 
    Led_Display.setLed(adresse,1,1,false);
  break;

  case 37: 
    Led_Display.setLed(adresse,3,2,false); //
  break;  

  case 38: 
    Led_Display.setLed(adresse,7,7,false);
  break;

  case 39: 
    Led_Display.setLed(adresse,0,0,false);
  break;

  case 40: 
    Led_Display.setLed(adresse,1,0,false); //
  break;

  case 41: 
    Led_Display.setLed(adresse,2,1,false); // 
  break;

  case 42: 
    Led_Display.setLed(adresse,6,5,false); //Probleme : déja fait
  break;

  case 43: 
    Led_Display.setLed(adresse,7,6,false);
  break;

  case 44: 
    Led_Display.setLed(adresse,5,3,false); // deja fait 
  break;

  case 45: 
    Led_Display.setLed(adresse,4,2,false);
  break;

  case 46: 
    Led_Display.setLed(adresse,6,4,false);
  break; 

  case 47: 
    Led_Display.setLed(adresse,3,1,false); //
  break; 

  case 48: 
    Led_Display.setLed(adresse,7,5,false); //
  break; 

  case 49: 
    Led_Display.setLed(adresse,2,0,false);
  break;

  case 50: 
    Led_Display.setLed(adresse,5,2,false); //
  break; 

  case 51: 
    Led_Display.setLed(adresse,7,4,false); // dernier ok
  break; 

  case 52: 
    Led_Display.setLed(adresse,6,3,false); //
  break;

  case 53: 
    Led_Display.setLed(adresse,3,0,false); //
  break;           

  case 54: 

    Led_Display.setLed(adresse,5,1,false); //
        delay(delaytime);
    Led_Display.setLed(adresse,4,1,false);
    Led_Display.setLed(adresse,5,1,true); //Probleme
  break;

  case 55: 
    Led_Display.setLed(adresse,4,0,false);
  break; 

  case 56: 
    Led_Display.setLed(adresse,7,3,false); // dernier check
  break; 

  case 57: 
    Led_Display.setLed(adresse,5,1,false); 
  break;

  case 58: 
    Led_Display.setLed(adresse,6,2,false);
  break;           

  case 59:                            //géré a partir d'ici
    Led_Display.setLed(adresse,5,0,false);
  break;  
  
  case 60: 
    Led_Display.setLed(adresse,7,2,false);
  break; 

  case 61: 
    Led_Display.setLed(adresse,6,1,false);
  break; 

  case 62: 
    Led_Display.setLed(adresse,6,0,false);
  break;

  case 63: 
    Led_Display.setLed(adresse,7,1,false);
  break;           

  case 64: 
    Led_Display.setLed(adresse,7,0,false);
  break;

           
}
}


