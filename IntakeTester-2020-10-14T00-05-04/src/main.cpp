/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\sambo                                            */
/*    Created:      Tue Oct 13 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// lInkake              motor         1               
// rInkake              motor         10              
// bump                 bumper        A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  bool isRunning = false;
  bool canToggle = false;
  while(true)
  {
    if(canToggle && bump.pressing() && !isRunning)
    {
      lInkake.spin(forward, 75, percent);
      rInkake.spin(forward, 75, percent);
      isRunning = true;
      canToggle = false;
    }
    else if(canToggle && bump.pressing() && isRunning)
    {
      lInkake.stop();
      rInkake.stop();
      isRunning = false;
      canToggle = false;
    }
    else if(!canToggle && !bump.pressing())
    {
      canToggle = true;  //Checks to see if you've let go of the button. If you have, you can toggle the effect by pressing the button. Preventative measure.
    }
  }
}
