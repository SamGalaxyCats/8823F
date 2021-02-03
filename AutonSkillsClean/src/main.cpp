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
  driveSystem.turnDistance(0, 0, -200, -180);

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
  driveSystem.turnDegrees(-35, 300);
  driveSystem.driveDistance(775, 900);

  //score corner ball  
  rIntake.stop();
  lIntake.stop();
  conveyor.spin(forward);
  trashHandler.spin(forward);

  while(!ballFlag || (dist.objectDistance(inches) < objectRange))
  {
    vex::task::sleep(10);
    if(dist.objectDistance(inches) < objectRange)
    {
      ballFlag = true;
    }
  }
  ballFlag = false;
  vex::task::sleep(100);
  
  conveyor.stop();
  trashHandler.stop();

  rIntake.spin(forward, -intakeSpeed/2, dps); //outtake, two balls are too risky.
  lIntake.spin(forward, -intakeSpeed/2, dps);
  driveSystem.driveDistance(-400, 360);
  rIntake.stop();
  lIntake.stop();

  
  driveSystem.turnDegrees(85, 360);
  conveyor.spin(forward);
  trashHandler.spin(forward, conveyorSpeed/2, dps); //spit out the two balls

  rIntake.spin(forward, intakeSpeed, dps);
  lIntake.spin(forward, intakeSpeed, dps);
  driveSystem.driveDistance(1800, 900);
  conveyor.stop();
  trashHandler.stop();
  vex::task::sleep(100);
  rIntake.stop();
  lIntake.stop();
  

  driveSystem.turnDegrees(0, 360);
  driveSystem.driveDistance(250, 720);

  conveyor.spin(forward);
  trashHandler.spin(forward);
  timeStamp = Brain.Timer.value();
  printf("Time: %f\n", timeStamp);
  while(!ballFlag || (dist.objectDistance(inches) < objectRange))
  {
    vex::task::sleep(10);
    if(dist.objectDistance(inches) < objectRange)
    {
      ballFlag = true;
    }
    if((Brain.Timer.value()-timeStamp) > 3)
    {
      break;
    }
  }
  ballFlag = false;
  vex::task::sleep(100);
  conveyor.stop();
  trashHandler.stop();

  //get out of the tower.
  rIntake.spin(forward, -intakeSpeed/2, dps); //outtake, we don't want that ball.
  lIntake.spin(forward, -intakeSpeed/2, dps);
  driveSystem.driveDistance(-250, -450); //drive back the same amount you went in.
  rIntake.stop();
  lIntake.stop();

  //get the next ball.
  driveSystem.turnDegrees(85, 900); //face 90
  rIntake.spin(forward, intakeSpeed, dps); //intake
  lIntake.spin(forward, intakeSpeed, dps);
  driveSystem.driveDistance(1600, 1000); //get ball

  //go to tower
  driveSystem.turnDegrees(52.5, 900);
  driveSystem.driveDistance(800, 720);

  conveyor.spin(forward);
  trashHandler.spin(forward);
  timeStamp = Brain.Timer.value();
  printf("Time: %f\n", timeStamp);
  while(!ballFlag || (dist.objectDistance(inches) < objectRange))
  {
    vex::task::sleep(10);
    if(dist.objectDistance(inches) < objectRange)
    {
      ballFlag = true;
    }
    if((Brain.Timer.value()-timeStamp) > 3)
    {
      break;
    }
  }
  ballFlag = false;
  vex::task::sleep(100);
  printf("Distance: %f\nTime: %f\n", dist.objectDistance(inches), Brain.Timer.value());
  conveyor.stop();
  trashHandler.stop();
  rIntake.stop();
  lIntake.stop();
}
