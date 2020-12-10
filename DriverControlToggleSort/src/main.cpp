// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// bLeftDrive           motor         11              
// bRightDrive          motor         20              
// Controller1          controller                    
// trashHandler         motor         5               
// conveyor             motor         3               
// lIntake              motor         15              
// rIntake              motor         16              
// Accella              inertial      18              
// eyes                 optical       12              
// dist                 distance      6               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// bLeftDrive           motor         11              
// bRightDrive          motor         20              
// Controller1          controller                    
// trashHandler         motor         5               
// conveyor             motor         3               
// lIntake              motor         15              
// rIntake              motor         16              
// sight                vision        17              
// Accella              inertial      18              
// eyes                 optical       12              
// dist                 distance      6               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// bLeftDrive           motor         11              
// bRightDrive          motor         20              
// Controller1          controller                    
// trashHandler         motor         5               
// conveyor             motor         3               
// lIntake              motor         15              
// rIntake              motor         16              
// sight                vision        17              
// Accella              inertial      18              
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
// ---- END VEXCODE CONFIGURED DEVICES ----
 
#include "vex.h"
#include "function-library.h"
using namespace vex;

bool hasTrash = false;

int statusCheck()
{
  BackgroundTask status;
  while(true)
  {
    status.heatCheck();
    vex::task::sleep(25000); //check the heat of the motors once every 25 seconds
  }
  return 1;
};

/*int sort()
{
  BackgroundTask handleTrash;
  while(1)
  {
    if(eyes.isNearObject())
    {
      if(handleTrash.isTrash(true))
      {
        hasTrash = true;
      }
      else
      {
        hasTrash = false;
      }
    }
    vex::task::sleep(10000000);
  }
  return 1;
}*/

int main()
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  vex::task stats(statusCheck);

  //drive vars
  double speedL = 0;
  double speedR = 0;
  double speedReducer = 1;
  bool tank = false;

  //conveyor vars
  double conveyorSpeed = 90;
  hasTrash = false;
  int redLimit = 50;
  double objectRange = 5;
  eyes.setLightPower(10, percent);

  //Controller setup
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print("You can do it! :)");
  //BackgroundTask backgroundTask;
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
    if(dist.objectDistance(inches) < objectRange) //if something is close enough to be an object,...
    {
      eyes.setLight(ledState::on); //reduce ambience-induced misreads
      if(eyes.hue() < redLimit) //...and you detect red,...
      {
        hasTrash = true; //you have trash.
      }
      else //If that something isn't red,...
      {
        hasTrash = false; //...it's blue, and it's not trash.
      }
    }
    else //If there's nothing near,...
    {
      eyes.setLight(ledState::off); //...turn the light off to prevent overheating.
    }

    //conveyor w/ autosorter
    if((Controller1.ButtonUp.pressing() && !hasTrash) || Controller1.ButtonR1.pressing())
    {
      conveyor.spin(forward, conveyorSpeed, percent); //intake
      trashHandler.spin(forward, -conveyorSpeed, percent); //trash handler helps lift this ball
    }
    else if(Controller1.ButtonDown.pressing())
    {
      conveyor.spin(forward, -conveyorSpeed, percent); //outtake
      trashHandler.spin(forward, conveyorSpeed, percent); //trash handler helps spit out this ball
    }
    else if((Controller1.ButtonUp.pressing() && hasTrash) || Controller1.ButtonR2.pressing())
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
    if(Controller1.ButtonL1.pressing())
    {
      lIntake.spin(forward, 75, percent); //inkake
      rIntake.spin(forward, 75, percent);
    }
    else if(Controller1.ButtonL2.pressing())
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
 
