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
// clicker              limit         B               
// accella              inertial      18              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  accella.calibrate();
  vex::task::sleep(2000);
  double avgPos = 0;
  double target = 0;
  double driveSpeed = 75;
  double turnDeg = -55;
  bRightDrive.setVelocity(driveSpeed, percent);
  bLeftDrive.setVelocity(driveSpeed, percent);
  fRightDrive.setVelocity(driveSpeed, percent);
  fLeftDrive.setVelocity(driveSpeed, percent);
  while(accella.isCalibrating())
  {
    vex::task::sleep(20);
  }

  //Prep to score side tower
  bRightDrive.spinFor(-250, degrees, -180, dps, false);
  fRightDrive.spinFor(-250, degrees, -180, dps, true);

  //run conveyor
  conveyor.spin(forward, 90, percent);
  vex::task::sleep(1000);
  conveyor.stop();

  //turn a little more
  bLeftDrive.spin(forward, driveSpeed*4, dps);
  bRightDrive.spin(forward, -driveSpeed*4, dps);
  fLeftDrive.spin(forward, driveSpeed*4, dps);
  fRightDrive.spin(forward, -driveSpeed*4, dps);
  while(accella.rotation() < 30)
  {
    printf("%f\n", accella.rotation());
    vex::task::sleep(20);
  }
  bLeftDrive.stop();
  bRightDrive.stop();
  fRightDrive.stop();
  bRightDrive.stop();

  //drive to next pos
  bRightDrive.setPosition(0, degrees);
  bLeftDrive.setPosition(0, degrees);
  fRightDrive.setPosition(0, degrees);
  fLeftDrive.setPosition(0, degrees);
  target = 1500;
  bRightDrive.spinFor(target, degrees, false);
  fRightDrive.spinFor(target, degrees, false);
  bLeftDrive.spinFor(target, degrees, false);
  fLeftDrive.spinFor(target, degrees, false);
  while(avgPos < target)
  {
    avgPos = (bLeftDrive.position(degrees) + fLeftDrive.position(degrees) + bRightDrive.position(degrees) + fRightDrive.position(degrees))/4;
    printf("br%f\nbl%f\nfr%f\nfl%f\n", bRightDrive.position(degrees), bLeftDrive.position(degrees), fRightDrive.position(degrees), fLeftDrive.position(degrees));
    vex::task::sleep(20);
  }
  bLeftDrive.stop(brakeType::coast);
  bRightDrive.stop(brakeType::coast);
  fRightDrive.stop(brakeType::coast);
  bRightDrive.stop(brakeType::coast);

  //turn toward ball
  bLeftDrive.spin(forward, -driveSpeed*4, dps);
  bRightDrive.spin(forward, driveSpeed*4, dps);
  fLeftDrive.spin(forward, -driveSpeed*4, dps);
  fRightDrive.spin(forward, driveSpeed*4, dps);
  while(accella.rotation() > turnDeg)
  {
    printf("%f\n", accella.rotation());
    vex::task::sleep(20);
  }
  bLeftDrive.stop();
  bRightDrive.stop();
  fRightDrive.stop();
  bRightDrive.stop();
  printf("I made it!\n");
  printf("I really made it!\n");

  //drive into ball and tower.
  target = 870;
  rIntake.spin(forward, 90, percent);
  lIntake.spin(forward, 90, percent);
  bRightDrive.setPosition(0, degrees);
  bLeftDrive.setPosition(0, degrees);
  fRightDrive.setPosition(0, degrees);
  fLeftDrive.setPosition(0, degrees);
  bRightDrive.spinFor(target, degrees, 450, dps, false);
  printf("BR\n");
  fRightDrive.spinFor(target, degrees, 450, dps, false);
  printf("FR\n");
  bLeftDrive.spinFor(target, degrees, 450, dps, false);
  printf("BL\nFL\n");
  fLeftDrive.spinFor(target, degrees, 450, dps, true);
  //while((avgPos < target))
  //{
    //avgPos = (bLeftDrive.position(degrees) + fLeftDrive.position(degrees) + bRightDrive.position(degrees) + fRightDrive.position(degrees))/4;
  //}
  bLeftDrive.stop();
  bRightDrive.stop();
  fRightDrive.stop();
  bRightDrive.stop();
  conveyor.spin(forward, 90, percent);
  trashHandler.spin(forward, -90, percent);  
  vex::task::sleep(1100);
  conveyor.stop();
  trashHandler.stop();
  rIntake.stop();
  lIntake.stop();

  bRightDrive.spinFor(-500, degrees, false);
  fRightDrive.spinFor(-500, degrees, false);
  bLeftDrive.spinFor(-500, degrees, false);
  fLeftDrive.spinFor(-500, degrees, true);
}
