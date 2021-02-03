#ifndef FUNCTION_LIBRARY_H
#define FUNCTION_LIBRARY_H

class Robot
{
  public:
    void driveDistance(double ticks, double degreesPerSecond);
    void driveDistance(double ticks, double degreesPerSecond, bool waitForComplete);
    void driveDistance(double ticks, double degreesPerSecond, bool waitForComplete, bool doCoast);
    void turnDegrees(double degreees, double degreesPerSecond);
    void turnDegrees(double degreees, double degreesPerSecond, bool doCoast);
    void turnLeft(double degreees, double degreesPerSecond);
    void turnRight(double degreees, double degreesPerSecond);
    void turnDistance(double ticksL, double speedL, double ticksR, double speedR);
    void turnDistance(double ticksL, double speedL, double ticksR, double speedR, bool waitForComplete);
    void turnDistance(double ticksL, double speedL, double ticksR, double speedR, bool waitForComplete, bool doCoast);
};

#endif