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
// lift                 motor         5               
// rampIntake           motor         4               
// bLinkake             motor         15              
// bRinkake             motor         16              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  double speedL;
  double speedR; 
  
  lift.setStopping(hold);
  rampIntake.setStopping(hold);
  bRinkake.setStopping(hold);
  bLinkake.setStopping(hold);

  while(true)
  {
    //arcade control
    speedL = ((Controller1.Axis3.position(percent) - Controller1.Axis1.position(percent))/2); //if the joysticks are wrong, switch the + and -.
    speedR = ((Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent))/2);
    bLeftDrive.spin(forward, speedL, percent);
    fLeftDrive.spin(forward, speedL, percent);
    fRightDrive.spin(forward, speedR, percent);
    bRightDrive.spin(forward, speedR, percent);

    //lift
    if(Controller1.ButtonUp.pressing())
    {
      lift.spin(forward, 50, percent); //go up
    }
    else if(Controller1.ButtonDown.pressing())
    {
      lift.spin(forward, -50, percent); //go down
    }
    else
    {
      lift.stop(); //stay still
    }

    //blinkake and brinkake
    if(Controller1.ButtonL1.pressing())
    {
      bLinkake.spin(forward, 50, percent); //inkake
      bRinkake.spin(forward, 50, percent);
    }
    else if(Controller1.ButtonL2.pressing())
    {
      bLinkake.spin(forward, -50, percent); //outkake
      bRinkake.spin(forward, -50, percent);
    }
    else
    {
      bLinkake.stop();
      bRinkake.stop();
    }

    //ramp intake
    if(Controller1.ButtonR1.pressing())
    {
      rampIntake.spin(forward, 50, percent);
    }
    else if(Controller1.ButtonR2.pressing())
    {
      rampIntake.spin(forward, -50, percent);
    }
    else
    {
      rampIntake.stop();
    }

    //All of the above
    if(Controller1.ButtonA.pressing())
    {
      rampIntake.spin(forward, 50, percent);
      bLinkake.spin(forward, 50, percent);
      bRinkake.spin(forward, 50, percent);
    }
    else if(Controller1.ButtonB.pressing())
    {
      rampIntake.spin(forward, -50, percent);
      bLinkake.spin(forward, -50, percent);
      bRinkake.spin(forward, -50, percent);
    }
    else
    {
      rampIntake.stop();
      bLinkake.stop();
      bRinkake.stop();
    }
  }  
}
