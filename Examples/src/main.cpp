/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Bow                                              */
/*    Created:      Tue May 19 2020                                           */
/*    Description:  This file will contain some important examples of useful  */
/*                  functions to keep in mind as we head into a new year.     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

//Here's the order of operations for motor configurations: 
// 1) Drivetrain.  If you're using a drivetrain, you want to configure that in the menu first
// 2) Other motors.  Still use the menu for those, that makes it easier to find.  Be certain about gear ratios.
// 3) Sensors, though we don't have those as of writing this, so I can't do a test with them.
// 4) Double check everything.  Once you go to step 5, there's no going back, or you'll have to repeat this entire list.
// 5) Enable expert robot configuration.  If you disable this after enabling it, it will reset all of your configurations, so from this point onwards all configuration has to be manual.
// 6) Measure the base.  Adjust the values in the drivetrain accordingly.
//    a) The numbers in order are: Track Width (from one side to the other, start in the center of one wheel and stop in the center of the wheel that mirrors it) 
//    b) Wheelbase (distance between two wheels on the same side from axel to axel).  
//       These are the only ones you should need to change.  If they are x and y respectively, find x, y, mm in the line that defines drivetrain.
// 7) Set up the extern motors in the header.  That way you can access the drivetrain motors individually.
//    Example: extern motor leftMotorB;
//             extern motor fLeftDrive;
// 8) Make a reference for the inertial sensor and drivetrain motors
//    Example: motor fLeftDrive = leftMotorB;
// 9) If you need to adjust any values or ports retroactively, either make a new file and fiddle around with the configurations with expert mode disabled until you know what to change,
//    or copy the drivetrain stuff, paste it in another file or a google doc, disable expert mode, fix whatever needs to be fixed, re enable expert mode, and paste in the important individual lines.

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2, 19, 20, 4 
// Claw                 motor         3               
// arm                  motor         5               
// bumpSwitch           bumper        A               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "library.h" //do this after you've set up the .h file and the .cpp.  It's not necessary but it'll give you lots of errors until you're done setting those up.

using namespace vex;

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  // This file will use manual configurations
  vexcodeInit();
  motion move; //Declare an object of your class so you can use the methods.
  move.forward(10);

}
