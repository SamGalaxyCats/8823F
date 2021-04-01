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
  double intakeSpeed = 540;
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
  printf("\n2nd tower\n");

  //Turn to next ball
  lIntake.spin(forward, intakeSpeed, rpm);
  rIntake.spin(forward, intakeSpeed, rpm);
  driveSystem.driveDistance(500, 600);
  conveyL.spin(forward, 300, rpm);
  conveyR.spin(forward, 300, rpm);
  vex::task::sleep(250);
  conveyL.stop();
  conveyR.stop();

  //get ANOTHER ball
  driveSystem.turnDegrees(34, 150);
  driveSystem.driveDistance(850, 600);
  conveyL.spin(forward, 300, rpm);
  conveyR.spin(forward, 300, rpm);
  vex::task::sleep(400);
  conveyL.stop();
  conveyR.stop();

  //Go to 2nd tower and score ball
  driveSystem.turnDegrees(-78, 300);
  driveSystem.driveDistance(750, 500, 2);
  lIntake.stop();
  rIntake.stop();
  driveSystem.score2Balls(6, 3);

  //back out
  lIntake.spin(forward, -intakeSpeed/2, rpm);
  rIntake.spin(forward, -intakeSpeed/2, rpm);
  driveSystem.driveDistance(-200, 300);
  lIntake.stop();
  rIntake.stop();

  //go for 3rd tower
  printf("\n3rd tower\n");
  driveSystem.turnDegrees(-10, 300); //turn to face next ball
  lIntake.spin(forward, intakeSpeed, rpm);
  rIntake.spin(forward, intakeSpeed, rpm);
  driveSystem.driveDistance(950, 600); //get ball
  driveSystem.turnDegrees(-35, 300); //face tower
  driveSystem.driveDistance(400, 400, 1.5);
  lIntake.stop();
  rIntake.stop();
  driveSystem.scoreBall(6, 2, 300);

  //back out
  lIntake.spin(forward, -intakeSpeed/4, rpm);
  rIntake.spin(forward, -intakeSpeed/4, rpm);
  driveSystem.driveDistance(-325, 600);
  lIntake.stop();
  rIntake.stop();

  //4th tower
  printf("\n4th tower\n");
  driveSystem.turnDegrees(81, 250);
  lIntake.spin(forward, intakeSpeed, rpm);
  rIntake.spin(forward, intakeSpeed, rpm);
  driveSystem.driveDistance(1050, 600); //get ball
  driveSystem.turnDegrees(10, 300);
  driveSystem.driveDistance(300, 600, 2); //go to tower
  lIntake.stop();
  rIntake.stop();
  driveSystem.scoreBall(6, 2, 300);

  //back out
  lIntake.spin(forward, -intakeSpeed/4, rpm);
  rIntake.spin(forward, -intakeSpeed/4, rpm);
  driveSystem.driveDistance(-225, 300); 
  lIntake.stop();
  rIntake.stop();

  //5th tower
  printf("\n5th tower\n");
  driveSystem.turnDegrees(95, 300);
  lIntake.spin(forward, intakeSpeed, rpm);
  rIntake.spin(forward, intakeSpeed, rpm);
  driveSystem.driveDistance(1000, 600); //get ball
  driveSystem.turnDegrees(43, 300);
  driveSystem.driveDistance(600, 600, 3); //go to tower
  lIntake.stop();
  rIntake.stop();
  driveSystem.scoreBall(6, 2);

  //back out
  lIntake.spin(forward, -intakeSpeed/4, rpm);
  rIntake.spin(forward, -intakeSpeed/4, rpm);
  driveSystem.driveDistance(-400, 600); 
  lIntake.stop();
  rIntake.stop();

  //6th tower
  printf("\n6th tower\n");
  driveSystem.turnDegrees(200, 300);
  lIntake.spin(forward, intakeSpeed, rpm);
  rIntake.spin(forward, intakeSpeed, rpm);
  driveSystem.driveDistance(1250, 600); //get ball
  driveSystem.turnDegrees(91, 300); //face tower
  driveSystem.driveDistance(850, 600, 2);
  lIntake.stop();
  rIntake.stop();
  driveSystem.scoreBall(6, 2);

  //back out
  lIntake.spin(forward, -intakeSpeed/2, rpm);
  rIntake.spin(forward, -intakeSpeed/2, rpm);
  driveSystem.driveDistance(-175, 300); //back out
  lIntake.stop();
  rIntake.stop();

  //7th tower
  printf("\n7th tower\n");
  driveSystem.turnDegrees(170, 300); //turn to face next ball
  lIntake.spin(forward, intakeSpeed, rpm);
  rIntake.spin(forward, intakeSpeed, rpm);
  driveSystem.driveDistance(900, 600); //get ball
  driveSystem.turnDegrees(140, 300); //face tower
  driveSystem.driveDistance(500, 400, 2);
  lIntake.stop();
  rIntake.stop();
  driveSystem.scoreBall(6, 2, 300);

  //back out
  lIntake.spin(forward, -intakeSpeed/4, rpm);
  rIntake.spin(forward, -intakeSpeed/4, rpm);
  driveSystem.driveDistance(-300, 575);
  lIntake.stop();
  rIntake.stop();

  //8th tower
  printf("\n8th tower\n");
  driveSystem.turnDegrees(266, 250);
  lIntake.spin(forward, intakeSpeed, rpm);
  rIntake.spin(forward, intakeSpeed, rpm);
  driveSystem.driveDistance(1100, 600); //get ball
  driveSystem.turnDegrees(190, 300);
  driveSystem.driveDistance(250, 400, 1.5); //go to tower
  lIntake.stop();
  rIntake.stop();
  driveSystem.scoreBall(6, 2, 300);

  //The fabled 9th tower
  printf("\n9th tower\n");
  driveSystem.backOut(intakeSpeed, 300, -250); //back out
  driveSystem.turnDegrees(6, 300); //face ball
  lIntake.spin(forward, intakeSpeed, rpm);
  rIntake.spin(forward, intakeSpeed, rpm);
  driveSystem.driveDistance(500, 600); //get ball
  conveyL.spin(forward); //pull the ball up
  conveyR.spin(forward); //that way we can outtake later.
  vex::task::sleep(400);
  conveyL.stop();
  conveyR.stop();

  //Poke out
  driveSystem.turnDegrees(-5, 150); //face tower
  lIntake.spin(forward, -intakeSpeed, rpm); //outtake to ensure that we poke out
  rIntake.spin(forward, -intakeSpeed, rpm);
  driveSystem.driveDistance(500, 600, 2); //get to the tower
  lIntake.spin(forward, intakeSpeed, rpm);
  rIntake.spin(forward, intakeSpeed, rpm);
  driveSystem.scoreBall(6, 2); //Try to score the ball for 2 seconds
  driveSystem.backOut(intakeSpeed, 300, -300); //get outta dodge
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
