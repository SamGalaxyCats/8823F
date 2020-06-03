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
// LeftMotor            motor         1               
// RightMotor           motor         10              
// ClawMotor            motor         3               
// ArmMotor             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath> //std::abs
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

//Settings
double kP = 0.0;
double kI = 0.0;
double kD = 0.0;
double turnkP = 0.0;
double turnkI = 0.0;
double turnkD = 0.0;

//Autonomous Settings
int desiredValue = 200;
int desiredTurnValue = 0;

int error; //SensorValue - DesiredValue : Position
int prevError = 0; //Position 20 miliseconds ago
int derivative; // error - prevError : Speed
int totalError = 0; //totalError = totalError + error

int turnError; //SensorValue - DesiredValue : Position
int turnPrevError = 0; //Position 20 miliseconds ago
int turnDerivative; // error - prevError : Speed
int turnTotalError = 0; //totalError = totalError + error

bool resetDriveSensors = false;

//Variables modified for use
bool enableDrivePID = true;

int drivePID(){
  
  while(enableDrivePID){

    if (resetDriveSensors) {
      resetDriveSensors = false;
      LeftMotor.setPosition(0,degrees);
      RightMotor.setPosition(0,degrees);
    }


    //Get the position of both motors
    int leftMotorPosition = LeftMotor.position(degrees);
    int rightMotorPosition = RightMotor.position(degrees);

    ///////////////////////////////////////////
    //Lateral movement PID
    /////////////////////////////////////////////////////////////////////
    //Get average of the two motors
    int averagePosition = (leftMotorPosition + rightMotorPosition)/2;

    //Potential
    error = averagePosition - desiredValue;

    //Derivative
    derivative = error - prevError;

    //Integral
    totalError += error;

    double lateralMotorPower = error * kP + derivative * kD + totalError * kI;
    /////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////
    //Turning movement PID
    /////////////////////////////////////////////////////////////////////
    //Get average of the two motors
    int turnDifference = leftMotorPosition - rightMotorPosition;

    //Potential
    turnError = turnDifference - desiredTurnValue;

    //Derivative
    turnDerivative = turnError - turnPrevError;

    //Integral
    turnTotalError += turnError;

    double turnMotorPower = turnError * turnkP + turnDerivative * turnkD + turnTotalError * turnkI;
    /////////////////////////////////////////////////////////////////////

    LeftMotor.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    RightMotor.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt);


    

    prevError = error;
    turnPrevError = turnError;
    vex::task::sleep(20);

  }

  return 1;
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

  vex::task billWiTheScienceFi(drivePID);

  resetDriveSensors = true;
  desiredValue = 300;
  desiredTurnValue = 600;

  vex::task::sleep(1000);

  resetDriveSensors = true;
  desiredValue = 300;
  desiredTurnValue = 300;


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

  enableDrivePID = false;

  ///////////////////////////
  //Settings
  ///////////////////////////////////////////////////////////////////////////

  //Drivetrain
  double turnImportance = 0.5;

  while (1) {

    ///////////////////////////
    //Driver Control
    ///////////////////////////////////////////////////////////////////////////
    double turnVal = Controller1.Axis1.position(percent);
    double forwardVal = Controller1.Axis3.position(percent);

    double turnVolts = turnVal * 0.12;
    double forwardVolts = forwardVal * 0.12 * (1 - (std::abs(turnVolts)/12.0) * turnImportance);

    //0 - 12 = -12
    //0 + 12 = 12(due to cap)


    LeftMotor.spin(forward, forwardVolts + turnVolts, voltageUnits::volt);
    RightMotor.spin(forward, forwardVolts - turnVolts, voltageUnits::volt);
    ///////////////////////////////////////////////////////////////////////////


    ///////////////////////////
    //Arm Control
    ///////////////////////////////////////////////////////////////////////////
    bool topRightButton = Controller1.ButtonR1.pressing();
    bool bottomRightButton = Controller1.ButtonR2.pressing();

    if (topRightButton){
      ArmMotor.spin(forward, 12.0, voltageUnits::volt);
    }
    else if (bottomRightButton){
      ArmMotor.spin(forward, -12.0, voltageUnits::volt);
    }
    else{
      ArmMotor.spin(forward, 0, voltageUnits::volt);
    }
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////
    //Claw Control
    ///////////////////////////////////////////////////////////////////////////
    bool topLeftButton = Controller1.ButtonL1.pressing();
    bool bottomLeftButton = Controller1.ButtonL2.pressing();

    if (topLeftButton){
      ClawMotor.spin(forward, 12.0, voltageUnits::volt);
    }
    else if (bottomLeftButton){
      ClawMotor.spin(forward, -12.0, voltageUnits::volt);
    }
    else{
      ClawMotor.spin(forward, 0, voltageUnits::volt);
    }
    ///////////////////////////////////////////////////////////////////////////



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
