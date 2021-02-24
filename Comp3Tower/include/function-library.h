#ifndef FUNCTION_LIBRARY_H
#define FUNCTION_LIBRARY_H

class BackgroundTask
{
  public:
    void heatCheck();
    bool isTrash(bool redTrash);
};

class ConveyorSystem
{
  public:
    bool hasTrash(bool redTrash);
    void takeUp(double systemSpeed);
    void spitOut(double systemSpeed);
    void takeDown(double systemSpeed);
    void autoSort(bool redTrash, double objectRange, double redTreshhold, double systemSpeed);
    void stopConveyor();
};

class Robot
{
  public:
    void driveDistance(double ticks, double degreesPerSecond);
    void driveDistance(double ticks, double degreesPerSecond, bool waitForComplete, bool doCoast);
    void driveDistance(double ticks, double degreesPerSecond, double timeLimit);
    void turnDegrees(double degreees, double degreesPerSecond);
    void turnDegrees(double degreees, double degreesPerSecond, bool doCoast);
    void turnLeft(double degreees, double degreesPerSecond);
    void turnRight(double degreees, double degreesPerSecond);
    void turnOnlyLeft(double degreees, double degreesPerSecond);
    void turnOnlyRight(double degreees, double degreesPerSecond);
    void turnOnlyLeftBack(double degreees, double degreesPerSecond);
    void turnOnlyRightBack(double degreees, double degreesPerSecond);
    void turnDistance(double ticksL, double speedL, double ticksR, double speedR);
    void turnDistance(double ticksL, double speedL, double ticksR, double speedR, bool waitForComplete);
    void turnDistance(double ticksL, double speedL, double ticksR, double speedR, bool waitForComplete, bool doCoast);
    void scoreBall(double objectRange, double timeLimit);
};

#endif