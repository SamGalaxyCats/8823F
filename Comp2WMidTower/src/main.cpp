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
  rIntake.setBrake(brake);
  lIntake.setBrake(brake);
  conveyL.setBrake(brake);
  conveyR.setBrake(brake);
  conveyL.setVelocity(525, rpm);
  conveyR.setVelocity(525, rpm);
  accella.calibrate();
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
  while(accella.isCalibrating())
  {
    vex::task::sleep(20);
  }

  //score 1st tower
  driveSystem.turnOnlyRightBack(19, 300);
  lIntake.spin(forward, -90, percent); //open up
  rIntake.spin(forward, -90, percent);
  conveyL.spin(forward, 90, percent);
  conveyR.spin(forward, 90, percent);
  vex::task::sleep(1500);
  conveyL.stop();
  conveyR.stop();
  lIntake.stop();
  rIntake.stop();


  //Go to 2nd tower
  driveSystem.driveDistance(1200, 600);
  driveSystem.turnDegrees(-88, 300);
  driveSystem.driveDistance(-750, 300, 2);
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
  double speedL = 0;
  double speedR = 0;
  double speedReducer = 1;
  double turnReducer = 0.65;
  double precisionModifier = 0.3;
  double regularModifier = 0.65;
  double conveyorSpeed = 525;
  double intakeSpeed = 540;

  Controller1.Screen.print("20, 10, 8, 4, 16 are dead ports! :)");
  // User control code here, inside the loop
  while (1) 
  {
    //Precision turning
    if((Controller1.Axis3.position(percent) < 30) && (Controller1.Axis3.position(percent) > -30))
    {
      turnReducer = precisionModifier;
    }
    else
    {
      turnReducer = regularModifier;
    }

    //RC Control
    speedL = ((Controller1.Axis3.position(percent) + (Controller1.Axis1.position(percent) * turnReducer))/speedReducer); //if the joysticks are wrong, switch the + and -.
    speedR = ((Controller1.Axis3.position(percent) - (Controller1.Axis1.position(percent) * turnReducer))/speedReducer);
    
    bLeftDrive.spin(forward, speedL, percent);
    fLeftDrive.spin(forward, speedL, percent);
    fRightDrive.spin(forward, speedR, percent);
    bRightDrive.spin(forward, speedR, percent);

    //Intakes
    if(Controller1.ButtonR1.pressing())
    {
      lIntake.spin(forward, intakeSpeed, rpm); //intake
      rIntake.spin(forward, intakeSpeed, rpm);
    }
    else if(Controller1.ButtonR2.pressing())
    {
      lIntake.spin(forward, -intakeSpeed, rpm); //outtake
      rIntake.spin(forward, -intakeSpeed, rpm);
    }
    else
    {
      lIntake.stop();
      rIntake.stop();
    }

    //Conveyor
    if(Controller1.ButtonL1.pressing())
    {
      conveyL.spin(forward, conveyorSpeed, rpm);
      conveyR.spin(forward, conveyorSpeed, rpm);
    }
    else if(Controller1.ButtonL2.pressing())
    {
      conveyL.spin(forward, -conveyorSpeed, rpm);
      conveyR.spin(forward, -conveyorSpeed, rpm);
    }
    else
    {
      conveyL.stop();
      conveyR.stop();
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
