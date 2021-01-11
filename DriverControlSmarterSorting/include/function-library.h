#ifndef FUNCTION_LIBRARY_H
#define FUNCTION_LIBRARY_H

class BackgroundTask
{
  public:
    void heatCheck();
    bool isTrash(bool redTrash);
};

class Ball
{
  public:
    bool isRed;
    bool inQueue;

    Ball()
    {
      isRed = false;
      inQueue = false;
    }
};

class ConveyorSystem
{
  public:
    void takeUp(double systemSpeed);
    void spitOut(double systemSpeed);
    void takeDown(double systemSpeed);
    void autoSort(double systemSpeed, bool redTrash);
    void stopConveyor();
    void setIntakeBall();
    void handleExit();
    void handleReentry();
    void handleEntry();
    void handleUnqueue();
    void update(bool redTrash, double redTreshhold, double objectRange);
    bool hadTrash;
    bool hadRed;
    bool intakesReversed;
    bool outTakeFlag;
    bool takingDown;
    bool exitingObjectInRange;
    bool reenteringObjectInRange;
    bool clickerPressed;
    int ballsInQueue;
    Ball ballToProcess;
    Ball nextBall;
    Ball afterNextBall;
    Ball intakeBall;
    Ball lastBall;

    ConveyorSystem()
    {
      hadTrash = false;
      hadRed = false;
      intakesReversed = false;
      outTakeFlag = false;
      takingDown = false;
      exitingObjectInRange = false;
      reenteringObjectInRange = false;
      clickerPressed = false;
      Ball ballToProcess;
      Ball nextBall;
      Ball afterNextBall;
      Ball intakeBall;
      Ball lastBall;
      ballsInQueue = 0;
    }
};

#endif