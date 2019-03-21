#include "LedControl.h"

class HourglassAnimation
{
public:
  void DisplayFilledMatrix(int address);
  void AddSandGrain(int TimeIndex, int address);                                             // Displays an animation of a SandGrain that falls in the bottom matrix, te animation depends on the TimeIndex
  void RemoveSandGrain(int TimeIndex, int address);
  void DisplayStateAtTimeIndex (int TimeIndex,int TopMatrixAddress, int BottomMatrixAddress ); // This function helps resume the animation at a certain time index without having to re-animate it. 
  void DisplayTimeMenu(int TimeSelecter, int address);
  void TimeMenuIconsDisappearingAnimation(int TimeSelecter, int address);
  int TopMatrixAddress = 1;
  int BottomMatrixAddress = 0;

private:
  void SandGrainFallingAnimation(int limite, int address);           //A function that displays an animation of the fall of SandGrain across the bottom matrix diagonal
  void TopMatrixSandGrainPosition(int TimeIndex, int address);       //Needed for function DisplayStateAtTimeIndex(), it contains the ordered positions of every fallen SandGrain from the top matrix
  void BottomMatrixSandGrainPosition (int TimeIndex, int address) ;  //Needed for function DisplayStateAtTimeIndex(), it contains the ordered positions of every added SandGrain to the bottom matrix
  void TimeMenuIcons(int TimeSelecter, int address);
  void TimeMenuIconsDisappearingAnimationFrames(int TimeSelecter, int FrameNumber, int address);
  LedControl HourGlass = LedControl(13, 11, 12, 2);
  int AnimationDelayTime = 50;                                       // A global animation parameter that changes the speed of AddSandGrain and RemoveSandGrain functions, originally 50
  int DisplayStateAtTimeIndexDelayTime = 12;                         // A global animation parameter that changes the speed of DisplayStateAtTimeIndex function, originally 11
  int TimeMenuIconsDisappearingAnimationDelayTime = 100;
};

extern HourglassAnimation hourglassanimation;
