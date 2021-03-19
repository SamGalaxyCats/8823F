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
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// lIntake              motor         15              
// rIntake              motor         14              
// conveyL              motor         3               
// conveyR              motor         5               
// accella              inertial      18              
// dist                 distance      13              
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
  rIntake.setBrake(brake);
  lIntake.setBrake(brake);
  conveyL.setBrake(brake);
  conveyR.setBrake(brake);
  bLeftDrive.setStopping(brake);
  fLeftDrive.setStopping(brake);
  bRightDrive.setStopping(brake);
  fRightDrive.setStopping(brake);
  conveyL.setVelocity(450, rpm);
  conveyR.setVelocity(450, rpm);
  bLeftDrive.setRotation(0, degrees);
  fLeftDrive.setRotation(0, degrees);
  bRightDrive.setRotation(0, degrees);
  fRightDrive.setRotation(0, degrees);
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
  Robot driveSystem;
  printf("Run start\n");
  while(accella.isCalibrating())
  {
    vex::task::sleep(10);
  }

  //Score 1st tower
  driveSystem.turnOnlyRightBack(20, 300);
  lIntake.spin(forward, -90, percent);
  rIntake.spin(forward, -90, percent);
  conveyL.spin(forward, 90, percent);
  conveyR.spin(forward, 90, percent);
  vex::task::sleep(1000); //1 second to flip out
  conveyL.stop();
  conveyR.stop();
  lIntake.stop();
  rIntake.stop();

  //Turn to next ball
  lIntake.spin(forward, 540, rpm);
  rIntake.spin(forward, 540, rpm);
  driveSystem.driveDistance(500, 800);
  conveyL.spin(forward, 300, rpm);
  conveyR.spin(forward, 300, rpm);
  vex::task::sleep(500);
  conveyL.stop();
  conveyR.stop();

  //get ANOTHER ball
  driveSystem.turnDegrees(30, 200);
  driveSystem.driveDistance(900, 900);


  //Go to 2nd tower and score ball
  driveSystem.turnDegrees(-80, 300);
  driveSystem.driveDistance(800, 500, 2);
  lIntake.stop();
  rIntake.stop();
  driveSystem.score2Balls(6, 3);

  //back out
  driveSystem.driveDistance(-250, 300);
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

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

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
