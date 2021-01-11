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
    bool isLocked;
    void lockColor(bool wasRed);
    void unlockColor();

    Ball()
    {
      isRed = false;
      isLocked = false;
    }
};

class ConveyorSystem
{
  public:
    bool hasTrash(bool redTrash, double objectRange, double redTreshhold, bool currentState);
    void takeUp(double systemSpeed);
    void spitOut(double systemSpeed);
    void takeDown(double systemSpeed);
    void autoSort(bool foundTrash, double systemSpeed);
    void stopConveyor();
    void lockIntakeBall();
    void lockConveyorBall();
    void update(bool redTrash, double redTreshhold, double objectRange);
    bool hadTrash;
    bool hadRed;
    Ball conveyorBall;
    Ball intakeBall;

    ConveyorSystem()
    {
      hadTrash = false;
      hadRed = false;
      Ball conveyorBall;
      Ball intakeBall;
    }
};

#endif