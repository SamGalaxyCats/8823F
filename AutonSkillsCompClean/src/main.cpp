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
// rIntake              motor         16              
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

  conveyor.setVelocity(conveyorSpeed, dps);
  trashHandler.setVelocity(-conveyorSpeed, dps);

  while(accella.isCalibrating())
  {
    vex::task::sleep(20);
  }
  //double timeOffSet = Brain.Timer.value();

  //Prep to score side tower
  driveSystem.turnOnlyRightBack(18.5, 200);

  //Flip ramp up
  conveyor.spin(forward, 90, percent);
  vex::task::sleep(1000);
  conveyor.stop();

  //Go get the nearest ball and score it.
  driveSystem.driveDistance(100, 180); //Drive a smidge forward
  driveSystem.turnDegrees(22.75, 300); //turn a little more
  rIntake.spin(forward, intakeSpeed, dps);
  lIntake.spin(forward, intakeSpeed, dps);
  driveSystem.driveDistance(1150, 900); //drive slightly past the original position of the ball to ensure it gets the ball.
  driveSystem.turnDegrees(-35, 300);//face tower
  driveSystem.driveDistance(770, 900, 4); //drive to tower

  //score corner ball  
  rIntake.stop();
  lIntake.stop();
  driveSystem.scoreBall(objectRange, 3);
 
  //get out of the tower
  rIntake.spin(forward, -intakeSpeed/2, dps); //outtake, two balls are too risky.
  lIntake.spin(forward, -intakeSpeed/2, dps);
  driveSystem.driveDistance(-450, 450);
  rIntake.stop();
  lIntake.stop();

  //turn toward the next ball
  driveSystem.turnDegrees(85, 450);
  //conveyor.spin(forward);
  //trashHandler.spin(forward, conveyorSpeed/2, dps); //spit out the two balls

  //Get the next ball
  rIntake.spin(forward, intakeSpeed, dps);
  lIntake.spin(forward, intakeSpeed, dps);
  driveSystem.driveDistance(1800, 900);
  conveyor.stop();
  trashHandler.stop();
  vex::task::sleep(100);
  
  
  //go to the left side tower and score the ball
  driveSystem.turnDegrees(0, 360);
  driveSystem.driveDistance(255, 720, 2);
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
  driveSystem.driveDistance(-255, -450); //drive back the same amount you went in.
  rIntake.stop();
  lIntake.stop();

  //get the next ball.
  driveSystem.turnDegrees(90, 900); //face 90
  rIntake.spin(forward, intakeSpeed, dps); //intake
  lIntake.spin(forward, intakeSpeed, dps);
  driveSystem.driveDistance(1600, 1000); //get ball
  
  //go to back corner tower
  driveSystem.turnDegrees(60, 900);
  driveSystem.driveDistance(950, 720, 4);
  rIntake.stop();
  lIntake.stop();

  //Score ball
  driveSystem.scoreBall(objectRange, 3);

  //back out of tower
  rIntake.spin(forward, -intakeSpeed/2, dps);
  lIntake.spin(forward, -intakeSpeed/2, dps);
  driveSystem.driveDistance(-750, 720);
  rIntake.stop();
  lIntake.stop();

  //get next ball
  driveSystem.turnDegrees(190, 900);
  rIntake.spin(forward, intakeSpeed, dps); //intake
  lIntake.spin(forward, intakeSpeed, dps);
  driveSystem.driveDistance(1650, 1200);
  vex::task::sleep(100);
  driveSystem.turnDegrees(115, 900);
  driveSystem.driveDistance(1000, 1200, 3.75);
  rIntake.stop();
  lIntake.stop();
  driveSystem.scoreBall(objectRange, 2);

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
