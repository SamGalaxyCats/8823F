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



void ConveyorSystem::autoSort(double systemSpeed, bool redTrash)
{
  if((ballToProcess.isRed && redTrash) || (!ballToProcess.isRed && !redTrash))
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
  takingDown = false;
  conveyor.spin(forward, systemSpeed, percent); //intake
  trashHandler.spin(forward, systemSpeed, percent); //trash is had, spit out ball
}

void ConveyorSystem::takeUp(double systemSpeed)
{
  takingDown = false;
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
  takingDown = true;
  conveyor.spin(forward, -systemSpeed, percent); //outtake
  trashHandler.spin(forward, systemSpeed, percent); //trash handler helps spit out this ball
}

void ConveyorSystem::update(bool redTrash, double redTreshhold, double objectRange)
{
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

    intakeBall.inQueue = true;
    intakeBall.isRed = hadRed;
  }

  //If the optical sensor loses sight of the intakeBall AND we're outtaking, un-queue it.
  if(intakeBall.inQueue && !eyes.isNearObject() && intakesReversed)
  {
    intakeBall.inQueue = false;
  }

  //If the optical sensor loses sight of the ball and we weren't outtaking, it made it in.
  if(intakeBall.inQueue && !eyes.isNearObject() && !intakesReversed)
  {
    handleEntry();
  }

  //If we're outtaking and there is no intake ball, trip a flag.
  if(intakesReversed && !intakeBall.inQueue)
  {
    outTakeFlag = true;
  }

  //If we stop outtaking, untrip the flag.
  if(outTakeFlag && !intakesReversed)
  {
    outTakeFlag = false;
  }

  //If we see a ball whilst the flag is tripped, start unqueuing from the bottom.
  if(outTakeFlag && intakeBall.inQueue)
  {
    handleUnqueue();
    outTakeFlag = false;
  }

  //If the limit switch is clicked, set a boolean to true.
  if(clickL.pressing())
  {
    clickerPressed = true;
  }
  
  //Once the limit switch isn't being pressed and the boolean is true, handle the exit.
  if(clickerPressed && !clickL.pressing())
  {
    handleExit();
    clickerPressed = false;
  }

  //If an object goes within range of the distance sensor, set a boolean to true.
  if((dist.objectDistance(inches) < objectRange) && !takingDown)
  {
    exitingObjectInRange = true;
  }

  //If the object leaves the range of the distance sensor, but the conveyor is reversed, set the flag to false.
  if(exitingObjectInRange && takingDown && !(dist.objectDistance(inches) < objectRange))
  {
    exitingObjectInRange = false;
  }

  //If the object leaves the range of the distance sensor and is going up, set the flag to false and handle the exit.
  if(exitingObjectInRange && !takingDown && !(dist.objectDistance(inches) < objectRange))
  {
    handleExit();
    exitingObjectInRange = false;
  }

  //If the distance sensor detects an object, but the system is in reverse, it needs to trip a different flag.
  if((dist.objectDistance(inches) < objectRange) && takingDown)
  {
    reenteringObjectInRange = true;
  }

  //If the distance sensor loses the object and it is going down, handle reentry.
  if(reenteringObjectInRange && takingDown && !(dist.objectDistance(inches) < objectRange))
  {
    handleReentry();
    reenteringObjectInRange = false;
  }

  //If the distance sensor loses the object and it is going up, untrip the flag.
  if(reenteringObjectInRange && !takingDown && !(dist.objectDistance(inches) < objectRange))
  {
    reenteringObjectInRange = false;
  }
}

void ConveyorSystem::handleEntry()
{
  //Don't run this without an intake ball!
  printf("handling entry\n");
  if(!intakeBall.inQueue)
  {
    return;
  }

  if(!ballToProcess.inQueue)
  {
    ballToProcess.inQueue = true;
    ballToProcess.isRed = intakeBall.isRed;
    intakeBall.inQueue = false;
  }
  else if(ballToProcess.inQueue && !nextBall.inQueue)
  {
    nextBall.inQueue = true;
    nextBall.isRed = intakeBall.isRed;
    intakeBall.inQueue = false;
  }
  else if(ballToProcess.inQueue && nextBall.inQueue && !afterNextBall.inQueue)
  {
    afterNextBall.inQueue = true;
    afterNextBall.isRed = intakeBall.isRed;
    intakeBall.inQueue = false;
  }
  else
  {
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Overqueued!");
    printf("Overqueued!");
    return;
  }
}

void ConveyorSystem::handleExit()
{
  printf("handling exit\n");
  lastBall.isRed = ballToProcess.isRed;
  if(nextBall.inQueue)
  {
    ballToProcess.isRed = nextBall.isRed;
    if(afterNextBall.inQueue)
    {
      afterNextBall.inQueue = false;
      nextBall.isRed = afterNextBall.isRed;
    }
    else 
    {
      nextBall.inQueue = false;
    }
  }
  else
  {
    ballToProcess.inQueue = false;
  }
}

void ConveyorSystem::handleReentry()
{
  printf("handling reentry\n");
  if(afterNextBall.inQueue)
  {
    afterNextBall.inQueue = false;
  }

  if(nextBall.inQueue)
  {
    afterNextBall.inQueue = true;
    afterNextBall.isRed = nextBall.isRed;
  }

  if(ballToProcess.inQueue)
  {
    nextBall.inQueue = true;
    nextBall.isRed = ballToProcess.isRed;
  }

  ballToProcess.inQueue = true;
  ballToProcess.isRed = lastBall.isRed;
}

void ConveyorSystem::handleUnqueue()
{
  printf("handling unqueue\n");
  if(afterNextBall.inQueue)
  {
    afterNextBall.inQueue = false;
  }
  else if(nextBall.inQueue)
  {
    nextBall.inQueue = false;
  }
  else if(ballToProcess.inQueue)
  {
    ballToProcess.inQueue = false;
  }
  else
  {
    printf("There was an extra ball in there??");
  }
}