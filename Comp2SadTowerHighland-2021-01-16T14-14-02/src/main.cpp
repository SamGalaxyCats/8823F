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
// rIntake              motor         16              
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
  double avgPos = 0;
  double target = 0;
  double driveSpeed = 75;
  double turnDeg = -42.5;
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

  //Drive a smidge forward
  bRightDrive.setPosition(0, degrees);
  bLeftDrive.setPosition(0, degrees);
  fRightDrive.setPosition(0, degrees);
  fLeftDrive.setPosition(0, degrees);
  target = 100;
  bRightDrive.spinFor(target, degrees, 180, dps, false);
  fRightDrive.spinFor(target, degrees, 180, dps, false);
  bLeftDrive.spinFor(target, degrees, 180, dps, false);
  fLeftDrive.spinFor(target, degrees, 180, dps, true);
  bLeftDrive.stop();
  fLeftDrive.stop();
  fRightDrive.stop();
  bRightDrive.stop();

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
  target = 1250;
  bRightDrive.spinFor(target, degrees, false);
  fRightDrive.spinFor(target, degrees, false);
  bLeftDrive.spinFor(target, degrees, false);
  fLeftDrive.spinFor(target, degrees, false);
  while(avgPos < target)
  {
    avgPos = (bLeftDrive.position(degrees) + fLeftDrive.position(degrees) + bRightDrive.position(degrees) + fRightDrive.position(degrees))/4;
    //printf("br%f\nbl%f\nfr%f\nfl%f\n", bRightDrive.position(degrees), bLeftDrive.position(degrees), fRightDrive.position(degrees), fLeftDrive.position(degrees));
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
    //printf("%f\n", accella.rotation());
    vex::task::sleep(20);
  }
  
  //drive into ball and tower.
  target = 900;
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
  bLeftDrive.stop();
  bRightDrive.stop();
  fRightDrive.stop();
  bRightDrive.stop();
  conveyor.spin(forward, 80, percent);
  trashHandler.spin(forward, -80, percent);
  rIntake.stop();
  lIntake.stop();  
  vex::task::sleep(1000);
  conveyor.stop();
  trashHandler.stop();
  rIntake.spin(forward, -75, percent);
  lIntake.spin(forward, -75, percent);

  bRightDrive.spinFor(-500, degrees, false);
  fRightDrive.spinFor(-500, degrees, false);
  bLeftDrive.spinFor(-500, degrees, false);
  fLeftDrive.spinFor(-500, degrees, true);
  rIntake.stop();
  lIntake.stop();  
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
      speedL = ((Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent))/speedReducer); //if the joysticks are wrong, switch the + and -.
      speedR = ((Controller1.Axis3.position(percent) - Controller1.Axis1.position(percent))/speedReducer);
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
