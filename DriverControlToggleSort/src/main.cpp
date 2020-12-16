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
  ConveyorSystem autoSorter;
  eyes.setLightPower(10, percent);
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
    if((Controller1.ButtonUp.pressing() && !hasTrash) || Controller1.ButtonL1.pressing())
    {
      autoSorter.takeUp(conveyorSpeed);
    }
    else if(Controller1.ButtonDown.pressing())
    {
      autoSorter.takeDown(conveyorSpeed);
    }
    else if((Controller1.ButtonUp.pressing() && hasTrash) || Controller1.ButtonL2.pressing())
    {
      autoSorter.spitOut(conveyorSpeed);
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
 
