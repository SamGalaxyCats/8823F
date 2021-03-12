/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\sambo                                            */
/*    Created:      Sat Mar 06 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// lIntake              motor         15              
// rIntake              motor         14              
// conveyL              motor         3               
// conveyR              motor         5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  double speedL = 0;
  double speedR = 0;
  double speedReducer = 1;
  double turnReducer = 0.65;
  double conveyorSpeed = 525;

  Controller1.Screen.print("Good Luck! :)");

  while(1)
  {
    //RC Control
    speedL = ((Controller1.Axis3.position(percent) + (Controller1.Axis1.position(percent)) * turnReducer)/speedReducer); //if the joysticks are wrong, switch the + and -.
    speedR = ((Controller1.Axis3.position(percent) - (Controller1.Axis1.position(percent)) * turnReducer)/speedReducer);

    bLeftDrive.spin(forward, speedL, percent);
    fLeftDrive.spin(forward, speedL, percent);
    fRightDrive.spin(forward, speedR, percent);
    bRightDrive.spin(forward, speedR, percent);

    //Intakes
    if(Controller1.ButtonR1.pressing())
    {
      lIntake.spin(forward, 540, rpm); //intake
      rIntake.spin(forward, 540, rpm);
    }
    else if(Controller1.ButtonR2.pressing())
    {
      lIntake.spin(forward, -540, rpm); //outtake
      rIntake.spin(forward, -540, rpm);
    }
    else
    {
      lIntake.stop();
      rIntake.stop();
    }

    //Conveyor
    if(Controller1.ButtonL1.pressing())
    {
      conveyL.spin(forward, conveyorSpeed, rpm);
      conveyR.spin(forward, conveyorSpeed, rpm);
    }
    else if(Controller1.ButtonL2.pressing())
    {
      conveyL.spin(forward, -conveyorSpeed, rpm);
      conveyR.spin(forward, -conveyorSpeed, rpm);
    }
    else
    {
      conveyL.stop();
      conveyR.stop();
    }
  }
}