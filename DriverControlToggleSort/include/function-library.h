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

#endif