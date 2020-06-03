/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Tue Oct 01 2019                                           */
/*    Description:  Detecting Distances                                       */
/*                  This program will use the Range Finder to stop a robot    */
/*                  300 mm away from a wall.                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 10           
// RangeFinderC         sonar         C, D            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Wait 1 second before driving forward.
  wait(1, seconds);

  // The robot will stop driving when the Range Finder is less than 300 mm away
  // from an object.
  while (RangeFinderC.distance(mm) > 300) {
    Drivetrain.drive(forward);
    Brain.Screen.print("%.2f", RangeFinderC.distance(mm));
    wait(200, msec);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.clearScreen();
    wait(5, msec);
  }
  Drivetrain.stop();
}
