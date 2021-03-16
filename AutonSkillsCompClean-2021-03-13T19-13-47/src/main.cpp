// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// lIntake              motor         15              
// rIntake              motor         14              
// conveyL              motor         3               
// conveyR              motor         5               
// dist                 distance      13              
// accella              inertial      18              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// lIntake              motor         15              
// rIntake              motor         14              
// conveyL              motor         3               
// conveyR              motor         5               
// dist                 distance      13              
// accella              inertial      18              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// lIntake              motor         15              
// rIntake              motor         14              
// conveyL              motor         3               
// conveyR              motor         5               
// dist                 distance      13              
// accella              inertial      18              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// lIntake              motor         15              
// rIntake              motor         14              
// conveyL              motor         3               
// conveyR              motor         5               
// dist                 distance      13              
// accella              inertial      18              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// lIntake              motor         15              
// rIntake              motor         14              
// conveyL              motor         3               
// conveyR              motor         5               
// dist                 distance      13              
// accella              inertial      18              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// lIntake              motor         15              
// rIntake              motor         14              
// conveyL              motor         3               
// conveyR              motor         5               
// dist                 distance      13              
// accella              inertial      18              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// lIntake              motor         15              
// rIntake              motor         14              
// conveyL              motor         3               
// trashHandler         motor         5               
// dist                 distance      13              
// accella              inertial      18              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// lIntake              motor         15              
// rIntake              motor         14              
// conveyor             motor         3               
// trashHandler         motor         5               
// dist                 distance      13              
// accella              inertial      18              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// lIntake              motor         15              
// rIntake              motor         14              
// conveyor             motor         3               
// trashHandler         motor         5               
// dist                 distance      13              
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

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

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
  accella.calibrate();

  //Set up variables
  Robot driveSystem;
  double intakeSpeed = 1800;
  double conveyorSpeed = 3400;
  bool ballFlag = false;
  double objectRange = 6;
  //double timeAtStep;
  double timeStamp;

  conveyL.setVelocity(conveyorSpeed, dps);
  conveyR.setVelocity(conveyorSpeed, dps);

  while(accella.isCalibrating())
  {
    vex::task::sleep(20);
  }
  //double timeOffSet = Brain.Timer.value();

  //Prep to score side tower
  driveSystem.turnOnlyRightBack(11.1, 100);

  //Flip ramp up (1st tower)
  lIntake.spin(forward, -90, percent);
  rIntake.spin(forward, -90, percent);
  conveyL.spin(forward, 90, percent);
  conveyR.spin(forward, 90, percent);
  vex::task::sleep(1000);
  conveyL.stop();
  conveyR.stop();
  lIntake.stop();
  rIntake.stop();

  //Go get the nearest ball and score it. (2nd tower)
  driveSystem.driveDistance(60, 90); //Drive a smidge forward
  driveSystem.turnDegrees(13.65, 150); //turn a little more
  rIntake.spin(forward, intakeSpeed, dps);
  lIntake.spin(forward, intakeSpeed, dps);
  driveSystem.driveDistance(690, 450); //drive slightly past the original position of the ball to ensure it gets the ball.
  driveSystem.turnDegrees(-21, 150);//face tower
  driveSystem.driveDistance(462, 450, 4); //drive to tower

  //score corner ball
  rIntake.stop();
  lIntake.stop();
  driveSystem.scoreBall(objectRange, 3);
 
  //get out of the tower
  rIntake.spin(forward, -intakeSpeed/2, dps); //outtake, two balls are too risky.
  lIntake.spin(forward, -intakeSpeed/2, dps);
  driveSystem.driveDistance(-162, 225);
  rIntake.stop();
  lIntake.stop();

  //turn toward the next ball (3rd tower)
  driveSystem.turnDegrees(51.9, 225);
  //conveyor.spin(forward);
  //trashHandler.spin(forward, conveyorSpeed/2, dps); //spit out the two balls

  //Get the next ball
  rIntake.spin(forward, intakeSpeed, dps);
  lIntake.spin(forward, intakeSpeed, dps);
  driveSystem.driveDistance(1035, 450, 7);
  conveyL.stop();
  conveyR.stop();
  vex::task::sleep(100);
  
  
  //go to the left side tower and score the ball
  driveSystem.turnDegrees(0, 180);
  driveSystem.driveDistance(153, 360, 2);
  rIntake.stop();
  lIntake.stop();
  driveSystem.scoreBall(objectRange, 4);

  //Recalibrate the inertial sensor.
  accella.calibrate();
  while(accella.isCalibrating())
  {
    vex::task::sleep(20);
  }

  //get out of the tower.
  rIntake.spin(forward, -intakeSpeed/2, dps); //outtake, we don't want that ball.
  lIntake.spin(forward, -intakeSpeed/2, dps);
  driveSystem.driveDistance(-153, -225); //drive back the same amount you went in.
  rIntake.stop();
  lIntake.stop();

  //get the next ball. (4th tower)
  driveSystem.turnDegrees(54.3, 450); //face 90
  rIntake.spin(forward, intakeSpeed, dps); //intake
  lIntake.spin(forward, intakeSpeed, dps);
  driveSystem.driveDistance(960, 500); //get ball
  
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
