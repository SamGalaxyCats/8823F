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
    bool hasTrash(bool redTrash, double objectRange, double redTreshhold, bool currentState);
    void takeUp(double systemSpeed);
    void spitOut(double systemSpeed);
    void takeDown(double systemSpeed);
    void autoSort(bool foundTrash, double systemSpeed);
    void stopConveyor();
    bool hadTrash;

    ConveyorSystem()
    {
      hadTrash = false;
    }
};

#endif