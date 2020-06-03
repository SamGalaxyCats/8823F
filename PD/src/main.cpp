/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Bow                                              */
/*    Created:      Sun May 24 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

//kP = 0.5, distance 56.75in, error stuck at 12.
//kP = 0.75, distance 55in, error reached 10.
//kP = 0.75, distance 54.75in, error reached 10, slight left tilt.
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftDrive            motor         1               
// rightDrive           motor         10              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

double kP = 0.75;
double kD = 0;
int pos = (leftDrive.position(degrees) + rightDrive.position(degrees)) / 2;
int error = 180;
int prevError = 0;
int derivative = error - prevError;
double speed;

int printStats()
{
  int counter = 0;
  while(true)
  {
    printf("Print statement %d.\n", counter);
    printf("Left position | Right position | Average | Error | Previous Error | Derivative | Speed\n");
    printf(" %f    | %f       | %d       | %d     | %d       | %d        | %f\n", leftDrive.position(degrees), rightDrive.position(degrees), pos, error, prevError, derivative, speed);
    counter++;
    vex::task::sleep(500); //print the stats every half second
  }
  return 1;
};

double dabs (double num)
{
  if(num < 0)
  {
    num *= -1;
  }
  return num;
}

void PD(int target)
{ 
  error = target;
  int stoppingRange = 10;
  while(dabs(error) > stoppingRange)
  {
    pos = (leftDrive.position(degrees) + rightDrive.position(degrees)) / 2;
    error = target - pos;
    derivative = error - prevError;

    speed = (error * kP) + (derivative * kD);
    leftDrive.spin(forward, speed, dps);
    rightDrive.spin(forward, speed, dps);
    prevError = error;

    wait(20, msec);
  }
  leftDrive.stop();
  rightDrive.stop();
}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  vex::task numbers(printStats);
  while(!Controller1.ButtonA.pressing())
  {
    wait(30, msec);
  }
  PD(1800); //53in 54in 54in 54in
  numbers.stop();
  printf("End result: \n");
  printf("Left position | Right position | Average | Error | Previous Error | Derivative | Speed\n");
  printf(" %f    | %f       | %d       | %d     | %d       | %d        | %f\n", leftDrive.position(degrees), rightDrive.position(degrees), pos, error, prevError, derivative, speed);
  Controller1.Screen.print("Done!");
}
