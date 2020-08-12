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
  while(true)
  {
    printf("Positions: %.2f / %.2f | %.2f / %.2f, %.2f degrees\n", leftEncoder.position(degrees), leftDrive.position(degrees), rightEncoder.position(degrees), rightDrive.position(degrees), accella.rotation(degrees));
    vex::task::sleep(250); //print the stats every half second
  }
  return 1;
};

double sensorFix(double reading)
{
  /*if(reading > 357)
  {
    return 0.0;
  }
  else if(reading < -357)
  {
    return 0.0;
  }
  else
  {*/
    return reading;
  //}
}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  accella.calibrate();
  while(accella.isCalibrating())
  {
    vex::task::sleep(250);
  }
  vex::task stats(printStats);
  printf("\nHello, world!");
  wait(1, seconds);
  double distanse = ultrasonic.distance(inches);
  printf("\nDistance: %.2f\n", distanse);
  vex::task::sleep(500);

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

  //printf("Positions: %.2f / %.2f | %.2f / %.2f, %.2f degrees\n", leftEncoder.position(degrees), leftDrive.position(degrees), rightEncoder.position(degrees), rightDrive.position(degrees), accella.rotation(degrees));
  //leftDrive.spinFor(forward, 720, degrees, false);
  //rightDrive.spinFor(forward, 720, degrees);
  //printf("Positions: %.2f / %.2f | %.2f / %.2f, %.2f degrees\n", leftEncoder.position(degrees), leftDrive.position(degrees), rightEncoder.position(degrees), rightDrive.position(degrees), accella.rotation(degrees));

  while((accella.rotation(degrees) > -180))
  {
    leftDrive.spin(forward, -50, percent);
    rightDrive.spin(forward, 50, percent);
  }

  leftDrive.stop();
  rightDrive.stop();

  while(1)
  {
    vex::task::sleep(500);
    //printf("Positions: %.2f / %.2f | %.2f / %.2f, %.2f degrees\n", leftEncoder.position(degrees), leftDrive.position(degrees), rightEncoder.position(degrees), rightDrive.position(degrees), accella.rotation(degrees));
  }
}
