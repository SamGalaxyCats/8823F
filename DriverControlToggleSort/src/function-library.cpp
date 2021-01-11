#include "function-library.h"
#include "vex.h"

//Check to make sure motors aren't overheating.
void BackgroundTask::heatCheck()
{
  bool overheat = false;
  int badHeat = 55;
  if(lIntake.temperature(celsius) > badHeat)
  {
    overheat = true;
    printf("lIntake overheating/n");
  }
  if(rIntake.temperature(celsius) > badHeat)
  {
    overheat = true;
    printf("rIntake overheating/n");
  }
  if(trashHandler.temperature(celsius) > badHeat)
  {
    overheat = true;
    printf("trashHandler overheating/n");
  }
  if(conveyor.temperature(celsius) > badHeat)
  {
    overheat = true;
    printf("conveyor overheating/n");
  }
  if(bLeftDrive.temperature(celsius) > badHeat)
  {
    overheat = true;
    printf("bLeftDrive overheating/n");
  }
  if(bRightDrive.temperature(celsius) > badHeat)
  {
    overheat = true;
    printf("bRightDrive overheating/n");
  }
  if(fLeftDrive.temperature(celsius) > badHeat)
  {
    overheat = true;
    printf("fLeftDrive overheating/n");
  }
  if(fRightDrive.temperature(celsius) > badHeat)
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

void Ball::lockColor(bool wasRed)
{
  isLocked = true;
  isRed = wasRed;
}

void Ball::unlockColor()
{
  isLocked = false;
}

void ConveyorSystem::lockConveyorBall()
{
  conveyorBall.lockColor(intakeBall.isRed);
}

void ConveyorSystem::lockIntakeBall()
{
  intakeBall.lockColor(hadRed);
}

bool ConveyorSystem::hasTrash(bool redTrash, double objectRange, double redTreshhold, bool currentState)
{
  if(conveyorBall.isRed && redTrash)
  {
    hadTrash = true; //You have trash
    return true;
  }
  //If it's not red, and blue is trash
  else if(!conveyorBall.isRed && !redTrash)
  {
    hadTrash = true; //You have trash
    return true;
  }
  //If it's red and blue is trash or vice versa,
  else
  {
      hadTrash = false; //There is no trash.
      return false;
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

void ConveyorSystem::update(bool redTrash, double redTreshhold, double objectRange)
{
  //New autosorting logic:
  //If the limit switches are being pressed, lock in the conveyor ball and unlock the intake ball.
  if(clickL.pressing() || clickR.pressing())
  {
    lockConveyorBall();
    intakeBall.unlockColor();
  }
  //If the distance sensor sees an object, lock in the intake ball again.
  else if(dist.objectDistance(inches) <= objectRange)
  {
    lockIntakeBall();
  }
  
  //If the optical sensor detects an object,
  if(eyes.isNearObject())
  {
    //determine whether it is red.
    if(eyes.hue() <= redTreshhold)
    {
      hadRed = true;
    }
    else
    {
      hadRed = false;
    }
  }
}