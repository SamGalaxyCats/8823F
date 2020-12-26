// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// fLeftDrive           motor         1               
// fRightDrive          motor         9               
// bLeftDrive           motor         11              
// bRightDrive          motor         19              
// Controller1          controller                    
// trashHandler         motor         5               
// conveyor             motor         3               
// lIntake              motor         15              
// rIntake              motor         16              
// Accella              inertial      18              
// eyes                 optical       12              
// dist                 distance      13              
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"
#include "function-library.h"
using namespace vex;


int statusCheck()
{
  BackgroundTask status;
  while(true)
  {
    status.heatCheck();
    printf("BR: %f \nBL: %f\nFR %f\nFL %f\n", bRightDrive.position(degrees), bLeftDrive.position(degrees), fRightDrive.position(degrees), fLeftDrive.position(degrees));
    vex::task::sleep(10000); //check the heat of the motors once every 25 seconds
  }
  return 1;
};

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
  bool hadTrash = false;
  int redLimit = 55;
  double objectRange = 6;
  bool trashFound = false;
  ConveyorSystem autoSorter;
  //eyes.setLightPower(10, percent);
  conveyor.setStopping(brake);
  trashHandler.setStopping(brake);

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
    trashFound = autoSorter.hasTrash(true, objectRange, redLimit, hadTrash);

    //conveyor w/ autosorter
    if(Controller1.ButtonL1.pressing())
    {
      autoSorter.takeUp(conveyorSpeed);
    }
    else if(Controller1.ButtonDown.pressing())
    {
      autoSorter.takeDown(conveyorSpeed);
    }
    else if(Controller1.ButtonL2.pressing())
    {
      autoSorter.spitOut(conveyorSpeed);
    }
    else if(Controller1.ButtonUp.pressing())
    {
      autoSorter.autoSort(trashFound, conveyorSpeed);
      Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print(eyes.hue());
    }
    else
    {
      autoSorter.stopConveyor();
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
 
