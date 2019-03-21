// ARDUINO CHESS/GO HOURGLASS

// Développé par David LE GALL 2017-2019
// Thank to Tatiana Grange fr her kind help on this project


//Principe de fonctionnement
// Le sablier permet de jouer à des jeux de société ou chacun des participants a une durée déterminée pour jouer la totalité de ses coups
// Chaque joueur retourne le sablier après avoir joué son coup.
// un TiltSwitch permet de savoir si le sablier est tête en haut ou en bas, c'est ce qui permet de passer la main
//

//Circuit Wiring
//
// 1 x TiltSwitch : pin10
// 2 x MAX 77219 8x8 Led Matrices
//        DataIn : pin 13
//        CLK : pin 11
//        LOAD : pin 12




//We always have to include the library
#include "LedControl.h"                        //Enables us to use the matrices
#include "HourglassAnimation.h"                //Contains the functions to display hourglass sand grains animations on the matrixes



// set pin numbers:
const int TiltSwitchPin = 10;                   // the number of the TiltSwitch pin
LedControl HourGlass = LedControl(13, 11, 12, 2); // Matrix 1 :  pin 13 is connected to the DataIn  pin 11 is connected to the CLK  pin 12 is connected to LOAD
HourglassAnimation hourglassanimation;          // Needed to call The HourGlassAnimation.cpp functions


int TiltSwitchState = 0;                        // The state of the TiltSwitch
int TopMatrixAddress = 1;                       // The Adress of the Matrix that is on top, this address will change as the hourglass is rotated
int BottomMatrixAddress = 0;

// Time Variables
int SelectedPlayTime = 0;                       //A counter that permits the user to select a preset time
int temps_propose[] = {900, 1800, 2700, 3600};  // Four different time presets (15, 30, 45 and 60 minutes)
unsigned long TotalTimeForEachPlayer = 0;       //Total amount of time for each player
unsigned long TimeAtStart = 0;                  //The time ( value of millis() ) when the first player makes his move
unsigned long TimeElapsedP1 = 0;                //Elapsed time for each player
unsigned long TimeElapsedP2 = 0;

bool ItsP1TurnToPlay = 0;                       // A boolean that can return 1 if it's Player 1's turn.
bool P1HasPlayedAtLeastOnce = 0;
bool P2HasPlayedAtLeastOnce = 0;



void setup() {


  pinMode(TiltSwitchPin, INPUT);// initialise TlitSwitch


  for (int address = 0; address < 2; address++) { // initialise Led Matrixes
    HourGlass.shutdown(address, false); /*The MAX72XX is in power-saving mode on startup*/
    HourGlass.setIntensity(address, 8); /* Set the brightness to a medium values */
    HourGlass.clearDisplay(address); /* and clear the display */
  }
  Serial.begin(9600);  // For debugging purposes

  InitialiseHourglass(); //See correponding function

}

void loop() {
  FindHourglassVerticalOrientation();                                    //Quite important, we don't want the SandGrains to fall torwards the sky.

  int CurrentPlayerTimeIndex = TimeIndex();                              // This local variable is used to know what time the current player has remaining, and to display the adequade animations
  hourglassanimation.DisplayStateAtTimeIndex ( CurrentPlayerTimeIndex, BottomMatrixAddress, TopMatrixAddress ); //Resumes the Hourglass display state, depending on the time index
  Serial.println(CurrentPlayerTimeIndex);
  if ( CurrentPlayerTimeIndex == 0 ) {                                   // In order for both players to know the system is working, the first SandGrain is forced to drop. But it might be that they both make a move before the second drops. So variables have to be used in order to know if it's their first move or not, so that the display behaves accordingly, otherwise they would see the first SandGrain drop everytime they flip the hourglass before the second grain hass dropped.

    if ( ItsP1TurnToPlay == digitalRead(TiltSwitchPin) && P1HasPlayedAtLeastOnce == 0 ) {
      delay (1000);
      hourglassanimation.RemoveSandGrain(1, TopMatrixAddress);             // These two lines describe the drop of the first SandGrain
      hourglassanimation.AddSandGrain(1, BottomMatrixAddress);
      P1HasPlayedAtLeastOnce = 1;
    } else if ( ItsP1TurnToPlay == digitalRead(TiltSwitchPin) && P1HasPlayedAtLeastOnce == 1 ) {
      hourglassanimation.DisplayStateAtTimeIndex ( 2, BottomMatrixAddress, TopMatrixAddress );   // If P1 has already played, the first grain has already fallen, no need to do it again.
    } else if ( ItsP1TurnToPlay != digitalRead(TiltSwitchPin) && P2HasPlayedAtLeastOnce == 0 ) {
      delay (1000);
      hourglassanimation.RemoveSandGrain(1, TopMatrixAddress);             // These two lines describe the drop of othe first SandGrain
      hourglassanimation.AddSandGrain(1, BottomMatrixAddress);
      P2HasPlayedAtLeastOnce = 1;
    } else if ( ItsP1TurnToPlay != digitalRead(TiltSwitchPin) && P2HasPlayedAtLeastOnce == 1 ) {
      hourglassanimation.DisplayStateAtTimeIndex ( 2, BottomMatrixAddress, TopMatrixAddress );
    }
    while (CurrentPlayerTimeIndex <= 1) {
      CurrentPlayerTimeIndex = TimeIndex();
      if (FindIfHourglassWasFlipped() == 1) break;                       // If the hourglass is flipped while we were waiting for time to pass, then it's the other player's turn.
      delay(10);
    }
  }

  while (FindIfHourglassWasFlipped() == 0) {                                       //As long as the hourglass is not flipped
    while (CurrentPlayerTimeIndex >= TimeIndex()) {                                //Wait for TimeIndex() to be greater than CurrentPlayerTimeIndex, that's to say, wait enough time for the next SandGrain Drop to trigger.
      if (FindIfHourglassWasFlipped() == 1) break;                                 // If the hourglass is flipped while we were waiting for time to pass, then it's the other player's turn.
      delay(15);
    }
    if (FindIfHourglassWasFlipped() == 1) break;                                   // If the hourglass is flipped while we were waiting for time to pass, then it's the other player's turn.
    hourglassanimation.RemoveSandGrain(CurrentPlayerTimeIndex, TopMatrixAddress);             // A sand grain is removed from the top matrix and added to the bottom matrix
    hourglassanimation.AddSandGrain(CurrentPlayerTimeIndex, BottomMatrixAddress);

    CurrentPlayerTimeIndex++;

    if (TimeElapsedP1 >= TotalTimeForEachPlayer || TimeElapsedP2 >= TotalTimeForEachPlayer ) {     // Checking that no player has run out of time.
      FindHourglassVerticalOrientation();                                                          // On vérifie dans quelle position est le sablier
      HourGlass.clearDisplay(TopMatrixAddress);
      for (int i = 0 ; i < 7; i++) {
        hourglassanimation.DisplayFilledMatrix(BottomMatrixAddress);                                  // Bottom matrix blinks to indicate time is out
        delay (500);
        HourGlass.clearDisplay(BottomMatrixAddress);
        delay(500);
      }
      InitialiseHourglass();                                                 // After that, the system is re-initialized
    }
  }

}

void InitialiseHourglass() {

  FindHourglassVerticalOrientation();                          // permet de savoir dans quelle position est le sablier

  hourglassanimation.DisplayFilledMatrix(BottomMatrixAddress);             // On commence avec la matrice du bas remplie, ca donne envie de le retourner

  //while (FindIfHourglassWasFlipped() == 0 ) {                // Wait for the hourglass to be flipped.
  //  delay(5);
  // }

  TotalTimeForEachPlayer = temps_propose[TimeSelecter()];    // Launches the TimeSelecter Function

  ItsP1TurnToPlay = digitalRead(TiltSwitchPin);              // First player to flip the Hourglass is called Player 1
  TimeAtStart = millis();                                    // Resets the Starting point of time count
  TimeElapsedP1 = 0;                                         // Resets both player's elapsed playing time
  TimeElapsedP2 = 0;

}


int TimeSelecter() {                                              // This time selecter works on the basis of morse code, the user can make a long or short press on a button (here, the tiltswitch) to decrease or increase a counter that controls the amount of time the hourglass will keep track of.

  unsigned long TimeAtPress = 0;                                  // a variable where to store the time at which the button is pressed
  unsigned long TimeAtRelease = 0;                                // a variable where to store the time at which the button is realeased
  int TimeSelecterCounter = 0;                                    // a counter that will be incremented or decremented
  const int TimeShortPress = 500;                                 // between 0 and 500ms the press will be considered a short or quick press
  const int TimeLongPress = TimeShortPress * 6;                   // between 0 and 500ms the press will be considered a long press
  int TimePressed = 0;
  bool TimeHasBeenSelected = 0 ;


  hourglassanimation.DisplayTimeMenu(TimeSelecterCounter, TopMatrixAddress); // Show the first time selection

  while (TimeHasBeenSelected == 0) {

    if (FindIfHourglassWasFlipped() == 1) {                     //Check if the pushbutton is pressed.if it is, the TiltSwitchState is HIGH:

      TimeAtPress = millis();                                   //Memorise when the button was pressed

      while (FindIfHourglassWasFlipped() == 1) {                //infinite loop while the button is pressed
        Serial.println("Waiting for button to be released");    //for debugging purposes, when this is displayed, the code is waiting for you to release the button
        TimePressed = millis() - TimeAtPress ;                  //Calculate Elapsed Time
        if (TimePressed > TimeLongPress )                       //If the pressed time is superior to a certain amount, we consider time has been selected and move on.
        {
          Serial.println("Waited too long");
          TimeHasBeenSelected = 1;
          break;
        }

        delay(200);                                              // delay introduced to avoid detecting rebounds of the marble in the TiltSwitch as increments of the counter
      }
      Serial.println("Button released");
      if (TimePressed <= TimeShortPress )                         //first, check if the time was shorter than a ShortPress
      {
        TimeSelecterCounter = TimeSelecterCounter + 1;            // if so, counter goes up
      }

      else if ( TimePressed <= TimeLongPress)                     //then, check if the time was less than a LongPress
      {
        TimeSelecterCounter = TimeSelecterCounter - 1 ;           // if so, counter goes down
      }


      if (TimeSelecterCounter < 0 )                               //Checking that the TimeSelecterCounter hasn't got a negative or too high value
      {
        TimeSelecterCounter = 0;
      }
      else if (TimeSelecterCounter > 3 )
      {
        TimeSelecterCounter = 3;
      }

      hourglassanimation.DisplayTimeMenu(TimeSelecterCounter, TopMatrixAddress);  // Displays an time menu that corresponds to the time counter, so that the user has a feedback
      Serial.println(TimeSelecterCounter);
    }

  }
  hourglassanimation.TimeMenuIconsDisappearingAnimation(TimeSelecterCounter, TopMatrixAddress);
  return TimeSelecterCounter;
}

void FindHourglassVerticalOrientation() {
  // Déterminer la position du sablier pour afficher dans le bon sens

  // read the state of the TiltSwitch value:
  TiltSwitchState = digitalRead(TiltSwitchPin);

  // check if the tiltswitch is pressed.
  // if it is, the TiltSwitchState is HIGH:

  if (TiltSwitchState == HIGH) {
    TopMatrixAddress = 0;
    BottomMatrixAddress = 1;
  } else {
    TopMatrixAddress = 1;
    BottomMatrixAddress = 0;
  }
}

bool FindIfHourglassWasFlipped() {
  if (TiltSwitchState == digitalRead(TiltSwitchPin)) {
    return 0;
  }
  else {
    return 1;
  }
}



int TimeIndex() {
  if (ItsP1TurnToPlay == digitalRead(TiltSwitchPin)) {                             // Depending on whose turn it is, ElapsedTime is updated
    TimeElapsedP1 = (millis() - TimeAtStart) / 1000 - TimeElapsedP2 ;              // This is quite tricky, i suggest you make a drawing if you don't understand.
    return  (TimeElapsedP1 * 65) / TotalTimeForEachPlayer ;                         // Time index is calculated as a fraction of the 64 leds of the matrix, with one more in order for the last few SandGrains to drop properly, the thing is divided by 65 in order for

  } else {
    TimeElapsedP2 = (millis() - TimeAtStart) / 1000 - TimeElapsedP1 ;
    return (TimeElapsedP2 * 65) / TotalTimeForEachPlayer ;
  }
}




