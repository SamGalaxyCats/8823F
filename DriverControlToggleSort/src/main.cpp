         
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// conveyor             motor         3              
// fLeftDrive           motor         1              
// fRightDrive          motor         9              
// bLeftDrive           motor         11             
// bRightDrive          motor         19             
// trashHandler         motor         5              
// lIntake              motor         15             
// rIntake              motor         16             
// Controller1          controller                   
// eyes                 optical       12             
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// conveyor             motor         3              
// fLeftDrive           motor         1              
// fRightDrive          motor         9              
// bLeftDrive           motor         11             
// bRightDrive          motor         19             
// trashHandler         motor         5              
// lIntake              motor         15             
// rIntake              motor         16             
// Controller1          controller                   
// eyes                 optical       12             
// Optical8             optical       8              
 
#include "vex.h"
using namespace vex;
int heatCheck()
{
while(true)
{
  bool overheat = false;
  int badHeat = 50;
  if(lIntake.temperature() > badHeat)
  {
    overheat = true;
    printf("lIntake overheating/n");
  }
  if(rIntake.temperature() > badHeat)
  {
    overheat = true;
    printf("rIntake overheating/n");
  }
  if(trashHandler.temperature() > badHeat)
  {
    overheat = true;
    printf("trashHandler overheating/n");
  }
  if(conveyor.temperature() > badHeat)
  {
    overheat = true;
    printf("conveyor overheating/n");
  }
  if(bLeftDrive.temperature() > badHeat)
  {
    overheat = true;
    printf("bLeftDrive overheating/n");
  }
  if(bRightDrive.temperature() > badHeat)
  {
    overheat = true;
    printf("bRightDrive overheating/n");
  }
  if(fLeftDrive.temperature() > badHeat)
  {
    overheat = true;
    printf("fLeftDrive overheating/n");
  }
  if(fRightDrive.temperature() > badHeat)
  {
    overheat = true;
    printf("fRightDrive overheating/n");
  }
  if(overheat)
  {
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Motors overheating");
  }
  else
  {
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Motors are fine :D");
  }
  vex::task::sleep(5000); //check the heat of the motors once every 5 seconds
}
return 1;
};
int main()
{
// Initializing Robot Configuration. DO NOT REMOVE!
vexcodeInit();
vex::task stats(heatCheck);
double speedL = 0;
double speedR = 0;
bool tank = false;
double conveyorSpeed = 90;
Controller1.Screen.clearScreen();
 
bool hasTrash = false;
int redLimit = 50;
//trashHandler.setStopping(hold);
//lIntake.setStopping(hold);
//rIntake.setStopping(hold);
//conveyor.setStopping(hold);
double speedReducer = 1.5;
while(true)
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
  if((Controller1.ButtonL1.pressing() && !hasTrash) || Controller1.ButtonUp.pressing())
  {
    conveyor.spin(forward, conveyorSpeed, percent); //intake
    trashHandler.spin(forward, -conveyorSpeed, percent); //trash handler helps lift this ball
  }
  else if(Controller1.ButtonL2.pressing())
  {
    conveyor.spin(forward, -conveyorSpeed, percent); //outtake
    trashHandler.spin(forward, -conveyorSpeed, percent); //trash handler helps spit out this ball
  }
  else if((Controller1.ButtonL1.pressing() && hasTrash) || Controller1.ButtonRight.pressing())
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
 
