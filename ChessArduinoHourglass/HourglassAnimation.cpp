#include "LedControl.h"
#include "HourglassAnimation.h"


void HourglassAnimation::TimeMenuIcons(int TimeSelecter, int address) {
  switch (TimeSelecter) {
    case 0:                                     //15min
      HourGlass.setLed(address, 0, 0, true);
      HourGlass.setLed(address, 0, 1, true);
      HourGlass.setLed(address, 0, 2, true);
      HourGlass.setLed(address, 0, 3, true);
      HourGlass.setLed(address, 1, 0, true);
      HourGlass.setLed(address, 2, 0, true);
      HourGlass.setLed(address, 3, 0, true);
      break;

    case 1:                                     //30min
      HourGlass.setLed(address, 0, 4, true);
      HourGlass.setLed(address, 0, 5, true);
      HourGlass.setLed(address, 0, 6, true);
      HourGlass.setLed(address, 0, 7, true);
      HourGlass.setLed(address, 1, 7, true);
      HourGlass.setLed(address, 2, 7, true);
      HourGlass.setLed(address, 3, 7, true);
      break;

    case 2:                                     //45min
      HourGlass.setLed(address, 4, 7, true);
      HourGlass.setLed(address, 5, 7, true);
      HourGlass.setLed(address, 6, 7, true);
      HourGlass.setLed(address, 7, 7, true);
      HourGlass.setLed(address, 7, 6, true);
      HourGlass.setLed(address, 7, 5, true);
      HourGlass.setLed(address, 7, 4, true);
      break;

    case 3:                                     //60min
      HourGlass.setLed(address, 7, 3, true);
      HourGlass.setLed(address, 7, 2, true);
      HourGlass.setLed(address, 7, 1, true);
      HourGlass.setLed(address, 7, 0, true);
      HourGlass.setLed(address, 6, 0, true);
      HourGlass.setLed(address, 5, 0, true);
      HourGlass.setLed(address, 4, 0, true);
      break;
  }
}

void HourglassAnimation::DisplayTimeMenu(int TimeSelecter, int address) {
  HourGlass.clearDisplay(address);
  for (int i = 0; i <= TimeSelecter; i++) {
    TimeMenuIcons(i, address);
  }
}

void HourglassAnimation::TimeMenuIconsDisappearingAnimationFrames(int TimeSelecter, int FrameNumber, int address) {
  switch (TimeSelecter) {
    case 0:                                     //15min
      switch (FrameNumber) {
        case 0:

          HourGlass.setLed(address, 0, 0, true);
          HourGlass.setLed(address, 0, 1, true);
          HourGlass.setLed(address, 0, 2, true);
          HourGlass.setLed(address, 0, 3, true);
          HourGlass.setLed(address, 1, 0, true);
          HourGlass.setLed(address, 2, 0, true);
          HourGlass.setLed(address, 3, 0, true);
          break;

        case 1:

          HourGlass.setLed(address, 1, 1, true);
          HourGlass.setLed(address, 1, 2, true);
          HourGlass.setLed(address, 1, 3, true);
          HourGlass.setLed(address, 2, 1, true);
          HourGlass.setLed(address, 3, 1, true);
          break;

        case 2:

          HourGlass.setLed(address, 2, 2, true);
          HourGlass.setLed(address, 2, 3, true);
          HourGlass.setLed(address, 3, 2, true);
          break;

        case 3:

          HourGlass.setLed(address, 3, 3, true);
          break;
      }
      break;


    case 1:                                     //30min
      switch (FrameNumber) {
        case 0:

          HourGlass.setLed(address, 0, 4, true);
          HourGlass.setLed(address, 0, 5, true);
          HourGlass.setLed(address, 0, 6, true);
          HourGlass.setLed(address, 0, 7, true);
          HourGlass.setLed(address, 1, 7, true);
          HourGlass.setLed(address, 2, 7, true);
          HourGlass.setLed(address, 3, 7, true);
          break;

        case 1:

          HourGlass.setLed(address, 1, 4, true);
          HourGlass.setLed(address, 1, 5, true);
          HourGlass.setLed(address, 1, 6, true);
          HourGlass.setLed(address, 2, 6, true);
          HourGlass.setLed(address, 3, 6, true);
          break;

        case 2:

          HourGlass.setLed(address, 2, 5, true);
          HourGlass.setLed(address, 2, 4, true);
          HourGlass.setLed(address, 3, 5, true);
          break;

        case 3:

          HourGlass.setLed(address, 3, 4, true);
          break;
      }
      break;

    case 2:                                     //45min
      switch (FrameNumber) {
        case 0:

          HourGlass.setLed(address, 4, 7, true);
          HourGlass.setLed(address, 5, 7, true);
          HourGlass.setLed(address, 6, 7, true);
          HourGlass.setLed(address, 7, 7, true);
          HourGlass.setLed(address, 7, 6, true);
          HourGlass.setLed(address, 7, 5, true);
          HourGlass.setLed(address, 7, 4, true);
          break;

        case 1:

          HourGlass.setLed(address, 6, 6, true);
          HourGlass.setLed(address, 6, 4, true);
          HourGlass.setLed(address, 6, 5, true);
          HourGlass.setLed(address, 5, 6, true);
          HourGlass.setLed(address, 4, 6, true);
          break;

        case 2:

          HourGlass.setLed(address, 5, 5, true);
          HourGlass.setLed(address, 5, 4, true);
          HourGlass.setLed(address, 4, 5, true);
          break;

        case 3:

          HourGlass.setLed(address, 4, 4, true);
          break;
      }
      break;

    case 3:                                     //60min
      switch (FrameNumber) {
        case 0:

          HourGlass.setLed(address, 7, 3, true);
          HourGlass.setLed(address, 7, 2, true);
          HourGlass.setLed(address, 7, 1, true);
          HourGlass.setLed(address, 7, 0, true);
          HourGlass.setLed(address, 6, 0, true);
          HourGlass.setLed(address, 5, 0, true);
          HourGlass.setLed(address, 4, 0, true);
          break;

        case 1:

          HourGlass.setLed(address, 4, 1, true);
          HourGlass.setLed(address, 5, 1, true);
          HourGlass.setLed(address, 6, 1, true);
          HourGlass.setLed(address, 6, 2, true);
          HourGlass.setLed(address, 6, 3, true);
          break;

        case 2:

          HourGlass.setLed(address, 5, 2, true);
          HourGlass.setLed(address, 4, 2, true);
          HourGlass.setLed(address, 5, 3, true);
          break;

        case 3:

          HourGlass.setLed(address, 4, 3, true);
          break;
      }
      break;
  }
}

void HourglassAnimation::TimeMenuIconsDisappearingAnimation(int TimeSelecter, int address) {
  HourGlass.clearDisplay(address);
  for (int i = 1; i <= 3; i++) {            // For i frames
    for (int j = 0; j <= TimeSelecter; j++) {          // Play the j animated corresponding frames
      TimeMenuIconsDisappearingAnimationFrames(j, i ,address);
      
    }
    delay(TimeMenuIconsDisappearingAnimationDelayTime);
    HourGlass.clearDisplay(address);
  }
}

void HourglassAnimation::DisplayFilledMatrix(int address) {
  for (int i = 0; i <= 7; i++) {
    for (int j = 0; j <= 7; j++) {
      HourGlass.setLed(address, j, i, true);
    }
    //HourGlass.setColumn(address, i); //Alternative Method, but doesn't compile for some reason.
  }
}



void HourglassAnimation::SandGrainFallingAnimation(int limite, int address) {
  for (int i = 0; i < limite; i++) { // Boucle qui décrit la diagonale descendante de M1
    HourGlass.setLed(address, 7 - i, i, true);
    delay(AnimationDelayTime);
    HourGlass.setLed(address, 7 - i, i, false);
  }
}

void HourglassAnimation::AddSandGrain(int TimeIndex, int address) {

  // la matrice fait 64 Leds, on a une animation pour chacune de ces 64 Leds, la variable etat de remplissage permet de choisir quelle animation on veut.

  switch (TimeIndex) {
    case 1:
      SandGrainFallingAnimation(8, address);

      HourGlass.setLed(address, 0, 7, true);         //1

      break;

    case 2:
      SandGrainFallingAnimation(7, address);

      // Ligne 2
      HourGlass.setLed(address, 1, 7, true);         //2

      break;

    case 3:
      SandGrainFallingAnimation(7, address);

      HourGlass.setLed(address, 0, 6, true);         //3

      break;

    case 4:
      SandGrainFallingAnimation(6, address);

      //Ligne 3
      HourGlass.setLed(address, 1, 6, true);         //4

      break;

    case 5:
      SandGrainFallingAnimation(6, address);

      //Anim 5
      HourGlass.setLed(address, 1, 5, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 1, 5, false);

      HourGlass.setLed(address, 0, 5, true);         //5

      break;

    case 6:
      SandGrainFallingAnimation(6, address);

      //Anim 6
      HourGlass.setLed(address, 2, 6, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 2, 6, false);

      HourGlass.setLed(address, 2, 7, true);        //6
      break;

    case 7:
      //Ligne 4

      SandGrainFallingAnimation(6, address);

      HourGlass.setLed(address, 1, 5, true);          //7
      break;

    case 8:
      SandGrainFallingAnimation(6, address);
      HourGlass.setLed(address, 2, 6, true);           //8
      break;

    case 9:
      SandGrainFallingAnimation(5, address);
      HourGlass.setLed(address, 2, 5, true);           //9
      break;

    case 10:
      SandGrainFallingAnimation(5, address);
      HourGlass.setLed(address, 3, 5, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 3, 5, false);

      HourGlass.setLed(address, 3, 6, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 3, 6, false);

      HourGlass.setLed(address, 3, 7, true);             //10
      break;

    case 11:
      SandGrainFallingAnimation(5, address);

      for (int i = 0; i < 3; i++) { // Anim 11
        HourGlass.setLed(address, 2 - i, 4, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 2 - i, 4, false);
      }

      HourGlass.setLed(address, 0, 4, true);           //11
      break;

    case 12:
      SandGrainFallingAnimation(5, address);

      for (int i = 0; i < 2; i++) { // Anim 11
        HourGlass.setLed(address, 2 - i, 4, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 2 - i, 4, false);
      }

      HourGlass.setLed(address, 1, 4, true);            //12
      break;

    case 13:
      SandGrainFallingAnimation(5, address);

      for (int i = 0; i < 2; i++) { // Anim 13
        HourGlass.setLed(address, 3, 5 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 3, 5 + i, false);
      }

      HourGlass.setLed(address, 3, 6, true);       //13
      break;


    case 14 :
      SandGrainFallingAnimation(5, address);

      HourGlass.setLed(address, 3, 5, true);       //14
      break;

    case 15 :
      SandGrainFallingAnimation(5, address);

      HourGlass.setLed(address, 2, 4, true);         //15
      break;

    case 16 :
      SandGrainFallingAnimation(4, address);

      HourGlass.setLed(address, 3, 4, true);         //16
      break;


    case 17 :
      SandGrainFallingAnimation(4, address);

      for (int i = 0; i < 4; i++) { // Anim 17
        HourGlass.setLed(address, 3 - i, 3, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 3 - i, 3, false);
      }

      HourGlass.setLed(address, 0, 3, true);         //17
      break;


    case 18 :
      SandGrainFallingAnimation(4, address);

      for (int i = 0; i < 3; i++) { // Anim 18
        HourGlass.setLed(address, 4, 4 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 4, 4 + i, false);
      }

      HourGlass.setLed(address, 4, 7, true);         //18
      break;


    case 19 :
      SandGrainFallingAnimation(3, address);

      for (int i = 0; i < 3; i++) { // Anim 18
        HourGlass.setLed(address, 4 - i, 3, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 4 - i, 3, false);
      }

      HourGlass.setLed(address, 1, 3, true);     //19
      break;

    case 20 :

      SandGrainFallingAnimation(3, address);

      for (int i = 0; i < 3; i++) { // Anim 18
        HourGlass.setLed(address, 4, 4 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 4, 4 + i, false);
      }


      HourGlass.setLed(address, 4, 6, true);  //20
      break;

    case 21 :
      SandGrainFallingAnimation(3, address);

      for (int i = 0; i < 2; i++) { // Anim 18
        HourGlass.setLed(address, 4, 4 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 4, 4 + i, false);
      }
      HourGlass.setLed(address, 5, 6, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 5, 6, false);

      HourGlass.setLed(address, 5, 7, true);  //21
      break;

    case 22 :
      SandGrainFallingAnimation(3, address);

      // Anim 22
      HourGlass.setLed(address, 3, 3, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 3, 3, false);

      HourGlass.setLed(address, 2, 3, true);       //22
      break;

    case 23 :
      SandGrainFallingAnimation(3, address);

      // Anim 22
      HourGlass.setLed(address, 3, 3, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 3, 3, false);

      for (int i = 0; i < 3; i++) { // Anim 18
        HourGlass.setLed(address, 3 - i, 2, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 3 - i, 2, false);
      }

      HourGlass.setLed(address, 0, 2, true);       //23
      break;

    case 24 :
      SandGrainFallingAnimation(3, address);
      delay(AnimationDelayTime);
      // Anim 22
      HourGlass.setLed(address, 3, 3, true);
      break;

    case 25 :
      SandGrainFallingAnimation(3, address);

      // Anim 25
      HourGlass.setLed(address, 4, 4, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 4, 4, false);

      HourGlass.setLed(address, 4, 5, true);       //25
      break;

    case 26 :
      SandGrainFallingAnimation(3, address);

      // Anim 25
      HourGlass.setLed(address, 4, 4, true);
      break;

    case 27 :
      SandGrainFallingAnimation(2, address);
      HourGlass.setLed(address, 4, 3, true);
      break;

    case 28 :
      SandGrainFallingAnimation(2, address);

      for (int i = 0; i < 4; i++) { // Anim 18
        HourGlass.setLed(address, 5, 3 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 5, 3 + i, false);
      }

      HourGlass.setLed(address, 5, 6, true);  //28
      break;

    case 29 :
      SandGrainFallingAnimation(2, address);

      for (int i = 0; i < 3; i++) { // Anim 18
        HourGlass.setLed(address, 5, 3 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 5, 3 + i, false);
      }

      HourGlass.setLed(address, 5, 5, true);  //29
      break;

    case 30 :
      SandGrainFallingAnimation(2, address);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(address, 4 - i, 2, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 4 - i, 2, false);
      }

      HourGlass.setLed(address, 1, 2, true);  //30
      break;

    case 31 :
      SandGrainFallingAnimation(2, address);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(address, 4 - i, 2, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 4 - i, 2, false);
      }
      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(address, 2 - i, 1, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 2 - i, 1, false);
      }

      HourGlass.setLed(address, 0, 1, true);  //31
      break;

    case 32 :
      SandGrainFallingAnimation(2, address);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(address, 4 - i, 2, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 4 - i, 2, false);
      }

      HourGlass.setLed(address, 2, 2, true);  //32
      break;

    case 33 :
      SandGrainFallingAnimation(2, address);

      // Anim 33
      HourGlass.setLed(address, 5, 3, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 5, 3, false);

      HourGlass.setLed(address, 5, 4, true);  //33
      break;

    case 34 :
      SandGrainFallingAnimation(2, address);

      // Anim 33
      HourGlass.setLed(address, 5, 3, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 5, 3, false);

      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(address, 6, 4 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 6, 4 + i, false);
      }
      HourGlass.setLed(address, 6, 7, true);  //33
      break;

    case 35 :
      SandGrainFallingAnimation(2, address);

      // Anim 33
      HourGlass.setLed(address, 5, 3, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 5, 3, false);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(address, 6, 4 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 6, 4 + i, false);
      }
      HourGlass.setLed(address, 6, 6, true);  //33
      break;

    case 36 :
      SandGrainFallingAnimation(2, address);

      for (int i = 0; i < 1; i++) { // Anim 30
        HourGlass.setLed(address, 4 - i, 2, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 4 - i, 2, false);
      }

      HourGlass.setLed(address, 3, 2, true);  //32
      break;

    case 37 :
      SandGrainFallingAnimation(2, address);

      HourGlass.setLed(address, 5, 3, true);  //32
      break;

    case 38 :
      SandGrainFallingAnimation(2, address);

      HourGlass.setLed(address, 4, 2, true);  //32
      break;

    case 39 :
      SandGrainFallingAnimation(1, address);

      HourGlass.setLed(address, 5, 2, true);  //32
      break;

    case 40 :
      SandGrainFallingAnimation(1, address);

      for (int i = 0; i < 4; i++) { // Anim 30
        HourGlass.setLed(address, 6, 2 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 6, 2 + i, false);
      }

      HourGlass.setLed(address, 6, 5, true);  //33
      break;

    case 41 :
      SandGrainFallingAnimation(2, address);

      for (int i = 0; i < 4; i++) { // Anim 30
        HourGlass.setLed(address, 5 - i, 1, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 5 - i, 1, false);
      }

      HourGlass.setLed(address, 1, 1, true);  //41
      break;

    case 42 :
      SandGrainFallingAnimation(1, address);

      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(address, 5 - i, 1, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 5 - i, 1, false);
      }

      HourGlass.setLed(address, 2, 1, true);  //33
      break;

    case 43 :
      SandGrainFallingAnimation(1, address);

      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(address, 5 - i, 1, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 5 - i, 1, false);
      }

      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(address, 3 - i, 0, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 3 - i, 0, false);
      }

      HourGlass.setLed(address, 0, 0, true);  //33
      break;

    case 44 :
      SandGrainFallingAnimation(1, address);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(address, 5 - i, 1, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 5 - i, 1, false);
      }

      HourGlass.setLed(address, 3, 1, true);  //33
      break;

    case 45 :
      SandGrainFallingAnimation(1, address);

      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(address, 6, 2 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 6, 2 + i, false);
      }

      HourGlass.setLed(address, 6, 4, true);  //33
      break;

    case 46 :
      SandGrainFallingAnimation(1, address);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(address, 6, 2 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 6, 2 + i, false);
      }

      for (int i = 0; i < 4; i++) { // Anim 30
        HourGlass.setLed(address, 7, 3 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 7, 3 + i, false);
      }

      HourGlass.setLed(address, 7, 7, true);  //33
      break;

    case 47 :
      SandGrainFallingAnimation(1, address);

      for (int i = 0; i < 1; i++) { // Anim 30
        HourGlass.setLed(address, 5 - i, 1, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 5 - i, 1, false);
      }

      HourGlass.setLed(address, 4, 1, true);  //33
      break;

    case 48 :
      SandGrainFallingAnimation(1, address);

      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(address, 6, 2 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 6, 2 + i, false);
      }

      for (int i = 0; i < 4; i++) { // Anim 30
        HourGlass.setLed(address, 7, 3 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 7, 3 + i, false);
      }

      HourGlass.setLed(address, 7, 6, true);  //33
      break;

    case 49 :
      SandGrainFallingAnimation(1, address);

      HourGlass.setLed(address, 5, 1, true);  //32
      break;

    case 50 :
      SandGrainFallingAnimation(1, address);

      HourGlass.setLed(address, 6, 2, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 6, 2, false);

      HourGlass.setLed(address, 6, 3, true);  //32
      break;

    case 51 :
      SandGrainFallingAnimation(1, address);

      HourGlass.setLed(address, 6, 2, true);
      break;

    case 52 :
      HourGlass.setLed(address, 7, 0, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 7, 0, false);

      HourGlass.setLed(address, 6, 1, true);
      break;

    case 53 :
      for (int i = 0; i < 4; i++) { // Anim 30
        HourGlass.setLed(address, 7, 0 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 7, 0 + i, false);
      }

      HourGlass.setLed(address, 7, 5, true);    //53
      break;

    case 54 :
      for (int i = 0; i < 6; i++) { // Anim 30
        HourGlass.setLed(address, 7 - i, 0, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 7 - i, 0, false);
      }

      HourGlass.setLed(address, 1, 0, true);
      break;

    case 55 :
      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(address, 7, 0 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 7, 0 + i, false);
      }

      HourGlass.setLed(address, 7, 4, true);
      break;

    case 56 :
      for (int i = 0; i < 5; i++) { // Anim 30
        HourGlass.setLed(address, 7 - i, 0, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 7 - i, 0, false);
      }

      HourGlass.setLed(address, 2, 0, true);
      break;

    case 57 :
      for (int i = 0; i < 4; i++) { // Anim 30
        HourGlass.setLed(address, 7 - i, 0, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 7 - i, 0, false);
      }

      HourGlass.setLed(address, 3, 0, true);
      break;

    case 58 :
      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(address, 7, 0 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 7, 0 + i, false);
      }

      HourGlass.setLed(address, 7, 3, true);
      break;

    case 59 :
      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(address, 7, 0 + i, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 7, 0 + i, false);
      }

      HourGlass.setLed(address, 7, 2, true);
      break;

    case 60 :
      for (int i = 0; i < 3; i++) { // Anim 30
        HourGlass.setLed(address, 7 - i, 0, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 7 - i, 0, false);
      }

      HourGlass.setLed(address, 4, 0, true);
      break;

    case 61 :
      for (int i = 0; i < 2; i++) { // Anim 30
        HourGlass.setLed(address, 7 - i, 0, true);
        delay(AnimationDelayTime);
        HourGlass.setLed(address, 7 - i, 0, false);
      }

      HourGlass.setLed(address, 5, 0, true);
      break;

    case 62 :
      HourGlass.setLed(address, 7, 0, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 7, 0, false);

      HourGlass.setLed(address, 7, 1, true);         //1
      break;

    case 63 :
      HourGlass.setLed(address, 7, 0, true);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 7, 0, false);

      HourGlass.setLed(address, 6, 0, true);         //1
      break;

    case 64 :
      HourGlass.setLed(address, 7, 0, true);         //64
      break;
  }
}

void HourglassAnimation::RemoveSandGrain(int TimeIndex, int address) {

  switch (TimeIndex) {
    case 1:
      HourGlass.setLed(address, 0, 7, false);
      break;

    case 2:
      HourGlass.setLed(address, 1, 7, false);
      break;

    case 3:
      HourGlass.setLed(address, 0, 6, false);
      break;

    case 4:
      HourGlass.setLed(address, 1, 6, false);
      break;

    case 5:
      HourGlass.setLed(address, 2, 7, false);
      break;

    case 6:
      HourGlass.setLed(address, 0, 5, false);
      break;

    case 7:
      HourGlass.setLed(address, 1, 5, false);
      break;

    case 8:
      HourGlass.setLed(address, 2, 6, false);
      break;

    case 9:
      HourGlass.setLed(address, 0, 4, false);
      break;

    case 10:
      HourGlass.setLed(address, 2, 4, false);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 1, 4, false);
      HourGlass.setLed(address, 2, 4, true);
      break;

    case 11:
      HourGlass.setLed(address, 3, 7, false);
      break;

    case 12:
      HourGlass.setLed(address, 2, 5, false);
      break;

    case 13:
      HourGlass.setLed(address, 3, 6, false);
      break;

    case 14:
      HourGlass.setLed(address, 3, 5, false); // doublon
      break;

    case 15:
      HourGlass.setLed(address, 0, 3, false);
      break;

    case 16:
      HourGlass.setLed(address, 2, 4, false);
      break;

    case 17:
      HourGlass.setLed(address, 4, 7, false);
      break;

    case 18:
      HourGlass.setLed(address, 1, 3, false);
      break;

    case 19:
      HourGlass.setLed(address, 5, 7, false);
      break;

    case 20:
      HourGlass.setLed(address, 5, 6, false);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 4, 6, false);
      HourGlass.setLed(address, 5, 6, true);
      break;

    case 21:
      HourGlass.setLed(address, 3, 4, false);
      break;

    case 22:
      HourGlass.setLed(address, 5, 6, false);
      break;

    case 23:
      HourGlass.setLed(address, 4, 5, false); /// attention, stop relecture ici, décalage car doublon avec cas 17
      break;

    case 24:
      HourGlass.setLed(address, 2, 3, false);
      break;

    case 25:
      HourGlass.setLed(address, 0, 2, false);
      break;

    case 26:
      HourGlass.setLed(address, 6, 7, false);
      break;

    case 27:
      HourGlass.setLed(address, 1, 2, false);
      break;

    case 28:
      HourGlass.setLed(address, 4, 4, false);
      break;

    case 29:
      HourGlass.setLed(address, 3, 3, false);
      break;

    case 30:
      HourGlass.setLed(address, 4, 3, false);
      break;

    case 31:
      HourGlass.setLed(address, 5, 5, false);
      break;

    case 32:
      HourGlass.setLed(address, 5, 4, false);
      break;

    case 33:
      HourGlass.setLed(address, 2, 2, false);
      break;

    case 34:
      HourGlass.setLed(address, 0, 1, false);
      break;

    case 35:
      HourGlass.setLed(address, 6, 6, false);
      break;

    case 36:
      HourGlass.setLed(address, 1, 1, false);
      break;

    case 37:
      HourGlass.setLed(address, 3, 2, false); //
      break;

    case 38:
      HourGlass.setLed(address, 7, 7, false);
      break;

    case 39:
      HourGlass.setLed(address, 0, 0, false);
      break;

    case 40:
      HourGlass.setLed(address, 1, 0, false); //
      break;

    case 41:
      HourGlass.setLed(address, 2, 1, false); //
      break;

    case 42:
      HourGlass.setLed(address, 6, 5, false); //Probleme : déja fait
      break;

    case 43:
      HourGlass.setLed(address, 7, 6, false);
      break;

    case 44:
      HourGlass.setLed(address, 5, 3, false); // deja fait
      break;

    case 45:
      HourGlass.setLed(address, 4, 2, false);
      break;

    case 46:
      HourGlass.setLed(address, 6, 4, false);
      break;

    case 47:
      HourGlass.setLed(address, 3, 1, false); //
      break;

    case 48:
      HourGlass.setLed(address, 7, 5, false); //
      break;

    case 49:
      HourGlass.setLed(address, 2, 0, false);
      break;

    case 50:
      HourGlass.setLed(address, 5, 2, false);
      break;

    case 51:
      HourGlass.setLed(address, 7, 4, false);
      break;

    case 52:
      HourGlass.setLed(address, 6, 3, false);
      break;

    case 53:
      HourGlass.setLed(address, 3, 0, false);
      break;

    case 54:
      HourGlass.setLed(address, 5, 1, false);
      delay(AnimationDelayTime);
      HourGlass.setLed(address, 4, 1, false);
      HourGlass.setLed(address, 5, 1, true);
      break;

    case 55:
      HourGlass.setLed(address, 4, 0, false);
      break;

    case 56:
      HourGlass.setLed(address, 7, 3, false);
      break;

    case 57:
      HourGlass.setLed(address, 5, 1, false);
      break;

    case 58:
      HourGlass.setLed(address, 6, 2, false);
      break;

    case 59:
      HourGlass.setLed(address, 5, 0, false);
      break;

    case 60:
      HourGlass.setLed(address, 7, 2, false);
      break;

    case 61:
      HourGlass.setLed(address, 6, 1, false);
      break;

    case 62:
      HourGlass.setLed(address, 6, 0, false);
      break;

    case 63:
      HourGlass.setLed(address, 7, 1, false);
      break;

    case 64:
      HourGlass.setLed(address, 7, 0, false);
      break;


  }
}




void HourglassAnimation::TopMatrixSandGrainPosition(int TimeIndex, int address) {

  switch (TimeIndex) {
    case 1:
      HourGlass.setLed(address, 0, 7, false);
      break;

    case 2:
      HourGlass.setLed(address, 1, 7, false);
      break;

    case 3:
      HourGlass.setLed(address, 0, 6, false);
      break;

    case 4:
      HourGlass.setLed(address, 1, 6, false);
      break;

    case 5:
      HourGlass.setLed(address, 2, 7, false);
      break;

    case 6:
      HourGlass.setLed(address, 0, 5, false);
      break;

    case 7:
      HourGlass.setLed(address, 1, 5, false);
      break;

    case 8:
      HourGlass.setLed(address, 2, 6, false);
      break;

    case 9:
      HourGlass.setLed(address, 0, 4, false);
      break;

    case 10:
      HourGlass.setLed(address, 1, 4, false); // Changé 2.4 true en 1.4 false
      break;

    case 11:
      HourGlass.setLed(address, 3, 7, false);
      break;

    case 12:
      HourGlass.setLed(address, 2, 5, false);
      break;

    case 13:
      HourGlass.setLed(address, 3, 6, false);
      break;

    case 14:
      HourGlass.setLed(address, 3, 5, false); // doublon
      break;

    case 15:
      HourGlass.setLed(address, 0, 3, false);
      break;

    case 16:
      HourGlass.setLed(address, 2, 4, false);
      break;

    case 17:
      HourGlass.setLed(address, 4, 7, false);
      break;

    case 18:
      HourGlass.setLed(address, 1, 3, false);
      break;

    case 19:
      HourGlass.setLed(address, 5, 7, false);
      break;

    case 20:
      HourGlass.setLed(address, 4, 6, false); // Changé 5,6 True en 4,6 false
      break;

    case 21:
      HourGlass.setLed(address, 3, 4, false);
      break;

    case 22:
      HourGlass.setLed(address, 5, 6, false);
      break;

    case 23:
      HourGlass.setLed(address, 4, 5, false); /// attention, stop relecture ici, décalage car doublon avec cas 17
      break;

    case 24:
      HourGlass.setLed(address, 2, 3, false);
      break;

    case 25:
      HourGlass.setLed(address, 0, 2, false);
      break;

    case 26:
      HourGlass.setLed(address, 6, 7, false);
      break;

    case 27:
      HourGlass.setLed(address, 1, 2, false);
      break;

    case 28:
      HourGlass.setLed(address, 4, 4, false);
      break;

    case 29:
      HourGlass.setLed(address, 3, 3, false);
      break;

    case 30:
      HourGlass.setLed(address, 4, 3, false);
      break;

    case 31:
      HourGlass.setLed(address, 5, 5, false);
      break;

    case 32:
      HourGlass.setLed(address, 5, 4, false);
      break;

    case 33:
      HourGlass.setLed(address, 2, 2, false);
      break;

    case 34:
      HourGlass.setLed(address, 0, 1, false);
      break;

    case 35:
      HourGlass.setLed(address, 6, 6, false);
      break;

    case 36:
      HourGlass.setLed(address, 1, 1, false);
      break;

    case 37:
      HourGlass.setLed(address, 3, 2, false); //
      break;

    case 38:
      HourGlass.setLed(address, 7, 7, false);
      break;

    case 39:
      HourGlass.setLed(address, 0, 0, false);
      break;

    case 40:
      HourGlass.setLed(address, 1, 0, false); //
      break;

    case 41:
      HourGlass.setLed(address, 2, 1, false); //
      break;

    case 42:
      HourGlass.setLed(address, 6, 5, false); //Probleme : déja fait
      break;

    case 43:
      HourGlass.setLed(address, 7, 6, false);
      break;

    case 44:
      HourGlass.setLed(address, 5, 3, false); // deja fait
      break;

    case 45:
      HourGlass.setLed(address, 4, 2, false);
      break;

    case 46:
      HourGlass.setLed(address, 6, 4, false);
      break;

    case 47:
      HourGlass.setLed(address, 3, 1, false); //
      break;

    case 48:
      HourGlass.setLed(address, 7, 5, false); //
      break;

    case 49:
      HourGlass.setLed(address, 2, 0, false);
      break;

    case 50:
      HourGlass.setLed(address, 5, 2, false);
      break;

    case 51:
      HourGlass.setLed(address, 7, 4, false);
      break;

    case 52:
      HourGlass.setLed(address, 6, 3, false);
      break;

    case 53:
      HourGlass.setLed(address, 3, 0, false);
      break;

    case 54:
      HourGlass.setLed(address, 5, 1, true);
      break;

    case 55:
      HourGlass.setLed(address, 4, 0, false);
      break;

    case 56:
      HourGlass.setLed(address, 7, 3, false);
      break;

    case 57:
      HourGlass.setLed(address, 5, 1, false);
      break;

    case 58:
      HourGlass.setLed(address, 6, 2, false);
      break;

    case 59:
      HourGlass.setLed(address, 5, 0, false);
      break;

    case 60:
      HourGlass.setLed(address, 7, 2, false);
      break;

    case 61:
      HourGlass.setLed(address, 6, 1, false);
      break;

    case 62:
      HourGlass.setLed(address, 6, 0, false);
      break;

    case 63:
      HourGlass.setLed(address, 7, 1, false);
      break;

    case 64:
      HourGlass.setLed(address, 7, 0, false);
      break;


  }
}





void HourglassAnimation::BottomMatrixSandGrainPosition (int TimeIndex, int address) {

  // la matrice fait 64 Leds, on a une animation pour chacune de ces 64 Leds, la variable etat de remplissage permet de choisir quelle animation on veut.

  switch (TimeIndex) {
    case 1:
      HourGlass.setLed(address, 0, 7, true);         //1
      break;

    case 2:
      HourGlass.setLed(address, 1, 7, true);         //2
      break;

    case 3:
      HourGlass.setLed(address, 0, 6, true);         //3
      break;

    case 4:
      HourGlass.setLed(address, 1, 6, true);         //4
      break;

    case 5:
      HourGlass.setLed(address, 0, 5, true);         //5
      break;

    case 6:
      HourGlass.setLed(address, 2, 7, true);        //6
      break;

    case 7:
      HourGlass.setLed(address, 1, 5, true);          //7
      break;

    case 8:
      HourGlass.setLed(address, 2, 6, true);           //8
      break;

    case 9:
      HourGlass.setLed(address, 2, 5, true);           //9
      break;

    case 10:
      HourGlass.setLed(address, 3, 7, true);             //10
      break;

    case 11:
      HourGlass.setLed(address, 0, 4, true);           //11
      break;

    case 12:
      HourGlass.setLed(address, 1, 4, true);            //12
      break;

    case 13:
      HourGlass.setLed(address, 3, 6, true);       //13
      break;

    case 14 :
      HourGlass.setLed(address, 3, 5, true);       //14
      break;

    case 15 :
      HourGlass.setLed(address, 2, 4, true);         //15
      break;

    case 16 :
      HourGlass.setLed(address, 3, 4, true);         //16
      break;

    case 17 :
      HourGlass.setLed(address, 0, 3, true);         //17
      break;

    case 18 :
      HourGlass.setLed(address, 4, 7, true);         //18
      break;

    case 19 :
      HourGlass.setLed(address, 1, 3, true);     //19
      break;

    case 20 :
      HourGlass.setLed(address, 4, 6, true);  //20
      break;

    case 21 :
      HourGlass.setLed(address, 5, 7, true);  //21
      break;

    case 22 :
      HourGlass.setLed(address, 2, 3, true);       //22
      break;

    case 23 :
      HourGlass.setLed(address, 0, 2, true);       //23
      break;

    case 24 :
      HourGlass.setLed(address, 3, 3, true);
      break;

    case 25 :
      HourGlass.setLed(address, 4, 5, true);       //25
      break;

    case 26 :
      HourGlass.setLed(address, 4, 4, true);
      break;

    case 27 :
      HourGlass.setLed(address, 4, 3, true);
      break;

    case 28 :
      HourGlass.setLed(address, 5, 6, true);  //28
      break;

    case 29 :
      HourGlass.setLed(address, 5, 5, true);  //29
      break;

    case 30 :
      HourGlass.setLed(address, 1, 2, true);  //30
      break;

    case 31 :
      HourGlass.setLed(address, 0, 1, true);  //31
      break;

    case 32 :
      HourGlass.setLed(address, 2, 2, true);  //32
      break;

    case 33 :
      HourGlass.setLed(address, 5, 4, true);  //33
      break;

    case 34 :
      HourGlass.setLed(address, 6, 7, true);  //33
      break;

    case 35 :
      HourGlass.setLed(address, 6, 6, true);  //33
      break;

    case 36 :
      HourGlass.setLed(address, 3, 2, true);  //32
      break;

    case 37 :
      HourGlass.setLed(address, 5, 3, true);  //32
      break;

    case 38 :
      HourGlass.setLed(address, 4, 2, true);  //32
      break;

    case 39 :
      HourGlass.setLed(address, 5, 2, true);  //32
      break;

    case 40 :
      HourGlass.setLed(address, 6, 5, true);  //33
      break;

    case 41 :
      HourGlass.setLed(address, 1, 1, true);  //41
      break;

    case 42 :
      HourGlass.setLed(address, 2, 1, true);  //33
      break;

    case 43 :
      HourGlass.setLed(address, 0, 0, true);  //33
      break;

    case 44 :
      HourGlass.setLed(address, 3, 1, true);  //33
      break;

    case 45 :
      HourGlass.setLed(address, 6, 4, true);  //33
      break;

    case 46 :
      HourGlass.setLed(address, 7, 7, true);  //33
      break;

    case 47 :
      HourGlass.setLed(address, 4, 1, true);  //33
      break;

    case 48 :
      HourGlass.setLed(address, 7, 6, true);  //33
      break;

    case 49 :
      HourGlass.setLed(address, 5, 1, true);  //32
      break;

    case 50 :
      HourGlass.setLed(address, 6, 3, true);  //32
      break;

    case 51 :
      HourGlass.setLed(address, 6, 2, true);
      break;

    case 52 :
      HourGlass.setLed(address, 6, 1, true);
      break;

    case 53 :
      HourGlass.setLed(address, 7, 5, true);    //53
      break;

    case 54 :
      HourGlass.setLed(address, 1, 0, true);
      break;

    case 55 :
      HourGlass.setLed(address, 7, 4, true);
      break;

    case 56 :
      HourGlass.setLed(address, 2, 0, true);
      break;

    case 57 :
      HourGlass.setLed(address, 3, 0, true);
      break;

    case 58 :
      HourGlass.setLed(address, 7, 3, true);
      break;

    case 59 :
      HourGlass.setLed(address, 7, 2, true);
      break;

    case 60 :
      HourGlass.setLed(address, 4, 0, true);
      break;

    case 61 :
      HourGlass.setLed(address, 5, 0, true);
      break;

    case 62 :
      HourGlass.setLed(address, 7, 1, true);         //1
      break;

    case 63 :
      HourGlass.setLed(address, 6, 0, true);         //1
      break;

    case 64 :
      HourGlass.setLed(address, 7, 0, true);         //64
      break;
  }
}

void HourglassAnimation::DisplayStateAtTimeIndex (int TimeIndex, int BottomMatrixAddress, int TopMatrixAddress ) {
  HourGlass.clearDisplay(BottomMatrixAddress);
  //HourGlass.clearDisplay(TopMatrixAddress);
  DisplayFilledMatrix(TopMatrixAddress);
  for (int i = 1 ; i <= TimeIndex -1; i++) { // the -1 is necessary, otherwise, the SandGrain that is to fall next has already fallen, it causes problems
    TopMatrixSandGrainPosition(i, TopMatrixAddress);
    delay(DisplayStateAtTimeIndexDelayTime);
    BottomMatrixSandGrainPosition(i, BottomMatrixAddress);
    delay(DisplayStateAtTimeIndexDelayTime);
  }
}


