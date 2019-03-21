// ARDUINO CHESS/GO HOURGLASS

// Développé par David LE GALL 

//Principe de fonctionnement 
// Le sablier permet de jouer à des jeux de société ou chacun des participants a une durée déterminée pour jouer la totalité de ses coups
// Chaque joueur retourne le sablier après avoir joué son coup. 
// un TiltSwitch permet de savoir si le sablier est tête en haut ou en bas, c'est ce qui permet de passer la main
// 




//We always have to include the library
#include "LedControl.h"
// Déclaration des deux matrices de LED
LedControl HourGlass = LedControl(13, 11, 12, 2); // Matrix 1 :  pin 13 is connected to the DataIn  pin 11 is connected to the CLK  pin 12 is connected to LOAD





/* we always wait a bit between updates of the display */
//Variables relatives aux matrices de Led
unsigned long delaytime = 50;
int AdresseMatriceHaut = 1;
int AdresseMatriceBas = 0;

// set pin numbers:
const int TiltSwitchPin = 10;                 // the number of the TiltSwitch pin

// variables interne  Tiltswith
int TiltSwitchPinState = 0;                   // variable qui permet de savoir dans quelle position est le sablier:

//Variables internes relatives au temps
int duree_select = 0;                         //compteur selection durée, 
unsigned long TempsParJoueur = 0;               //durée sélectionnée en s, Le temps que les deux joueurs ont au début de la parie
unsigned long TimeAtStart = 0;                //instant ou l'on a appuyé sur le bouton start en ms
long TempsEcoule = 0;                         //temps ecoule en s depuis instant start
char* temps_affiche[] = {"  1", "  3", "  5", " 10", " 15", " 20", " 30", " 45", " 1h", "1h30", " 2h"}; //les différents temps affichés dans le menu, à faire correspondre avec les temps internes ci dessous
int temps_propose[] = {60, 180, 300, 600, 900, 1200, 1800, 2700, 3600, 5400, 7200}; // les différents temps proposés dans le menu ( variable interne en secondes, n'est pas affichée)
int temps_restant_min_segondes = 0;           //variable permettant  d'afficher le temps restant apres avoir lancé un chrono

//Variables internes pour les temps restants aux deux joueurs
         
unsigned long TempsEcouleJ1 =0;              // Le temps restant pour chacun des joueurs
unsigned long TempsEcouleJ2 =0;

bool TourJoueur1 = 0;                       // booléen permettant de savoir au tour de quel joueur on est




void setup() {

  // initialsation du TlitSwitch
  pinMode(TiltSwitchPin, INPUT);

  // initialisation des matrices de Leds
  for (int address = 0; address < 2; address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    HourGlass.shutdown(address, false);
    /* Set the brightness to a medium values */
    HourGlass.setIntensity(address, 8);
    /* and clear the display */
    HourGlass.clearDisplay(address);
  }
  Serial.begin(9600);

  InitialisationSablier();

  calcul_temps(duree_select); //faire la correspondance entre le temps selectionné et le temps à décompter
  
}

void loop() {

// Savoir si c'est au joueur 1 ou de 2 de jouer, on commence par le joeur 1, donc on peut se repérer avec l'état du Tiltswitch. 
// on sait que (TiltSwitchPinState == digitalRead(TiltSwitchPin) ) est FALSE pendant le tour du Joueur1 
// on sait que (TiltSwitchPinState == digitalRead(TiltSwitchPin) ) est TRUE pendant le tour du Joueur2

DeterminerDirectionSablier();


// En fonction de cela, on doit décompter le temps du J1 ou du J2

// A qui est-ce de jouer ? 


// Afficher le sablier en fonction du temps qu'il lui reste
// Décompter le temps et faire l'affichage

// on doit vérifier en permanence que le sablier n'est pas retourné

int etat_remplissage_joueur_en_cours = calcul_remplissage(); //Déterminer à quelle étape est le joueur en cours, on met cela dans une variable locale, elle s'efface à chaque boucle 

// Afficher le sablier en fonction du temps qu'il lui reste


ReprendreRemplissageMatrice ( etat_remplissage_joueur_en_cours );

if ( etat_remplissage_joueur_en_cours == 0 ) {                                   // on fait tomber un grain de force au tout début, simplement pour savoir que le sablier est en marche.
  delay (1000);
  Vider_matrice(1, AdresseMatriceHaut);             
  RemplirMatrice(1, AdresseMatriceBas);
  while (etat_remplissage_joueur_en_cours <= 1){                                 // on attend que l'état passe à 2, pas à 1, sinon on voit la première animation 2 fois
    etat_remplissage_joueur_en_cours = calcul_remplissage(); 
    if (DeterminerSiSablierRetourne()==1) break;                                 // Sortir de la boucle while si l'état du sablier est différent
    delay(10);
  }
  }



while (DeterminerSiSablierRetourne()==0){                                          //tant que le sablier n'est pas retourné 
  int etat_remplissage = calcul_remplissage();                                     // on définit l'etat de remplassage en fonction du temps écoulé, c'est une valeur interne
  while (etat_remplissage_joueur_en_cours >= etat_remplissage) {                   //Attendre qu'assez de temps soit passé, donc que l'état aie augmenté pour faire s'écouler le prochain grain ( on recalcule temps remplissage jusqu'a ce qu'il dépasse i).
      etat_remplissage = calcul_remplissage();
      Serial.print(TempsEcouleJ1);  // print as an ASCII-encoded hexadecimal
      Serial.print("\t");    // prints a tab
      Serial.print(etat_remplissage_joueur_en_cours);
      Serial.println(); 
      if (DeterminerSiSablierRetourne()==1) break;                                 // Sortir de la boucle while si l'état du sablier est différent
      delay(2);
      }
  Vider_matrice(etat_remplissage_joueur_en_cours, AdresseMatriceHaut);             // on fait tomber un grain
  RemplirMatrice(etat_remplissage_joueur_en_cours, AdresseMatriceBas);
  
  etat_remplissage_joueur_en_cours++;
  
  if (TempsEcouleJ1 >= TempsParJoueur || TempsEcouleJ2 >= TempsParJoueur ){  // On vérifie qu'il reste du temps à chaque joueur, la boucle se déclenche si un des deux temps est écoulé
        DeterminerDirectionSablier();                                                          // On vérifie dans quelle position est le sablier
        HourGlass.clearDisplay(AdresseMatriceHaut);
          for (int i = 0 ; i < 7; i++) {
            AfficherMatriceRemplie(AdresseMatriceBas);                                  // On fait blinker la matrice du bas
            delay (500);
            HourGlass.clearDisplay(AdresseMatriceBas);
            delay(500);  
           }
        InitialisationSablier();                                                 // Ensuite le système est pret a repartir
      }
  }

}

void InitialisationSablier(){

  DeterminerDirectionSablier();                          // permet de savoir dans quelle position est le sablier
 
  AfficherMatriceRemplie(AdresseMatriceBas);             // On commence avec la matrice du bas remplie, ca donne envie de le retourner

  while (DeterminerSiSablierRetourne()==0 ) {            // attendre que le sablier soit retourné, c'est à dire que l'etat du TiltSwitch soit différent
    delay(5);                                            
  }
  TourJoueur1 = digitalRead(TiltSwitchPin);              // Le joueur qui a retourné le sablier, donc qui fait le premier coup dans le jeu sera appelé Joueur1, l'autre Joueur2
                                                         // tour joueur 1 = état du tiltswitch a ce moment
  TimeAtStart = millis();                                // des que l'on sort de la boucle le jeu a commencé.
  TempsEcouleJ1 =0;
  TempsEcouleJ2 =0;
 
}

void DeterminerDirectionSablier(){
    // Déterminer la position du sablier pour afficher dans le bon sens
  
  // read the state of the TiltSwitch value:
  TiltSwitchPinState = digitalRead(TiltSwitchPin);

  // check if the tiltswitch is pressed.
  // if it is, the TiltSwitchPinState is HIGH:
  
    if (TiltSwitchPinState == HIGH) {
    AdresseMatriceHaut = 0;
    AdresseMatriceBas = 1;
  } else {
    AdresseMatriceHaut = 1;
    AdresseMatriceBas = 0;
  }
}

bool DeterminerSiSablierRetourne(){
  if (TiltSwitchPinState == digitalRead(TiltSwitchPin)){
    return 0;
    }
  else{
    return 1;
    }
}



int calcul_remplissage() {
  if (TourJoueur1 == digitalRead(TiltSwitchPin)){                                    //Si on est pdt le tour du joueur 1
      TempsEcouleJ1 = (millis() - TimeAtStart) / 1000 - TempsEcouleJ2 ;              //calcul du temps écoulé 
      return (TempsEcouleJ1 * 64) / TempsParJoueur ;   
  }else{
      TempsEcouleJ2 = (millis() - TimeAtStart) / 1000 - TempsEcouleJ1 ;             
      return (TempsEcouleJ2 * 64) / TempsParJoueur ;
  }
}
 

void calcul_temps(int select) {
  TempsParJoueur = temps_propose[select];
}

void AfficherMatriceRemplie(int adresse) {
  for (int i = 0; i <= 7; i++) {
    for (int j = 0; j <= 7; j++) {
      HourGlass.setLed(adresse, i, j, true);
    }
  }
}



void Descente_limitee_diag_matrice(int limite, int adresse) {
  for (int i = 0; i < limite; i++) { // Boucle qui décrit la diagonale descendante de M1
    HourGlass.setLed(adresse, 7 - i, i, true);
    delay(delaytime);
    HourGlass.setLed(adresse, 7 - i, i, false);
  }
}

void RemplirMatrice(int etat_de_remplissage, int adresse) {

  // la matrice fait 64 Leds, on a une animation pour chacune de ces 64 Leds, la variable etat de remplissage permet de choisir quelle animation on veut.

  switch (etat_de_remplissage) {
    case 1:
      Descente_limitee_diag_matrice(8, adresse);

      HourGlass.setLed(adresse, 0, 7, true);         //1

      break;

    case 2:
      Descente_limitee_diag_matrice(7, adresse);

      // Ligne 2
      HourGlass.setLed(adresse, 1, 7, true);         //2

      break;

    case 3:
      Descente_limitee_diag_matrice(7, adresse);

      HourGlass.setLed(adresse, 0, 6, true);         //3

      break;

    case 4:
      Descente_limitee_diag_matrice(6, adresse);

      //Ligne 3
      HourGlass.setLed(adresse, 1, 6, true);         //4

      break;

    case 5:
      Descente_limitee_diag_matrice(6, adresse);

      //Anim 5
      HourGlass.setLed(adresse, 1, 5, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 1, 5, false);

      HourGlass.setLed(adresse, 0, 5, true);         //5

      break;

    case 6:
      Descente_limitee_diag_matrice(6, adresse);

      //Anim 6
      HourGlass.setLed(adresse, 2, 6, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 2, 6, false);

      HourGlass.setLed(adresse, 2, 7, true);        //6
      break;

    case 7:
      //Ligne 4

      Descente_limitee_diag_matrice(6, adresse);

      HourGlass.setLed(adresse, 1, 5, true);          //7
      break;

    case 8:
      Descente_limitee_diag_matrice(6, adresse);
      HourGlass.setLed(adresse, 2, 6, true);           //8
      break;

    case 9:
      Descente_limitee_diag_matrice(5, adresse);
      HourGlass.setLed(adresse, 2, 5, true);           //9
      break;

    case 10:
      Descente_limitee_diag_matrice(5, adresse);
      HourGlass.setLed(adresse, 3, 5, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 3, 5, false);

      HourGlass.setLed(adresse, 3, 6, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 3, 6, false);

      HourGlass.setLed(adresse, 3, 7, true);             //10
      break;

    case 11:
      Descente_limitee_diag_matrice(5, adresse);

      for (int i = 0; i < 3; i++) { // Anim 11
        HourGlass.setLed(adresse, 2 - i, 4, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 2 - i, 4, false);
      }

      HourGlass.setLed(adresse, 0, 4, true);           //11
      break;

    case 12:
      Descente_limitee_diag_matrice(5, adresse);

      for (int i = 0; i < 2; i++) { // Anim 11
        HourGlass.setLed(adresse, 2 - i, 4, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 2 - i, 4, false);
      }

      HourGlass.setLed(adresse, 1, 4, true);            //12
      break;

    case 13:
      Descente_limitee_diag_matrice(5, adresse);

      for (int i = 0; i < 2; i++) { // Anim 13
        HourGlass.setLed(adresse, 3, 5 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 3, 5 + i, false);
      }

      HourGlass.setLed(adresse, 3, 6, true);       //13
      break;


    case 14 :
      Descente_limitee_diag_matrice(5, adresse);

      HourGlass.setLed(adresse, 3, 5, true);       //14
      break;

    case 15 :
      Descente_limitee_diag_matrice(5, adresse);

      HourGlass.setLed(adresse, 2, 4, true);         //15
      break;

    case 16 :
      Descente_limitee_diag_matrice(4, adresse);

      HourGlass.setLed(adresse, 3, 4, true);         //16
      break;


    case 17 :
      Descente_limitee_diag_matrice(4, adresse);

      for (int i = 0; i < 4; i++) { // Anim 17
        HourGlass.setLed(adresse, 3 - i, 3, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 3 - i, 3, false);
      }

      HourGlass.setLed(adresse, 0, 3, true);         //17
      break;


    case 18 :
      Descente_limitee_diag_matrice(4, adresse);

      for (int i = 0; i < 3; i++) { // Anim 18
        HourGlass.setLed(adresse, 4, 4 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 4, 4 + i, false);
      }

      HourGlass.setLed(adresse, 4, 7, true);         //18
      break;


    case 19 :
      Descente_limitee_diag_matrice(3, adresse);

      for (int i = 0; i < 3; i++) { // Anim 18
        HourGlass.setLed(adresse, 4 - i, 3, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 4 - i, 3, false);
      }

      HourGlass.setLed(adresse, 1, 3, true);     //19
      break;

    case 20 :

      Descente_limitee_diag_matrice(3, adresse);

      for (int i = 0; i < 3; i++) { // Anim 18
        HourGlass.setLed(adresse, 4, 4 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 4, 4 + i, false);
      }


      HourGlass.setLed(adresse, 4, 6, true);  //20
      break;

    case 21 :
      Descente_limitee_diag_matrice(3, adresse);

      for (int i = 0; i < 2; i++) { // Anim 18
        HourGlass.setLed(adresse, 4, 4 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 4, 4 + i, false);
      }
      HourGlass.setLed(adresse, 5, 6, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 5, 6, false);

      HourGlass.setLed(adresse, 5, 7, true);  //21
      break;

    case 22 :
      Descente_limitee_diag_matrice(3, adresse);

      // Anim 22
      HourGlass.setLed(adresse, 3, 3, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 3, 3, false);

      HourGlass.setLed(adresse, 2, 3, true);       //22
      break;

    case 23 :
      Descente_limitee_diag_matrice(3, adresse);

      // Anim 22
      HourGlass.setLed(adresse, 3, 3, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 3, 3, false);

      for (int i = 0; i < 3; i++) { // Anim 18
        HourGlass.setLed(adresse, 3 - i, 2, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 3 - i, 2, false);
      }

      HourGlass.setLed(adresse, 0, 2, true);       //23
      break;

    case 24 :
      Descente_limitee_diag_matrice(3, adresse);
      delay(delaytime);
      // Anim 22
      HourGlass.setLed(adresse, 3, 3, true);
      break;

    case 25 :
      Descente_limitee_diag_matrice(3, adresse);

      // Anim 25
      HourGlass.setLed(adresse, 4, 4, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 4, 4, false);

      HourGlass.setLed(adresse, 4, 5, true);       //25
      break;

    case 26 :
      Descente_limitee_diag_matrice(3, adresse);

      // Anim 25
      HourGlass.setLed(adresse, 4, 4, true);
      break;

    case 27 :
      Descente_limitee_diag_matrice(2, adresse);
      HourGlass.setLed(adresse, 4, 3, true);
      break;

    case 28 :
      Descente_limitee_diag_matrice(2, adresse);

      for (int i = 0; i < 4; i++) { // Anim 18
        HourGlass.setLed(adresse, 5, 3 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 5, 3 + i, false);
      }

      HourGlass.setLed(adresse, 5, 6, true);  //28
      break;

    case 29 :
      Descente_limitee_diag_matrice(2, adresse);

      for (int i = 0; i < 3; i++) { // Anim 18
        HourGlass.setLed(adresse, 5, 3 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 5, 3 + i, false);
      }

      HourGlass.setLed(adresse, 5, 5, true);  //29
      break;

    case 30 :
      Descente_limitee_diag_matrice(2, adresse);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(adresse, 4 - i, 2, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 4 - i, 2, false);
      }

      HourGlass.setLed(adresse, 1, 2, true);  //30
      break;

    case 31 :
      Descente_limitee_diag_matrice(2, adresse);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(adresse, 4 - i, 2, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 4 - i, 2, false);
      }
      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(adresse, 2 - i, 1, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 2 - i, 1, false);
      }

      HourGlass.setLed(adresse, 0, 1, true);  //31
      break;

    case 32 :
      Descente_limitee_diag_matrice(2, adresse);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(adresse, 4 - i, 2, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 4 - i, 2, false);
      }

      HourGlass.setLed(adresse, 2, 2, true);  //32
      break;

    case 33 :
      Descente_limitee_diag_matrice(2, adresse);

      // Anim 33
      HourGlass.setLed(adresse, 5, 3, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 5, 3, false);

      HourGlass.setLed(adresse, 5, 4, true);  //33
      break;

    case 34 :
      Descente_limitee_diag_matrice(2, adresse);

      // Anim 33
      HourGlass.setLed(adresse, 5, 3, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 5, 3, false);

      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(adresse, 6, 4 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 6, 4 + i, false);
      }
      HourGlass.setLed(adresse, 6, 7, true);  //33
      break;

    case 35 :
      Descente_limitee_diag_matrice(2, adresse);

      // Anim 33
      HourGlass.setLed(adresse, 5, 3, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 5, 3, false);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(adresse, 6, 4 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 6, 4 + i, false);
      }
      HourGlass.setLed(adresse, 6, 6, true);  //33
      break;

    case 36 :
      Descente_limitee_diag_matrice(2, adresse);

      for (int i = 0; i < 1; i++) { // Anim 30
        HourGlass.setLed(adresse, 4 - i, 2, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 4 - i, 2, false);
      }

      HourGlass.setLed(adresse, 3, 2, true);  //32
      break;

    case 37 :
      Descente_limitee_diag_matrice(2, adresse);

      HourGlass.setLed(adresse, 5, 3, true);  //32
      break;

    case 38 :
      Descente_limitee_diag_matrice(2, adresse);

      HourGlass.setLed(adresse, 4, 2, true);  //32
      break;

    case 39 :
      Descente_limitee_diag_matrice(1, adresse);

      HourGlass.setLed(adresse, 5, 2, true);  //32
      break;

    case 40 :
      Descente_limitee_diag_matrice(1, adresse);

      for (int i = 0; i < 4; i++) { // Anim 30
        HourGlass.setLed(adresse, 6, 2 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 6, 2 + i, false);
      }

      HourGlass.setLed(adresse, 6, 5, true);  //33
      break;

    case 41 :
      Descente_limitee_diag_matrice(2, adresse);

      for (int i = 0; i < 4; i++) { // Anim 30
        HourGlass.setLed(adresse, 5 - i, 1, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 5 - i, 1, false);
      }

      HourGlass.setLed(adresse, 1, 1, true);  //41
      break;

    case 42 :
      Descente_limitee_diag_matrice(1, adresse);

      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(adresse, 5 - i, 1, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 5 - i, 1, false);
      }

      HourGlass.setLed(adresse, 2, 1, true);  //33
      break;

    case 43 :
      Descente_limitee_diag_matrice(1, adresse);

      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(adresse, 5 - i, 1, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 5 - i, 1, false);
      }

      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(adresse, 3 - i, 0, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 3 - i, 0, false);
      }

      HourGlass.setLed(adresse, 0, 0, true);  //33
      break;

    case 44 :
      Descente_limitee_diag_matrice(1, adresse);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(adresse, 5 - i, 1, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 5 - i, 1, false);
      }

      HourGlass.setLed(adresse, 3, 1, true);  //33
      break;

    case 45 :
      Descente_limitee_diag_matrice(1, adresse);

      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(adresse, 6, 2 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 6, 2 + i, false);
      }

      HourGlass.setLed(adresse, 6, 4, true);  //33
      break;

    case 46 :
      Descente_limitee_diag_matrice(1, adresse);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(adresse, 6, 2 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 6, 2 + i, false);
      }

      for (int i = 0; i < 4; i++) { // Anim 30
        HourGlass.setLed(adresse, 7, 3 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 7, 3 + i, false);
      }

      HourGlass.setLed(adresse, 7, 7, true);  //33
      break;

    case 47 :
      Descente_limitee_diag_matrice(1, adresse);

      for (int i = 0; i < 1; i++) { // Anim 30
        HourGlass.setLed(adresse, 5 - i, 1, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 5 - i, 1, false);
      }

      HourGlass.setLed(adresse, 4, 1, true);  //33
      break;

    case 48 :
      Descente_limitee_diag_matrice(1, adresse);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(adresse, 6, 2 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 6, 2 + i, false);
      }

      for (int i = 0; i < 4; i++) { // Anim 30
        HourGlass.setLed(adresse, 7, 3 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 7, 3 + i, false);
      }

      HourGlass.setLed(adresse, 7, 6, true);  //33
      break;

    case 49 :
      Descente_limitee_diag_matrice(1, adresse);

      HourGlass.setLed(adresse, 5, 1, true);  //32
      break;

    case 50 :
      Descente_limitee_diag_matrice(1, adresse);

      HourGlass.setLed(adresse, 6, 2, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 6, 2, false);

      HourGlass.setLed(adresse, 6, 3, true);  //32
      break;

    case 51 :
      Descente_limitee_diag_matrice(1, adresse);

      HourGlass.setLed(adresse, 6, 2, true);
      break;

    case 52 :
      HourGlass.setLed(adresse, 7, 0, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 7, 0, false);

      HourGlass.setLed(adresse, 6, 1, true);
      break;

    case 53 :
      for (int i = 0; i < 4; i++) { // Anim 30
        HourGlass.setLed(adresse, 7, 0 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 7, 0 + i, false);
      }

      HourGlass.setLed(adresse, 7, 5, true);    //53
      break;

    case 54 :
      for (int i = 0; i < 6; i++) { // Anim 30
        HourGlass.setLed(adresse, 7 - i, 0, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 7 - i, 0, false);
      }

      HourGlass.setLed(adresse, 1, 0, true);
      break;

    case 55 :
      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(adresse, 7, 0 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 7, 0 + i, false);
      }

      HourGlass.setLed(adresse, 7, 4, true);
      break;

    case 56 :
      for (int i = 0; i < 5; i++) { // Anim 30
        HourGlass.setLed(adresse, 7 - i, 0, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 7 - i, 0, false);
      }

      HourGlass.setLed(adresse, 2, 0, true);
      break;

    case 57 :
      for (int i = 0; i < 4; i++) { // Anim 30
        HourGlass.setLed(adresse, 7 - i, 0, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 7 - i, 0, false);
      }

      HourGlass.setLed(adresse, 3, 0, true);
      break;

    case 58 :
      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(adresse, 7, 0 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 7, 0 + i, false);
      }

      HourGlass.setLed(adresse, 7, 3, true);
      break;

    case 59 :
      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(adresse, 7, 0 + i, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 7, 0 + i, false);
      }

      HourGlass.setLed(adresse, 7, 2, true);
      break;

    case 60 :
      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(adresse, 7 - i, 0, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 7 - i, 0, false);
      }

      HourGlass.setLed(adresse, 4, 0, true);
      break;

    case 61 :
      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(adresse, 7 - i, 0, true);
        delay(delaytime);
        HourGlass.setLed(adresse, 7 - i, 0, false);
      }

      HourGlass.setLed(adresse, 5, 0, true);
      break;

    case 62 :
      HourGlass.setLed(adresse, 7, 0, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 7, 0, false);

      HourGlass.setLed(adresse, 7, 1, true);         //1
      break;

    case 63 :
      HourGlass.setLed(adresse, 7, 0, true);
      delay(delaytime);
      HourGlass.setLed(adresse, 7, 0, false);

      HourGlass.setLed(adresse, 6, 0, true);         //1
      break;

    case 64 :
      HourGlass.setLed(adresse, 7, 0, true);         //64
      break;
  }
}

void Vider_matrice(int etat_de_remplissage, int adresse) {

  switch (etat_de_remplissage) {
    case 1:
      HourGlass.setLed(adresse, 0, 7, false);
      break;

    case 2:
      HourGlass.setLed(adresse, 1, 7, false);
      break;

    case 3:
      HourGlass.setLed(adresse, 0, 6, false);
      break;

    case 4:
      HourGlass.setLed(adresse, 1, 6, false);
      break;

    case 5:
      HourGlass.setLed(adresse, 2, 7, false);
      break;

    case 6:
      HourGlass.setLed(adresse, 0, 5, false);
      break;

    case 7:
      HourGlass.setLed(adresse, 1, 5, false);
      break;

    case 8:
      HourGlass.setLed(adresse, 2, 6, false);
      break;

    case 9:
      HourGlass.setLed(adresse, 0, 4, false);
      break;

    case 10:
      HourGlass.setLed(adresse, 2, 4, false);
      delay(delaytime);
      HourGlass.setLed(adresse, 1, 4, false);
      HourGlass.setLed(adresse, 2, 4, true);
      break;

    case 11:
      HourGlass.setLed(adresse, 3, 7, false);
      break;

    case 12:
      HourGlass.setLed(adresse, 2, 5, false);
      break;

    case 13:
      HourGlass.setLed(adresse, 3, 6, false);
      break;

    case 14:
      HourGlass.setLed(adresse, 3, 5, false); // doublon
      break;

    case 15:
      HourGlass.setLed(adresse, 0, 3, false);
      break;

    case 16:
      HourGlass.setLed(adresse, 2, 4, false);
      break;

    case 17:
      HourGlass.setLed(adresse, 4, 7, false);
      break;

    case 18:
      HourGlass.setLed(adresse, 1, 3, false);
      break;

    case 19:
      HourGlass.setLed(adresse, 5, 7, false);
      break;

    case 20:
      HourGlass.setLed(adresse, 5, 6, false);
      delay(delaytime);
      HourGlass.setLed(adresse, 4, 6, false);
      HourGlass.setLed(adresse, 5, 6, true);
      break;

    case 21:
      HourGlass.setLed(adresse, 3, 4, false);
      break;

    case 22:
      HourGlass.setLed(adresse, 5, 6, false);
      break;

    case 23:
      HourGlass.setLed(adresse, 4, 5, false); /// attention, stop relecture ici, décalage car doublon avec cas 17
      break;

    case 24:
      HourGlass.setLed(adresse, 2, 3, false);
      break;

    case 25:
      HourGlass.setLed(adresse, 0, 2, false);
      break;

    case 26:
      HourGlass.setLed(adresse, 6, 7, false);
      break;

    case 27:
      HourGlass.setLed(adresse, 1, 2, false);
      break;

    case 28:
      HourGlass.setLed(adresse, 4, 4, false);
      break;

    case 29:
      HourGlass.setLed(adresse, 3, 3, false);
      break;

    case 30:
      HourGlass.setLed(adresse, 4, 3, false);
      break;

    case 31:
      HourGlass.setLed(adresse, 5, 5, false);
      break;

    case 32:
      HourGlass.setLed(adresse, 5, 4, false);
      break;

    case 33:
      HourGlass.setLed(adresse, 2, 2, false);
      break;

    case 34:
      HourGlass.setLed(adresse, 0, 1, false);
      break;

    case 35:
      HourGlass.setLed(adresse, 6, 6, false);
      break;

    case 36:
      HourGlass.setLed(adresse, 1, 1, false);
      break;

    case 37:
      HourGlass.setLed(adresse, 3, 2, false); //
      break;

    case 38:
      HourGlass.setLed(adresse, 7, 7, false);
      break;

    case 39:
      HourGlass.setLed(adresse, 0, 0, false);
      break;

    case 40:
      HourGlass.setLed(adresse, 1, 0, false); //
      break;

    case 41:
      HourGlass.setLed(adresse, 2, 1, false); //
      break;

    case 42:
      HourGlass.setLed(adresse, 6, 5, false); //Probleme : déja fait
      break;

    case 43:
      HourGlass.setLed(adresse, 7, 6, false);
      break;

    case 44:
      HourGlass.setLed(adresse, 5, 3, false); // deja fait
      break;

    case 45:
      HourGlass.setLed(adresse, 4, 2, false);
      break;

    case 46:
      HourGlass.setLed(adresse, 6, 4, false);
      break;

    case 47:
      HourGlass.setLed(adresse, 3, 1, false); //
      break;

    case 48:
      HourGlass.setLed(adresse, 7, 5, false); //
      break;

    case 49:
      HourGlass.setLed(adresse, 2, 0, false);
      break;

    case 50:
      HourGlass.setLed(adresse, 5, 2, false);
      break;

    case 51:
      HourGlass.setLed(adresse, 7, 4, false);
      break;

    case 52:
      HourGlass.setLed(adresse, 6, 3, false);
      break;

    case 53:
      HourGlass.setLed(adresse, 3, 0, false);
      break;

    case 54:
      HourGlass.setLed(adresse, 5, 1, false);
      delay(delaytime);
      HourGlass.setLed(adresse, 4, 1, false);
      HourGlass.setLed(adresse, 5, 1, true);
      break;

    case 55:
      HourGlass.setLed(adresse, 4, 0, false);
      break;

    case 56:
      HourGlass.setLed(adresse, 7, 3, false);
      break;

    case 57:
      HourGlass.setLed(adresse, 5, 1, false);
      break;

    case 58:
      HourGlass.setLed(adresse, 6, 2, false);
      break;

    case 59:
      HourGlass.setLed(adresse, 5, 0, false);
      break;

    case 60:
      HourGlass.setLed(adresse, 7, 2, false);
      break;

    case 61:
      HourGlass.setLed(adresse, 6, 1, false);
      break;

    case 62:
      HourGlass.setLed(adresse, 6, 0, false);
      break;

    case 63:
      HourGlass.setLed(adresse, 7, 1, false);
      break;

    case 64:
      HourGlass.setLed(adresse, 7, 0, false);
      break;


  }
}


void ReprendreRemplissageMatrice (int etat_de_remplissage ) {
  HourGlass.clearDisplay(AdresseMatriceBas);
  HourGlass.clearDisplay(AdresseMatriceHaut);
  AfficherMatriceRemplie(AdresseMatriceHaut);
  for (int i = 0 ; i <= etat_de_remplissage - 1; i++){ // j'ai soustrait 1 car la fonction "reprendre remplissage reprenait en fiat en avance
    EtatMatriceVidee(i, AdresseMatriceHaut);
    delay(11);
    EtatMatriceRemplie(i, AdresseMatriceBas);
    delay(11);
  }  
}

void EtatMatriceVidee(int etat_de_remplissage, int adresse) {

  switch (etat_de_remplissage) {
    case 1:
      HourGlass.setLed(adresse, 0, 7, false);
      break;

    case 2:
      HourGlass.setLed(adresse, 1, 7, false);
      break;

    case 3:
      HourGlass.setLed(adresse, 0, 6, false);
      break;

    case 4:
      HourGlass.setLed(adresse, 1, 6, false);
      break;

    case 5:
      HourGlass.setLed(adresse, 2, 7, false);
      break;

    case 6:
      HourGlass.setLed(adresse, 0, 5, false);
      break;

    case 7:
      HourGlass.setLed(adresse, 1, 5, false);
      break;

    case 8:
      HourGlass.setLed(adresse, 2, 6, false);
      break;

    case 9:
      HourGlass.setLed(adresse, 0, 4, false);
      break;

    case 10:
      HourGlass.setLed(adresse, 1, 4, false); // Changé 2.4 true en 1.4 false
      break;

    case 11:
      HourGlass.setLed(adresse, 3, 7, false);
      break;

    case 12:
      HourGlass.setLed(adresse, 2, 5, false);
      break;

    case 13:
      HourGlass.setLed(adresse, 3, 6, false);
      break;

    case 14:
      HourGlass.setLed(adresse, 3, 5, false); // doublon
      break;

    case 15:
      HourGlass.setLed(adresse, 0, 3, false);
      break;

    case 16:
      HourGlass.setLed(adresse, 2, 4, false);
      break;

    case 17:
      HourGlass.setLed(adresse, 4, 7, false);
      break;

    case 18:
      HourGlass.setLed(adresse, 1, 3, false);
      break;

    case 19:
      HourGlass.setLed(adresse, 5, 7, false);
      break;

    case 20:
      HourGlass.setLed(adresse, 4, 6, false); // Changé 5,6 True en 4,6 false
      break;

    case 21:
      HourGlass.setLed(adresse, 3, 4, false);
      break;

    case 22:
      HourGlass.setLed(adresse, 5, 6, false);
      break;

    case 23:
      HourGlass.setLed(adresse, 4, 5, false); /// attention, stop relecture ici, décalage car doublon avec cas 17
      break;

    case 24:
      HourGlass.setLed(adresse, 2, 3, false);
      break;

    case 25:
      HourGlass.setLed(adresse, 0, 2, false);
      break;

    case 26:
      HourGlass.setLed(adresse, 6, 7, false);
      break;

    case 27:
      HourGlass.setLed(adresse, 1, 2, false);
      break;

    case 28:
      HourGlass.setLed(adresse, 4, 4, false);
      break;

    case 29:
      HourGlass.setLed(adresse, 3, 3, false);
      break;

    case 30:
      HourGlass.setLed(adresse, 4, 3, false);
      break;

    case 31:
      HourGlass.setLed(adresse, 5, 5, false);
      break;

    case 32:
      HourGlass.setLed(adresse, 5, 4, false);
      break;

    case 33:
      HourGlass.setLed(adresse, 2, 2, false);
      break;

    case 34:
      HourGlass.setLed(adresse, 0, 1, false);
      break;

    case 35:
      HourGlass.setLed(adresse, 6, 6, false);
      break;

    case 36:
      HourGlass.setLed(adresse, 1, 1, false);
      break;

    case 37:
      HourGlass.setLed(adresse, 3, 2, false); //
      break;

    case 38:
      HourGlass.setLed(adresse, 7, 7, false);
      break;

    case 39:
      HourGlass.setLed(adresse, 0, 0, false);
      break;

    case 40:
      HourGlass.setLed(adresse, 1, 0, false); //
      break;

    case 41:
      HourGlass.setLed(adresse, 2, 1, false); //
      break;

    case 42:
      HourGlass.setLed(adresse, 6, 5, false); //Probleme : déja fait
      break;

    case 43:
      HourGlass.setLed(adresse, 7, 6, false);
      break;

    case 44:
      HourGlass.setLed(adresse, 5, 3, false); // deja fait
      break;

    case 45:
      HourGlass.setLed(adresse, 4, 2, false);
      break;

    case 46:
      HourGlass.setLed(adresse, 6, 4, false);
      break;

    case 47:
      HourGlass.setLed(adresse, 3, 1, false); //
      break;

    case 48:
      HourGlass.setLed(adresse, 7, 5, false); //
      break;

    case 49:
      HourGlass.setLed(adresse, 2, 0, false);
      break;

    case 50:
      HourGlass.setLed(adresse, 5, 2, false);
      break;

    case 51:
      HourGlass.setLed(adresse, 7, 4, false);
      break;

    case 52:
      HourGlass.setLed(adresse, 6, 3, false);
      break;

    case 53:
      HourGlass.setLed(adresse, 3, 0, false);
      break;

    case 54:
      HourGlass.setLed(adresse, 5, 1, true);
      break;

    case 55:
      HourGlass.setLed(adresse, 4, 0, false);
      break;

    case 56:
      HourGlass.setLed(adresse, 7, 3, false);
      break;

    case 57:
      HourGlass.setLed(adresse, 5, 1, false);
      break;

    case 58:
      HourGlass.setLed(adresse, 6, 2, false);
      break;

    case 59:
      HourGlass.setLed(adresse, 5, 0, false);
      break;

    case 60:
      HourGlass.setLed(adresse, 7, 2, false);
      break;

    case 61:
      HourGlass.setLed(adresse, 6, 1, false);
      break;

    case 62:
      HourGlass.setLed(adresse, 6, 0, false);
      break;

    case 63:
      HourGlass.setLed(adresse, 7, 1, false);
      break;

    case 64:
      HourGlass.setLed(adresse, 7, 0, false);
      break;


  }
}





void EtatMatriceRemplie (int etat_de_remplissage, int adresse) {

  // la matrice fait 64 Leds, on a une animation pour chacune de ces 64 Leds, la variable etat de remplissage permet de choisir quelle animation on veut.

  switch (etat_de_remplissage) {
    case 1:
      HourGlass.setLed(adresse, 0, 7, true);         //1
      break;

    case 2:
      HourGlass.setLed(adresse, 1, 7, true);         //2
      break;

    case 3:
      HourGlass.setLed(adresse, 0, 6, true);         //3
      break;

    case 4:
      HourGlass.setLed(adresse, 1, 6, true);         //4
      break;

    case 5:
      HourGlass.setLed(adresse, 0, 5, true);         //5
      break;

    case 6:
      HourGlass.setLed(adresse, 2, 7, true);        //6
      break;

    case 7:
      HourGlass.setLed(adresse, 1, 5, true);          //7
      break;

    case 8:
      HourGlass.setLed(adresse, 2, 6, true);           //8
      break;

    case 9:
      HourGlass.setLed(adresse, 2, 5, true);           //9
      break;

    case 10:
      HourGlass.setLed(adresse, 3, 7, true);             //10
      break;

    case 11:
      HourGlass.setLed(adresse, 0, 4, true);           //11
      break;

    case 12:
      HourGlass.setLed(adresse, 1, 4, true);            //12
      break;

    case 13:
      HourGlass.setLed(adresse, 3, 6, true);       //13
      break;

    case 14 :
      HourGlass.setLed(adresse, 3, 5, true);       //14
      break;

    case 15 :
      HourGlass.setLed(adresse, 2, 4, true);         //15
      break;

    case 16 :
      HourGlass.setLed(adresse, 3, 4, true);         //16
      break;

    case 17 :
      HourGlass.setLed(adresse, 0, 3, true);         //17
      break;

    case 18 :
      HourGlass.setLed(adresse, 4, 7, true);         //18
      break;


    case 19 :
      HourGlass.setLed(adresse, 1, 3, true);     //19
      break;

    case 20 :
      HourGlass.setLed(adresse, 4, 6, true);  //20
      break;

    case 21 :
      HourGlass.setLed(adresse, 5, 7, true);  //21
      break;

    case 22 :
      HourGlass.setLed(adresse, 2, 3, true);       //22
      break;

    case 23 :
      HourGlass.setLed(adresse, 0, 2, true);       //23
      break;

    case 24 :
      HourGlass.setLed(adresse, 3, 3, true);
      break;

    case 25 :
      HourGlass.setLed(adresse, 4, 5, true);       //25
      break;

    case 26 :
      HourGlass.setLed(adresse, 4, 4, true);
      break;

    case 27 :
      HourGlass.setLed(adresse, 4, 3, true);
      break;

    case 28 :
      HourGlass.setLed(adresse, 5, 6, true);  //28
      break;

    case 29 :
      HourGlass.setLed(adresse, 5, 5, true);  //29
      break;

    case 30 :
      HourGlass.setLed(adresse, 1, 2, true);  //30
      break;

    case 31 :
      HourGlass.setLed(adresse, 0, 1, true);  //31
      break;

    case 32 :
      HourGlass.setLed(adresse, 2, 2, true);  //32
      break;

    case 33 :
      HourGlass.setLed(adresse, 5, 4, true);  //33
      break;

    case 34 :
      HourGlass.setLed(adresse, 6, 7, true);  //33
      break;

    case 35 :
      HourGlass.setLed(adresse, 6, 6, true);  //33
      break;

    case 36 :
      HourGlass.setLed(adresse, 3, 2, true);  //32
      break;

    case 37 :
      HourGlass.setLed(adresse, 5, 3, true);  //32
      break;

    case 38 :
      HourGlass.setLed(adresse, 4, 2, true);  //32
      break;

    case 39 :
      HourGlass.setLed(adresse, 5, 2, true);  //32
      break;

    case 40 :
      HourGlass.setLed(adresse, 6, 5, true);  //33
      break;

    case 41 :
      HourGlass.setLed(adresse, 1, 1, true);  //41
      break;

    case 42 :
      HourGlass.setLed(adresse, 2, 1, true);  //33
      break;

    case 43 :
      HourGlass.setLed(adresse, 0, 0, true);  //33
      break;

    case 44 :
      HourGlass.setLed(adresse, 3, 1, true);  //33
      break;

    case 45 :
      HourGlass.setLed(adresse, 6, 4, true);  //33
      break;

    case 46 :
      HourGlass.setLed(adresse, 7, 7, true);  //33
      break;

    case 47 :
      HourGlass.setLed(adresse, 4, 1, true);  //33
      break;

    case 48 :
      HourGlass.setLed(adresse, 7, 6, true);  //33
      break;

    case 49 :
      HourGlass.setLed(adresse, 5, 1, true);  //32
      break;

    case 50 :
      HourGlass.setLed(adresse, 6, 3, true);  //32
      break;

    case 51 :
      HourGlass.setLed(adresse, 6, 2, true);
      break;

    case 52 :
      HourGlass.setLed(adresse, 6, 1, true);
      break;

    case 53 :
      HourGlass.setLed(adresse, 7, 5, true);    //53
      break;

    case 54 :
      HourGlass.setLed(adresse, 1, 0, true);
      break;

    case 55 :
      HourGlass.setLed(adresse, 7, 4, true);
      break;

    case 56 :
      HourGlass.setLed(adresse, 2, 0, true);
      break;

    case 57 :
      HourGlass.setLed(adresse, 3, 0, true);
      break;

    case 58 :
      HourGlass.setLed(adresse, 7, 3, true);
      break;

    case 59 :
      HourGlass.setLed(adresse, 7, 2, true);
      break;

    case 60 :
      HourGlass.setLed(adresse, 4, 0, true);
      break;

    case 61 :
      HourGlass.setLed(adresse, 5, 0, true);
      break;

    case 62 :
      HourGlass.setLed(adresse, 7, 1, true);         //1
      break;

    case 63 :
      HourGlass.setLed(adresse, 6, 0, true);         //1
      break;

    case 64 :
      HourGlass.setLed(adresse, 7, 0, true);         //64
      break;
  }
}




