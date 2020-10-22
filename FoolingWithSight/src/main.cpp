/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\sambo                                            */
/*    Created:      Thu Oct 22 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Sight                vision        3               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  double counter = 0;
  //Successes: screen updates every 100 msec, vision sensor successfully detects when it finds the red object used for testing.
  while(true)
  {
    Sight.takeSnapshot(Sight__RED_THING);
    wait(100, msec);
    //Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    if(Sight.objects[0].exists)
    {
      Brain.Screen.print("I found it!     :D");
    }
    else
    {
      Brain.Screen.print("Nothing's there :(");
    }
    counter++;
  }
}
