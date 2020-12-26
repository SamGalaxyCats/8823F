#include "function-library.h"
#include "vex.h"

//Check to make sure motors aren't overheating.
void BackgroundTask::heatCheck()
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

}

//Check whether the ball in the conveyor is trash.
bool BackgroundTask::isTrash(bool redTrash)
{
  return true;
}

bool ConveyorSystem::hasTrash(bool redTrash, double objectRange, double redTreshhold, bool currentState)
{
  if(dist.objectDistance(inches) < objectRange)
  {
    //eyes.setLightPower(10, percent);
    //eyes.setLight(ledState::on);
    if((eyes.hue() <= redTreshhold) && redTrash)
    {
      hadTrash = true;
      return true;
    }
    else if((eyes.hue() > redTreshhold) && !redTrash)
    {
      hadTrash = true;
      return true;
    }
    else
    {
      hadTrash = false;
      return false;
    }
  }
  else
  {
    //eyes.setLight(ledState::off);
    return hadTrash;
  }
}

void ConveyorSystem::autoSort(bool foundTrash, double systemSpeed)
{
  if(foundTrash)
  {
    spitOut(systemSpeed);
  }
  else
  {
    takeUp(systemSpeed);
  }
}

void ConveyorSystem::spitOut(double systemSpeed)
{
  conveyor.spin(forward, systemSpeed, percent); //intake
  trashHandler.spin(forward, systemSpeed, percent); //trash is had, spit out ball
}

void ConveyorSystem::takeUp(double systemSpeed)
{
  conveyor.spin(forward, systemSpeed, percent); //intake
  trashHandler.spin(forward, -systemSpeed, percent); //trash handler helps lift this ball
}

void ConveyorSystem::stopConveyor()
{
  conveyor.stop();
  trashHandler.stop();
}

void ConveyorSystem::takeDown(double systemSpeed)
{
  conveyor.spin(forward, -systemSpeed, percent); //outtake
  trashHandler.spin(forward, systemSpeed, percent); //trash handler helps spit out this ball
}