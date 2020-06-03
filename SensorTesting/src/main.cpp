/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Bow                                              */
/*    Created:      Sun May 31 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// leftDrive            motor         20              
// rightDrive           motor         11              
// accella              inertial      6               
// rightEncoder         encoder       C, D            
// leftEncoder          encoder       G, H            
// sight                vision        15              
// ultrasonic           sonar         E, F            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int printStats()
{
  int counter = 0;
  while(true)
  {
    printf("Positions: %.2f %.2f, %.2f degrees\n", leftEncoder.position(degrees), rightEncoder.position(degrees), accella.heading());
    vex::task::sleep(500); //print the stats every half second
  }
  return 1;
};

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  printf("\nHello, world!");
  wait(1, seconds);
  double distanse = ultrasonic.distance(inches);
  printf("\nDistance: %.2f\n", distanse);
  vex::task::sleep(500);
  accella.calibrate();

  /*if(ultrasonic.foundObject() && sight.objects[0].exists)
  {
    printf("\nI see something, and I know what it is!\n");
  }
  else if(ultrasonic.foundObject())
  {
    printf("\nI see something, but I don't know what it is.\n");
  }
  else
  {
    printf("\nI need to be reconfigured, I think.\n");
  }*/

  printf("Positions: %.2f %.2f, %.2f degrees\n", leftEncoder.position(degrees), rightEncoder.position(degrees), accella.heading());
  leftDrive.spinFor(forward, 720, degrees, false);
  rightDrive.spinFor(forward, 720, degrees);
  printf("Positions: %.2f %.2f, %.2f degrees\n", leftEncoder.position(degrees), rightEncoder.position(degrees), accella.heading());
  accella.calibrate();

  while((accella.heading() < 180))
  {
    leftDrive.spin(forward, -50, percent);
    rightDrive.spin(forward, 50, percent);
  }

  leftDrive.stop();
  rightDrive.stop();

  while(1)
  {
    vex::task::sleep(500);
    printf("Positions: %.2f %.2f\n", leftEncoder.position(degrees), rightEncoder.position(degrees)); 
    printf("Positions: %.2f %.2f, %.2f degrees\n", leftEncoder.position(degrees), rightEncoder.position(degrees), accella.heading());
  }
}
