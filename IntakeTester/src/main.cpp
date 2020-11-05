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
// lInkake              motor         15              
// rInkake              motor         8               
// bump                 bumper        A               
// Controller1          controller                    
// fLeftDrive           motor         5               
// fRightDrive          motor         6               
// bLeftDrive           motor         2               
// bRightDrive          motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  bool isRunning = false;
  bool canToggle = false;
  double speed = 75;
  double speedL;
  double speedR; 
  while(true)
  {
    if(Controller1.ButtonA.pressing())
    {
      speed = 75;
    }
    if(Controller1.ButtonB.pressing())
    {
      speed = -75;
    }

    if(canToggle && (bump.pressing() || (Controller1.ButtonA.pressing() || Controller1.ButtonB.pressing())) && !isRunning)
    {
      lInkake.spin(forward, speed, percent);
      rInkake.spin(forward, speed, percent);
      isRunning = true;
      canToggle = false;
    }
    else if(canToggle && (bump.pressing() || (Controller1.ButtonA.pressing() || Controller1.ButtonB.pressing())) && isRunning)
    {
      lInkake.stop();
      rInkake.stop();
      isRunning = false;
      canToggle = false;
    }
    else if(!canToggle && !(bump.pressing() || (Controller1.ButtonA.pressing() || Controller1.ButtonB.pressing())))
    {
      canToggle = true;  //Checks to see if you've let go of the button. If you have, you can toggle the effect by pressing the button. Preventative measure.
    }

    //arcade control
    //speedL = ((Controller1.Axis3.position(percent) - Controller1.Axis1.position(percent))/2); //if the joysticks are wrong, switch the + and -.
    //speedR = ((Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent))/2);
    speedR = (Controller1.Axis2.position(percent));
    speedL = (Controller1.Axis3.position(percent));
    bLeftDrive.spin(forward, speedL, percent);
    fLeftDrive.spin(forward, speedL, percent);
    fRightDrive.spin(forward, speedR, percent);
    bRightDrive.spin(forward, speedR, percent);
    /*if(Controller1.ButtonL2.pressing())
    {
      bLeftDrive.spin(forward, 50, percent); 
    }
    else if(!Controller1.ButtonL2.pressing())
    {
      bLeftDrive.stop(brakeType::coast);   
    }
    else if(Controller1.ButtonL1.pressing())
    {
      fLeftDrive.spin(forward, 50, percent);  
    }
    else if(!Controller1.ButtonL1.pressing())
    {
      fLeftDrive.stop(brakeType::coast);  
    }
    else if(Controller1.ButtonR1.pressing())
    {
      fRightDrive.spin(forward, 50, percent);  
    }
    else if(!Controller1.ButtonR1.pressing())
    {
      fRightDrive.stop(brakeType::coast);  
    }
    else if(Controller1.ButtonR2.pressing())
    {
      bRightDrive.spin(forward, 50, percent);  
    }
    else if(!Controller1.ButtonR2.pressing())
    {
      bRightDrive.stop(brakeType::coast);  
    }
    else
    {
      //bLeftDrive.stop();
      //bRightDrive.stop();
      //fLeftDrive.stop();
      //fRightDrive.stop();
    }*/
  }
}
