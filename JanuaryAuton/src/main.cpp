/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\sambo                                            */
/*    Created:      Mon Jan 11 2021                                           */
/*    Description:  V5 project                                                */
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
// eyes                 optical       12              
// dist                 distance      13              
// clickL               limit         B               
// accella              inertial      18              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "function-library.h"

using namespace vex;

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  accella.calibrate();

  Robot driveSystem;

  while(accella.isCalibrating())
  {
    vex::task::sleep(20);
  }

  //This is our exact current auton, but using the new and improved methods.

  //Prep to score side tower
  driveSystem.turnDistance(-250, -180, 0, 0);

  //run conveyor
  conveyor.spin(forward, 90, percent);
  vex::task::sleep(1000);
  conveyor.stop();

  //Drive a smidge forward
  driveSystem.driveDistance(100, 180);

  //turn a little more
  driveSystem.turnDegrees(30, 300);

  //drive to next pos
  driveSystem.driveDistance(1250, 900); //200 rpm (max speed of normal motor) = 1200 dps, 75% of 1200 = 900.

  //turn toward ball
  driveSystem.turnDegrees(-42.5, 300, true); //in the original code, it never stopped, so we coast.

  //drive into ball and tower.
  rIntake.spin(forward, 90, percent);
  lIntake.spin(forward, 90, percent);
  driveSystem.driveDistance(915, 450);
  conveyor.spin(forward, 80, percent);
  trashHandler.spin(forward, -80, percent);  
  vex::task::sleep(1300);
  conveyor.stop();
  trashHandler.stop();
  rIntake.stop();
  lIntake.stop();

  driveSystem.driveDistance(-500, 900);
}
