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
// lIntake              motor         15              
// rIntake              motor         16              
// trashHandler         motor         5               
// conveyor             motor         3               
// eyes                 optical       20              
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
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
  double speedL = 0;
  double speedR = 0;
  bool tank = false;
  double conveyorSpeed = 90;

  bool hasTrash = false;
  int redLimit = 50;

  double speedReducer = 1.5;
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("You got this! :D");
  // Prevent main from exiting with an infinite loop.
  while (true) 
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
  
  //trash check
  if(eyes.hue() < redLimit)
  {
    hasTrash = true;
  }
  else
  {
    hasTrash = false;
  }
  //printf("\n%f", eyes.hue());
  //conveyor w/ autosorter
  if((Controller1.ButtonUp.pressing() && !hasTrash) || Controller1.ButtonL1.pressing())
  {
    conveyor.spin(forward, conveyorSpeed, percent); //intake
    trashHandler.spin(forward, -conveyorSpeed, percent); //trash handler helps lift this ball
  }
  else if(Controller1.ButtonDown.pressing())
  {
    conveyor.spin(forward, -conveyorSpeed, percent); //outtake
    trashHandler.spin(forward, -conveyorSpeed, percent); //trash handler helps spit out this ball
  }
  else if((Controller1.ButtonRight.pressing() && hasTrash) || Controller1.ButtonL2.pressing())
  {
    conveyor.spin(forward, conveyorSpeed, percent); //intake
    trashHandler.spin(forward, conveyorSpeed, percent); //trash is had, spit out ball
  }
  else
  {
    conveyor.stop();
    trashHandler.stop();
  }
   //intakes
  if(Controller1.ButtonR1.pressing())
  {
    lIntake.spin(forward, 75, percent); //inkake
    rIntake.spin(forward, 75, percent);
  }
  else if(Controller1.ButtonR2.pressing())
  {
    lIntake.spin(forward, -75, percent); //outkake
    rIntake.spin(forward, -75, percent);
  }
  else
  {
    lIntake.stop();
    rIntake.stop();
  }
  wait(20, msec);

  }
}
