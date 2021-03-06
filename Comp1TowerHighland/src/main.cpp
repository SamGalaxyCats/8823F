/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
// lIntake              motor         15              
// rIntake              motor         14              
// conveyor             motor         3               
// trashHandler         motor         5               
// eyes                 optical       12              
// dist                 distance      6               
// accella              inertial      18              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "function-library.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  accella.calibrate();
  eyes.setLightPower(0, percent);
  conveyor.setStopping(brake);
  trashHandler.setStopping(brake);

  //Controller setup
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print("You can do it! :)");
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) 
{
  //run conveyor
  conveyor.spin(forward, 90, percent);
  vex::task::sleep(1000);
  conveyor.stop();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) 
{
  // User control code here, inside the loop
  //drive vars
  double speedL = 0;
  double speedR = 0;
  double speedReducer = 1;
  double turnReducer = 0.65;
  bool tank = false;

  //conveyor vars
  double conveyorSpeed = 90;
  bool hasTrash = false;
  //int redLimit = 50;
  //double objectRange = 5;
  ConveyorSystem autoSorter;
  
  while (1) 
  {
    //RC control
    bLeftDrive.spin(forward, speedL, percent);
    fLeftDrive.spin(forward, speedL, percent);
    fRightDrive.spin(forward, speedR, percent);
    bRightDrive.spin(forward, speedR, percent);
 
    //tank toggle
    if((Controller1.ButtonX.pressing() && tank))
    {
      tank = false;
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print("RC   MODE ! !");
    }
    else if((Controller1.ButtonX.pressing() && !tank))
    {
      tank = true;
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print("TANK mode ! !");
    }
    if(!tank)
    {
      speedL = ((Controller1.Axis3.position(percent) + (Controller1.Axis1.position(percent)) * turnReducer)/speedReducer); //if the joysticks are wrong, switch the + and -.
      speedR = ((Controller1.Axis3.position(percent) - (Controller1.Axis1.position(percent)) * turnReducer)/speedReducer);
    }
    else
    {
      speedL = (Controller1.Axis3.position(percent));
      speedR = (Controller1.Axis2.position(percent));
    }

    //conveyor w/ autosorter
    if((Controller1.ButtonUp.pressing() && !hasTrash) || Controller1.ButtonL1.pressing())
    {
      autoSorter.takeUp(conveyorSpeed);
    }
    else if(Controller1.ButtonDown.pressing())
    {
      autoSorter.takeDown(conveyorSpeed);
    }
    else if((Controller1.ButtonUp.pressing() && hasTrash) || Controller1.ButtonL2.pressing())
    {
      autoSorter.spitOut(conveyorSpeed);
    }
    else
    {
      autoSorter.stopConveyor();
    }
     //intakes
    if(Controller1.ButtonR1.pressing())
    {
      lIntake.spin(forward, 85, percent); //inkake
      rIntake.spin(forward, 85, percent);
    }
    else if(Controller1.ButtonR2.pressing())
    {
      lIntake.spin(forward, -85, percent); //outkake
      rIntake.spin(forward, -85, percent);
    }
    else
    {
      lIntake.stop();
      rIntake.stop();
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
