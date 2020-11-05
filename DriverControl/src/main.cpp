/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\sambo                                            */
/*    Created:      Tue Aug 11 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// fLeftDrive           motor         1               
// fRightDrive          motor         10              
// bLeftDrive           motor         11              
// bRightDrive          motor         20              
// Controller1          controller                    
// trashHandler         motor         5               
// conveyor             motor         4               
// lIntake              motor         15              
// rIntake              motor         16              
// sight                vision        17              
// Accella              inertial      18              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  double speedL;
  double speedR; 
  double conveyorSpeed = 50;

  bool hasTrash = false;
  
  trashHandler.setStopping(hold);
  lIntake.setStopping(hold);
  rIntake.setStopping(hold);
  conveyor.setStopping(hold);

  while(true)
  {
    //arcade control
    speedL = ((Controller1.Axis3.position(percent) - Controller1.Axis1.position(percent))/2); //if the joysticks are wrong, switch the + and -.
    speedR = ((Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent))/2);
    bLeftDrive.spin(forward, speedL, percent);
    fLeftDrive.spin(forward, speedL, percent);
    fRightDrive.spin(forward, speedR, percent);
    bRightDrive.spin(forward, speedR, percent);

    //conveyor w/ autosorter
    if(Controller1.ButtonA.pressing() && !hasTrash)
    {
      conveyor.spin(forward, conveyorSpeed, percent); //intake
      trashHandler.spin(forward, conveyorSpeed, percent); //trash handler helps lift this ball
    }
    else if(Controller1.ButtonB.pressing())
    {
      conveyor.spin(forward, -conveyorSpeed, percent); //outtake
      trashHandler.spin(forward, -conveyorSpeed, percent); //trash handler helps spit out this ball
    }
    else if(Controller1.ButtonA.pressing() && hasTrash)
    {
      conveyor.spin(forward, conveyorSpeed, percent); //intake
      trashHandler.spin(forward, -conveyorSpeed, percent); //trash is had, spit out ball
    }

    //don't let either system block each other.
    if(!Controller1.ButtonA.pressing() && !Controller1.ButtonB.pressing() && !Controller1.ButtonUp.pressing() && !Controller1.ButtonDown.pressing() && !!Controller1.ButtonRight.pressing())
    {
      conveyor.stop(); //stay still
      trashHandler.stop();
    }

    //conveyor w/o autosorter
    if(Controller1.ButtonUp.pressing())
    {
      conveyor.spin(forward, conveyorSpeed, percent);
      trashHandler.spin(forward, conveyorSpeed, percent);
    }
    else if(Controller1.ButtonDown.pressing())
    {
      conveyor.spin(forward, conveyorSpeed, percent);
      trashHandler.spin(forward, conveyorSpeed, percent);
    }
    else if(Controller1.ButtonRight.pressing())
    {
      conveyor.spin(forward, conveyorSpeed, percent);
      trashHandler.spin(forward, conveyorSpeed, percent);
    }

    //blinkake and brinkake
    if(Controller1.ButtonL1.pressing())
    {
      lIntake.spin(forward, 50, percent); //inkake
      rIntake.spin(forward, 50, percent);
    }
    else if(Controller1.ButtonL2.pressing())
    {
      lIntake.spin(forward, -50, percent); //outkake
      rIntake.spin(forward, -50, percent);
    }
    else
    {
      lIntake.stop();
      rIntake.stop();
    }
  }  
}
