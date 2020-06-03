/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Bow                                              */
/*    Created:      Fri May 22 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor         1               
// rightMotor           motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath> //std::abs for absolute value.
using namespace vex;

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

int drivePID()
{
  
  while(enableDrivePID)
  {

    if (resetDriveSensors) 
    {
      resetDriveSensors = false;
      leftMotor.setPosition(0,degrees);
      rightMotor.setPosition(0,degrees);
    }


    //Get the position of both motors
    int leftMotorPosition = leftMotor.position(degrees);
    int rightMotorPosition = rightMotor.position(degrees);

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

    leftMotor.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    rightMotor.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt);


    

    prevError = error;
    turnPrevError = turnError;
    vex::task::sleep(20); 

  }

  return 1;
}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  wait(20, msec); //Don't go over 30msec in driver control.
}