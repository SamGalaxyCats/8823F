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
// bRightDrive          motor         1               
// bLeftDrive           motor         2               
// fRightDrive          motor         10              
// fLeftDrive           motor         11              
// rIntake              motor         3               
// lIntake              motor         9               
// trashHandler         motor         4               
// conveyor             motor         8               
// sight                vision        17              
// accella              inertial      18              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

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

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  accella.calibrate();

  
  trashHandler.setStopping(hold);
  lIntake.setStopping(hold);
  rIntake.setStopping(hold);
  conveyor.setStopping(hold);
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

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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
  double speedL;
  double speedR; 
  double conveyorSpeed = 50;

  bool hasTrash = false;
  
  // User control code here, inside the loop
  while (1) 
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
    if(!Controller1.ButtonA.pressing() && !Controller1.ButtonB.pressing())
    {
      conveyor.stop(); //stay still
      trashHandler.stop();
    }

    /*//conveyor w/o autosorter
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
    }*/

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

    //sight.takeSnapshot(sight__BLUE_BALL);
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
  while (true) 
  {
    wait(100, msec);
  }
}
