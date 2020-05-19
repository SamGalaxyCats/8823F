#include "library.h"
#include "vex.h" //that file contains all the vex-specific stuff that doesn't come with C++ (like motors).

void motion::forward(double distanse)
{
  Drivetrain.driveFor(distanse, inches);
}