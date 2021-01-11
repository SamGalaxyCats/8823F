/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\sambo                                            */
/*    Created:      Fri Jan 01 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// shaftEncoder         rotation      13              
// bLeftDrive           motor         9               
// bRightDrive          motor         10              
// fLeftDrive           motor         11              
// fRightDrive          motor         12              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  shaftEncoder.resetPosition();
  double speedL = 0;
  double speedR = 0;
  printf("\n");
  while(1)
  {
    speedL = Controller1.Axis3.position();
    speedR = Controller1.Axis2.position();
    bLeftDrive.spin(forward, speedL, percent);
    fLeftDrive.spin(forward, speedL, percent);
    bRightDrive.spin(forward, speedR, percent);
    fRightDrive.spin(forward, speedR, percent);

    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("BL: %f", bLeftDrive.position(degrees));
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("BR: %f", bRightDrive.position(degrees));
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("FL: %f", fLeftDrive.position(degrees));
    Controller1.Screen.setCursor(4, 1);
    Controller1.Screen.print("FR: %f", fRightDrive.position(degrees));
    Controller1.Screen.setCursor(5, 1);
    Controller1.Screen.print("SE: %f", shaftEncoder.position(degrees));

    vex::task::sleep(20);
    printf("\nPos: %f, V: %f, Time: %lu", shaftEncoder.position(degrees), shaftEncoder.velocity(dps), shaftEncoder.timestamp());
  }
}
