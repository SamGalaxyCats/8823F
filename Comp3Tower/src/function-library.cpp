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

void ConveyorSystem::autoSort(bool redTrash, double objectRange, double redThreshhold, double systemSpeed)
{
  if(dist.objectDistance(inches) < objectRange)
  {
    eyes.setLight(ledState::on);
    if((eyes.hue() <= redThreshhold) && redTrash)
    {
      spitOut(systemSpeed);
    }
    else if((eyes.hue() > redThreshhold) && !redTrash)
    {
      spitOut(systemSpeed);
    }
    else
    {
      takeUp(systemSpeed);
    }
  }
  else
  {
    eyes.setLight(ledState::off);
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

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*\
|*^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^*|
|*                                                                                                         */
//driveDistance methods

//Drive ticks at degreesPerSecond dps. By using the spinFor method, we don't have to rely on time, but we also
//don't have to worry about slight discrepancies in motor rotations having a large overall effect.
void Robot::driveDistance(double ticks, double degreesPerSecond)
{
  bLeftDrive.spinFor(forward, ticks, degrees, degreesPerSecond, dps, false);
  fLeftDrive.spinFor(forward, ticks, degrees, degreesPerSecond, dps, false);
  bRightDrive.spinFor(forward, ticks, degrees, degreesPerSecond, dps, false);
  fRightDrive.spinFor(forward, ticks, degrees, degreesPerSecond, dps, true);
}

//Drive ticks at degreesPerSecond dps with a time limit, so that the robot can't get stuck.
void Robot::driveDistance(double ticks, double degreesPerSecond, double timeLimit)
{
  bLeftDrive.spinFor(forward, ticks, degrees, degreesPerSecond, dps, false);
  fLeftDrive.spinFor(forward, ticks, degrees, degreesPerSecond, dps, false);
  bRightDrive.spinFor(forward, ticks, degrees, degreesPerSecond, dps, false);
  fRightDrive.spinFor(forward, ticks, degrees, degreesPerSecond, dps, false);

  double timeStamp = Brain.Timer.value();
  while(!bLeftDrive.isDone() || !fLeftDrive.isDone() || !bRightDrive.isDone() || !fRightDrive.isDone())
  {
    if((Brain.Timer.value() - timeStamp) > timeLimit)
    {
      printf("Timeout triggered, did we hit a wall?\n");
      break;
    }
  }
  bLeftDrive.stop();
  fLeftDrive.stop();
  bRightDrive.stop();
  fRightDrive.stop();
}

//Drive ticks at degreesPerSecond dps with the option to move to the next line after this method before it completes
//and the option to stop using coast, if it seems like it's too sudden a stop.
void Robot::driveDistance(double ticks, double degreesPerSecond, bool waitForComplete, bool doCoast)
{
  if(doCoast)
  {
    bLeftDrive.setStopping(coast);
    fLeftDrive.setStopping(coast);
    bRightDrive.setStopping(coast);
    fRightDrive.setStopping(coast);
  }

  bLeftDrive.spinFor(forward, ticks, degrees, degreesPerSecond, dps, false);
  fLeftDrive.spinFor(forward, ticks, degrees, degreesPerSecond, dps, false);
  bRightDrive.spinFor(forward, ticks, degrees, degreesPerSecond, dps, false);
  fRightDrive.spinFor(forward, ticks, degrees, degreesPerSecond, dps, waitForComplete);

  //Return Stopping to the default brakeType.
  bLeftDrive.setStopping(brake);
  fLeftDrive.setStopping(brake);
  bRightDrive.setStopping(brake);
  fRightDrive.setStopping(brake);
}
/*                                                                                                         *|
|*v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v*|
\*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*\
|*^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^*|
|*                                                                                                         */
//turnDegrees methods
//This family of methods uses the inertial sensor to turn in place to face an exact rotation.

//turn until you match the desired accella.rotation() value at degreesPerSecond. Should determine which way you need
//to turn to accomplish that and run the related method. If the robot is already there, it informs you of the redundancy.
void Robot::turnDegrees(double degreees, double degreesPerSecond)
{
  if(accella.rotation() < degreees)
  {
    turnRight(degreees, degreesPerSecond);
  }
  else if(accella.rotation() > degreees)
  {
    turnLeft(degreees, degreesPerSecond);
  }
  else
  {
    printf("There was a turn that didn't need to be here.\n");
  }
}

//Same thing as above, but with the option to coast instead of break.
void Robot::turnDegrees(double degreees, double degreesPerSecond, bool doCoast)
{
  if(doCoast)
  {
    bLeftDrive.setStopping(coast);
    fLeftDrive.setStopping(coast);
    bRightDrive.setStopping(coast);
    fRightDrive.setStopping(coast);
  }

  if(accella.rotation() < degreees)
  {
    turnRight(degreees, degreesPerSecond);
  }
  else if(accella.rotation() > degreees)
  {
    turnLeft(degreees, degreesPerSecond);
  }
  else
  {
    printf("There was a turn that didn't need to be here.\n");
  }

  //Return Stopping to the default brakeType.
  bLeftDrive.setStopping(brake);
  fLeftDrive.setStopping(brake);
  bRightDrive.setStopping(brake);
  fRightDrive.setStopping(brake);
}

//Left wheels reverse, as degrees need to go down. This method is called by turnDegrees, but can be used on its own.
//Turns left at degreesPerSecond until accella.rotation() no longer exceeds degrees, at which point it stops.
void Robot::turnLeft(double degreees, double degreesPerSecond)
{
  bLeftDrive.spin(forward, -degreesPerSecond, dps);
  fLeftDrive.spin(forward, -degreesPerSecond, dps);
  bRightDrive.spin(forward, degreesPerSecond, dps);
  fRightDrive.spin(forward, degreesPerSecond, dps);

  while(accella.rotation() > degreees)
  {
    vex::task::sleep(10);
  }
  bLeftDrive.stop();
  bRightDrive.stop();
  fRightDrive.stop();
  bRightDrive.stop();

  printf("Pos: BL %f | FL %f | BR %f | FR %f\nFacing: %f\n", bLeftDrive.position(degrees), fLeftDrive.position(degrees), bRightDrive.position(degrees), fRightDrive.position(degrees), accella.rotation());
}

//Right wheels reverse, as degrees need to go up. This method is called by turnDegrees, but can be used on its own.
//Turns right at degreesPerSecond until accella.rotation() exceeds degrees, at which point it stops.
void Robot::turnRight(double degreees, double degreesPerSecond)
{
  bLeftDrive.spin(forward, degreesPerSecond, dps);
  fLeftDrive.spin(forward, degreesPerSecond, dps);
  bRightDrive.spin(forward, -degreesPerSecond, dps);
  fRightDrive.spin(forward, -degreesPerSecond, dps);

  while(accella.rotation() < degreees)
  {
    vex::task::sleep(10);
  }
  bLeftDrive.stop();
  bRightDrive.stop();
  fRightDrive.stop();
  bRightDrive.stop();
  printf("Pos: BL %f | FL %f | BR %f | FR %f\nFacing: %f\n", bLeftDrive.position(degrees), fLeftDrive.position(degrees), bRightDrive.position(degrees), fRightDrive.position(degrees), accella.rotation());
}

/*                                                                                                         *|
|*v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v*|
\*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*\
|*^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^*|
|*                                                                                                         */
//TurnOnly methods
//Used to turn only one set of wheels, for when we aren't turning in place.  
//Currently only used to make the first turn, but could have future use for precision scoring.


//TurnOnlyLeft
void Robot::turnOnlyLeft(double degreees, double degreesPerSecond)
{
  bLeftDrive.spin(forward, degreesPerSecond, dps);
  fLeftDrive.spin(forward, degreesPerSecond, dps);

  while(accella.rotation() < degreees)
  {
    vex::task::sleep(10);
  }
  bLeftDrive.stop();
  fLeftDrive.stop();

  printf("Pos: BL %f | FL %f | BR %f | FR %f\nFacing: %f\n", bLeftDrive.position(degrees), fLeftDrive.position(degrees), bRightDrive.position(degrees), fRightDrive.position(degrees), accella.rotation());
}

//TurnOnlyRight
void Robot::turnOnlyRight(double degreees, double degreesPerSecond)
{
  bRightDrive.spin(forward, degreesPerSecond, dps);
  fRightDrive.spin(forward, degreesPerSecond, dps);

  while(accella.rotation() > degreees)
  {
    vex::task::sleep(10);
  }
  bRightDrive.stop();
  fRightDrive.stop();

  printf("Pos: BL %f | FL %f | BR %f | FR %f\nFacing: %f\n", bLeftDrive.position(degrees), fLeftDrive.position(degrees), bRightDrive.position(degrees), fRightDrive.position(degrees), accella.rotation());
}

//TurnOnlyLeftBack
void Robot::turnOnlyLeftBack(double degreees, double degreesPerSecond)
{
  bLeftDrive.spin(forward, -degreesPerSecond, dps);
  fLeftDrive.spin(forward, -degreesPerSecond, dps);

  while(accella.rotation() > degreees)
  {
    vex::task::sleep(10);
  }
  bLeftDrive.stop();
  fLeftDrive.stop();

  printf("Pos: BL %f | FL %f | BR %f | FR %f\nFacing: %f\n", bLeftDrive.position(degrees), fLeftDrive.position(degrees), bRightDrive.position(degrees), fRightDrive.position(degrees), accella.rotation());
}

//TurnOnlyRightBack
void Robot::turnOnlyRightBack(double degreees, double degreesPerSecond)
{
  bRightDrive.spin(forward, -degreesPerSecond, dps);
  fRightDrive.spin(forward, -degreesPerSecond, dps);

  while(accella.rotation() < degreees)
  {
    vex::task::sleep(10);
  }
  bRightDrive.stop();
  fRightDrive.stop();

  printf("Pos: BL %f | FL %f | BR %f | FR %f\nFacing: %f\n", bLeftDrive.position(degrees), fLeftDrive.position(degrees), bRightDrive.position(degrees), fRightDrive.position(degrees), accella.rotation());
}
/*                                                                                                         *|
|*v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v*|
\*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*\
|*^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^*|
|*                                                                                                         */
//turnDistance methods
//useful for turning only one side, turning with speed discrepancies, etc. I highly recommend using a turnDegrees
//method soon afterward to ensure that rotational positioning is maintained. A distance sensor could be useful to do 
//some odometry here.

//The left motors drive ticksL at speedL while the right motors drive ticksR at speedR.
void Robot::turnDistance(double ticksL, double speedL, double ticksR, double speedR)
{
  bLeftDrive.spinFor(forward, ticksL, degrees, speedL, dps, false);
  fLeftDrive.spinFor(forward, ticksL, degrees, speedL, dps, false);
  bRightDrive.spinFor(forward, ticksR, degrees, speedR, dps, false);
  fRightDrive.spinFor(forward, ticksR, degrees, speedR, dps, true); 

  printf("Pos: BL %f | FL %f | BR %f | FR %f\nFacing: %f\n", bLeftDrive.position(degrees), fLeftDrive.position(degrees), bRightDrive.position(degrees), fRightDrive.position(degrees), accella.rotation());
}

void Robot::turnDistance(double ticksL, double speedL, double ticksR, double speedR, bool waitForComplete)
{
  bLeftDrive.spinFor(forward, ticksL, degrees, speedL, dps, false);
  fLeftDrive.spinFor(forward, ticksL, degrees, speedL, dps, false);
  bRightDrive.spinFor(forward, ticksR, degrees, speedR, dps, false);
  fRightDrive.spinFor(forward, ticksR, degrees, speedR, dps, waitForComplete);

  //in the event that the left wheels have to go further or faster than the right AND waitForComplete is true, 
  //wait for them.
  if((!bLeftDrive.isDone() && !fLeftDrive.isDone()) && waitForComplete)
  {
    while(!bLeftDrive.isDone() && !fLeftDrive.isDone())
    {
      vex::task::sleep(20);
    }
  }

  printf("Pos: BL %f | FL %f | BR %f | FR %f\nFacing: %f\n", bLeftDrive.position(degrees), fLeftDrive.position(degrees), bRightDrive.position(degrees), fRightDrive.position(degrees), accella.rotation());
}

void Robot::turnDistance(double ticksL, double speedL, double ticksR, double speedR, bool waitForComplete, bool doCoast)
{
  if(doCoast)
  {
    bLeftDrive.setStopping(coast);
    fLeftDrive.setStopping(coast);
    bRightDrive.setStopping(coast);
    fRightDrive.setStopping(coast);
  }

  bLeftDrive.spinFor(forward, ticksL, degrees, speedL, dps, false);
  fLeftDrive.spinFor(forward, ticksL, degrees, speedL, dps, false);
  bRightDrive.spinFor(forward, ticksR, degrees, speedR, dps, false);
  fRightDrive.spinFor(forward, ticksR, degrees, speedR, dps, waitForComplete);

  //in the event that the left wheels have to go further or faster than the right AND waitForComplete is true, 
  //wait for them.
  if((!bLeftDrive.isDone() || !fLeftDrive.isDone()) && waitForComplete)
  {
    while(!bLeftDrive.isDone() || !fLeftDrive.isDone())
    {
      vex::task::sleep(20);
    }
  }

  //Return Stopping to the default brakeType.
  bLeftDrive.setStopping(brake);
  fLeftDrive.setStopping(brake);
  bRightDrive.setStopping(brake);
  fRightDrive.setStopping(brake);

  printf("Pos: BL %f | FL %f | BR %f | FR %f\nFacing: %f\n", bLeftDrive.position(degrees), fLeftDrive.position(degrees), bRightDrive.position(degrees), fRightDrive.position(degrees), accella.rotation());
}

/*                                                                                                         *|
|*v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v*|
\*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*\
|*^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^*|
|*                                                                                                         */
//Score ball
void Robot::scoreBall(double objectRange, double timeLimit)
{
  bool ballFlag = false;
  conveyor.spin(forward);
  trashHandler.spin(forward);
  double timeStamp = Brain.Timer.value();
  printf("Time: %f\n", timeStamp);
  while(!ballFlag || (dist.objectDistance(inches) < objectRange))
  {
    vex::task::sleep(10);
    if(dist.objectDistance(inches) < objectRange)
    {
      ballFlag = true;
    }
    if((Brain.Timer.value()-timeStamp) > timeLimit)
    {
      break;
    }
  }
  ballFlag = false;
  vex::task::sleep(200);
  printf("Distance: %f\nTime: %f\n", dist.objectDistance(inches), Brain.Timer.value());
  conveyor.stop();
  trashHandler.stop();
}
/*                                                                                                         *|
|*v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v*|
\*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/